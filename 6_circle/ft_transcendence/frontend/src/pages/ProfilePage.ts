import { escapeHtml } from '../utils/sanitize';
import ApiService from '../services/ApiService';
import { t } from '../l10n/index';
import { getErrorMessage } from '../utils/errorHandler';

export class ProfilePage {
    isSelf = true;

    async render() {
        return `
            <div class="container mx-auto px-4 py-8">
                <div class="max-w-4xl mx-auto">
                    <h1 class="text-4xl font-bold mb-8">${t("profile.title")}</h1>

                    <div class="grid grid-cols-1 gap-6">
                        <!-- Info & Settings -->
                        <div class="space-y-6">
                            <!-- Avatar Section -->
                            <div class="card">
                                <h2 class="text-2xl font-bold mb-4">${t("profile.avatarTitle")}</h2>
                                <div class="flex items-center gap-6">
                                    <div id="avatarDisplay" class="w-32 h-32 rounded-full bg-gray-700 flex items-center justify-center text-4xl font-bold overflow-hidden">
                                        <div class="spinner"></div>
                                    </div>
                                    <div class="flex-1">
                                        <input type="file" id="avatarInput" accept="image/jpeg,image/jpg,image/png,image/gif,image/webp" class="hidden" />
                                        <div class="space-y-2">
                                            <button id="uploadAvatarBtn" class="btn btn-primary">${t("profile.uploadAvatar")}</button>
                                            <button id="deleteAvatarBtn" class="btn btn-danger hidden">${t("profile.deleteAvatar")}</button>
                                        </div>
                                        <p id="avatarHint" class="text-sm text-gray-400 mt-2">${t("profile.avatarHint")}</p>
                                    </div>
                                </div>
                            </div>

                            <div class="card">
                                <h2 class="text-2xl font-bold mb-4">${t("profile.infoTitle")}</h2>
                                <div id="userInfo">
                                    <div class="spinner"></div>
                                </div>
                            </div>

                            <div class="card">
                                <h2 class="text-2xl font-bold mb-4">${t("profile.statsTitle")}</h2>
                                <div id="userStats">
                                    <div class="spinner"></div>
                                </div>
                            </div>

                            <div class="card">
                                <h2 class="text-2xl font-bold mb-4">${t("profile.securityTitle")}</h2>
                                <div id="securitySection">
                                    <div class="spinner"></div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        `;
    }

    async onMount() {
        await this.loadProfile();
        if (this.isSelf) {
            this.attachAvatarListeners();
        }
        else
        {
            document.getElementById('deleteAvatarBtn') ?.classList.remove('hidden');
        }
    }

    attachAvatarListeners() {
        const uploadBtn = document.getElementById('uploadAvatarBtn');
        const avatarInput = document.getElementById('avatarInput') as HTMLInputElement;
        const deleteBtn = document.getElementById('deleteAvatarBtn');

        if (uploadBtn && avatarInput) {
            uploadBtn.addEventListener('click', () => avatarInput.click());
            avatarInput.addEventListener('change', () => this.handleAvatarUpload());
        }

        if (deleteBtn) {
            deleteBtn.addEventListener('click', () => this.handleAvatarDelete());
        }
    }

    async loadProfile() {
        try {
            const targetIdRaw = sessionStorage.getItem('profileTargetId');
            const targetId = targetIdRaw ? Number(targetIdRaw) : null;
            const hasValidTargetId = Number.isInteger(targetId) && (targetId as number) > 0;
            const currentUser = this.getCurrentUser();
            this.isSelf = !hasValidTargetId || (currentUser.id && targetId === currentUser.id);
            if (this.isSelf && targetIdRaw) {
                sessionStorage.removeItem('profileTargetId');
            }
            const endpoint = this.isSelf || !hasValidTargetId
                ? '/users/me'
                : `/users/${targetId}`;
            const data = await ApiService.get(endpoint);
            const user = data.user;

            this.toggleSelfControls(this.isSelf);

            // Avatar display
            this.updateAvatarDisplay(user);

            // User info
            const userInfoEl = document.getElementById('userInfo');
            if (!userInfoEl) {
                console.error('userInfo element not found');
                return;
            }
            
            const displayName = user.display_name || user.username || '';
            const username = user.username || '';
            const showUsername = displayName && username && displayName !== username;
            userInfoEl.innerHTML = `
                <div class="space-y-3">
                    <div>
                        <label class="text-sm text-gray-400">${t("signup.usernameLabel")}</label>
                        <p class="font-medium">${escapeHtml(displayName || username || '')}</p>
                        ${showUsername ? `<p class="text-sm text-gray-400">@${escapeHtml(username)}</p>` : ''}
                    </div>
                    ${this.isSelf ? `
                    <div>
                        <label class="text-sm text-gray-400">${t("profile.emailLabel")}</label>
                        <p class="font-medium">${escapeHtml(user.email)}</p>
                    </div>
                    ` : ''}
                    <div>
                        <label class="text-sm text-gray-400">${t("profile.memberSinceLabel")}</label>
                        <p class="font-medium">${escapeHtml(new Date(user.created_at).toLocaleDateString())}</p>
                    </div>
                    <div>
                        <label class="text-sm text-gray-400">${t("profile.statusLabel")}</label>
                        <p class="font-medium">
                            <span class="badge ${user.is_online ? 'badge-success' : 'badge-danger'}">
                                ${user.is_online ? t("profile.statusOnline") : t("profile.statusOffline")}
                            </span>
                        </p>
                    </div>
                </div>
            `;

            // Stats
            const userStatsEl = document.getElementById('userStats');
            if (!userStatsEl) {
                console.error('userStats element not found');
                return;
            }
            
            userStatsEl.innerHTML = `
                <div class="grid grid-cols-2 gap-4">
                    <div>
                        <div class="text-3xl font-bold text-primary-400">${user.total_games}</div>
                        <div class="text-gray-400 text-sm">${t("profile.totalGames")}</div>
                    </div>
                    <div>
                        <div class="text-3xl font-bold text-green-400">${user.total_wins}</div>
                        <div class="text-gray-400 text-sm">${t("profile.wins")}</div>
                    </div>
                    <div>
                        <div class="text-3xl font-bold text-red-400">${user.total_losses}</div>
                        <div class="text-gray-400 text-sm">${t("profile.losses")}</div>
                    </div>
                    <div>
                        <div class="text-3xl font-bold text-yellow-400">${(user.win_rate * 100).toFixed(1)}%</div>
                        <div class="text-gray-400 text-sm">${t("profile.winRate")}</div>
                    </div>
                </div>
            `;

            // Security
            const securitySectionEl = document.getElementById('securitySection');
            if (!securitySectionEl) {
                console.error('securitySection element not found');
                return;
            }

            if (!this.isSelf) {
                securitySectionEl.innerHTML = '';
                return;
            }

            securitySectionEl.innerHTML = `
                <div class="space-y-4">
                    <div class="flex justify-between items-center">
                        <div>
                            <h3 class="font-bold">${t("profile.twoFATitle")}</h3>
                            <p class="text-sm text-gray-400">${t("profile.twoFADesc")}</p>
                        </div>
                        <button id="toggle2FABtn" class="btn ${user.two_fa_enabled ? 'btn-danger' : 'btn-primary'} btn-sm">
                            ${user.two_fa_enabled ? t("profile.disable2FA") : t("profile.enable2FA")}
                        </button>
                    </div>
                </div>
            `;

            // 2FA toggle
            const toggle2FABtn = document.getElementById('toggle2FABtn');
            if (!toggle2FABtn) {
                console.error('toggle2FABtn not found');
                return;
            }
            
            toggle2FABtn.addEventListener('click', async () => {
                if (user.two_fa_enabled) {
                    await this.disable2FA();
                } else {
                    await this.setup2FA();
                }
            });
        } catch (error) {
            console.error('Failed to load profile:', error);
        }
    }

    async setup2FA() {
        try {
            const data = await ApiService.post('/auth/2fa/setup');

            // Show QR code modal
            const modal = document.createElement('div');
            modal.className = 'fixed inset-0 bg-black bg-opacity-75 flex items-center justify-center z-50';
            modal.innerHTML = `
                <div class="card max-w-md">
                    <h3 class="text-2xl font-bold mb-4">${t("profile.setup2FATitle")}</h3>
                    <p class="mb-4 text-gray-400">${t("profile.setup2FAInstructions")}</p>
                    <img src="${data.qrCode}" alt="QR Code" class="mx-auto mb-4">
                    <p class="mb-4 text-sm text-gray-400">${t("profile.setup2FAManual")}: <code class="bg-gray-700 px-2 py-1 rounded">${data.secret}</code></p>
                    <input type="text" id="verify2FACode" placeholder="${t("profile.enter2FACode")}" class="input mb-4" maxlength="6">
                    <div class="flex space-x-2">
                        <button id="verify2FABtn" class="btn btn-primary flex-1">${t("profile.verifyAndEnable")}</button>
                        <button id="cancel2FABtn" class="btn btn-secondary flex-1">${t("profile.cancel")}</button>
                    </div>
                </div>
            `;
            document.body.appendChild(modal);

            const verify2FABtn = document.getElementById('verify2FABtn');
            const cancel2FABtn = document.getElementById('cancel2FABtn');
            
            if (verify2FABtn) {
                verify2FABtn.addEventListener('click', async () => {
                    const codeInput = document.getElementById('verify2FACode') as HTMLInputElement;
                    if (!codeInput) {
                        console.error('verify2FACode input not found');
                        return;
                    }
                    const code = codeInput.value;
                    await this.verify2FA(code);
                    document.body.removeChild(modal);
                });
            }

            if (cancel2FABtn) {
                cancel2FABtn.addEventListener('click', () => {
                    document.body.removeChild(modal);
                });
            }
        } catch (error) {
            console.error('Failed to setup 2FA:', error);
            alert(t('profile.errors.setup2FAFailed'));
        }
    }

    async verify2FA(code: string) {
        try {
            await ApiService.post('/auth/2fa/verify', { token: code });

            alert(t('profile.success.2FAEnabled'));
            await this.loadProfile();
        } catch (error: any) {
            console.error('Failed to verify 2FA:', error);
            alert(t('profile.errors.verify2FAFailed') + ': ' + getErrorMessage(error));
        }
    }

    async disable2FA() {
        const password = prompt(t('profile.enterPasswordToDisable2FA'));
        if (!password) return;

        try {
            await ApiService.post('/auth/2fa/disable', { password });

            alert(t('profile.success.2FADisabled'));
            await this.loadProfile();
        } catch (error: any) {
            console.error('Failed to disable 2FA:', error);
            alert(t('profile.errors.disable2FAFailed') + ': ' + getErrorMessage(error));
        }
    }

    updateAvatarDisplay(user: any) {
        const avatarDisplay = document.getElementById('avatarDisplay');
        const deleteBtn = document.getElementById('deleteAvatarBtn');

        if (!avatarDisplay) return;

        if (user.avatar_url) {
            avatarDisplay.innerHTML = `<img src="${escapeHtml(user.avatar_url)}" alt="Avatar" class="w-full h-full object-cover" />`;
            deleteBtn?.classList.remove('hidden');
        } else {
            const initial = (user.display_name || user.username || '?').charAt(0).toUpperCase();
            avatarDisplay.innerHTML = escapeHtml(initial);
            deleteBtn?.classList.add('hidden');
        }
    }

    getCurrentUser() {
        try {
            return JSON.parse(localStorage.getItem('user') || '{}');
        } catch {
            return {};
        }
    }

    toggleSelfControls(isSelf: boolean) {
        const uploadBtn = document.getElementById('uploadAvatarBtn');
        const deleteBtn = document.getElementById('deleteAvatarBtn');
        const avatarHint = document.getElementById('avatarHint');
        const securitySectionEl = document.getElementById('securitySection');
        const securityCard = securitySectionEl?.closest('.card');

        if (isSelf) {
            uploadBtn?.classList.remove('hidden');
            avatarHint?.classList.remove('hidden');
            securityCard?.classList.remove('hidden');
        } else {
            uploadBtn?.classList.add('hidden');
            deleteBtn?.classList.add('hidden');
            avatarHint?.classList.add('hidden');
            securityCard?.classList.add('hidden');
        }
    }

    async handleAvatarUpload() {
        const avatarInput = document.getElementById('avatarInput') as HTMLInputElement;
        if (!avatarInput || !avatarInput.files || avatarInput.files.length === 0) {
            return;
        }

        const file = avatarInput.files[0];

        // Validate file type
        const allowedTypes = ['image/jpeg', 'image/jpg', 'image/png', 'image/gif', 'image/webp'];
        if (!allowedTypes.includes(file.type)) {
            alert(t('profile.errors.invalidFileType'));
            return;
        }

        // Validate file size (5MB)
        if (file.size > 5 * 1024 * 1024) {
            alert(t('profile.errors.fileTooLarge'));
            return;
        }

        try {
            const formData = new FormData();
            formData.append('file', file);

            const token = localStorage.getItem('auth_token');
            const env = (import.meta as any).env || {};
            const apiUrl = env.MODE === 'development' ? '' : (env.VITE_API_URL || '');
            const response = await fetch(`${apiUrl}/api/users/me/avatar`, {
                method: 'POST',
                headers: {
                    'Authorization': `Bearer ${token}`
                },
                body: formData
            });

            if (!response.ok) {
                const error = await response.json();
                throw new Error(error.error || 'Upload failed');
            }

            await response.json();
            alert(t('profile.success.avatarUploaded'));

            // Reset input
            avatarInput.value = '';

            // Reload profile to show new avatar
            await this.loadProfile();
        } catch (error: any) {
            console.error('Failed to upload avatar:', error);
            alert(t('profile.errors.uploadFailed') + ': ' + getErrorMessage(error));
        }
    }

    async handleAvatarDelete() {
        if (!confirm(t('profile.confirmDeleteAvatar'))) {
            return;
        }

        try {
            await ApiService.delete('/users/me/avatar');
            alert(t('profile.success.avatarDeleted'));
            await this.loadProfile();
        } catch (error: any) {
            console.error('Failed to delete avatar:', error);
            alert(t('profile.errors.deleteFailed') + ': ' + getErrorMessage(error));
        }
    }
}
