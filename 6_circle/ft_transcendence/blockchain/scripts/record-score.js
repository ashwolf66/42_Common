const hre = require('hardhat');

function parseBytes32(value) {
  if (!value) return hre.ethers.ZeroHash;
  if (value.length === 66 && value.startsWith('0x')) return value;
  throw new Error('METADATA_HASH must be a 32-byte hex string (0x-prefixed)');
}

async function main() {
  const contractAddress = process.env.SCORE_CONTRACT;
  const tournamentId = Number(process.env.TOURNAMENT_ID || 0);
  const gameId = Number(process.env.GAME_ID || 0);
  const player = process.env.PLAYER_ADDRESS;
  const score = Number(process.env.SCORE || 0);
  const metadataHash = parseBytes32(process.env.METADATA_HASH);

  if (!contractAddress) throw new Error('Set SCORE_CONTRACT to the deployed contract address');
  if (!player) throw new Error('Set PLAYER_ADDRESS to the target wallet');
  if (!tournamentId) throw new Error('Set TOURNAMENT_ID to a non-zero value');
  if (!score) throw new Error('Set SCORE to a non-zero value');

  const contract = await hre.ethers.getContractAt('TournamentScoreStorage', contractAddress);
  const tx = await contract.recordScore(tournamentId, gameId, player, score, metadataHash);
  const receipt = await tx.wait();

  console.log('Score stored. Tx hash:', receipt.hash);
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
