import { escapeHtml } from '../utils/sanitize';
import ApiService from '../services/ApiService';
import { createChatComponent, mountLiveChat } from '../components/LiveChat';
import { t } from '../l10n/index';

export class HomePage {
    private chatDispose?: () => void;
    async render() {
        const isAuthenticated = !!localStorage.getItem('auth_token');

        if (!isAuthenticated) {
            return this.renderPublic();
        }

        return this.renderDashboard();
    }

    renderPublic() {
        return `
            <div class="min-h-screen flex items-center justify-center px-4">
                <div class="text-center max-w-4xl">
                    <h1 class="text-6xl font-bold mb-6 animate-fade-in">
                        <span class="text-primary-400">${t("home.welcomeTo")}</span>
                        <br>
                        <span class="text-white">ft_transcendence</span>
                    </h1>

                    <p class="text-xl text-gray-400 mb-12 animate-slide-up">
                        ${t("home.tagline")}
                    </p>

                    <div class="grid grid-cols-1 md:grid-cols-3 gap-6 mb-12">
                        <div class="card animate-slide-up">
                            <div class="text-4xl mb-4">🎮</div>
                            <h3 class="text-xl font-bold mb-2">${t("home.features.playOnline")}</h3>
                            <p class="text-gray-400">${t("home.features.playOnlineDesc")}</p>
                        </div>

                        <div class="card animate-slide-up" style="animation-delay: 0.1s">
                            <div class="text-4xl mb-4">🤖</div>
                            <h3 class="text-xl font-bold mb-2">${t("home.features.aiOpponents")}</h3>
                            <p class="text-gray-400">${t("home.features.aiOpponentsDesc")}</p>
                        </div>

                        <div class="card animate-slide-up" style="animation-delay: 0.2s">
                            <div class="text-4xl mb-4">🏆</div>
                            <h3 class="text-xl font-bold mb-2">${t("home.features.tournaments")}</h3>
                            <p class="text-gray-400">${t("home.features.tournamentsDesc")}</p>
                        </div>
                    </div>

                    <div class="flex justify-center space-x-4">
                        <a href="/register" data-link class="btn btn-primary text-lg px-8 py-3">
                            ${t("home.getStarted")}
                        </a>
                        <a href="/login" data-link class="btn btn-secondary text-lg px-8 py-3">
                            ${t("home.login")}
                        </a>
                    </div>
                </div>
            </div>
        `;
    }

    renderDashboard() {
        const user = JSON.parse(localStorage.getItem('user') || '{}');

        return `
            <div class="container mx-auto px-4 py-8">
                <div class="mb-8 animate-slide-up">
                    <h1 class="text-4xl font-bold mb-2">${t("home.welcomeBack", { name: user.display_name || user.username })}</h1>
                    <p class="text-gray-400">${t("home.readyToPlay")}</p>
                </div>

                <div class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6 mb-8">
                    <!-- Quick Play -->
                    <div class="card hover:bg-gray-750 transition cursor-pointer" onclick="window.location.href='/game/local'">
                        <div class="flex items-center mb-4">
                            <div class="text-4xl mr-4">⚡</div>
                            <div>
                                <h3 class="text-xl font-bold">${t("home.quickPlay.localPlay")}</h3>
                                <p class="text-gray-400 text-sm">${t("home.quickPlay.localPlayDesc")}</p>
                            </div>
                        </div>
                    </div>

                    <!-- AI Match -->
                    <div class="card hover:bg-gray-750 transition cursor-pointer" onclick="window.location.href='/game/ai'">
                        <div class="flex items-center mb-4">
                            <div class="text-4xl mr-4">🤖</div>
                            <div>
                                <h3 class="text-xl font-bold">${t("home.quickPlay.vsAI")}</h3>
                                <p class="text-gray-400 text-sm">${t("home.quickPlay.vsAIDesc")}</p>
                            </div>
                        </div>
                    </div>

                    <!-- Online Match -->
                    <div class="card hover:bg-gray-750 transition cursor-pointer" onclick="window.location.href='/game/remote'">
                        <div class="flex items-center mb-4">
                            <div class="text-4xl mr-4">🌐</div>
                            <div>
                                <h3 class="text-xl font-bold">${t("home.quickPlay.onlineMatch")}</h3>
                                <p class="text-gray-400 text-sm">${t("home.quickPlay.onlineMatchDesc")}</p>
                            </div>
                        </div>
                    </div>

                    <!-- Tournament -->
                    <div class="card hover:bg-gray-750 transition cursor-pointer" onclick="window.location.href='/tournament'">
                        <div class="flex items-center mb-4">
                            <div class="text-4xl mr-4">🏆</div>
                            <div>
                                <h3 class="text-xl font-bold">${t("home.quickPlay.tournament")}</h3>
                                <p class="text-gray-400 text-sm">${t("home.quickPlay.tournamentDesc")}</p>
                            </div>
                        </div>
                    </div>

                    <!-- Profile -->
                    <div class="card hover:bg-gray-750 transition cursor-pointer" onclick="sessionStorage.removeItem('profileTargetId'); sessionStorage.removeItem('profileTarget'); window.location.href='/profile'">
                        <div class="flex items-center mb-4">
                            <div class="text-4xl mr-4">👤</div>
                            <div>
                                <h3 class="text-xl font-bold">${t("home.quickPlay.profile")}</h3>
                                <p class="text-gray-400 text-sm">${t("home.quickPlay.profileDesc")}</p>
                            </div>
                        </div>
                    </div>

                    <!-- Friends -->
                    <div class="card hover:bg-gray-750 transition cursor-pointer" onclick="window.location.href='/friends'">
                        <div class="flex items-center mb-4">
                            <div class="text-4xl mr-4">👥</div>
                            <div>
                                <h3 class="text-xl font-bold">${t("home.quickPlay.friends")}</h3>
                                <p class="text-gray-400 text-sm">${t("home.quickPlay.friendsDesc")}</p>
                            </div>
                        </div>
                    </div>
                </div>

                <!-- live chat -->
                <div class="card animate-slide-up">
                    ${createChatComponent()}
                </div>

                <!-- User Stats -->
                <div class="card mt-6 animate-slide-up">
                    <h2 class="text-2xl font-bold mb-4">${t("home.stats.title")}</h2>
                    <div id="userStats" class="grid grid-cols-2 md:grid-cols-4 gap-4">
                        <div class="text-center">
                            <div class="spinner mx-auto"></div>
                        </div>
                    </div>
                </div>

                <!-- Recent Games -->
                <div class="card mt-6 animate-slide-up">
                    <h2 class="text-2xl font-bold mb-4">${t("home.recentMatches.title")}</h2>
                    <div id="recentGames">
                        <div class="text-center py-8">
                            <div class="spinner mx-auto"></div>
                        </div>
                    </div>
                </div>
            </div>
        `;
    }

    async onMount() {
        const isAuthenticated = !!localStorage.getItem('auth_token');
        if (!isAuthenticated) return;

        await this.loadUserStats();
        await this.loadRecentGames();

        // Initialize live chat
        const user = JSON.parse(localStorage.getItem('user') || '{}');
        if (user.username) {
            this.chatDispose = mountLiveChat(user.username);
        }
    }

    cleanup() {
        // Cleanup live chat when leaving page
        if (this.chatDispose) {
            this.chatDispose();
            this.chatDispose = undefined;
        }
    }

    async loadUserStats() {
        try {
            const user = JSON.parse(localStorage.getItem('user') || '{}');
            
            const userStatsEl = document.getElementById('userStats');
            if (!userStatsEl) {
                console.error('userStats element not found');
                return;
            }
            
            if (!user.id) {
                console.error('No user ID found');
                userStatsEl.innerHTML = `<p class="text-gray-400">${t("home.stats.pleaseLogin")}</p>`;
                return;
            }

            const data = await ApiService.get(`/users/${user.id}/stats`);
            const stats = data.stats || data;

            // Ensure all stats values exist with defaults
            const safeStats = {
                total_games: stats.total_games || 0,
                total_wins: stats.total_wins || 0,
                total_losses: stats.total_losses || 0,
                win_rate: stats.win_rate || 0,
                highest_score: stats.highest_score || 0
            };

            if (userStatsEl) {
                userStatsEl.innerHTML = `
                <div class="text-center">
                    <div class="text-3xl font-bold text-primary-400">${safeStats.total_games}</div>
                    <div class="text-gray-400 text-sm">${t("home.stats.totalGames")}</div>
                </div>
                <div class="text-center">
                    <div class="text-3xl font-bold text-green-400">${safeStats.total_wins}</div>
                    <div class="text-gray-400 text-sm">${t("home.stats.wins")}</div>
                </div>
                <div class="text-center">
                    <div class="text-3xl font-bold text-red-400">${safeStats.total_losses}</div>
                    <div class="text-gray-400 text-sm">${t("home.stats.losses")}</div>
                </div>
                <div class="text-center">
                    <div class="text-3xl font-bold text-yellow-400">${(safeStats.win_rate * 100).toFixed(1)}%</div>
                    <div class="text-gray-400 text-sm">${t("home.stats.winRate")}</div>
                </div>
            `;
            }
        } catch (error) {
            console.error('Failed to load stats:', error);
            const userStatsEl = document.getElementById('userStats');
            if (userStatsEl) {
                userStatsEl.innerHTML = `<p class="text-red-400">${t("home.stats.loadFailed")}</p>`;
            }
        }
    }

    async loadRecentGames() {
        try {
            const recentGamesEl = document.getElementById('recentGames');
            if (!recentGamesEl) {
                console.error('recentGames element not found');
                return;
            }
            
            const user = JSON.parse(localStorage.getItem('user') || '{}');
            const data = await ApiService.get(`/games/user/${user.id}?limit=5`);

            if (data.games.length === 0) {
                recentGamesEl.innerHTML = `<p class="text-gray-400 text-center py-4">${t("home.recentMatches.noMatches")}</p>`;
                return;
            }

            recentGamesEl.innerHTML = data.games.map((game: any) => {
                // Determine if user is player1 or player2
                const isPlayer1 = game.player1_id === user.id;
                const myName = isPlayer1
                    ? (game.player1_display_name || game.player1_username)
                    : (game.player2_display_name || game.player2_username);
                const opponentName = isPlayer1
                    ? (game.player2_display_name || game.player2_username || 'AI')
                    : (game.player1_display_name || game.player1_username);
                const myScore = isPlayer1 ? game.player1_score : game.player2_score;
                const opponentScore = isPlayer1 ? game.player2_score : game.player1_score;

                return `
                    <div class="border-b border-gray-700 py-3 last:border-0">
                        <div class="flex justify-between items-center">
                            <div class="flex items-center space-x-4">
                                <div class="${game.winner_id === user.id ? 'text-green-400' : 'text-red-400'} font-bold">
                                    ${game.winner_id === user.id ? t("home.recentMatches.win") : t("home.recentMatches.loss")}
                                </div>
                                <div>
                                    <span class="font-semibold">${escapeHtml(myName)}</span>
                                    <span class="text-gray-400"> ${t("home.recentMatches.vs")} </span>
                                    <span class="font-semibold">${escapeHtml(opponentName)}</span>
                                </div>
                            </div>
                            <div class="text-right">
                                <div class="font-bold">${myScore} - ${opponentScore}</div>
                                <div class="text-sm text-gray-400">${new Date(game.finished_at).toLocaleDateString()}</div>
                            </div>
                        </div>
                    </div>
                `;
            }).join('');
        } catch (error) {
            console.error('Failed to load recent games:', error);
            const recentGamesEl = document.getElementById('recentGames');
            if (recentGamesEl) {
                recentGamesEl.innerHTML = `<p class="text-red-400 text-center py-4">${t("home.recentMatches.loadFailed")}</p>`;
            }
        }
    }
}
