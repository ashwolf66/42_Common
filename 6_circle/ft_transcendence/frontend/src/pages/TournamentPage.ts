import { escapeHtml } from '../utils/sanitize';
import ApiService from '../services/ApiService';
import { t } from '../l10n/index';
import { getErrorMessage } from '../utils/errorHandler';

export class TournamentPage {
    async render() {
        return `
            <div class="container mx-auto px-4 py-8">
                <h1 class="text-4xl font-bold mb-8">${t("tournament.title")}</h1>

                <div class="grid grid-cols-1 lg:grid-cols-3 gap-6">
                    <div class="lg:col-span-2">
                        <div class="card mb-6">
                            <h2 class="text-2xl font-bold mb-4">${t("tournament.activeTitle")}</h2>
                            <div id="tournamentsList">
                                <div class="spinner"></div>
                            </div>
                        </div>
                    </div>

                    <div>
                        <div class="card">
                            <h2 class="text-2xl font-bold mb-4">${t("tournament.createTitle")}</h2>
                            <form id="createTournamentForm" class="space-y-4">
                                <div>
                                    <label class="block text-sm font-medium mb-2">${t("tournament.nameLabel")}</label>
                                    <input type="text" id="tournamentName" class="input" required>
                                </div>

                                <div>
                                    <label class="block text-sm font-medium mb-2">${t("tournament.maxPlayersLabel")}</label>
                                    <select id="maxPlayers" class="input">
                                        <option value="2">${t("tournament.players", { count: 2 })}</option>
                                        <option value="4">${t("tournament.players", { count: 4 })}</option>
                                        <option value="8">${t("tournament.players", { count: 8 })}</option>
                                        <option value="16">${t("tournament.players", { count: 16 })}</option>
                                    </select>
                                </div>

                                <button type="submit" class="btn btn-primary w-full">${t("tournament.createButton")}</button>
                            </form>
                        </div>
                    </div>
                </div>
            </div>
        `;
    }

    async onMount() {
        await this.loadTournaments();

        const form = document.getElementById('createTournamentForm');
        if (form) {
            form.addEventListener('submit', async (e) => {
                e.preventDefault();
                await this.createTournament();
            });
        }
    }

    async loadTournaments() {
        try {
            const data = await ApiService.get('/tournaments');

            const list = document.getElementById('tournamentsList');
            if (!list) return;

            if (data.tournaments.length === 0) {
                list.innerHTML = `
                    <p class="text-gray-400 text-center py-8">${t("tournament.noTournaments")}</p>
                `;
                return;
            }

            list.innerHTML = data.tournaments.map((tournament: any) => `
                <div class="border-b border-gray-700 py-4 last:border-0">
                    <div class="flex justify-between items-start">
                        <div>
                            <h3 class="font-bold text-lg">${escapeHtml(tournament.name)}</h3>
                            <p class="text-gray-400 text-sm">
                                ${tournament.participant_count}/${tournament.max_players} ${t("tournament.playersLabel")} |
                                <span class="badge badge-${tournament.status === 'pending' ? 'warning' : tournament.status === 'active' ? 'info' : 'success'}">
                                    ${t(`tournament.status.${tournament.status}`)}
                                </span>
                            </p>
                        </div>
                        <a href="/tournament/${tournament.id}" class="btn btn-primary btn-sm">${t("tournament.viewButton")}</a>
                    </div>
                </div>
            `).join('');
        } catch (error) {
            console.error('Failed to load tournaments:', error);
        }
    }

    async createTournament() {
        const nameInput = document.getElementById('tournamentName') as HTMLInputElement;
        const maxPlayersInput = document.getElementById('maxPlayers') as HTMLInputElement;
        const form = document.getElementById('createTournamentForm') as HTMLFormElement;
        
        if (!nameInput || !maxPlayersInput) {
            console.error('Form elements not found');
            return;
        }
        
        const name = nameInput.value;
        const max_players = parseInt(maxPlayersInput.value);

        try {
            await ApiService.post('/tournaments', { name, max_players });

            alert(t('tournament.success.created'));
            if (form) form.reset();
            await this.loadTournaments();
        } catch (error: any) {
            console.error('Failed to create tournament:', error);
            alert(t('tournament.errors.createFailed') + ': ' + (getErrorMessage(error)));
        }
    }
}
