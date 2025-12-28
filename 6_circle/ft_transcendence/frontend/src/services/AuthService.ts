import ApiService from './ApiService.js';

interface User {
    id: number;
    username: string;
    display_name?: string;
    [key: string]: any;
}

export class AuthService {
    token: string | null;
    user: User | null;

    constructor() {
        this.token = localStorage.getItem('auth_token');
        this.user = JSON.parse(localStorage.getItem('user') || 'null');
    }

    isAuthenticated() {
        return !!this.token && !!this.user;
    }

    getToken() {
        return this.token;
    }

    getUser() {
        return this.user;
    }

    async register(userData: any): Promise<any> {
        const response = await ApiService.post('/auth/register', userData);
        return response;
    }

    async login(username: string, password: string, twofa_code: string | null = null): Promise<any> {
        const response = await ApiService.post('/auth/login', { 
            username, 
            password, 
            twofa_code 
        });

        if (response.requires_2fa) {
            return { requires_2fa: true };
        }

        if (response.token) {
            this.setAuth(response.token, response.user);
        }

        return response;
    }

    async logout() {
        try {
            await ApiService.post('/auth/logout');
        } catch (error) {
            console.error('Logout error:', error);
        } finally {
            this.clearAuth();
        }
    }

    setAuth(token: string, user: User): void {
        this.token = token;
        this.user = user;
        localStorage.setItem('auth_token', token);
        localStorage.setItem('user', JSON.stringify(user));
        this.emitAuthChange();
    }

    clearAuth() {
        this.token = null;
        this.user = null;
        localStorage.removeItem('auth_token');
        localStorage.removeItem('user');
        this.emitAuthChange();
        window.location.href = '/';
    }

    async validateToken() {
        try {
            const response = await ApiService.get('/users/me');
            this.user = response.user;
            localStorage.setItem('user', JSON.stringify(response.user));
            return true;
        } catch (error) {
            // Silently clear invalid token without logging
            this.token = null;
            this.user = null;
            localStorage.removeItem('auth_token');
            localStorage.removeItem('user');
            return false;
        }
    }

    async setup2FA() {
        return await ApiService.post('/auth/2fa/setup');
    }

    async verify2FA(token: string): Promise<any> {
        return await ApiService.post('/auth/2fa/verify', { token });
    }

    async disable2FA(password: string): Promise<any> {
        return await ApiService.post('/auth/2fa/disable', { password });
    }

    emitAuthChange() {
        window.dispatchEvent(new CustomEvent('auth-change', { 
            detail: { authenticated: this.isAuthenticated(), user: this.user } 
        }));
    }
}
