const hre = require('hardhat');

async function main() {
  const [deployer] = await hre.ethers.getSigners();
  const writer = process.env.SCORE_WRITER || deployer.address;

  console.log('Deploying with account:', deployer.address);
  console.log('Using writer address:', writer);

  const Factory = await hre.ethers.getContractFactory('TournamentScoreStorage');
  const contract = await Factory.deploy(writer);
  await contract.waitForDeployment();

  console.log('TournamentScoreStorage deployed to:', await contract.getAddress());
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
