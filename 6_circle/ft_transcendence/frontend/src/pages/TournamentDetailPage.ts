import { escapeHtml } from '../utils/sanitize';
import ApiService from '../services/ApiService';
import { getErrorMessage } from '../utils/errorHandler';

export class TournamentDetailPage {
    tournamentId: string;
    tournament: any;
    matches: any[];
    renderRetryCount: number;
    refreshInterval?: number;

    constructor(tournamentId: string) {
        this.tournamentId = tournamentId;
        this.tournament = null;
        this.matches = [];
        this.renderRetryCount = 0;
    }

    cleanup() {
        if (this.refreshInterval) {
            clearInterval(this.refreshInterval);
            this.refreshInterval = undefined;
        }
    }

    async render() {
        return `
            <div class="container mx-auto px-4 py-8">
                <div id="tournamentContent">
                    <div class="spinner"></div>
                </div>
            </div>

            <!-- Join Tournament Modal -->
            <div id="joinTournamentModal" class="modal-overlay hidden">
                <div class="modal-content">
                    <h2 class="text-2xl font-bold mb-4">Join Tournament</h2>
                    <p class="text-gray-400 mb-4">You can use a custom display name for this tournament (optional)</p>
                    <form id="joinTournamentForm" class="space-y-4">
                        <div>
                            <label class="block mb-2">Custom Display Name (Optional)</label>
                            <input 
                                type="text" 
                                id="tournamentAlias" 
                                class="input w-full" 
                                placeholder="Leave empty to use your username"
                                maxlength="50"
                            />
                            <p class="text-sm text-gray-400 mt-1">Max 50 characters</p>
                        </div>
                        <div class="flex gap-2">
                            <button type="submit" class="btn btn-primary flex-1">Join</button>
                            <button type="button" id="cancelJoinBtn" class="btn btn-secondary flex-1">Cancel</button>
                        </div>
                    </form>
                </div>
            </div>
        `;
    }

    async onMount() {
        // Wait for DOM to be fully ready
        await new Promise(resolve => setTimeout(resolve, 0));
        
        await this.loadTournament();
        this.attachEventListeners();

        // Auto-refresh if tournament is active
        if (this.tournament && this.tournament.status === 'active') {
            this.refreshInterval = setInterval(() => {
                this.loadTournament().then(() => this.attachEventListeners());
            }, 5000);
        }
    }

    attachEventListeners() {
        // Join tournament button - show modal
        const joinBtn = document.getElementById('joinTournamentBtn');
        if (joinBtn) {
            joinBtn.addEventListener('click', () => this.showJoinModal());
        }

        // Start tournament button
        const startBtn = document.getElementById('startTournamentBtn');
        if (startBtn) {
            startBtn.addEventListener('click', () => this.startTournament());
        }

        // Join tournament form submission
        const joinForm = document.getElementById('joinTournamentForm');
        if (joinForm) {
            joinForm.addEventListener('submit', (e) => {
                e.preventDefault();
                this.submitJoinTournament();
            });
        }

        // Cancel join button
        const cancelJoinBtn = document.getElementById('cancelJoinBtn');
        if (cancelJoinBtn) {
            cancelJoinBtn.addEventListener('click', () => this.hideJoinModal());
        }
    }

    showJoinModal() {
        const modal = document.getElementById('joinTournamentModal');
        if (modal) {
            modal.classList.remove('hidden');
        }
    }

    hideJoinModal() {
        const modal = document.getElementById('joinTournamentModal');
        if (modal) {
            modal.classList.add('hidden');
            // Clear the input
            const aliasInput = document.getElementById('tournamentAlias') as HTMLInputElement;
            if (aliasInput) {
                aliasInput.value = '';
            }
        }
    }

    onUnmount() {
        if (this.refreshInterval) {
            clearInterval(this.refreshInterval);
        }
    }

    getCurrentUserId() {
        const token = localStorage.getItem('auth_token');
        if (!token) return null;
        
        try {
            const payload = JSON.parse(atob(token.split('.')[1]));
            return payload.id;
        } catch {
            return null;
        }
    }

    async loadTournament() {
        try {
            const data = await ApiService.get(`/tournaments/${this.tournamentId}`);

            this.tournament = data.tournament;
            this.matches = data.matches || [];

            this.renderTournamentDetails();
        } catch (error: any) {
            console.error('Failed to load tournament:', error);
            const contentEl = document.getElementById('tournamentContent');
            if (contentEl) {
                contentEl.innerHTML = `
                    <div class="card bg-red-900 border border-red-700">
                        <h2 class="text-2xl font-bold mb-4">Error</h2>
                        <p>${escapeHtml(error.message || 'An unknown error occurred')}</p>
                        <a href="/tournament" data-link class="btn btn-primary mt-4">Back to Tournaments</a>
                    </div>
                `;
            }
        }
    }

    renderTournamentDetails() {
        const t = this.tournament;
        const canJoin = t.status === 'pending' && t.participants.length < t.max_players;
        const canStart = t.status === 'pending' && t.participants.length >= t.max_players && t.is_creator;
        const currentUserId = this.getCurrentUserId();
        const hasJoined = t.participants.some((p: any) => p.user_id === currentUserId);

        const contentEl = document.getElementById('tournamentContent');
        if (!contentEl) {
            if (this.renderRetryCount < 10) {
                this.renderRetryCount++;
                console.log(`tournamentContent element not found, retrying (${this.renderRetryCount}/10)...`);
                setTimeout(() => this.renderTournamentDetails(), 50);
            } else {
                console.error('tournamentContent element not found after 10 retries');
            }
            return;
        }

        // Reset retry count on successful render
        this.renderRetryCount = 0;

        contentEl.innerHTML = `
            <div class="mb-6">
                <a href="/tournament" data-link class="text-primary hover:underline">&larr; Back to Tournaments</a>
            </div>

            <div class="card mb-6">
                <div class="flex justify-between items-start mb-4">
                    <div>
                        <h1 class="text-4xl font-bold mb-2">${escapeHtml(t.name)}</h1>
                        <p class="text-gray-400">
                            ${t.participants.length}/${t.max_players} players | 
                            <span class="badge badge-${t.status === 'pending' ? 'warning' : t.status === 'active' ? 'info' : 'success'}">
                                ${t.status}
                            </span>
                            ${t.status === 'active' ? ` | Round ${t.current_round || 1}` : ''}
                        </p>
                    </div>
                    <div class="space-x-2">
                        ${canJoin && !hasJoined ? `<button id="joinTournamentBtn" class="btn btn-primary">Join Tournament</button>` : ''}
                        ${canStart ? `<button id="startTournamentBtn" class="btn btn-success">Start Tournament</button>` : ''}
                    </div>
                </div>

                <div class="border-t border-gray-700 pt-4">
                    <h2 class="text-2xl font-bold mb-4">Participants</h2>
                    ${t.participants.length > 0 ? `
                        <div class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-4">
                            ${t.participants.map((p: any) => {
                                const displayName = p.alias || p.username || 'Guest';
                                const hasAlias = p.alias && p.username;
                                return `
                                <div class="bg-gray-800 rounded-lg p-3 flex items-center space-x-3">
                                    <div class="w-10 h-10 rounded-full bg-primary flex items-center justify-center font-bold text-lg">
                                        ${escapeHtml(displayName.charAt(0).toUpperCase())}
                                    </div>
                                    <div>
                                        <div class="font-bold">${escapeHtml(displayName)}</div>
                                        ${hasAlias ? `<div class="text-xs text-gray-500">@${escapeHtml(p.username)}</div>` : ''}
                                        <div class="text-sm text-gray-400">
                                            ${p.is_creator ? 'Creator' : `Seed ${p.seed}`}
                                            ${p.eliminated ? ' • Eliminated' : ''}
                                        </div>
                                    </div>
                                </div>
                            `}).join('')}
                        </div>
                    ` : `
                        <p class="text-gray-400 text-center py-4">No participants yet</p>
                    `}
                </div>
            </div>

            ${this.matches.length > 0 ? `
                <div class="card">
                    <h2 class="text-2xl font-bold mb-4">Tournament Bracket</h2>
                    ${this.renderBracket()}
                </div>
            ` : t.status === 'active' ? `
                <div class="card">
                    <h2 class="text-2xl font-bold mb-4">Tournament Bracket</h2>
                    <p class="text-gray-400 text-center py-4">Matches are being created...</p>
                </div>
            ` : ''}
        `;
    }

    renderBracket() {
        if (this.matches.length === 0) {
            return '<p class="text-gray-400 text-center py-4">No matches yet</p>';
        }

        const currentUserId = this.getCurrentUserId();
        
        // Group matches by round
        const matchesByRound = this.groupMatchesByRound();

        return `
            <div class="space-y-6">
                ${Object.keys(matchesByRound).sort().map(roundNum => {
                    const roundMatches = matchesByRound[parseInt(roundNum)];
                    const totalRounds = this.tournament.total_rounds || Math.ceil(Math.log2(this.tournament.max_players));
                    const roundName = parseInt(roundNum) === totalRounds 
                        ? 'Final' 
                        : parseInt(roundNum) === totalRounds - 1 
                            ? 'Semi-Finals' 
                            : `Round ${roundNum}`;
                    
                    const allFinished = roundMatches.every((m: any) => m.finished_at !== null);
                    const someFinished = roundMatches.some((m: any) => m.finished_at !== null);
                    
                    return `
                        <div class="border-l-4 ${parseInt(roundNum) === this.tournament.current_round ? 'border-blue-500' : allFinished ? 'border-green-500' : 'border-gray-700'} pl-4">
                            <h3 class="text-xl font-bold mb-3 flex items-center gap-2">
                                ${roundName}
                                ${parseInt(roundNum) === this.tournament.current_round ? `
                                    <span class="badge badge-info text-xs">Current</span>
                                ` : allFinished ? `
                                    <span class="badge badge-success text-xs">Complete</span>
                                ` : someFinished ? `
                                    <span class="badge badge-warning text-xs">In Progress</span>
                                ` : ''}
                            </h3>
                            <div class="space-y-3">
                                ${roundMatches.map((match: any, idx: number) => {
                                    const isMyMatch = currentUserId && (match.player1_id === currentUserId || match.player2_id === currentUserId);
                                    const isFinished = match.finished_at !== null;
                                    const canPlay = isMyMatch && !isFinished;
                                    
                                    return `
                                        <div class="bg-gray-800 rounded-lg p-4 ${isMyMatch ? 'border-2 border-primary' : ''} ${canPlay ? 'animate-pulse' : ''}">
                                            <div class="flex justify-between items-center mb-3">
                                                <div class="text-sm text-gray-400">Match ${idx + 1}</div>
                                                ${isFinished ? `
                                                    <span class="badge badge-success">Finished</span>
                                                ` : `
                                                    <span class="badge badge-warning">Pending</span>
                                                `}
                                            </div>
                                            <div class="grid grid-cols-3 gap-4 items-center">
                                                <div class="text-right ${match.winner_id === match.player1_id ? 'font-bold text-green-400' : isFinished && match.winner_id === match.player2_id ? 'text-red-400' : ''}">
                                                    ${escapeHtml(match.player1_alias || match.player1_username || 'TBD')}
                                                    ${match.player1_score !== null ? ` <span class="text-2xl">${match.player1_score}</span>` : ''}
                                                </div>
                                                <div class="text-center text-gray-400 font-bold">VS</div>
                                                <div class="text-left ${match.winner_id === match.player2_id ? 'font-bold text-green-400' : isFinished && match.winner_id === match.player1_id ? 'text-red-400' : ''}">
                                                    ${escapeHtml(match.player2_alias || match.player2_username || 'TBD')}
                                                    ${match.player2_score !== null ? ` <span class="text-2xl">${match.player2_score}</span>` : ''}
                                                </div>
                                            </div>
                                            ${canPlay ? `
                                                <div class="mt-4 text-center">
                                                    <a href="/game/remote?tournament=${this.tournamentId}&match=${match.id}" data-link class="btn btn-primary btn-lg">
                                                        🎮 Play Your Match Now!
                                                    </a>
                                                </div>
                                            ` : isMyMatch && isFinished ? `
                                                <div class="mt-4 text-center">
                                                    <span class="${match.winner_id === currentUserId ? 'text-green-400' : 'text-red-400'}">${match.winner_id === currentUserId ? '✓ You won' : '✗ You lost'} this match</span>
                                                </div>
                                            ` : !isFinished && !isMyMatch ? `
                                                <div class="mt-4 text-center text-gray-500 text-sm">
                                                    Waiting for players...
                                                </div>
                                            ` : ''}
                                        </div>
                                    `;
                                }).join('')}
                            </div>
                        </div>
                    `;
                }).join('')}
            </div>
        `;
    }

    groupMatchesByRound() {
        const grouped: { [key: number]: any[] } = {};
        
        // Calculate matches per round based on max_players
        const maxPlayers = this.tournament.max_players;
        let matchIndex = 0;
        let currentRound = 1;
        let playersInRound = maxPlayers;
        
        for (const match of this.matches) {
            const matchesInRound = playersInRound / 2;
            
            if (!grouped[currentRound]) {
                grouped[currentRound] = [];
            }
            
            grouped[currentRound].push(match);
            matchIndex++;
            
            // Move to next round when current round is complete
            if (grouped[currentRound].length >= matchesInRound) {
                currentRound++;
                playersInRound = playersInRound / 2;
            }
        }
        
        return grouped;
    }

    async submitJoinTournament() {
        try {
            const aliasInput = document.getElementById('tournamentAlias') as HTMLInputElement;
            const alias = aliasInput?.value.trim() || null;

            await ApiService.post(`/tournaments/${this.tournamentId}/join`, { alias });

            this.hideJoinModal();
            alert('Successfully joined tournament!');
            await this.loadTournament();
        } catch (error: any) {
            console.error('Failed to join tournament:', error);
            alert('Failed to join tournament: ' + (getErrorMessage(error)));
        }
    }

    async startTournament() {
        try {
            await ApiService.post(`/tournaments/${this.tournamentId}/start`, {});

            alert('Tournament started!');
            await this.loadTournament();
        } catch (error: any) {
            console.error('Failed to start tournament:', error);
            alert('Failed to start tournament: ' + (getErrorMessage(error)));
        }
    }
}
