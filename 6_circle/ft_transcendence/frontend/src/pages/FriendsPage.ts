import { escapeHtml } from '../utils/sanitize';
import { t } from '../l10n/index';
import { getErrorMessage } from '../utils/errorHandler';

export class FriendsPage {
    async render() {
        return `
            <div class="container mx-auto px-4 py-8">
                <div class="mb-8">
                    <h1 class="text-4xl font-bold mb-2">${t("friends.title")}</h1>
                    <p class="text-gray-400">${t("friends.description")}</p>
                </div>

                <!-- Friend Requests -->
                <div class="card mb-6">
                    <div class="flex items-center justify-between mb-4">
                        <h2 class="text-2xl font-bold">${t("friends.requestsTitle")}</h2>
                        <span id="requestCount" class="bg-primary-500 text-white px-3 py-1 rounded-full text-sm">0</span>
                    </div>
                    <div id="friendRequests">
                        <div class="text-center py-4">
                            <div class="spinner mx-auto"></div>
                        </div>
                    </div>
                </div>

                <!-- Add Friend -->
                <div class="card mb-6">
                    <h2 class="text-2xl font-bold mb-4">${t("friends.addFriendTitle")}</h2>
                    <div class="flex gap-4">
                        <input
                            type="text"
                            id="searchUsername"
                            placeholder="${t("friends.searchPlaceholder")}"
                            class="flex-1 bg-gray-700 border border-gray-600 rounded-lg px-4 py-2 text-white focus:outline-none focus:border-primary-500"
                        />
                        <button id="searchBtn" class="btn btn-primary">${t("friends.searchButton")}</button>
                    </div>
                    <div id="searchResults" class="mt-4"></div>
                </div>

                <!-- Friends List -->
                <div class="card">
                    <h2 class="text-2xl font-bold mb-4">${t("friends.myFriendsTitle")}</h2>
                    <div id="friendsList">
                        <div class="text-center py-4">
                            <div class="spinner mx-auto"></div>
                        </div>
                    </div>
                </div>
            </div>
        `;
    }

    async onMount() {
        await this.loadFriendRequests();
        await this.loadFriends();
        this.attachEventListeners();
    }

    attachEventListeners() {
        const searchBtn = document.getElementById('searchBtn');
        const searchInput = document.getElementById('searchUsername');

        searchBtn?.addEventListener('click', () => this.searchUsers());
        searchInput?.addEventListener('keypress', (e) => {
            if (e.key === 'Enter') this.searchUsers();
        });
    }

    async loadFriendRequests() {
        try {
            const response = await (window as any).apiService.get('/friends/requests');
            const { requests } = response;

            const requestCount = document.getElementById('requestCount');
            const requestsContainer = document.getElementById('friendRequests');

            if (requestCount) requestCount.textContent = requests.length;

            if (!requestsContainer) return;

            if (requests.length === 0) {
                requestsContainer.innerHTML = `
                    <p class="text-gray-400 text-center py-4">${t("friends.noRequests")}</p>
                `;
                return;
            }

            requestsContainer.innerHTML = requests.map((req: any) => `
                <div class="flex items-center justify-between p-4 bg-gray-750 rounded-lg mb-2">
                    <div>
                        <p class="font-bold">${escapeHtml(req.display_name || req.username)}</p>
                        <p class="text-sm text-gray-400">@${escapeHtml(req.username)}</p>
                    </div>
                    <div class="flex gap-2">
                        <button
                            class="btn btn-primary btn-sm"
                            onclick="window.friendsPage.acceptRequest(${req.id})"
                        >
                            ${t("friends.acceptButton")}
                        </button>
                        <button
                            class="btn btn-secondary btn-sm"
                            onclick="window.friendsPage.rejectRequest(${req.id})"
                        >
                            ${t("friends.rejectButton")}
                        </button>
                    </div>
                </div>
            `).join('');
        } catch (error) {
            console.error('Failed to load friend requests:', error);
            const container = document.getElementById('friendRequests');
            if (container) {
                container.innerHTML = `<p class="text-red-400 text-center py-4">${t("friends.errors.loadRequestsFailed")}</p>`;
            }
        }
    }

    async loadFriends() {
        try {
            const response = await (window as any).apiService.get('/friends');
            const { friends } = response;

            const friendsContainer = document.getElementById('friendsList');
            if (!friendsContainer) return;

            const acceptedFriends = friends.filter((f: any) => f.status === 'accepted');

            if (acceptedFriends.length === 0) {
                friendsContainer.innerHTML = `
                    <p class="text-gray-400 text-center py-4">${t("friends.noFriends")}</p>
                `;
                return;
            }

            friendsContainer.innerHTML = acceptedFriends.map((friend: any) => `
                <div class="flex items-center justify-between p-4 bg-gray-750 rounded-lg mb-2">
                    <div class="flex items-center gap-3">
                        <div class="relative">
                            ${friend.avatar_url
                                ? `<img src="${escapeHtml(friend.avatar_url)}" alt="${escapeHtml(friend.username)}" class="w-12 h-12 rounded-full object-cover">`
                                : `<div class="w-12 h-12 bg-primary-500 rounded-full flex items-center justify-center text-xl font-bold">
                                    ${escapeHtml((friend.display_name || friend.username).charAt(0).toUpperCase())}
                                   </div>`
                            }
                            ${friend.is_online ? '<div class="absolute bottom-0 right-0 w-3 h-3 bg-green-500 rounded-full border-2 border-gray-800"></div>' : ''}
                        </div>
                        <div>
                            <p class="font-bold">${escapeHtml(friend.display_name || friend.username)}</p>
                            <p class="text-sm text-gray-400">@${escapeHtml(friend.username)}</p>
                            <p class="text-xs ${friend.is_online ? 'text-green-400' : 'text-gray-500'}">
                                ${friend.is_online ? t("friends.statusOnline") : t("friends.statusOffline")}
                            </p>
                        </div>
                    </div>
                    <button
                        class="btn btn-secondary btn-sm"
                        onclick="window.friendsPage.removeFriend(${friend.id}, '${escapeHtml(friend.username).replace(/'/g, '&#x27;')}')"
                    >
                        ${t("friends.removeButton")}
                    </button>
                </div>
            `).join('');
        } catch (error) {
            console.error('Failed to load friends:', error);
            const container = document.getElementById('friendsList');
            if (container) {
                container.innerHTML = `<p class="text-red-400 text-center py-4">${t("friends.errors.loadFriendsFailed")}</p>`;
            }
        }
    }

    async searchUsers() {
        const searchInput = document.getElementById('searchUsername') as HTMLInputElement;
        const searchResults = document.getElementById('searchResults');
        
        if (!searchInput || !searchResults) return;

        const username = searchInput.value.trim();
        if (!username) {
            searchResults.innerHTML = `<p class="text-gray-400 text-center py-2">${t("friends.enterUsername")}</p>`;
            return;
        }

        try {
            searchResults.innerHTML = `<div class="text-center py-4"><div class="spinner mx-auto"></div></div>`;

            const response = await (window as any).apiService.get(`/users/search?q=${encodeURIComponent(username)}`);
            const { users } = response;

            const currentUser = JSON.parse(localStorage.getItem('user') || '{}');

            if (users.length === 0) {
                searchResults.innerHTML = `<p class="text-gray-400 text-center py-2">${t("friends.noUsersFound")}</p>`;
                return;
            }

            searchResults.innerHTML = users
                .filter((user: any) => user.id !== currentUser.id)
                .map((user: any) => `
                    <div class="flex items-center justify-between p-4 bg-gray-750 rounded-lg mb-2">
                        <div>
                            <p class="font-bold">${escapeHtml(user.display_name || user.username)}</p>
                            <p class="text-sm text-gray-400">@${escapeHtml(user.username)}</p>
                        </div>
                        <button
                            class="btn btn-primary btn-sm"
                            onclick="window.friendsPage.sendRequest(${user.id}, '${escapeHtml(user.username).replace(/'/g, '&#x27;')}')"
                        >
                            ${t("friends.addFriendButton")}
                        </button>
                    </div>
                `).join('');
        } catch (error) {
            console.error('Search failed:', error);
            searchResults.innerHTML = `<p class="text-red-400 text-center py-2">${t("friends.errors.searchFailed")}</p>`;
        }
    }

    async sendRequest(userId: number, username: string) {
        try {
            await (window as any).apiService.post('/friends/request', { friend_id: userId });
            alert(t('friends.success.requestSent', { username }));
            const searchResults = document.getElementById('searchResults');
            const searchInput = document.getElementById('searchUsername') as HTMLInputElement;
            if (searchResults) searchResults.innerHTML = '';
            if (searchInput) searchInput.value = '';
        } catch (error: any) {
            console.error('Failed to send friend request:', error);
            alert(error.error || t('friends.errors.sendRequestFailed'));
        }
    }

    async acceptRequest(requestId: number) {
        try {
            await (window as any).apiService.post(`/friends/accept/${requestId}`);
            await this.loadFriendRequests();
            await this.loadFriends();
        } catch (error) {
            console.error('Failed to accept request:', error);
            alert(t('friends.errors.acceptFailed'));
        }
    }

    async rejectRequest(requestId: number) {
        try {
            await (window as any).apiService.delete(`/friends/${requestId}`);
            await this.loadFriendRequests();
        } catch (error) {
            console.error('Failed to reject request:', error);
            alert(t('friends.errors.rejectFailed'));
        }
    }

    async removeFriend(friendId: number, username: string) {
        if (!confirm(t('friends.confirmRemove', { username }))) return;

        try {
            // Find friendship ID
            const response = await (window as any).apiService.get('/friends');
            const friendship = response.friends.find((f: any) => f.id === friendId);

            if (friendship) {
                await (window as any).apiService.delete(`/friends/${friendship.id}`);
                await this.loadFriends();
            }
        } catch (error) {
            console.error('Failed to remove friend:', error);
            alert(t('friends.errors.removeFailed'));
        }
    }
}
