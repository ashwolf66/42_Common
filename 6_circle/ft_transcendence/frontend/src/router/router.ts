import { HomePage } from '../pages/HomePage.js';
import { LoginPage } from '../pages/LoginPage.js';
import { RegisterPage } from '../pages/RegisterPage.js';
import { ProfilePage } from '../pages/ProfilePage.js';
import { GamePage } from '../pages/GamePage.js';
import { TournamentPage } from '../pages/TournamentPage.js';
import { TournamentDetailPage } from '../pages/TournamentDetailPage.js';
import { FriendsPage } from '../pages/FriendsPage.js';
import { NotFoundPage } from '../pages/NotFoundPage.js';
import { escapeHtml } from '../utils/sanitize.js';

export class Router {
    routes: any[];
    publicRoutes: string[];
    currentPage: any;

    constructor() {
        this.routes = [
            { path: '/', component: HomePage, exact: true },
            { path: '/login', component: LoginPage, exact: true },
            { path: '/register', component: RegisterPage, exact: true },
            { path: '/profile', component: ProfilePage, exact: true },
            { path: '/friends', component: FriendsPage, exact: true },
            { path: '/game', component: GamePage, exact: true },
            { path: '/game/local', component: GamePage, exact: true },
            { path: '/game/ai', component: GamePage, exact: true },
            { path: '/game/remote', component: GamePage, exact: true },
            { path: '/tournament', component: TournamentPage, exact: true },
            { path: '/tournament/:id', component: TournamentDetailPage, exact: false },
        ];

        this.publicRoutes = ['/', '/login', '/register'];
        this.currentPage = null;
    }

    init() {
        // Handle initial route
        this.handleRoute();

        // Listen for popstate (browser back/forward)
        window.addEventListener('popstate', () => this.handleRoute());

        // Intercept link clicks
        document.addEventListener('click', (e) => {
            const target = e.target as HTMLElement;
            if (target.matches('[data-link]')) {
                e.preventDefault();
                this.navigateTo(target.getAttribute('href') || '/');
            }
        });
    }

    navigateTo(path: string): void {
        history.pushState(null, '', path);
        this.handleRoute();
    }

    matchRoute(pathname: string): { component: any; params: Record<string, string> } {
        for (const route of this.routes) {
            const pattern = route.path.replace(/:[^\s/]+/g, '([^/]+)');
            const regex = new RegExp(`^${pattern}${route.exact ? '$' : ''}`);
            const match = pathname.match(regex);
            
            if (match) {
                const params: Record<string, string> = {};
                const paramNames = route.path.match(/:[^\s/]+/g);
                
                if (paramNames) {
                    paramNames.forEach((name: string, index: number) => {
                        params[name.slice(1)] = match[index + 1];
                    });
                }
                
                return { component: route.component, params };
            }
        }
        
        return { component: NotFoundPage, params: {} };
    }

    async handleRoute(): Promise<void> {
        const path = window.location.pathname;
        const { component: RouteComponent, params } = this.matchRoute(path);

        // Check authentication
        const token = localStorage.getItem('auth_token');
        const isAuthenticated = !!token;

        if (!isAuthenticated && !this.publicRoutes.includes(path)) {
            // Redirect to login
            history.pushState(null, '', '/login');
            this.renderPage(LoginPage, {});
            return;
        }

        if (isAuthenticated && (path === '/login' || path === '/register')) {
            // Redirect to home if already logged in
            history.pushState(null, '', '/');
            this.renderPage(HomePage, {});
            return;
        }

        this.renderPage(RouteComponent, params);
    }

    async renderPage(PageComponent: any, params: Record<string, string> = {}): Promise<void> {
        const app = document.getElementById('app');
        
        if (!app) {
            console.error('App element not found');
            return;
        }
        
        // Cleanup previous page
        if (this.currentPage && typeof this.currentPage.cleanup === 'function') {
            try {
                this.currentPage.cleanup();
            } catch (error) {
                console.error('Error during page cleanup:', error);
            }
        }
        
        // Fade out
        app.style.opacity = '0';
        
        await new Promise(resolve => setTimeout(resolve, 150));
        
        // Render new page
        try {
            // Pass params to constructor if route has parameters
            const page = Object.keys(params).length > 0 
                ? new PageComponent(...Object.values(params))
                : new PageComponent();
            
            // Store current page instance
            this.currentPage = page;
            
            // Make page instance available globally for event handlers
            if (PageComponent.name === 'FriendsPage') {
                (window as any).friendsPage = page;
            }
            
            app.innerHTML = await page.render();
            
            // Run page lifecycle methods
            if (page.onMount) {
                await page.onMount();
            }
        } catch (error: any) {
            console.error('Error rendering page:', error);
            app.innerHTML = `
                <div class="container mx-auto px-4 py-8">
                    <div class="card bg-red-900 border border-red-700">
                        <h2 class="text-2xl font-bold mb-4">Error</h2>
                        <p>${escapeHtml(error.message || 'An unknown error occurred')}</p>
                    </div>
                </div>
            `;
        }
        
        // Fade in
        app.style.opacity = '1';
        app.style.transition = 'opacity 0.15s';
    }
}

// Export navigate function for use in other modules
export function navigate(path: string): void {
    window.history.pushState({}, '', path);
    window.dispatchEvent(new PopStateEvent('popstate'));
}
