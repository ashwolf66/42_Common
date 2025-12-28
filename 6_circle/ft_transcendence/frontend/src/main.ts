import './styles/main.css';
import { Router } from './router/router.js';
import { AuthService } from './services/AuthService.js';
import ApiService from './services/ApiService.js';
import { createNavbar, initLanguageSwitcher } from './components/Navbar.js';
import { initL10n, onLanguageChange } from './l10n/index.js';

// Initialize app
class App {
    router: Router;
    authService: AuthService;
    languageSwitcherDispose?: () => void;

    constructor() {
        this.router = new Router();
        this.authService = new AuthService();
        this.init();
    }

    async init() {
        // Initialize i18n
        initL10n();

        // Listen for language changes and re-render current page
        // Register this BEFORE renderNavbar to ensure it's set up first
        onLanguageChange(() => {
            this.renderNavbar();
            this.router.handleRoute();
        });

        // Skip token validation on login/register pages
        const currentPath = window.location.pathname;
        if (currentPath !== '/login' && currentPath !== '/register') {
            // Check if user is logged in
            const token = this.authService.getToken();
            if (token) {
                // Validate token silently, don't redirect on failure
                await this.authService.validateToken().catch(() => {
                    // Silently ignore validation failures on init
                });
            }
        }

        // Create navbar
        this.renderNavbar();

        // Listen for auth changes
        window.addEventListener('auth-change', () => {
            this.renderNavbar();
        });

        // Initialize router
        this.router.init();
    }

    renderNavbar() {
        // Cleanup previous language switcher listeners
        if (this.languageSwitcherDispose) {
            this.languageSwitcherDispose();
            this.languageSwitcherDispose = undefined;
        }

        const existingNavbar = document.getElementById('navbar');
        if (existingNavbar) {
            existingNavbar.remove();
        }

        const navbarHtml = createNavbar(this.authService.isAuthenticated());
        const tempDiv = document.createElement('div');
        tempDiv.innerHTML = navbarHtml;
        const navbarElement = tempDiv.firstElementChild;

        if (navbarElement) {
            document.body.insertBefore(navbarElement, document.body.firstChild);
        }

        // Initialize language switcher after navbar is rendered
        this.languageSwitcherDispose = initLanguageSwitcher();
    }
}

// Start app when DOM is ready
document.addEventListener('DOMContentLoaded', () => {
    new App();
});

// Export for debugging
(window as any).authService = new AuthService();
(window as any).apiService = ApiService;
