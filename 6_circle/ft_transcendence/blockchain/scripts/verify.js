const hre = require('hardhat');
require('dotenv').config({ path: require('path').join(__dirname, '../.env') });

async function main() {
  const address = process.env.CONTRACT_ADDRESS;
  const writer = process.env.SCORE_WRITER;

  if (!address) {
    throw new Error('CONTRACT_ADDRESS env is required for verification');
  }
  if (!writer) {
    throw new Error('SCORE_WRITER env must match the constructor writer used at deployment');
  }

  console.log('Verifying contract', address, 'with writer arg', writer);
  await hre.run('verify:verify', {
    address,
    constructorArguments: [writer],
    contract: 'contracts/TournamentScoreStorage.sol:TournamentScoreStorage'
  });
}

main().catch((err) => {
  console.error(err);
  process.exitCode = 1;
});
