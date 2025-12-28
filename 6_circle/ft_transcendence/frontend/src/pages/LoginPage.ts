import ApiService from '../services/ApiService';
import { t } from '../l10n/index';
import { getErrorMessage } from '../utils/errorHandler';

export class LoginPage {
    async render() {
        return `
            <div class="min-h-screen flex items-center justify-center px-4">
                <div class="card max-w-md w-full">
                    <h2 class="text-3xl font-bold mb-6 text-center">${t("login.title")}</h2>

                    <form id="loginForm" class="space-y-4">
                        <div>
                            <label for="username" class="block text-sm font-medium mb-2">${t("login.usernameLabel")}</label>
                            <input type="text" id="username" name="username"
                                   class="input" required autofocus>
                        </div>

                        <div>
                            <label for="password" class="block text-sm font-medium mb-2">${t("login.passwordLabel")}</label>
                            <input type="password" id="password" name="password"
                                   class="input" required>
                        </div>

                        <div id="twoFASection" class="hidden">
                            <label for="twofa_code" class="block text-sm font-medium mb-2">${t("login.twoFALabel")}</label>
                            <input type="text" id="twofa_code" name="twofa_code"
                                   class="input" pattern="[0-9]{6}" maxlength="6"
                                   placeholder="${t("login.twoFAPlaceholder")}">
                            <p class="text-xs text-gray-400 mt-1">${t("login.twoFAHint")}</p>
                        </div>

                        <div id="errorMessage" class="hidden bg-red-900 border border-red-700 text-red-300 px-4 py-3 rounded-lg"></div>

                        <button type="submit" id="submitBtn" class="btn btn-primary w-full">
                            ${t("login.submit")}
                        </button>
                    </form>

                    <p class="text-center mt-6 text-gray-400">
                        ${t("login.noAccount")}
                        <a href="/register" data-link class="text-primary-400 hover:text-primary-300">${t("login.toSignup")}</a>
                    </p>
                </div>
            </div>
        `;
    }

    async onMount() {
        const form = document.getElementById('loginForm');
        const errorMessage = document.getElementById('errorMessage');
        const twoFASection = document.getElementById('twoFASection');
        const submitBtn = document.getElementById('submitBtn');
        
        if (!form || !errorMessage || !twoFASection || !submitBtn) {
            console.error('Login form elements not found');
            return;
        }
        
        let requires2FA = false;

        form.addEventListener('submit', async (e) => {
            e.preventDefault();
            errorMessage.classList.add('hidden');

            const username = (document.getElementById('username') as HTMLInputElement).value;
            const password = (document.getElementById('password') as HTMLInputElement).value;
            const twofa_code = (document.getElementById('twofa_code') as HTMLInputElement).value || null;

            (submitBtn as HTMLButtonElement).disabled = true;
            submitBtn.textContent = t('login.submitting');

            try {
                console.log('Attempting login...', { username });
                const data = await ApiService.post('/auth/login', {
                    username,
                    password,
                    twofa_code
                });

                console.log('Login response:', data);

                if (data.requires_2fa) {
                    requires2FA = true;
                    twoFASection.classList.remove('hidden');
                    (document.getElementById('twofa_code') as HTMLInputElement).focus();
                    (submitBtn as HTMLButtonElement).disabled = false;
                    submitBtn.textContent = t('login.verify2FA');
                    return;
                }

                // Success
                localStorage.setItem('auth_token', data.token);
                localStorage.setItem('user', JSON.stringify(data.user));
                
                window.dispatchEvent(new CustomEvent('auth-change', { 
                    detail: { authenticated: true, user: data.user } 
                }));

                window.location.href = '/';
            } catch (error: unknown) {
                console.error('Login error:', error);
                const errorMsg = getErrorMessage(error);
                
                if (errorMsg === 'ALREADY_LOGGED_IN') {
                    alert(t('login.alreadyLoggedIn'));
                } else {
                    errorMessage.textContent = errorMsg;
                    errorMessage.classList.remove('hidden');
                }
                
                (submitBtn as HTMLButtonElement).disabled = false;
                submitBtn.textContent = requires2FA ? t('login.verify2FA') : t('login.submit');
            }
        });
    }
}
