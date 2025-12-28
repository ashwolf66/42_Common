const { ethers } = require('ethers');
const fs = require('fs');
const { execSync } = require('child_process');

// Path to the compiled contract artifact (mounted via docker-compose)
const ARTIFACT_PATH = '/app/blockchain/artifacts/contracts/TournamentScoreStorage.sol/TournamentScoreStorage.json';

async function initBlockchain(db, { autoDeploy = false } = {}) {
    console.log('[Blockchain] Initializing...');

    const privateKey = process.env.BLOCKCHAIN_PRIVATE_KEY;
    const configuredWalletAddress = process.env.BLOCKCHAIN_WALLET_ADDRESS;

    if (configuredWalletAddress) {
        db.prepare("INSERT OR REPLACE INTO blockchain_config (key, value) VALUES ('wallet_address', ?)").run(configuredWalletAddress);
        console.log(`[Blockchain] Wallet configured from env: ${configuredWalletAddress}`);
    } else {
        console.warn('[Blockchain] BLOCKCHAIN_WALLET_ADDRESS not set. Set it in .env to proceed.');
    }

    // 1. Check if contract address exists in DB
    let contractAddress = null;
    const config = db.prepare("SELECT value FROM blockchain_config WHERE key = 'tournament_contract_address'").get();
    
    if (config && config.value) {
        console.log(`[Blockchain] Found existing contract address in DB: ${config.value}`);
        contractAddress = config.value;
    }

    if (contractAddress) {
        process.env.BLOCKCHAIN_CONTRACT_ADDRESS = contractAddress;
        return contractAddress;
    }

    if (!autoDeploy) {
        console.warn('[Blockchain] No contract address found and autoDeploy=false. Skipping deployment.');
        return null;
    }

    console.log('[Blockchain] No contract address found. Attempting to deploy...');

    // 2. Check prerequisites for deployment
    if (!privateKey) {
        console.error('[Blockchain] CRITICAL: BLOCKCHAIN_PRIVATE_KEY is not set in environment variables.');
        console.error('[Blockchain] Please check your .env file and ensure docker-compose.yml passes it to the backend container.');
        console.warn('[Blockchain] Blockchain features will be disabled.');
        return null;
    }

    if (!fs.existsSync(ARTIFACT_PATH)) {
        console.error(`[Blockchain] CRITICAL: Artifact not found at ${ARTIFACT_PATH}.`);
        console.error('[Blockchain] Please run "make blockchain" or "npx hardhat compile" in the blockchain directory.');
        return null;
    }

    // 3. Deploy Contract
    try {
        const rpcUrl = process.env.BLOCKCHAIN_RPC_URL || 'https://api.avax-test.network/ext/bc/C/rpc';
        const provider = new ethers.JsonRpcProvider(rpcUrl);
        const wallet = new ethers.Wallet(privateKey, provider);

        if (configuredWalletAddress && configuredWalletAddress.toLowerCase() !== wallet.address.toLowerCase()) {
            console.warn('[Blockchain] WARNING: BLOCKCHAIN_WALLET_ADDRESS does not match the private key signer. Deploy will use the signer from BLOCKCHAIN_PRIVATE_KEY.');
        }

        const writerAddress = configuredWalletAddress || wallet.address;
        console.log(`[Blockchain] Deploying with account: ${wallet.address}, writer address: ${writerAddress}`);
        
        const artifact = JSON.parse(fs.readFileSync(ARTIFACT_PATH, 'utf8'));
        const factory = new ethers.ContractFactory(artifact.abi, artifact.bytecode, wallet);

        const contract = await factory.deploy(writerAddress);
        await contract.waitForDeployment();
        
        const contractAddress = await contract.getAddress();
        console.log(`[Blockchain] Contract deployed successfully at: ${contractAddress}`);

        // 4. Save to DB
        db.prepare("INSERT OR REPLACE INTO blockchain_config (key, value) VALUES ('tournament_contract_address', ?)").run(contractAddress);
        
        process.env.BLOCKCHAIN_CONTRACT_ADDRESS = contractAddress;

        // Optional: auto-verify on Snowtrace if API key is provided
        const snowtraceKey = process.env.SNOWTRACE_API_KEY || process.env.SNOWTRACE_TOKEN;
        const fujiRpc = process.env.FUJI_RPC_URL || process.env.BLOCKCHAIN_RPC_URL || rpcUrl;
        if (!snowtraceKey) {
            console.warn('[Blockchain] SNOWTRACE_API_KEY not set. Skipping auto verification.');
            return contractAddress;
        }

        try {
            console.log('[Blockchain] Verifying contract on Snowtrace...');
            // npx hardhat verify --network fuji <address> <writerAddress>
            // Ensure envs for hardhat are present
            const cmd = `cd /app/blockchain && SNOWTRACE_API_KEY=${snowtraceKey} FUJI_RPC_URL=${fujiRpc} PRIVATE_KEY=${privateKey} SCORE_WRITER=${writerAddress} npx hardhat verify --network fuji ${contractAddress} ${writerAddress}`;
            execSync(cmd, { stdio: 'inherit', timeout: 180000 });
            console.log('[Blockchain] Verification request sent. Check Snowtrace for status.');
        } catch (err) {
            console.warn('[Blockchain] Auto verification failed:', err.message || err);
        }

        return contractAddress;

    } catch (error) {
        console.error('[Blockchain] Deployment failed:', error);
        return null;
    }
}

module.exports = initBlockchain;
