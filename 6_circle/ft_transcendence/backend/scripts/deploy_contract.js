const { ethers } = require('ethers');
const fs = require('fs');
const path = require('path');
require('dotenv').config({ path: path.join(__dirname, '../../.env') });

// Contract ABI and Bytecode (Compiled artifact)
// Note: In a real setup, we would import this from the hardhat artifacts.
// For simplicity here, we assume the user has run 'npx hardhat compile' in the blockchain folder
// OR we can use a pre-compiled minimal version. 
// Let's try to read from the blockchain folder artifacts if they exist.

const ARTIFACT_PATH = path.join(__dirname, '../../blockchain/artifacts/contracts/TournamentScoreStorage.sol/TournamentScoreStorage.json');

async function main() {
    console.log('🚀 Starting Smart Contract Deployment...');

    const privateKey = process.env.BLOCKCHAIN_PRIVATE_KEY;
    if (!privateKey) {
        console.error('❌ Error: BLOCKCHAIN_PRIVATE_KEY is missing in .env file.');
        console.log('Please add your private key to the .env file first.');
        process.exit(1);
    }

    const rpcUrl = process.env.BLOCKCHAIN_RPC_URL || 'https://api.avax-test.network/ext/bc/C/rpc';
    const provider = new ethers.JsonRpcProvider(rpcUrl);
    const wallet = new ethers.Wallet(privateKey, provider);

    console.log(`Using Wallet: ${wallet.address}`);
    
    try {
        const balance = await provider.getBalance(wallet.address);
        console.log(`Wallet Balance: ${ethers.formatEther(balance)} AVAX`);
        
        if (balance === 0n) {
            console.error('❌ Error: Wallet has 0 AVAX. You need gas to deploy.');
            console.log('Please get free testnet AVAX from: https://core.app/tools/testnet-faucet/');
            process.exit(1);
        }
    } catch (err) {
        console.error('❌ Error connecting to network:', err.message);
        process.exit(1);
    }

    if (!fs.existsSync(ARTIFACT_PATH)) {
        console.error(`❌ Error: Contract artifacts not found at ${ARTIFACT_PATH}`);
        console.log('Please run "npx hardhat compile" in the blockchain directory first.');
        process.exit(1);
    }

    const artifact = JSON.parse(fs.readFileSync(ARTIFACT_PATH, 'utf8'));
    const factory = new ethers.ContractFactory(artifact.abi, artifact.bytecode, wallet);

    console.log('Deploying contract... (this may take a few seconds)');
    try {
        // Deploy with the deployer as the initial writer
        const contract = await factory.deploy(wallet.address);
        await contract.waitForDeployment();
        
        const contractAddress = await contract.getAddress();
        console.log('\n✅ Contract Deployed Successfully!');
        console.log('----------------------------------------');
        console.log(`Contract Address: ${contractAddress}`);
        console.log('----------------------------------------');
        console.log('\n📝 Please update your .env file with this address:');
        console.log(`BLOCKCHAIN_CONTRACT_ADDRESS=${contractAddress}`);
        
        // Optional: Try to update .env automatically
        // updateEnvFile(contractAddress);

    } catch (error) {
        console.error('❌ Deployment failed:', error);
    }
}

main();
