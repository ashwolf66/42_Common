const path = require('path');
require('dotenv').config({ path: path.join(__dirname, '../.env') });
const { ethers } = require('ethers');
const artifact = require('../artifacts/contracts/TournamentScoreStorage.sol/TournamentScoreStorage.json');

async function main() {
  const rpc = process.env.FUJI_RPC_URL || 'https://api.avax-test.network/ext/bc/C/rpc';
  const address = process.env.CONTRACT_ADDRESS;
  const tournamentId = process.env.TOURNAMENT_ID;

  if (!address) throw new Error('CONTRACT_ADDRESS env is required');
  if (!tournamentId) throw new Error('TOURNAMENT_ID env is required');

  const provider = new ethers.JsonRpcProvider(rpc);
  const contract = new ethers.Contract(address, artifact.abi, provider);

  const scores = await contract.getScores(tournamentId);
  console.log(`Scores for tournament ${tournamentId} (count=${scores.length}):`);
  scores.forEach((s, idx) => {
    console.log(`#${idx} gameId=${s.gameId} player=${s.player} score=${s.score} recordedAt=${new Date(Number(s.recordedAt) * 1000).toISOString()} metadataHash=${s.metadataHash}`);
  });
}

main().catch((err) => {
  console.error(err);
  process.exitCode = 1;
});
