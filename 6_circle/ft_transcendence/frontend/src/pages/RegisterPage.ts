import ApiService from '../services/ApiService';
import { t } from '../l10n/index';
import { getErrorMessage } from '../utils/errorHandler';

export class RegisterPage {
    async render() {
        return `
            <div class="min-h-screen flex items-center justify-center px-4 py-8">
                <div class="card max-w-md w-full">
                    <h2 class="text-3xl font-bold mb-6 text-center">${t("signup.title")}</h2>

                    <form id="registerForm" class="space-y-4">
                        <div>
                            <label for="username" class="block text-sm font-medium mb-2">${t("signup.usernameLabel")}</label>
                            <input type="text" id="username" name="username"
                                   class="input" required autofocus
                                   minlength="3" maxlength="20"
                                   pattern="[a-zA-Z0-9_]+"
                                   title="${t("signup.usernameHint")}">
                            <p class="text-xs text-gray-400 mt-1">${t("signup.usernameHint")}</p>
                        </div>

                        <div>
                            <label for="email" class="block text-sm font-medium mb-2">${t("signup.emailLabel")}</label>
                            <input type="email" id="email" name="email"
                                   class="input" required>
                        </div>

                        <div>
                            <label for="display_name" class="block text-sm font-medium mb-2">${t("signup.displayNameLabel")}</label>
                            <input type="text" id="display_name" name="display_name"
                                   class="input" maxlength="50">
                        </div>

                        <div>
                            <label for="password" class="block text-sm font-medium mb-2">${t("signup.passwordLabel")}</label>
                            <input type="password" id="password" name="password"
                                   class="input" required minlength="6">
                            <p class="text-xs text-gray-400 mt-1">${t("signup.passwordHint")}</p>
                        </div>

                        <div>
                            <label for="confirm_password" class="block text-sm font-medium mb-2">${t("signup.confirmPasswordLabel")}</label>
                            <input type="password" id="confirm_password" name="confirm_password"
                                   class="input" required>
                        </div>

                        <div id="errorMessage" class="hidden bg-red-900 border border-red-700 text-red-300 px-4 py-3 rounded-lg"></div>
                        <div id="successMessage" class="hidden bg-green-900 border border-green-700 text-green-300 px-4 py-3 rounded-lg"></div>

                        <button type="submit" id="submitBtn" class="btn btn-primary w-full">
                            ${t("signup.submit")}
                        </button>
                    </form>

                    <p class="text-center mt-6 text-gray-400">
                        ${t("signup.hasAccount")}
                        <a href="/login" data-link class="text-primary-400 hover:text-primary-300">${t("signup.toLogin")}</a>
                    </p>
                </div>
            </div>
        `;
    }

    async onMount() {
        const form = document.getElementById('registerForm');
        const errorMessage = document.getElementById('errorMessage');
        const successMessage = document.getElementById('successMessage');
        const submitBtn = document.getElementById('submitBtn');

        if (!form || !errorMessage || !successMessage || !submitBtn) {
            console.error('Register form elements not found');
            return;
        }

        form.addEventListener('submit', async (e) => {
            e.preventDefault();
            errorMessage.classList.add('hidden');
            successMessage.classList.add('hidden');

            const username = (document.getElementById('username') as HTMLInputElement).value;
            const email = (document.getElementById('email') as HTMLInputElement).value;
            const displayName = (document.getElementById('display_name') as HTMLInputElement).value;
            const password = (document.getElementById('password') as HTMLInputElement).value;
            const confirmPassword = (document.getElementById('confirm_password') as HTMLInputElement).value;

            // Validate passwords match
            if (password !== confirmPassword) {
                errorMessage.textContent = t('signup.errors.passwordMismatch');
                errorMessage.classList.remove('hidden');
                return;
            }

            (submitBtn as HTMLButtonElement).disabled = true;
            submitBtn.textContent = t('signup.submitting');

            try {
                await ApiService.post('/auth/register', {
                    username,
                    email,
                    display_name: displayName,
                    password
                });

                successMessage.textContent = t('signup.success');
                successMessage.classList.remove('hidden');

                setTimeout(() => {
                    window.location.href = '/login';
                }, 2000);
            } catch (error: unknown) {
                const errorMsg = getErrorMessage(error);
                errorMessage.textContent = errorMsg;
                errorMessage.classList.remove('hidden');
                (submitBtn as HTMLButtonElement).disabled = false;
                submitBtn.textContent = t('signup.submit');
            }
        });
    }
}
