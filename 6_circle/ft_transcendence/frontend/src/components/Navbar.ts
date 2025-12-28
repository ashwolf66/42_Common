import { createLanguageSwitcher } from './LanguageSwitcher';
import { t } from '../l10n/index';

export function createNavbar(isAuthenticated: boolean): string {
    if (!isAuthenticated) {
        return `
            <nav id="navbar" class="bg-gray-800 border-b border-gray-700 shadow-lg">
                <div class="container mx-auto px-4">
                    <div class="flex items-center justify-between h-16">
                        <a href="/" data-link class="text-2xl font-bold text-primary-400">
                            🏓 ft_transcendence
                        </a>
                        <div class="flex items-center space-x-4">
                            ${createLanguageSwitcher()}
                            <a href="/login" data-link class="btn btn-secondary btn-sm">${t("header.login")}</a>
                            <a href="/register" data-link class="btn btn-primary btn-sm">${t("signup.submit")}</a>
                        </div>
                    </div>
                </div>
            </nav>
        `;
    }

    const user = JSON.parse(localStorage.getItem('user') || '{}');

    return `
        <nav id="navbar" class="bg-gray-800 border-b border-gray-700 shadow-lg">
            <div class="container mx-auto px-4">
                <div class="flex items-center justify-between h-16">
                    <a href="/" data-link class="text-2xl font-bold text-primary-400">
                        🏓 ft_transcendence
                    </a>

                    <div class="flex items-center space-x-6">
                        <a href="/game" data-link class="text-gray-300 hover:text-white transition">${t("header.play")}</a>
                        <a href="/tournament" data-link class="text-gray-300 hover:text-white transition">${t("header.tournaments")}</a>

                        ${createLanguageSwitcher()}

                        <div class="relative group">
                            <button class="flex items-center space-x-2 text-gray-300 hover:text-white transition">
                                <span>${user.display_name || user.username}</span>
                                <svg class="w-4 h-4" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                                    <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 9l-7 7-7-7"></path>
                                </svg>
                            </button>

                            <div class="absolute right-0 mt-2 w-48 bg-gray-800 border border-gray-700 rounded-lg shadow-xl opacity-0 invisible group-hover:opacity-100 group-hover:visible transition-all">
                                <a href="/profile" data-link onclick="sessionStorage.removeItem('profileTargetId'); sessionStorage.removeItem('profileTarget')" class="block px-4 py-2 text-gray-300 hover:bg-gray-700 rounded-t-lg">${t("header.profile")}</a>
                                <button onclick="window.authService.logout()" class="w-full text-left px-4 py-2 text-red-400 hover:bg-gray-700 rounded-b-lg">
                                    ${t("header.logout")}
                                </button>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </nav>
    `;
}

export { initLanguageSwitcher } from './LanguageSwitcher';
