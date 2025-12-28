const { ethers } = require('ethers');
const fs = require('fs');
const path = require('path');

// Path to .env file
const ENV_PATH = path.join(__dirname, '../../.env');

function generateWallet() {
    console.log('🔑 Generating new wallet for blockchain deployment...');
    
    try {
        // Update .env file
        let envContent = '';
        if (fs.existsSync(ENV_PATH)) {
            envContent = fs.readFileSync(ENV_PATH, 'utf8');
        }

        // Check if BLOCKCHAIN_PRIVATE_KEY already exists and has a real value
        const privateKeyMatch = envContent.match(/BLOCKCHAIN_PRIVATE_KEY=(.*)/);
        if (privateKeyMatch && privateKeyMatch[1] && privateKeyMatch[1].trim() !== '' && privateKeyMatch[1].trim() !== 'your_private_key_here') {
            console.log('ℹ️  BLOCKCHAIN_PRIVATE_KEY already exists in .env. Skipping generation.');
            return;
        }

        // Create a random wallet
        const wallet = ethers.Wallet.createRandom();
        const privateKey = wallet.privateKey; // Includes '0x' prefix
        const address = wallet.address;

        console.log('----------------------------------------');
        console.log('✅ New Wallet Generated!');
        console.log(`Address: ${address}`);
        console.log(`Private Key: ${privateKey}`);
        console.log('----------------------------------------');
        console.log('⚠️  IMPORTANT: You need to fund this wallet with AVAX to deploy contracts!');
        console.log(`👉 Get free testnet AVAX here: https://core.app/tools/testnet-faucet/`);
        console.log(`👉 Address to fund: ${address}`);
        console.log('----------------------------------------');

        if (envContent.includes('BLOCKCHAIN_PRIVATE_KEY=')) {
            // Replace existing key (empty or placeholder)
            envContent = envContent.replace(/BLOCKCHAIN_PRIVATE_KEY=.*/g, `BLOCKCHAIN_PRIVATE_KEY=${privateKey}`);
        } else {
            // Append new key
            envContent += `\n# Blockchain\nBLOCKCHAIN_PRIVATE_KEY=${privateKey}\n`;
        }

        // Ensure RPC URL exists
        if (!envContent.includes('BLOCKCHAIN_RPC_URL=')) {
            envContent += `BLOCKCHAIN_RPC_URL=https://api.avax-test.network/ext/bc/C/rpc\n`;
        }

        fs.writeFileSync(ENV_PATH, envContent);
        console.log('✅ .env file updated with new private key.');

    } catch (error) {
        console.error('❌ Failed to generate wallet:', error);
        process.exit(1);
    }
}

generateWallet();
