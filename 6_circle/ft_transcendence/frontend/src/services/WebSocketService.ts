// Use relative URL in development to ensure Vite proxy handles WebSocket connections
const env = (import.meta as any).env || {};
let WS_BASE_URL = env.MODE === 'development' ? '' : (env.VITE_WS_URL || 'wss://localhost:4000');

// WebSocket constructor requires absolute URL
if (WS_BASE_URL === '' || WS_BASE_URL.startsWith('/')) {
    const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
    const host = window.location.host;
    WS_BASE_URL = `${protocol}//${host}${WS_BASE_URL}`;
}

export class WebSocketService {
    ws: WebSocket | null;
    roomId: string | null;
    authenticated: boolean;
    reconnectAttempts: number;
    maxReconnectAttempts: number;
    reconnectDelay: number;
    messageHandlers: Map<string, Array<(data: any) => void>>;

    constructor() {
        this.ws = null;
        this.roomId = null;
        this.authenticated = false;
        this.reconnectAttempts = 0;
        this.maxReconnectAttempts = 5;
        this.reconnectDelay = 1000;
        this.messageHandlers = new Map();
    }

    connect(token: string): Promise<void> {
        return new Promise((resolve, reject) => {
            try {
                this.ws = new WebSocket(`${WS_BASE_URL}/ws/game`);

                this.ws.onopen = () => {
                    console.log('WebSocket connected');
                    // Authenticate
                    this.send({ type: 'auth', token });
                };

                this.ws.onmessage = (event) => {
                    const data = JSON.parse(event.data);
                    
                    if (data.type === 'authenticated') {
                        this.authenticated = true;
                        this.reconnectAttempts = 0;
                        resolve();
                    } else if (data.type === 'error') {
                        console.error('WebSocket error:', data.message);
                        if (!this.authenticated) {
                            reject(new Error(data.message));
                        }
                    }

                    // Call registered handlers
                    if (this.messageHandlers.has(data.type)) {
                        const handlers = this.messageHandlers.get(data.type);
                        if (handlers) {
                            handlers.forEach(handler => handler(data));
                        }
                    }
                };

                this.ws.onerror = (error) => {
                    console.error('WebSocket error:', error);
                    reject(error);
                };

                this.ws.onclose = (event) => {
                    console.log('WebSocket closed', event.code, event.reason);
                    if (!this.authenticated) {
                        reject(new Error(`Connection closed before authentication (Code: ${event.code})`));
                    }
                    this.authenticated = false;
                    
                    // Attempt to reconnect only if not manually closed
                    if (this.reconnectAttempts < this.maxReconnectAttempts && event.code !== 1000) {
                        this.reconnectAttempts++;
                        setTimeout(() => {
                            const token = localStorage.getItem('auth_token');
                            if (token) {
                                this.connect(token).catch(console.error);
                            }
                        }, this.reconnectDelay * this.reconnectAttempts);
                    }
                };
            } catch (error) {
                console.error('WebSocket connection error:', error);
                reject(error);
            }
        });
    }

    disconnect(): void {
        if (this.ws) {
            this.ws.onclose = null; // Prevent reconnect
            this.ws.close(1000, 'Client disconnected');
            this.ws = null;
            this.authenticated = false;
        }
    }

    send(message: any): void {
        if (this.ws && this.ws.readyState === WebSocket.OPEN) {
            this.ws.send(JSON.stringify(message));
        } else {
            console.error('WebSocket is not open');
        }
    }

    on(messageType: string, handler: (data: any) => void): void {
        if (!this.messageHandlers.has(messageType)) {
            this.messageHandlers.set(messageType, []);
        }
        this.messageHandlers.get(messageType)!.push(handler);
    }

    off(messageType: string, handler: (data: any) => void): void {
        if (this.messageHandlers.has(messageType)) {
            const handlers = this.messageHandlers.get(messageType)!;
            const index = handlers.indexOf(handler);
            if (index > -1) {
                handlers.splice(index, 1);
            }
        }
    }

    createRoom(tournamentId: number | null = null, matchId: number | null = null, roomName: string | null = null, gameMode: string = 'classic'): void {
        this.send({ type: 'createRoom', tournamentId, matchId, roomName, gameMode });
    }

    joinRoom(roomId: string, roomName?: string): void {
        this.roomId = roomId;
        this.send({ type: 'joinRoom', roomId, roomName });
    }

    sendPaddleMove(direction: string): void {
        this.send({ type: 'paddleMove', direction });
    }

    listRooms(): void {
        this.send({ type: 'listRooms' });
    }
}
