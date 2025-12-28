// Use relative URL in development to ensure Vite proxy handles API requests and avoid CORS
const env = (import.meta as any).env || {};
const API_BASE_URL = env.MODE === 'development' ? '' : (env.VITE_API_URL || '');

interface RequestOptions extends RequestInit {
    headers?: Record<string, string>;
}

class ApiService {
    baseUrl: string;

    constructor() {
        this.baseUrl = `${API_BASE_URL}/api`;
    }

    getAuthHeaders(): Record<string, string> {
        const token = localStorage.getItem('auth_token');
        const headers: Record<string, string> = {
            ...(token && { 'Authorization': `Bearer ${token}` })
        };
        
        return headers;
    }

    async request(endpoint: string, options: RequestOptions = {}): Promise<any> {
        const url = `${this.baseUrl}${endpoint}`;
        
        const config = {
            ...options,
            headers: {
                ...this.getAuthHeaders(),
                ...options.headers
            }
        };
        
        // Only set Content-Type if there's a body
        if (config.body) {
            config.headers['Content-Type'] = 'application/json';
        }

        try {
            const response = await fetch(url, config);

            // Read raw text first to handle empty responses
            const text = await response.text();
            let data: any = null;

            if (text && text.length > 0) {
                try {
                    data = JSON.parse(text);
                } catch (err) {
                    // If response is not valid JSON, return raw text
                    data = text;
                }
            }

            if (!response.ok) {
                // Throw an error object that includes both the response data and status
                const error: any = new Error(
                    (data && (data.error || data.errorCode))
                        ? (data.error || data.errorCode)
                        : `HTTP error! status: ${response.status}`
                );
                error.response = { data, status: response.status };
                throw error;
            }

            return data;
        } catch (error) {
            // Only log errors for non-auth validation requests
            if (!endpoint.includes('/users/me')) {
                console.error('API Request Error:', error);
            }
            throw error;
        }
    }

    async get(endpoint: string): Promise<any> {
        return this.request(endpoint, { method: 'GET' });
    }

    async post(endpoint: string, body?: any): Promise<any> {
        const options: RequestOptions = {
            method: 'POST'
        };
        
        // Only add body if provided
        if (body !== undefined && body !== null) {
            options.body = JSON.stringify(body);
        }
        
        return this.request(endpoint, options);
    }

    async put(endpoint: string, body: any): Promise<any> {
        return this.request(endpoint, {
            method: 'PUT',
            body: JSON.stringify(body)
        });
    }

    async delete(endpoint: string): Promise<any> {
        return this.request(endpoint, { method: 'DELETE' });
    }
}

export default new ApiService();
