import { GameEngine, DEFAULT_RENDER_MODE, RenderMode, isRenderMode  } from '../game/GameEngine.js';
import { WebSocketService } from '../services/WebSocketService.js';
import ApiService from '../services/ApiService';
import { t } from '../l10n/index';

interface Room {
    id: string;
    name: string;
    playerCount: number;
    maxPlayers: number;
    [key: string]: any;
}

export class GamePage {
    ws: WebSocketService | null;
    remoteGame: GameEngine | null;
    roomId: string | null;
    rooms: Room[];
    roomsRefreshInterval: number | null;
    game?: GameEngine;
    localGame?: GameEngine;
    aiGame?: GameEngine;
    gameConfig?: any;
    playerPosition?: number;
    opponentId?: string;
    remoteKeyDownHandler?: (e: KeyboardEvent) => void;
    remoteKeyUpHandler?: (e: KeyboardEvent) => void;
    handleGameEnd?: (event: CustomEvent) => void;
    serverObstacles?: any[];
    serverGameMode?: string;
    renderMode: RenderMode;
    renderModeKeyHandler?: (e: KeyboardEvent) => void;

    constructor() {
        this.ws = null;
        this.remoteGame = null;
        this.roomId = null;
        this.rooms = [];
        this.roomsRefreshInterval = null;
        this.renderMode = DEFAULT_RENDER_MODE;
    }

    async render() {
        const path = window.location.pathname;
        let mode = 'local';
        let title = t("game.local.title");
        let instructions = t("game.local.instructions");

        if (path.includes('/ai')) {
            mode = 'ai';
            title = t("game.ai.title");
            instructions = t("game.ai.instructions");
        } else if (path.includes('/remote')) {
            mode = 'remote';
            title = t("game.remote.title");
            instructions = t("game.remote.instructions");
            
            // Show room lobby instead of game canvas
            return `
                <div class="container mx-auto px-4 py-8">
                    <div class="max-w-6xl mx-auto">
                        <div class="flex justify-between items-center mb-6">
                            <div>
                                <h1 class="text-3xl font-bold">${title}</h1>
                                <p class="text-gray-400 text-sm mt-1">${instructions}</p>
                            </div>
                            <a href="/" data-link class="btn btn-secondary">${t("game.exitButton")}</a>
                        </div>

                        <div class="grid grid-cols-1 lg:grid-cols-3 gap-6">
                            <div class="lg:col-span-2">
                                <div class="card">
                                    <h2 class="text-2xl font-bold mb-4">${t("game.remote.availableRooms")}</h2>
                                    <div id="roomsList">
                                        <div class="spinner"></div>
                                    </div>
                                </div>
                            </div>

                            <div>
                                <div class="card mb-6">
                                    <h2 class="text-2xl font-bold mb-4">${t("game.remote.createRoom")}</h2>
                                    <div class="mb-4">
                                        <h3 class="text-sm font-bold mb-2">${t("game.gameModeLabel")}</h3>
                                        <div class="flex space-x-2 mb-4">
                                            <button class="remote-gamemode-btn btn btn-primary text-sm flex-1" data-gamemode="classic">${t("game.modes.classic")}</button>
                                            <button class="remote-gamemode-btn btn btn-secondary text-sm flex-1" data-gamemode="custom">${t("game.modes.custom")}</button>
                                        </div>
                                    </div>
                                    <button id="createRoomBtn" class="btn btn-primary w-full">${t("game.remote.createNewRoom")}</button>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            `;
        }

        return `
            <div class="container mx-auto px-4 py-8">
                <div class="max-w-4xl mx-auto">
                    <div class="flex justify-between items-center mb-6">
                        <div>
                            <h1 class="text-3xl font-bold">${title}</h1>
                            <p class="text-gray-400 text-sm mt-1" id="pageInstructions">${instructions}</p>
                        </div>
                        <a href="/" data-link class="btn btn-secondary">${t("game.exitButton")}</a>
                    </div>

                    ${this.renderGameModeSelector()}
                    ${mode === 'ai' ? this.renderDifficultySelector() : ''}

                    <div class="card text-center">
                        <div class="mb-4" id="canvasContainer">
                            <canvas id="gameCanvas"></canvas>
                        </div>

                        <div class="flex justify-center space-x-4 ${mode === 'remote' ? 'hidden' : ''}" id="gameControls">
                            <button id="resetBtn" class="btn btn-secondary">${t("game.resetButton")}</button>
                        </div>

                        <div id="gameStatus" class="mt-4 text-gray-400">${mode === 'remote' ? t("game.remote.connecting") : t("game.pressSpaceToStart")}</div>
                    </div>
                </div>
            </div>
        `;
    }

    renderDifficultySelector() {
        return `
            <div class="card mb-6">
                <h3 class="text-lg font-bold mb-3">${t("game.ai.selectDifficulty")}</h3>
                <div class="flex justify-center space-x-4">
                    <button class="difficulty-btn btn btn-secondary" data-difficulty="easy">${t("game.ai.easy")}</button>
                    <button class="difficulty-btn btn btn-primary" data-difficulty="medium">${t("game.ai.medium")}</button>
                    <button class="difficulty-btn btn btn-secondary" data-difficulty="hard">${t("game.ai.hard")}</button>
                </div>
            </div>
        `;
    }

    renderGameModeSelector() {
        return `
            <div class="card mb-6">
                <h3 class="text-lg font-bold mb-3">${t("game.gameModeLabel")}</h3>
                <div class="flex justify-center space-x-4 mb-4">
                    <button class="gamemode-btn btn btn-primary" data-gamemode="classic">${t("game.modes.classic")}</button>
                    <button class="gamemode-btn btn btn-secondary" data-gamemode="custom">${t("game.modes.customWithObstacles")}</button>
                </div>
                <div class="border-t border-gray-700 pt-4 mt-4">
                    <h3 class="text-lg font-bold mb-3">${t("game.renderModeLabel")}</h3>
                    <div class="flex justify-center space-x-4">
                        <button class="rendermode-btn btn btn-primary" data-rendermode="2d">${t("game.renderModes.2d")}</button>
                        <button class="rendermode-btn btn btn-secondary" data-rendermode="3d">${t("game.renderModes.3d")}</button>
                    </div>
                </div>
            </div>
        `;
    }

    async recreateGame(mode: string, difficulty: string, gameMode: string, preserveState: boolean = false) {
        const canvas = document.getElementById('gameCanvas') as HTMLCanvasElement | null;
        if (!canvas) {
            console.error('Game canvas not found');
            return;
        }
        const previousState = preserveState && this.game ? this.game.getState() : null;
        if (this.game) {
            this.game.stop();
            this.game = undefined;
        }
        const parent = canvas.parentElement;
        const newCanvas = document.createElement('canvas');
        newCanvas.id = 'gameCanvas';
        newCanvas.className = canvas.className;
        newCanvas.width = 800;
        newCanvas.height = 600;
        newCanvas.style.cssText = 'width: 800px; height: 600px; border: 2px solid #374151; border-radius: 8px; background-color: #111827; display: block; position: relative; margin: 0 auto;';
        if (!parent) {
            console.error('Canvas parent not found');
            return;
        }
        parent.replaceChild(newCanvas, canvas);
        const gameStatus = document.getElementById('gameStatus');
        const resetBtn = document.getElementById('resetBtn');
        if (this.renderMode === '3d') {
            if (gameStatus) gameStatus.style.display = 'none';
            if (resetBtn) resetBtn.style.display = 'inline-block';
            try {
                this.game = new GameEngine(newCanvas, mode, difficulty, gameMode, '3d');
                this.game.init();
                this.game.start();
                if (previousState) {
                    this.game.setState(previousState);
                }
            } catch (error: any) {
                console.error('Failed to initialize 3D game:', error);
                alert('3D 모드를 시작할 수 없습니다.\n\n' +
                      '원인: ' + (error.message || 'WebGL이 지원되지 않습니다') + '\n\n' +
                      '해결 방법:\n' +
                      '1. Chrome 설정 → 시스템 → "하드웨어 가속 사용" 활성화\n' +
                      '2. chrome://flags에서 WebGL 활성화\n' +
                      '3. 그래픽 드라이버 업데이트\n' +
                      '4. 다른 브라우저 사용\n\n' +
                      '2D 모드로 전환합니다.');
                // Fallback to 2D mode
                this.renderMode = DEFAULT_RENDER_MODE;
                const renderModeBtns = document.querySelectorAll('.rendermode-btn');
                renderModeBtns.forEach(btn => {
                    if (btn.getAttribute('data-rendermode') === '2d') {
                        btn.classList.add('btn-primary');
                        btn.classList.remove('btn-secondary');
                    } else {
                        btn.classList.remove('btn-primary');
                        btn.classList.add('btn-secondary');
                    }
                });
                this.game = new GameEngine(newCanvas, mode, difficulty, gameMode, DEFAULT_RENDER_MODE);
                this.game.init();
                this.game.start();
                if (previousState) {
                    this.game.setState(previousState);
                }
            }
        } else {
            // Show 2D UI elements
            if (gameStatus) gameStatus.style.display = 'block';
            if (resetBtn) resetBtn.style.display = 'inline-block';

            this.game = new GameEngine(newCanvas, mode, difficulty, gameMode, DEFAULT_RENDER_MODE);
            this.game.init();
            this.game.start();
            if (previousState) {
                this.game.setState(previousState);
            }
        }
    }

    async onMount() {
        const path = window.location.pathname;
        let mode = 'local';
        let difficulty = 'medium';
        let gameMode = 'classic'; // classic or custom

        if (path.includes('/ai')) {
            mode = 'ai';
        } else if (path.includes('/remote')) {
            mode = 'remote';
            
            // Check if joining a specific room
            const urlParams = new URLSearchParams(window.location.search);
            const roomId = urlParams.get('room');
            const tournamentId = urlParams.get('tournament');
            const matchId = urlParams.get('match');
            const createRoom = urlParams.get('create');
            
            if (roomId || (tournamentId && matchId) || createRoom) {
                // Join specific room, tournament match, or create new room
                this.setupRemoteGame();
            } else {
                // Show room lobby
                this.setupRoomLobby();
            }
            return;
        }

        const canvas = document.getElementById('gameCanvas') as HTMLCanvasElement | null;
        const resetBtn = document.getElementById('resetBtn');
        const gameStatus = document.getElementById('gameStatus');

        // Check if elements exist
        if (!canvas || !resetBtn || !gameStatus) {
            console.error('Game elements not found');
            return;
        }
        // Set canvas size
        canvas.width = 800;
        canvas.height = 600;
        canvas.style.cssText = 'width: 800px; height: 600px; border: 2px solid #374151; border-radius: 8px; background-color: #111827; display: block; position: relative; margin: 0 auto;';
        // Render mode selector (2D vs 3D)
        const renderModeBtns = document.querySelectorAll('.rendermode-btn');
        const applyRenderMode = async (nextMode: RenderMode) => {
            const previousState = this.game?.getState() || null;
            this.renderMode = nextMode;
            renderModeBtns.forEach(b => b.classList.remove('btn-primary'));
            renderModeBtns.forEach(b => b.classList.add('btn-secondary'));
            renderModeBtns.forEach(b => {
                if (b.getAttribute('data-rendermode') === nextMode) {
                    b.classList.remove('btn-secondary');
                    b.classList.add('btn-primary');
                }
            });
            await this.recreateGame(mode, difficulty, gameMode, true);
            if (!previousState?.started || previousState.gameOver) {
                gameStatus.textContent = t('game.pressSpaceToStart');
            }
        };
        renderModeBtns.forEach(btn => {
            btn.addEventListener('click', async () => {
                const nextRenderMode = btn.getAttribute('data-rendermode');
                await applyRenderMode(isRenderMode(nextRenderMode) ? nextRenderMode : DEFAULT_RENDER_MODE);
            });
        });
        this.renderModeKeyHandler = async (e: KeyboardEvent) => {
            if (e.key !== 'Tab' || e.repeat) {
                return;
            }
            e.preventDefault();
            const nextRenderMode = this.renderMode === '2d' ? '3d' : '2d';
            await applyRenderMode(nextRenderMode);
        };
        window.addEventListener('keydown', this.renderModeKeyHandler);

        // Game mode selector (Classic vs Custom)
        const gameModeBtns = document.querySelectorAll('.gamemode-btn');
        gameModeBtns.forEach(btn => {
            btn.addEventListener('click', async () => {
                gameMode = btn.getAttribute('data-gamemode') || 'classic';
                gameModeBtns.forEach(b => b.classList.remove('btn-primary'));
                gameModeBtns.forEach(b => b.classList.add('btn-secondary'));
                btn.classList.remove('btn-secondary');
                btn.classList.add('btn-primary');
                // Recreate game with new game mode
                await this.recreateGame(mode, difficulty, gameMode);
                gameStatus.textContent = t('game.pressSpaceToStart');
            });
        });

        // Difficulty selector for AI mode
        if (mode === 'ai') {
            const difficultyBtns = document.querySelectorAll('.difficulty-btn');
            difficultyBtns.forEach(btn => {
                btn.addEventListener('click', async () => {
                    difficulty = btn.getAttribute('data-difficulty') || 'medium';
                    difficultyBtns.forEach(b => b.classList.remove('btn-primary'));
                    difficultyBtns.forEach(b => b.classList.add('btn-secondary'));
                    btn.classList.remove('btn-secondary');
                    btn.classList.add('btn-primary');
                    // Recreate game with new difficulty
                    await this.recreateGame(mode, difficulty, gameMode);
                    gameStatus.textContent = t('game.pressSpaceToStart');
                });
            });
        }

        // Initialize and start game
        await this.recreateGame(mode, difficulty, gameMode);

        // Reset button
        resetBtn.addEventListener('click', async () => {
            await this.recreateGame(mode, difficulty, gameMode);
            gameStatus.textContent = t('game.pressSpaceToStart');
        });

        // Listen for game end
        window.addEventListener('game-end', async (e: Event) => {
            const customEvent = e as CustomEvent;
            const { winner, score, mode: gameMode, difficulty: gameDifficulty } = customEvent.detail;
            
            const winnerText = winner === 'player1' ? t('game.status.player1') : (gameMode === 'ai' ? t('game.status.ai') : t('game.status.player2'));
            gameStatus.innerHTML = `
                <div class="text-xl font-bold text-green-400 mb-2">
                    ${t('game.status.winner', { winner: winnerText })}
                </div>
                <div class="text-gray-400">
                    ${t('game.status.finalScore', { player1: score.player1, player2: score.player2 })}
                </div>
            `;

            // Save game result to backend
            await this.saveGameResult(score, gameMode, gameDifficulty);
        });
    }

    async setupRoomLobby(): Promise<void> {
        try {
            // Initialize WebSocket
            this.ws = new WebSocketService();
            const token = localStorage.getItem('auth_token');
            if (!token) {
                throw new Error('No authentication token found');
            }
            await this.ws.connect(token);

            // Load rooms
            await this.loadRooms();

            // Game mode selection for remote games
            let selectedGameMode = 'classic';
            const gameModeBtns = document.querySelectorAll('.remote-gamemode-btn');
            gameModeBtns.forEach(btn => {
                btn.addEventListener('click', () => {
                    selectedGameMode = btn.getAttribute('data-gamemode') || 'classic';
                    gameModeBtns.forEach(b => b.classList.remove('btn-primary'));
                    gameModeBtns.forEach(b => b.classList.add('btn-secondary'));
                    btn.classList.remove('btn-secondary');
                    btn.classList.add('btn-primary');
                });
            });

            // Set up create room button
            const createRoomBtn = document.getElementById('createRoomBtn');
            if (createRoomBtn) {
                createRoomBtn.addEventListener('click', () => {
                    // Clear refresh interval
                    if (this.roomsRefreshInterval) {
                        clearInterval(this.roomsRefreshInterval);
                        this.roomsRefreshInterval = null;
                    }
                    
                    // Navigate to game with create parameter and game mode
                    const roomName = prompt('Enter room name (leave empty to use your username):');
                    const nameParam = roomName && roomName.trim() !== '' ? `&name=${encodeURIComponent(roomName)}` : '';
                    const gameModeParam = `&gameMode=${selectedGameMode}`;
                    window.history.pushState({}, '', `/game/remote?create=true${nameParam}${gameModeParam}`);
                    
                    // Re-render and setup game
                    this.render().then(html => {
                        const app = document.getElementById('app');
                        if (app) {
                            app.innerHTML = html;
                            this.setupRemoteGame();
                        }
                    });
                });
            }

            // Refresh rooms every 3 seconds
            this.roomsRefreshInterval = setInterval(() => {
                this.loadRooms();
            }, 3000);

        } catch (error) {
            console.error('Failed to setup room lobby:', error);
            const roomsList = document.getElementById('roomsList');
            if (roomsList) {
                roomsList.innerHTML = `
                    <div class="text-red-400 text-center py-8">
                        ${t("game.remote.connectionFailed")}
                    </div>
                `;
            }
        }
    }

    async loadRooms() {
        if (!this.ws) return;

        this.ws.listRooms();
        
        // Wait for room list response
        this.ws.on('roomList', (data) => {
            this.rooms = data.rooms || [];
            this.renderRoomList();
        });
    }

    renderRoomList() {
        const roomsList = document.getElementById('roomsList');
        if (!roomsList) return;

        if (this.rooms.length === 0) {
            roomsList.innerHTML = `
                <p class="text-gray-400 text-center py-8">${t("game.remote.noRooms")}</p>
            `;
            return;
        }

        roomsList.innerHTML = this.rooms.map((room, index) => `
            <div class="border-b border-gray-700 py-4 last:border-0">
                <div class="flex justify-between items-center">
                    <div>
                        <h3 class="font-bold text-lg">${room.name || `Room ${index + 1}`}</h3>
                        <p class="text-gray-400 text-sm">
                            ${room.players}/2 ${t("game.remote.players")} |
                            <span class="badge badge-warning">${t("game.remote.waiting")}</span>
                        </p>
                    </div>
                    <button class="btn btn-primary btn-sm join-room-btn" data-room-id="${room.id}">
                        ${t("game.remote.joinButton")}
                    </button>
                </div>
            </div>
        `).join('');

        // Add event listeners to join buttons
        document.querySelectorAll('.join-room-btn').forEach(btn => {
            btn.addEventListener('click', (e) => {
                const roomId = (e.target as HTMLElement).getAttribute('data-room-id');
                
                // Clear refresh interval
                if (this.roomsRefreshInterval) {
                    clearInterval(this.roomsRefreshInterval);
                    this.roomsRefreshInterval = null;
                }
                
                // Navigate to game with room ID
                window.history.pushState({}, '', `/game/remote?room=${roomId}`);
                
                // Re-render and setup game
                this.render().then(html => {
                    const app = document.getElementById('app');
                    if (app) {
                        app.innerHTML = html;
                        this.setupRemoteGame();
                    }
                });
            });
        });
    }

    // These methods are no longer needed but kept for reference
    createRoom(roomName: string | null): void {
        const name = roomName || 'Room';
        window.history.pushState({}, '', `/game/remote?create=true&name=${encodeURIComponent(name)}`);
    }

    joinRoom(roomId: string): void {
        window.history.pushState({}, '', `/game/remote?room=${roomId}`);
    }

    async setupRemoteGame(): Promise<void> {
        // For actual game play, we need to render the game canvas
        const gameContainer = document.querySelector('.max-w-6xl');
        if (!gameContainer) {
            console.error('Game container not found');
            return;
        }
        
        gameContainer.innerHTML = `
                <div class="flex justify-between items-center mb-6">
                    <div>
                        <h1 class="text-3xl font-bold">${t("game.remote.title")}</h1>
                        <p class="text-gray-400 text-sm mt-1" id="pageInstructions">${t("game.remote.connecting")}</p>
                    </div>
                    <a href="/game/remote" data-link class="btn btn-secondary">${t("game.remote.backToLobby")}</a>
                </div>

                <div class="card text-center">
                    <div class="mb-4" id="canvasContainer">
                        <canvas id="gameCanvas"></canvas>
                    </div>
                    <div id="gameStatus" class="mt-4 text-gray-400">${t("game.remote.connecting")}</div>
                </div>
            `;

        const gameStatus = document.getElementById('gameStatus');
        const canvas = document.getElementById('gameCanvas') as HTMLCanvasElement | null;
        const pageInstructions = document.getElementById('pageInstructions');
        
        if (!gameStatus || !canvas) {
            console.error('Game elements not found');
            return;
        }

        // Get parameters from URL
        const urlParams = new URLSearchParams(window.location.search);
        const tournamentId = urlParams.get('tournament');
        const matchId = urlParams.get('match');
        const roomParam = urlParams.get('room'); // This can be roomId or roomName
        const createRoom = urlParams.get('create');
        const roomName = urlParams.get('name');
        const inviter = urlParams.get('inviter');
        const gameMode = urlParams.get('gameMode') || 'classic';

        gameStatus.innerHTML = `<div class="text-yellow-400">${t("game.remote.connectingToServer")}</div>`;

        try {
            // Initialize WebSocket
            if (this.ws) {
                this.ws.disconnect();
            }
            this.ws = new WebSocketService();
            const token = localStorage.getItem('auth_token');
            if (!token) {
                console.error('No authentication token found');
                gameStatus.innerHTML = `<div class="text-red-400">${t("game.remote.error", { message: "No authentication token" })}</div>`;
                return;
            }

            await this.ws.connect(token);

            if (tournamentId && matchId) {
                // Tournament match
                gameStatus.innerHTML = `<div class="text-yellow-400">${t("game.remote.connectingToMatch")}</div>`;
                this.ws.createRoom(parseInt(tournamentId), parseInt(matchId), null, gameMode);
            } else if (roomParam) {
                // Join or create room
                // If inviter is present, this is from an invite - try to create/join by name
                if (inviter) {
                    gameStatus.innerHTML = `<div class="text-yellow-400">${t("game.remote.joiningRoom")}</div>`;
                    // First try to join existing room, if not found create it
                    this.ws.createRoom(null, null, roomParam, gameMode);
                } else {
                    // Regular join by room ID
                    gameStatus.innerHTML = `<div class="text-yellow-400">${t("game.remote.joiningRoom")}</div>`;
                    this.ws.joinRoom(roomParam, roomParam);
                }
            } else if (createRoom) {
                // Create new room
                gameStatus.innerHTML = `<div class="text-yellow-400">${t("game.remote.creatingRoom")}</div>`;
                // Pass gameMode from URL parameter
                this.ws.createRoom(null, null, roomName || null, gameMode);
            } else {
                // Should not reach here
                gameStatus.innerHTML = `<div class="text-red-400">${t("game.remote.error", { message: "Invalid game mode" })}</div>`;
                return;
            }

            // WebSocket message handlers
            this.ws.on('roomList', () => {
                // Not used in game mode
            });

            this.ws.on('roomCreated', (data) => {
                this.roomId = data.roomId;
                this.gameConfig = data.config;
                
                // Initialize game in waiting state
                this.remoteGame = new GameEngine(canvas as HTMLCanvasElement, 'remote');
                this.remoteGame.init();
                
                const isTournamentMatch = data.tournamentId && data.matchId;
                const roomName = data.roomName || 'Game Room';
                
                if (pageInstructions) {
                    pageInstructions.textContent = isTournamentMatch
                        ? t("game.remote.instructions")
                        : `${roomName} - ${t("game.remote.waitingForOpponent")}`;
                }

                if (isTournamentMatch) {
                    gameStatus.innerHTML = `
                        <div class="text-yellow-400">
                            <div class="mb-2">${t("game.remote.tournamentMatchReady")}</div>
                            <div class="text-xs text-gray-400 mt-2">${t("game.remote.waitingForOpponent")}</div>
                        </div>
                    `;
                } else {
                    gameStatus.innerHTML = `
                        <div class="text-yellow-400">
                            <div class="mb-2 text-xl font-bold">${roomName}</div>
                            <div class="text-sm">${t("game.remote.roomCreated")}</div>
                            <div class="text-xs text-gray-400 mt-2">${t("game.remote.waitingForOpponent")}</div>
                        </div>
                    `;
                }
            });

            this.ws.on('gameStart', (data) => {
                this.gameConfig = data.config;
                this.playerPosition = data.playerPosition; // 'player1' or 'player2'
                this.opponentId = data.opponentId;
                
                // Store obstacles and gameMode from server
                if (data.obstacles) {
                    this.serverObstacles = data.obstacles;
                }
                if (data.gameMode) {
                    this.serverGameMode = data.gameMode;
                }
                
                if (pageInstructions) {
                    pageInstructions.textContent = t("game.remote.instructionsPlaying");
                }
                this.startRemoteGame(canvas, gameStatus);
            });

            this.ws.on('gameState', (data) => {
                if (this.remoteGame) {
                    this.remoteGame.updateRemoteState(data.state);
                }
            });

            this.ws.on('gameEnd', (data) => {
                // Stop the game and hide canvas
                if (this.remoteGame) {
                    this.remoteGame.stop();
                }
                
                const canvas = document.getElementById('gameCanvas') as HTMLCanvasElement;
                if (canvas) {
                    canvas.style.display = 'none';
                }
                
                const user = JSON.parse(localStorage.getItem('user') || '{}');
                const isWinner = data.winner === user.id;
                const isForfeit = data.forfeit === true;
                
                let winnerText = isWinner ? t("game.remote.youWin") : t("game.remote.youLose");
                let winnerSubtext = '';

                if (isForfeit) {
                    winnerText = isWinner ? t("game.remote.victoryByForfeit") : t("game.remote.defeatByForfeit");
                    winnerSubtext = isWinner ? t("game.remote.opponentLeft") : t("game.remote.youLeftGame");
                }

                // Determine scores based on player position
                let myScore, opponentScore;
                if (data.playerPosition === 'player1') {
                    myScore = data.score.player1;
                    opponentScore = data.score.player2;
                } else {
                    myScore = data.score.player2;
                    opponentScore = data.score.player1;
                }

                if (pageInstructions) {
                    pageInstructions.textContent = t("game.remote.gameFinished");
                }
                
                const urlParams = new URLSearchParams(window.location.search);
                const tournamentId = urlParams.get('tournament');
                
                gameStatus.innerHTML = `
                    <div class="text-xl font-bold ${isWinner ? 'text-green-400' : 'text-red-400'} mb-2">
                        ${winnerText}
                    </div>
                    ${winnerSubtext ? `<div class="text-sm text-gray-400 mb-2">${winnerSubtext}</div>` : ''}
                    <div class="text-gray-400 mb-4">
                        ${t("game.remote.finalScore", { myScore, opponentScore })}
                    </div>
                    <div>
                        ${tournamentId ?
                            `<a href="/tournament/${tournamentId}" data-link class="btn btn-primary">${t("game.remote.backToTournament")}</a>` :
                            `<a href="/game/remote" data-link class="btn btn-primary">${t("game.remote.playAgain")}</a>`
                        }
                    </div>
                `;

                // Game result is saved on server side, no need to save from client
            });

            this.ws.on('opponentDisconnected', () => {
                // Stop the game
                if (this.remoteGame) {
                    this.remoteGame.stop();
                }
                
                // Hide the canvas
                const canvas = document.getElementById('gameCanvas') as HTMLCanvasElement;
                if (canvas) {
                    canvas.style.display = 'none';
                }
                
                if (pageInstructions) {
                    pageInstructions.textContent = t("game.remote.opponentDisconnected");
                }

                // Check if this is a tournament game
                const urlParams = new URLSearchParams(window.location.search);
                const tournamentId = urlParams.get('tournament');

                gameStatus.innerHTML = `
                    <div class="text-red-400 text-2xl font-bold mb-4">
                        ${t("game.remote.opponentDisconnected")}
                    </div>
                    <div class="text-gray-400 mb-6">
                        ${t("game.remote.opponentDisconnectedMessage")}
                    </div>
                    <div>
                        ${tournamentId ? 
                            `<a href="/tournament/${tournamentId}" data-link class="btn btn-primary">${t("game.remote.backToTournament")}</a>` :
                            `<a href="/game/remote" data-link class="btn btn-primary">${t("game.remote.findNewMatch")}</a>`
                        }
                    </div>
                `;
            });

            this.ws.on('error', (data) => {
                // Check if this is a tournament game
                const urlParams = new URLSearchParams(window.location.search);
                const tournamentId = urlParams.get('tournament');

                gameStatus.innerHTML = `
                    <div class="text-red-400 mb-4">
                        ${t("game.remote.error", { message: data.message })}
                    </div>
                    <div>
                        ${tournamentId ? 
                            `<a href="/tournament/${tournamentId}" data-link class="btn btn-primary">${t("game.remote.backToTournament")}</a>` :
                            `<a href="/game/remote" data-link class="btn btn-primary">${t("game.remote.tryAgain")}</a>`
                        }
                    </div>
                `;
            });

        } catch (error: any) {
            console.error('WebSocket connection failed:', error);
            gameStatus.innerHTML = `
                <div class="text-red-400 mb-4">
                    ${t("game.remote.connectionFailed")}
                    <div class="text-sm mt-2 text-gray-500">${error.message || 'Unknown error'}</div>
                </div>
                <div>
                    <a href="/" data-link class="btn btn-secondary">${t("game.remote.backToHome")}</a>
                </div>
            `;
        }
    }

    sendPaddleMovement() {
        if (!this.ws || !this.remoteGame) return;
        const keys = this.remoteGame.keys;
        if (keys.ArrowUp && !keys.ArrowDown) {
            this.ws.sendPaddleMove('-1');
        } else if (keys.ArrowDown && !keys.ArrowUp) {
            this.ws.sendPaddleMove('1');
        } else {
            this.ws.sendPaddleMove('0');
        }
    }

    startRemoteGame(canvas: HTMLCanvasElement, gameStatus: HTMLElement) {
        gameStatus.innerHTML = `
            <div class="text-green-400 font-bold mb-2">${t("game.remote.opponentFound")}</div>
            <div class="text-gray-400 text-sm">${t("game.remote.gameStarting")}</div>
        `;
        
        // Always reinitialize the game with the correct gameMode from server
        const gameMode = this.serverGameMode || 'classic';
        
        // If game exists, stop it first
        if (this.remoteGame) {
            this.remoteGame.stop();
        }
        
        // Create new game instance with correct mode
        this.remoteGame = new GameEngine(canvas, 'remote', 'medium', gameMode);
        this.remoteGame.init();
        
        // Apply server obstacles if they exist (for custom mode)
        if (this.serverObstacles && gameMode === 'custom') {
            this.remoteGame.state.obstacles = this.serverObstacles;
        }
        
        this.remoteGame.start();
        const handleRemoteKey = (e: KeyboardEvent) => {
            if (e.key === 'ArrowUp' || e.key === 'ArrowDown') {
                e.preventDefault();
                this.sendPaddleMovement();
            }
        };

        // Add the event listeners
        window.addEventListener('keydown', handleRemoteKey);
        window.addEventListener('keyup', handleRemoteKey);

        // Update status after a moment
        setTimeout(() => {
            gameStatus.innerHTML = `
                <div class="text-green-400 mb-1">${t("game.remote.gameInProgress")}</div>
                <div class="text-sm text-gray-400">${t("game.remote.useArrowKeys")}</div>
            `;
        }, 1000);
    }

    async saveGameResult(score: any, mode: string, difficulty: string | null) {
        try {
            const user = JSON.parse(localStorage.getItem('user') || '{}');
            const player1_id = user.id;
            const player2_id = mode === 'ai' ? null : user.id; // TODO: Get actual player2_id for remote

            await ApiService.post('/games', {
                player1_id,
                player2_id,
                player1_score: score.player1,
                player2_score: score.player2,
                game_mode: mode,
                difficulty: mode === 'ai' ? difficulty : null,
                duration_seconds: 0 // TODO: Track actual duration
            });

            console.log('Game result saved successfully');
        } catch (error) {
            console.error('Failed to save game result:', error);
        }
    }

    cleanup() {
        // Clear room refresh interval
        if (this.roomsRefreshInterval) {
            clearInterval(this.roomsRefreshInterval);
            this.roomsRefreshInterval = null;
        }

        // Stop any running games
        if (this.game) {
            this.game.stop();
        }
        if (this.localGame) {
            this.localGame.stop();
            this.localGame = undefined;
        }
        if (this.aiGame) {
            this.aiGame.stop();
            this.aiGame = undefined;
        }
        if (this.remoteGame) {
            this.remoteGame.stop();
            this.remoteGame = null;
        }

        // Remove remote game key handlers
        if (this.remoteKeyDownHandler) {
            window.removeEventListener('keydown', this.remoteKeyDownHandler);
            this.remoteKeyDownHandler = undefined;
        }
        if (this.remoteKeyUpHandler) {
            window.removeEventListener('keyup', this.remoteKeyUpHandler);
            this.remoteKeyUpHandler = undefined;
        }
        if (this.renderModeKeyHandler) {
            window.removeEventListener('keydown', this.renderModeKeyHandler);
            this.renderModeKeyHandler = undefined;
        }

        // Close WebSocket connection
        if (this.ws) {
            this.ws.disconnect();
            this.ws = null;
        }

        // Remove game-end event listener
        if (this.handleGameEnd) {
            window.removeEventListener('game-end', this.handleGameEnd as EventListener);
        }
    }
}
