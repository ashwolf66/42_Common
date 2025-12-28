const { ethers } = require('ethers');

class BlockchainService {
    constructor() {
        this.provider = null;
        this.wallet = null;
        this.contract = null;
        this.isConnected = false;

        this.init();
    }

    init() {
        // We will re-initialize when needed or rely on process.env being updated by initBlockchain
        // But initBlockchain runs async, so this constructor might run before env is set.
        // Better to have a method to refresh connection or check env lazily.
        this.connect();
    }

    connect(force = false) {
        if (this.isConnected && !force) {
            return;
        }

        // reset previous connection state when forcing reconnect
        this.provider = null;
        this.wallet = null;
        this.contract = null;
        this.isConnected = false;

        const rpcUrl = process.env.BLOCKCHAIN_RPC_URL || 'https://api.avax-test.network/ext/bc/C/rpc';
        const privateKey = process.env.BLOCKCHAIN_PRIVATE_KEY;
        const contractAddress = process.env.BLOCKCHAIN_CONTRACT_ADDRESS;

        if (!privateKey) {
            console.warn('[BlockchainService] Missing BLOCKCHAIN_PRIVATE_KEY. Cannot connect.');
            return;
        }
        if (!contractAddress) {
            console.warn('[BlockchainService] Missing BLOCKCHAIN_CONTRACT_ADDRESS. Cannot connect.');
            return;
        }

        try {
            this.provider = new ethers.JsonRpcProvider(rpcUrl);
            this.wallet = new ethers.Wallet(privateKey, this.provider);

            // Minimal ABI for recordScore
            const abi = [
                "function recordScore(uint256 tournamentId, uint256 gameId, address player, uint256 score, string displayName, bytes32 metadataHash) external returns (uint256)"
            ];

            this.contract = new ethers.Contract(contractAddress, abi, this.wallet);
            this.isConnected = true;
            console.log('[BlockchainService] Connected with contract:', contractAddress);
            console.log('[BlockchainService] Wallet address:', this.wallet.address);
        } catch (error) {
            console.error('[BlockchainService] Connection failed:', error);
        }
    }

    async recordGameScore(tournamentId, gameId, playerAddress, score, displayName) {
        console.log(`[BlockchainService] Request to record score: T=${tournamentId}, G=${gameId}, P=${playerAddress}, S=${score}, Name=${displayName}`);
        
        if (!this.isConnected) {
            console.log('[BlockchainService] Not connected. Attempting to reconnect...');
            this.connect(); // Try to connect if not connected (e.g. env updated late)
            if (!this.isConnected) {
                console.error('[BlockchainService] Service still not connected. Skipping score recording.');
                return;
            }
        }

        if (!playerAddress || !ethers.isAddress(playerAddress)) {
            console.warn('[BlockchainService] Invalid player address:', playerAddress);
            return;
        }

        try {
            // metadataHash is optional, sending zero bytes
            const metadataHash = ethers.ZeroHash;
            const safeDisplayName = displayName || "Unknown";

            console.log('[BlockchainService] Sending transaction...');
            // Send transaction
            const tx = await this.contract.recordScore(
                tournamentId || 0,
                gameId,
                playerAddress,
                score,
                safeDisplayName,
                metadataHash
            );

            console.log(`[BlockchainService] Transaction sent: ${tx.hash}`);
            
            // Wait for confirmation to prevent nonce issues with sequential transactions
            console.log('[BlockchainService] Waiting for confirmation...');
            await tx.wait();
            console.log(`[BlockchainService] Transaction confirmed: ${tx.hash}`);
            
            return tx.hash;
        } catch (error) {
            console.error('[BlockchainService] Failed to record score:', error);
            if (error.reason) console.error('[BlockchainService] Revert reason:', error.reason);
            if (error.code) console.error('[BlockchainService] Error code:', error.code);
        }
    }
}

module.exports = new BlockchainService();
