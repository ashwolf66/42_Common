import { AIOpponent } from './AIOpponent.js';
import { Game3DRenderer } from './Game3DRenderer.js';
import { t } from '../l10n/index';

export const RENDER_MODE_2D = '2d' as const;
export const RENDER_MODE_3D = '3d' as const;
export const RENDER_MODES = [RENDER_MODE_2D, RENDER_MODE_3D] as const;

export type RenderMode = typeof RENDER_MODES[number];

export const DEFAULT_RENDER_MODE: RenderMode = RENDER_MODE_2D;

export function isRenderMode(value: string | null | undefined): value is RenderMode {
    return value === RENDER_MODE_2D || value === RENDER_MODE_3D;
}

export const GAME_CONFIG = {
    WIDTH: 800,
    HEIGHT: 600,
    PADDLE_WIDTH: 10,
    PADDLE_HEIGHT: 100,
    BALL_SIZE: 10,
    PADDLE_SPEED: 8,
    BALL_SPEED: 5,
    WINNING_SCORE: 11,
    FPS: 60,
    // Custom game mode settings
    OBSTACLE_COUNT: 3, // Number of obstacles per side
    OBSTACLE_MIN_SIZE: 30,
    OBSTACLE_MAX_SIZE: 60,
    OBSTACLE_MIN_GAP: 80 // Minimum gap from paddles and edges
};

export interface Obstacle {
    x: number;
    y: number;
    width: number;
    height: number;
}

export interface GameState {
    ball: {
        x: number;
        y: number;
        dx: number;
        dy: number;
    };
    paddle1: {
        y: number;
        dy: number;
    };
    paddle2: {
        y: number;
        dy: number;
    };
    score: {
        player1: number;
        player2: number;
    };
    started: boolean;
    paused: boolean;
    gameOver: boolean;
    winner: string | null;
    obstacles: Obstacle[];
}

interface KeyState {
    w: boolean;
    s: boolean;
    ArrowUp: boolean;
    ArrowDown: boolean;
}

export class GameEngine {
    canvas: HTMLCanvasElement;
    ctx: CanvasRenderingContext2D | null;
    mode: string;
    difficulty: string;
    gameMode: string; // 'classic' or 'custom'
    renderMode: RenderMode;
    state: GameState;
    keys: KeyState;
    ai: AIOpponent | null;
    lastTime: number;
    frameId: number | null;
    isRunning: boolean;
    renderer3d: Game3DRenderer | null;

    constructor(canvas: HTMLCanvasElement, mode: string = 'local', difficulty: string = 'medium', gameMode: string = 'classic', renderMode: RenderMode = DEFAULT_RENDER_MODE) {
        this.canvas = canvas;
        this.mode = mode; // 'local', 'ai', 'remote'
        this.difficulty = difficulty;
        this.gameMode = gameMode; // 'classic' or 'custom'
        this.renderMode = renderMode;
        
        // Set canvas size
        this.canvas.width = GAME_CONFIG.WIDTH;
        this.canvas.height = GAME_CONFIG.HEIGHT;
        this.ctx = this.renderMode === RENDER_MODE_2D ? this.canvas.getContext('2d') : null;
        this.renderer3d = this.renderMode === RENDER_MODE_3D ? new Game3DRenderer(this.canvas, GAME_CONFIG) : null;

        // Game state
        this.state = {
            ball: {
                x: GAME_CONFIG.WIDTH / 2,
                y: GAME_CONFIG.HEIGHT / 2,
                dx: GAME_CONFIG.BALL_SPEED / Math.sqrt(2), // Normalized for 45 degree angle
                dy: GAME_CONFIG.BALL_SPEED / Math.sqrt(2)
            },
            paddle1: {
                y: GAME_CONFIG.HEIGHT / 2 - GAME_CONFIG.PADDLE_HEIGHT / 2,
                dy: 0
            },
            paddle2: {
                y: GAME_CONFIG.HEIGHT / 2 - GAME_CONFIG.PADDLE_HEIGHT / 2,
                dy: 0
            },
            score: {
                player1: 0,
                player2: 0
            },
            started: false,
            paused: false,
            gameOver: false,
            winner: null,
            obstacles: []
        };

        // Generate obstacles for custom mode
        if (this.gameMode === 'custom') {
            this.state.obstacles = this.generateObstacles();
        }

        // Input state
        this.keys = {
            w: false,
            s: false,
            ArrowUp: false,
            ArrowDown: false
        };

        // AI
        this.ai = null;
        if (mode === 'ai') {
            this.ai = new AIOpponent(this, difficulty);
        }

        // Game loop
        this.lastTime = 0;
        this.frameId = null;
        this.isRunning = false;

        // Bind methods
        this.handleKeyDown = this.handleKeyDown.bind(this);
        this.handleKeyUp = this.handleKeyUp.bind(this);
        this.gameLoop = this.gameLoop.bind(this);
    }

    init() {
        // Add event listeners
        window.addEventListener('keydown', this.handleKeyDown);
        window.addEventListener('keyup', this.handleKeyUp);

        // Reset ball
        this.resetBall();
        
        // Initial render to show start screen
        this.render();
    }

    start() {
        if (this.isRunning) return;
        this.isRunning = true;
        this.state.started = false; // Will be set to true when space is pressed
        this.lastTime = performance.now();
        this.gameLoop(this.lastTime);
    }

    pause() {
        this.state.paused = !this.state.paused;
    }

    stop() {
        this.isRunning = false;
        if (this.frameId) {
            cancelAnimationFrame(this.frameId);
        }
        window.removeEventListener('keydown', this.handleKeyDown);
        window.removeEventListener('keyup', this.handleKeyUp);
        if (this.renderer3d) {
            this.renderer3d.dispose();
        }
    }

    handleKeyDown(e: KeyboardEvent) {
        if (e.key in this.keys) {
            e.preventDefault();
            this.keys[e.key as keyof KeyState] = true;
        }
        if (e.key === ' ') {
            e.preventDefault();
            // Don't handle space key in remote mode
            if (this.mode === 'remote') {
                return;
            }
            // Start game if not started
            if (!this.state.started && !this.state.gameOver) {
                this.state.started = true;
            } 
            // Pause/unpause if game is started
            else if (this.state.started && !this.state.gameOver) {
                this.pause();
            }
        }
    }

    handleKeyUp(e: KeyboardEvent) {
        if (e.key in this.keys) {
            e.preventDefault();
            this.keys[e.key as keyof KeyState] = false;
        }
    }

    gameLoop(currentTime: number) {
        if (!this.isRunning) return;

        const deltaTime = currentTime - this.lastTime;
        this.lastTime = currentTime;

        // Only update game if started and not paused
        if (this.state.started && !this.state.paused && !this.state.gameOver) {
            this.update(deltaTime);
        }

        this.render();

        this.frameId = requestAnimationFrame(this.gameLoop);
    }

    update(_deltaTime: number) {
        // Update paddle velocities based on input
        if (this.mode === 'local') {
            // Player 1 (W/S)
            if (this.keys.w) {
                this.state.paddle1.dy = -GAME_CONFIG.PADDLE_SPEED;
            } else if (this.keys.s) {
                this.state.paddle1.dy = GAME_CONFIG.PADDLE_SPEED;
            } else {
                this.state.paddle1.dy = 0;
            }

            // Player 2 (Arrow keys)
            if (this.keys.ArrowUp) {
                this.state.paddle2.dy = -GAME_CONFIG.PADDLE_SPEED;
            } else if (this.keys.ArrowDown) {
                this.state.paddle2.dy = GAME_CONFIG.PADDLE_SPEED;
            } else {
                this.state.paddle2.dy = 0;
            }
        } else if (this.mode === 'ai') {
            // Player 1 (W/S or Arrow keys)
            if (this.keys.w || this.keys.ArrowUp) {
                this.state.paddle1.dy = -GAME_CONFIG.PADDLE_SPEED;
            } else if (this.keys.s || this.keys.ArrowDown) {
                this.state.paddle1.dy = GAME_CONFIG.PADDLE_SPEED;
            } else {
                this.state.paddle1.dy = 0;
            }

            // AI controls paddle2
            if (this.ai) {
                this.ai.update();
            }
        } else if (this.mode === 'remote') {
            // In remote mode, don't update paddle velocities here
            // They are updated via WebSocket and updateRemoteState()
            // Just return early - server handles all game logic
            return;
        }

        // Update paddle positions
        this.state.paddle1.y += this.state.paddle1.dy;
        this.state.paddle2.y += this.state.paddle2.dy;

        // Clamp paddles to canvas
        this.state.paddle1.y = Math.max(0, Math.min(GAME_CONFIG.HEIGHT - GAME_CONFIG.PADDLE_HEIGHT, this.state.paddle1.y));
        this.state.paddle2.y = Math.max(0, Math.min(GAME_CONFIG.HEIGHT - GAME_CONFIG.PADDLE_HEIGHT, this.state.paddle2.y));

        // Update ball position
        this.state.ball.x += this.state.ball.dx;
        this.state.ball.y += this.state.ball.dy;

        // Ball collision with obstacles (custom mode only) - Check FIRST
        if (this.gameMode === 'custom') {
            this.checkObstacleCollisions();
        }

        // Ball collision with top/bottom walls
        if (this.state.ball.y <= 0 || this.state.ball.y >= GAME_CONFIG.HEIGHT - GAME_CONFIG.BALL_SIZE) {
            this.state.ball.dy = -this.state.ball.dy;
            
            // Normalize speed to handle any floating point errors
            const currentSpeed = Math.sqrt(this.state.ball.dx * this.state.ball.dx + this.state.ball.dy * this.state.ball.dy);
            if (currentSpeed > 0 && Math.abs(currentSpeed - GAME_CONFIG.BALL_SPEED) > 0.01) {
                this.state.ball.dx = (this.state.ball.dx / currentSpeed) * GAME_CONFIG.BALL_SPEED;
                this.state.ball.dy = (this.state.ball.dy / currentSpeed) * GAME_CONFIG.BALL_SPEED;
            }
            
            // Clamp ball position to prevent getting stuck
            if (this.state.ball.y <= 0) {
                this.state.ball.y = 0;
            } else {
                this.state.ball.y = GAME_CONFIG.HEIGHT - GAME_CONFIG.BALL_SIZE;
            }
        }

        // Ball collision with paddles
        // Left paddle (player 1)
        if (this.state.ball.x <= GAME_CONFIG.PADDLE_WIDTH &&
            this.state.ball.y + GAME_CONFIG.BALL_SIZE >= this.state.paddle1.y &&
            this.state.ball.y <= this.state.paddle1.y + GAME_CONFIG.PADDLE_HEIGHT) {
            // Add some angle variation based on where ball hits paddle
            const paddleCenter = this.state.paddle1.y + GAME_CONFIG.PADDLE_HEIGHT / 2;
            const ballCenter = this.state.ball.y + GAME_CONFIG.BALL_SIZE / 2;
            const offset = (ballCenter - paddleCenter) / (GAME_CONFIG.PADDLE_HEIGHT / 2);
            
            // Calculate new direction angle
            const angle = offset * (Math.PI / 4); // Max 45 degrees up or down
            
            // Set velocity components with proper angle
            this.state.ball.dx = Math.abs(Math.cos(angle)) * GAME_CONFIG.BALL_SPEED;
            this.state.ball.dy = Math.sin(angle) * GAME_CONFIG.BALL_SPEED;
            
            // Move ball outside paddle to prevent multiple collisions
            this.state.ball.x = GAME_CONFIG.PADDLE_WIDTH;
        }

        // Right paddle (player 2)
        if (this.state.ball.x >= GAME_CONFIG.WIDTH - GAME_CONFIG.PADDLE_WIDTH - GAME_CONFIG.BALL_SIZE &&
            this.state.ball.y + GAME_CONFIG.BALL_SIZE >= this.state.paddle2.y &&
            this.state.ball.y <= this.state.paddle2.y + GAME_CONFIG.PADDLE_HEIGHT) {
            // Add some angle variation based on where ball hits paddle
            const paddleCenter = this.state.paddle2.y + GAME_CONFIG.PADDLE_HEIGHT / 2;
            const ballCenter = this.state.ball.y + GAME_CONFIG.BALL_SIZE / 2;
            const offset = (ballCenter - paddleCenter) / (GAME_CONFIG.PADDLE_HEIGHT / 2);
            
            // Calculate new direction angle
            const angle = offset * (Math.PI / 4); // Max 45 degrees up or down
            
            // Set velocity components with proper angle (negative x direction)
            this.state.ball.dx = -Math.abs(Math.cos(angle)) * GAME_CONFIG.BALL_SPEED;
            this.state.ball.dy = Math.sin(angle) * GAME_CONFIG.BALL_SPEED;
            
            // Move ball outside paddle to prevent multiple collisions
            this.state.ball.x = GAME_CONFIG.WIDTH - GAME_CONFIG.PADDLE_WIDTH - GAME_CONFIG.BALL_SIZE;
        }

        // Scoring
        if (this.state.ball.x <= 0) {
            this.state.score.player2++;
            this.resetBall();
            this.checkWinner();
        } else if (this.state.ball.x >= GAME_CONFIG.WIDTH) {
            this.state.score.player1++;
            this.resetBall();
            this.checkWinner();
        }
        
        // Debug: Verify ball speed (can be removed in production)
        const currentSpeed = Math.sqrt(this.state.ball.dx * this.state.ball.dx + this.state.ball.dy * this.state.ball.dy);
        const speedDiff = Math.abs(currentSpeed - GAME_CONFIG.BALL_SPEED);
        if (speedDiff > 0.1) {
            console.warn(`Ball speed deviation detected: ${currentSpeed.toFixed(2)} (expected: ${GAME_CONFIG.BALL_SPEED})`);
            // Force correction if speed drifts too much
            if (currentSpeed > 0) {
                this.state.ball.dx = (this.state.ball.dx / currentSpeed) * GAME_CONFIG.BALL_SPEED;
                this.state.ball.dy = (this.state.ball.dy / currentSpeed) * GAME_CONFIG.BALL_SPEED;
            }
        }
    }

    resetBall() {
        this.state.ball.x = GAME_CONFIG.WIDTH / 2;
        this.state.ball.y = GAME_CONFIG.HEIGHT / 2;
        // Random direction
        const angle = (Math.random() * Math.PI / 3) - Math.PI / 6; // -30 to +30 degrees
        const direction = Math.random() > 0.5 ? 1 : -1;
        
        // Calculate velocity components
        this.state.ball.dx = Math.cos(angle) * direction;
        this.state.ball.dy = Math.sin(angle);
        
        // Normalize to ensure constant speed
        const magnitude = Math.sqrt(this.state.ball.dx * this.state.ball.dx + this.state.ball.dy * this.state.ball.dy);
        if (magnitude > 0) {
            this.state.ball.dx = (this.state.ball.dx / magnitude) * GAME_CONFIG.BALL_SPEED;
            this.state.ball.dy = (this.state.ball.dy / magnitude) * GAME_CONFIG.BALL_SPEED;
        }
    }

    checkWinner() {
        if (this.state.score.player1 >= GAME_CONFIG.WINNING_SCORE) {
            this.endGame('player1');
        } else if (this.state.score.player2 >= GAME_CONFIG.WINNING_SCORE) {
            this.endGame('player2');
        }
    }

    generateObstacles(): Obstacle[] {
        const obstacles: Obstacle[] = [];
        const centerX = GAME_CONFIG.WIDTH / 2;
        
        // Generate obstacles for left side (player 1)
        for (let i = 0; i < GAME_CONFIG.OBSTACLE_COUNT; i++) {
            const size = Math.random() * (GAME_CONFIG.OBSTACLE_MAX_SIZE - GAME_CONFIG.OBSTACLE_MIN_SIZE) + GAME_CONFIG.OBSTACLE_MIN_SIZE;
            
            // Random position in left half, avoiding paddle area and edges
            const x = Math.random() * (centerX - GAME_CONFIG.OBSTACLE_MIN_GAP * 2 - GAME_CONFIG.PADDLE_WIDTH - size) + GAME_CONFIG.OBSTACLE_MIN_GAP + GAME_CONFIG.PADDLE_WIDTH;
            const y = Math.random() * (GAME_CONFIG.HEIGHT - size - GAME_CONFIG.OBSTACLE_MIN_GAP * 2) + GAME_CONFIG.OBSTACLE_MIN_GAP;
            
            obstacles.push({ x, y, width: size, height: size });
        }
        
        // Generate obstacles for right side (player 2) - completely random, not mirrored
        for (let i = 0; i < GAME_CONFIG.OBSTACLE_COUNT; i++) {
            const size = Math.random() * (GAME_CONFIG.OBSTACLE_MAX_SIZE - GAME_CONFIG.OBSTACLE_MIN_SIZE) + GAME_CONFIG.OBSTACLE_MIN_SIZE;
            
            // Random position in right half, avoiding paddle area and edges
            const x = Math.random() * (centerX - GAME_CONFIG.OBSTACLE_MIN_GAP * 2 - GAME_CONFIG.PADDLE_WIDTH - size) + centerX + GAME_CONFIG.OBSTACLE_MIN_GAP;
            const y = Math.random() * (GAME_CONFIG.HEIGHT - size - GAME_CONFIG.OBSTACLE_MIN_GAP * 2) + GAME_CONFIG.OBSTACLE_MIN_GAP;
            
            obstacles.push({ x, y, width: size, height: size });
        }
        
        return obstacles;
    }

    checkObstacleCollisions() {
        for (const obstacle of this.state.obstacles) {
            // Expanded collision detection - add margin for better detection
            const margin = 1; // Extra pixel margin for detection
            
            // Check if ball intersects with obstacle (with margin)
            if (this.state.ball.x < obstacle.x + obstacle.width + margin &&
                this.state.ball.x + GAME_CONFIG.BALL_SIZE > obstacle.x - margin &&
                this.state.ball.y < obstacle.y + obstacle.height + margin &&
                this.state.ball.y + GAME_CONFIG.BALL_SIZE > obstacle.y - margin) {
                
                // Calculate ball center
                const ballCenterX = this.state.ball.x + GAME_CONFIG.BALL_SIZE / 2;
                const ballCenterY = this.state.ball.y + GAME_CONFIG.BALL_SIZE / 2;
                
                // Calculate obstacle center
                const obstacleCenterX = obstacle.x + obstacle.width / 2;
                const obstacleCenterY = obstacle.y + obstacle.height / 2;
                
                // Calculate overlap on each side
                const overlapLeft = (this.state.ball.x + GAME_CONFIG.BALL_SIZE) - obstacle.x;
                const overlapRight = (obstacle.x + obstacle.width) - this.state.ball.x;
                const overlapTop = (this.state.ball.y + GAME_CONFIG.BALL_SIZE) - obstacle.y;
                const overlapBottom = (obstacle.y + obstacle.height) - this.state.ball.y;
                
                // Find minimum overlap to determine collision side
                const minOverlap = Math.min(overlapLeft, overlapRight, overlapTop, overlapBottom);
                
                // Determine collision direction more reliably
                let hitHorizontal = false;
                
                if (minOverlap === overlapLeft || minOverlap === overlapRight) {
                    hitHorizontal = true;
                } else if (minOverlap === overlapTop || minOverlap === overlapBottom) {
                    hitHorizontal = false;
                }
                
                // Bounce based on collision side
                if (hitHorizontal) {
                    // Only reverse if moving towards the obstacle
                    if ((ballCenterX < obstacleCenterX && this.state.ball.dx > 0) ||
                        (ballCenterX > obstacleCenterX && this.state.ball.dx < 0)) {
                        this.state.ball.dx = -this.state.ball.dx;
                    }
                } else {
                    // Only reverse if moving towards the obstacle
                    if ((ballCenterY < obstacleCenterY && this.state.ball.dy > 0) ||
                        (ballCenterY > obstacleCenterY && this.state.ball.dy < 0)) {
                        this.state.ball.dy = -this.state.ball.dy;
                    }
                }
                
                // Always normalize to BALL_SPEED to ensure constant velocity
                const currentSpeed = Math.sqrt(this.state.ball.dx * this.state.ball.dx + this.state.ball.dy * this.state.ball.dy);
                if (currentSpeed > 0) {
                    this.state.ball.dx = (this.state.ball.dx / currentSpeed) * GAME_CONFIG.BALL_SPEED;
                    this.state.ball.dy = (this.state.ball.dy / currentSpeed) * GAME_CONFIG.BALL_SPEED;
                }
                
                // Move ball outside obstacle more aggressively
                const pushDistance = 2; // Extra pixels to push ball out
                if (minOverlap === overlapLeft) {
                    this.state.ball.x = obstacle.x - GAME_CONFIG.BALL_SIZE - pushDistance;
                } else if (minOverlap === overlapRight) {
                    this.state.ball.x = obstacle.x + obstacle.width + pushDistance;
                } else if (minOverlap === overlapTop) {
                    this.state.ball.y = obstacle.y - GAME_CONFIG.BALL_SIZE - pushDistance;
                } else if (minOverlap === overlapBottom) {
                    this.state.ball.y = obstacle.y + obstacle.height + pushDistance;
                }
                
                break; // Only handle one collision per frame
            }
        }
    }

    endGame(winner: string) {
        this.state.gameOver = true;
        this.state.winner = winner;
        
        // Emit game end event
        window.dispatchEvent(new CustomEvent('game-end', {
            detail: {
                winner: winner,
                score: this.state.score,
                mode: this.mode,
                difficulty: this.difficulty
            }
        }));
    }

    render() {
        if (this.renderMode === RENDER_MODE_3D && this.renderer3d) {
            this.renderer3d.render(this.state, this.mode, this.difficulty);
            return;
        }
        if (!this.ctx) {
            return;
        }
        const ctx = this.ctx;

        // Clear canvas
        ctx.fillStyle = '#111827';
        ctx.fillRect(0, 0, GAME_CONFIG.WIDTH, GAME_CONFIG.HEIGHT);

        // Draw center line
        ctx.strokeStyle = '#374151';
        ctx.lineWidth = 2;
        ctx.setLineDash([10, 10]);
        ctx.beginPath();
        ctx.moveTo(GAME_CONFIG.WIDTH / 2, 0);
        ctx.lineTo(GAME_CONFIG.WIDTH / 2, GAME_CONFIG.HEIGHT);
        ctx.stroke();
        ctx.setLineDash([]);

        // Draw paddles
        ctx.fillStyle = '#0ea5e9';
        ctx.fillRect(0, this.state.paddle1.y, GAME_CONFIG.PADDLE_WIDTH, GAME_CONFIG.PADDLE_HEIGHT);
        ctx.fillRect(GAME_CONFIG.WIDTH - GAME_CONFIG.PADDLE_WIDTH, this.state.paddle2.y, GAME_CONFIG.PADDLE_WIDTH, GAME_CONFIG.PADDLE_HEIGHT);

        // Draw obstacles (custom mode only)
        if (this.gameMode === 'custom') {
            ctx.fillStyle = '#0ea5e9'; // Same color as paddles
            for (const obstacle of this.state.obstacles) {
                ctx.fillRect(obstacle.x, obstacle.y, obstacle.width, obstacle.height);
            }
        }

        // Draw ball
        ctx.fillStyle = '#ffffff';
        ctx.fillRect(this.state.ball.x, this.state.ball.y, GAME_CONFIG.BALL_SIZE, GAME_CONFIG.BALL_SIZE);

        // Draw scores
        ctx.font = 'bold 48px Inter';
        ctx.fillStyle = '#4b5563';
        ctx.textAlign = 'center';
        ctx.fillText(String(this.state.score.player1), GAME_CONFIG.WIDTH / 4, 60);
        ctx.fillText(String(this.state.score.player2), (GAME_CONFIG.WIDTH * 3) / 4, 60);

        // Draw paused/game over/start overlay
        if (!this.state.started) {
            const title = this.mode === 'ai'
                ? `${t('game.status.vsAI')} - ${this.difficulty.toUpperCase()}`
                : this.mode === 'remote'
                ? t('game.status.onlineMatch')
                : t('game.status.localMultiplayer');
            const subtitle = this.mode === 'remote'
                ? t('game.status.waitingToStart')
                : t('game.status.pressSpace');
            this.renderOverlay(title, subtitle);
        } else if (this.state.paused) {
            this.renderOverlay(t('game.status.paused'), t('game.status.pressToContinue'));
        } else if (this.state.gameOver) {
            const winnerText = this.state.winner === 'player1'
                ? t('game.status.player1Wins')
                : t('game.status.player2Wins');
            this.renderOverlay(winnerText, '');
        }
    }

    renderOverlay(title: string, subtitle: string) {
        if (!this.ctx) {
            return;
        }
        const ctx = this.ctx;
        
        // Semi-transparent background
        ctx.fillStyle = 'rgba(0, 0, 0, 0.8)';
        ctx.fillRect(0, 0, GAME_CONFIG.WIDTH, GAME_CONFIG.HEIGHT);

        // Title
        ctx.font = 'bold 48px Inter';
        ctx.fillStyle = '#ffffff';
        ctx.textAlign = 'center';
        ctx.fillText(title, GAME_CONFIG.WIDTH / 2, GAME_CONFIG.HEIGHT / 2);

        // Subtitle
        if (subtitle) {
            ctx.font = '24px Inter';
            ctx.fillStyle = '#9ca3af';
            ctx.fillText(subtitle, GAME_CONFIG.WIDTH / 2, GAME_CONFIG.HEIGHT / 2 + 50);
        }
    }

    getState() {
        return this.state;
    }

    setState(newState: Partial<GameState>) {
        this.state = { ...this.state, ...newState };
    }

    updateRemoteState(remoteState: GameState | null) {
        // Update game state from server for remote multiplayer
        if (remoteState) {
            this.state.ball = { ...remoteState.ball };
            this.state.paddle1 = { ...remoteState.paddle1 };
            this.state.paddle2 = { ...remoteState.paddle2 };
            this.state.score = { ...remoteState.score };
            this.state.started = true;
        }
    }
}
