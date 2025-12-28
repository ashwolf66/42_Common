const { expect } = require('chai');
const { ethers } = require('hardhat');

describe('TournamentScoreStorage', function () {
  async function deployFixture() {
    const [admin, writer, other, player] = await ethers.getSigners();
    const Factory = await ethers.getContractFactory('TournamentScoreStorage');
    const contract = await Factory.deploy(writer.address);
    await contract.waitForDeployment();
    return { contract, admin, writer, other, player };
  }

  it('only writers can record scores', async function () {
    const { contract, other, player } = await deployFixture();
    await expect(
      contract.connect(other).recordScore(1, 1, player.address, 7, ethers.ZeroHash)
    ).to.be.revertedWithCustomError(contract, 'AccessControlUnauthorizedAccount');
  });

  it('stores scores and tracks best per player', async function () {
    const { contract, writer, player } = await deployFixture();

    const tx1 = await contract
      .connect(writer)
      .recordScore(10, 1001, player.address, 7, ethers.ZeroHash);
    await expect(tx1).to.emit(contract, 'ScoreRecorded');

    await contract
      .connect(writer)
      .recordScore(10, 1002, player.address, 9, ethers.ZeroHash);

    const scores = await contract.getScores(10);
    expect(scores.length).to.equal(2);
    expect(scores[1].score).to.equal(9);

    const [found, best] = await contract.getBestScore(10, player.address);
    expect(found).to.equal(true);
    expect(best.score).to.equal(9);
  });
});
