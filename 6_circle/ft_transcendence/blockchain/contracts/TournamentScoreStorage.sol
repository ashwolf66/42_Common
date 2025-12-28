// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

import '@openzeppelin/contracts/access/AccessControl.sol';

/**
 * @title TournamentScoreStorage
 * @dev Stores immutable tournament score records on-chain for auditability.
 */
contract TournamentScoreStorage is AccessControl {
    bytes32 public constant SCORE_WRITER_ROLE = keccak256('SCORE_WRITER_ROLE');

    struct ScoreRecord {
        uint256 tournamentId;
        uint256 gameId;
        address player;
        uint256 score;
        string displayName; // Player's display name
        uint256 recordedAt;
        bytes32 metadataHash; // Optional hash of off-chain payload (e.g., JSON with full game state)
    }

    // Tournament ID => immutable list of score records
    mapping(uint256 => ScoreRecord[]) private tournamentScores;

    // Tracks best score per player: value stores index + 1 (0 means no score yet)
    mapping(uint256 => mapping(address => uint256)) private bestScoreIndexPlusOne;

    event ScoreRecorded(
        uint256 indexed tournamentId,
        uint256 indexed gameId,
        address indexed player,
        uint256 score,
        string displayName,
        bytes32 metadataHash,
        uint256 recordedAt
    );

    constructor(address initialWriter) {
        _grantRole(DEFAULT_ADMIN_ROLE, msg.sender);
        if (initialWriter != address(0)) {
            _grantRole(SCORE_WRITER_ROLE, initialWriter);
        }
    }

    /**
     * @notice Records a score for a tournament game.
     * @dev Only accounts with SCORE_WRITER_ROLE can call this. Records are append-only.
     * @param tournamentId Numeric tournament identifier from the backend.
     * @param gameId Optional game identifier to correlate with off-chain DB (0 if not provided).
     * @param player Player wallet address.
     * @param score Final score achieved by the player.
     * @param metadataHash Optional hash of structured data for integrity (bytes32(0) if unused).
     * @return recordIndex Index of the newly stored record within the tournament list.
     */
    function recordScore(
        uint256 tournamentId,
        uint256 gameId,
        address player,
        uint256 score,
        string memory displayName,
        bytes32 metadataHash
    ) external onlyRole(SCORE_WRITER_ROLE) returns (uint256 recordIndex) {
        require(tournamentId != 0, 'tournamentId required');
        require(player != address(0), 'player required');
        require(score > 0, 'score required');

        ScoreRecord memory record = ScoreRecord({
            tournamentId: tournamentId,
            gameId: gameId,
            player: player,
            score: score,
            displayName: displayName,
            recordedAt: block.timestamp,
            metadataHash: metadataHash
        });

        tournamentScores[tournamentId].push(record);
        recordIndex = tournamentScores[tournamentId].length - 1;

        uint256 existing = bestScoreIndexPlusOne[tournamentId][player];
        if (existing == 0 || score > tournamentScores[tournamentId][existing - 1].score) {
            bestScoreIndexPlusOne[tournamentId][player] = recordIndex + 1;
        }

        emit ScoreRecorded(tournamentId, gameId, player, score, displayName, metadataHash, record.recordedAt);
    }

    /**
     * @notice Returns all score records for a tournament.
     */
    function getScores(uint256 tournamentId) external view returns (ScoreRecord[] memory) {
        return tournamentScores[tournamentId];
    }

    /**
     * @notice Returns how many score records exist for a tournament.
     */
    function getScoreCount(uint256 tournamentId) external view returns (uint256) {
        return tournamentScores[tournamentId].length;
    }

    /**
     * @notice Returns the best score recorded for a player in a tournament.
     * @return found Boolean indicating presence.
     * @return record ScoreRecord for the best score if found.
     */
    function getBestScore(uint256 tournamentId, address player)
        external
        view
        returns (bool found, ScoreRecord memory record)
    {
        uint256 idxPlusOne = bestScoreIndexPlusOne[tournamentId][player];
        if (idxPlusOne == 0) {
            return (false, record);
        }
        record = tournamentScores[tournamentId][idxPlusOne - 1];
        return (true, record);
    }

    /**
     * @notice Grants or revokes writer privileges.
     * @dev Wrapper around AccessControl to simplify backend calls.
     */
    function setScoreWriter(address account, bool enabled) external onlyRole(DEFAULT_ADMIN_ROLE) {
        require(account != address(0), 'zero address');
        if (enabled) {
            grantRole(SCORE_WRITER_ROLE, account);
        } else {
            revokeRole(SCORE_WRITER_ROLE, account);
        }
    }
}
