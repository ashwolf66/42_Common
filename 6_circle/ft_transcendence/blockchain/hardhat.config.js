require('@nomicfoundation/hardhat-toolbox');
require('dotenv').config();

const FUJI_RPC_URL = process.env.FUJI_RPC_URL || 'https://api.avax-test.network/ext/bc/C/rpc';
const PRIVATE_KEY = process.env.PRIVATE_KEY || '';
const REPORT_GAS = process.env.REPORT_GAS === 'true';
const SNOWTRACE_API_KEY = process.env.SNOWTRACE_API_KEY || '';

module.exports = {
  solidity: '0.8.20',
  networks: {
    hardhat: {},
    fuji: {
      url: FUJI_RPC_URL,
      chainId: 43113,
      accounts: PRIVATE_KEY ? [PRIVATE_KEY] : []
    }
  },
  etherscan: {
    apiKey: {
      avalancheFujiTestnet: SNOWTRACE_API_KEY
    },
    customChains: [
      {
        network: 'fuji',
        chainId: 43113,
        urls: {
          apiURL: 'https://api-testnet.snowtrace.io/api',
          browserURL: 'https://testnet.snowtrace.io'
        }
      }
    ]
  },
  gasReporter: {
    enabled: REPORT_GAS,
    currency: 'USD'
  }
};
