import { GAME_CONFIG, GameEngine } from './GameEngine.js';

interface DifficultySettings {
    reactionTime: number;
    errorMargin: number;
    speed: number;
    predictionAccuracy: number;
    centerBias: number;
}

interface SimulatedKeys {
    up: boolean;
    down: boolean;
}

/**
 * AI Opponent for Pong Game
 * 
 * Constraints (as per subject):
 * - No A* algorithm
 * - Only keyboard input simulation allowed
 * - Can only check game state once per second
 * - Must be at human-level speed
 */
export class AIOpponent {
    game: GameEngine;
    difficulty: string;
    settings: DifficultySettings;
    lastCheckTime: number;
    checkInterval: number;
    targetY: number;
    reaction_delay: number;
    simulatedKeys: SimulatedKeys;

    constructor(gameEngine: GameEngine, difficulty: string = 'medium') {
        this.game = gameEngine;
        this.difficulty = difficulty;
        
        // Difficulty settings
        this.settings = this.getDifficultySettings(difficulty);
        
        // AI state
        this.lastCheckTime = 0;
        this.checkInterval = 1000; // 1 second constraint
        this.targetY = GAME_CONFIG.HEIGHT / 2;
        this.reaction_delay = 0;
        
        // Simulated keyboard state
        this.simulatedKeys = {
            up: false,
            down: false
        };
    }

    getDifficultySettings(difficulty: string): DifficultySettings {
        switch (difficulty) {
            case 'easy':
                return {
                    reactionTime: 500,  // 반응 느림 (500ms)
                    errorMargin: 120,   // 큰 실수 (120 픽셀)
                    speed: 0.5,         // 느린 속도 (50%)
                    predictionAccuracy: 0.3, // 낮은 예측력 (벽 튕김 계산 안함)
                    centerBias: 0.7     // 중앙으로 돌아가려는 경향
                };
            case 'medium':
                return {
                    reactionTime: 250,  // 보통 반응 (250ms)
                    errorMargin: 50,    // 중간 실수 (50 픽셀)
                    speed: 0.75,        // 중간 속도 (75%)
                    predictionAccuracy: 0.6, // 중간 예측력 (1-2번 튕김)
                    centerBias: 0.4     // 약간 중앙 경향
                };
            case 'hard':
                return {
                    reactionTime: 80,   // 빠른 반응 (80ms)
                    errorMargin: 15,    // 작은 실수 (15 픽셀)
                    speed: 0.95,        // 빠른 속도 (95%)
                    predictionAccuracy: 0.95, // 높은 예측력 (정확한 계산)
                    centerBias: 0.1     // 중앙 경향 거의 없음
                };
            default:
                return this.getDifficultySettings('medium');
        }
    }

    update() {
        const currentTime = Date.now();
        
        // Check game state only once per second (constraint)
        if (currentTime - this.lastCheckTime >= this.checkInterval) {
            this.lastCheckTime = currentTime;
            this.analyzeGameState();
        }

        // Apply reaction delay
        if (this.reaction_delay > 0) {
            this.reaction_delay -= 16; // Approximate frame time
            return;
        }

        // Simulate keyboard input
        this.simulateKeyboard();
    }

    analyzeGameState() {
        const state = this.game.getState();
        const ball = state.ball;
        const paddle2 = state.paddle2;

        // Only react if ball is moving towards AI paddle
        if (ball.dx > 0) {
            // Easy AI sometimes "loses focus" and doesn't track the ball
            if (this.difficulty === 'easy' && Math.random() < 0.15) {
                // 15% chance to not react properly on easy
                return;
            }
            
            // Predict where ball will be
            const predictedY = this.predictBallPosition(ball);
            
            // Add error margin based on difficulty
            const error = (Math.random() - 0.5) * this.settings.errorMargin;
            this.targetY = predictedY + error;

            // Clamp target
            this.targetY = Math.max(
                GAME_CONFIG.PADDLE_HEIGHT / 2,
                Math.min(GAME_CONFIG.HEIGHT - GAME_CONFIG.PADDLE_HEIGHT / 2, this.targetY)
            );

            // Set reaction delay
            this.reaction_delay = this.settings.reactionTime;
        } else {
            // If ball is moving away, go to center (with centerBias affecting tendency)
            const centerY = GAME_CONFIG.HEIGHT / 2;
            const currentY = paddle2.y + GAME_CONFIG.PADDLE_HEIGHT / 2;
            
            // Apply center bias - higher bias means more likely to return to center
            if (Math.random() < this.settings.centerBias) {
                this.targetY = centerY;
            } else {
                // Stay in current position
                this.targetY = currentY;
            }
        }
    }

    predictBallPosition(ball: { x: number; y: number; dx: number; dy: number }): number {
        // Simple linear prediction with wall bounces
        let x = ball.x;
        let y = ball.y;
        let dx = ball.dx;
        let dy = ball.dy;

        // Simulate ball movement until it reaches paddle x position
        const paddleX = GAME_CONFIG.WIDTH - GAME_CONFIG.PADDLE_WIDTH;
        
        // Use prediction accuracy to determine how many bounces to calculate
        const maxBounces = Math.floor(this.settings.predictionAccuracy * 5);
        let bounces = 0;

        while (x < paddleX && bounces < maxBounces) {
            // Calculate time to reach paddle or wall
            const timeToWall = dy > 0 ? 
                (GAME_CONFIG.HEIGHT - y) / dy : 
                -y / dy;
            const timeToPaddle = (paddleX - x) / dx;

            if (timeToPaddle < timeToWall) {
                // Ball reaches paddle before wall
                y += dy * timeToPaddle;
                break;
            } else {
                // Ball hits wall first
                x += dx * timeToWall;
                y += dy * timeToWall;
                dy = -dy; // Bounce
                bounces++;
            }
        }

        return y;
    }

    simulateKeyboard() {
        const state = this.game.getState();
        const paddle2 = state.paddle2;
        const paddleCenter = paddle2.y + GAME_CONFIG.PADDLE_HEIGHT / 2;

        // Determine if we need to move up or down
        const diff = this.targetY - paddleCenter;
        
        // Threshold varies by difficulty - easier AI is less precise
        const threshold = this.difficulty === 'easy' ? 15 : 
                         this.difficulty === 'medium' ? 8 : 5;

        if (Math.abs(diff) < threshold) {
            // Stop moving - close enough
            state.paddle2.dy = 0;
        } else if (diff < 0) {
            // Move up (simulate up arrow key)
            state.paddle2.dy = -GAME_CONFIG.PADDLE_SPEED * this.settings.speed;
        } else {
            // Move down (simulate down arrow key)
            state.paddle2.dy = GAME_CONFIG.PADDLE_SPEED * this.settings.speed;
        }
    }
}
