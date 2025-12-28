import * as BABYLON from '@babylonjs/core';
import '@babylonjs/core/Materials/standardMaterial';
import '@babylonjs/core/Meshes/meshBuilder';
import * as GUI from '@babylonjs/gui';
import { t } from '../l10n/index';
import type { GameState, Obstacle } from './GameEngine.js';

type RenderConfig = {
    WIDTH: number;
    HEIGHT: number;
    PADDLE_WIDTH: number;
    PADDLE_HEIGHT: number;
    BALL_SIZE: number;
};

const SCENE_CLEAR_COLOR = new BABYLON.Color4(0.067, 0.094, 0.153, 1);
const CAMERA_ALPHA = (3 * Math.PI) / 2;
const CAMERA_BETA = Math.PI / 3;
const CAMERA_RADIUS = 500;
const CAMERA_LOWER_RADIUS = 960;
const CAMERA_UPPER_RADIUS = 1200;
const CAMERA_LOWER_BETA = Math.PI / 6;
const CAMERA_UPPER_BETA = Math.PI / 2.2;

const AMBIENT_LIGHT_INTENSITY = 0.6;
const DIRECTIONAL_LIGHT_INTENSITY = 0.6;
const DIRECTIONAL_LIGHT1_DIRECTION = new BABYLON.Vector3(-1, -2, -1);

const ARENA_LINE_COLOR = new BABYLON.Color3(0.2, 0.25, 0.32);
const ARENA_BAR_ALPHA = 0.4;
const ARENA_BAR_HEIGHT = 10.0;
const CENTER_LINE_SEGMENT_LENGTH = 20;
const CENTER_LINE_GAP = 20;
const CENTER_LINE_THICKNESS = 2;

const PADDLE_COLOR = new BABYLON.Color3(0.055, 0.647, 0.914);
const PADDLE_EMISSIVE = new BABYLON.Color3(0.055, 0.4, 0.6);

const BALL_DIFFUSE = new BABYLON.Color3(1, 1, 1);
const BALL_EMISSIVE = new BABYLON.Color3(0.7, 0.7, 0.7);
const BALL_MIN_DIAMETER = 1.2;

const SCORE_PLANE_WIDTH_RATIO = 0.18;
const SCORE_PLANE_HEIGHT_RATIO = 0.18;
const SCORE_PLANE_Y_OFFSET = 35;
const SCORE_PLANE_X_RATIO = 0.25;
const SCORE_TEXTURE_WIDTH = 256;
const SCORE_TEXTURE_HEIGHT = 128;
const SCORE_TEXT_COLOR = '#9ca3af';
const SCORE_TEXT_WEIGHT = 'bold';
const SCORE_TEXT_SIZE = 60;

const OVERLAY_TEXT_COLOR = 'white';
const OVERLAY_TEXT_SIZE = 48;
const OVERLAY_SUBTEXT_COLOR = '#9ca3af';
const OVERLAY_SUBTEXT_SIZE = 24;
const OVERLAY_SUBTEXT_TOP = '60px';

const OBSTACLE_BOX_SIZE = 1;
const OBSTACLE_COLOR = new BABYLON.Color3(0.055, 0.647, 0.914);
const OBSTACLE_EMISSIVE = new BABYLON.Color3(0.055, 0.4, 0.6);


export class Game3DRenderer {
    private engine: BABYLON.Engine;
    private scene: BABYLON.Scene;
    private camera: BABYLON.ArcRotateCamera;
    private config: RenderConfig;
    private handleResize: () => void;

    private paddle1Mesh: BABYLON.Mesh;
    private paddle2Mesh: BABYLON.Mesh;
    private ballMesh: BABYLON.Mesh;
    private obstacleMeshes: BABYLON.Mesh[] = [];

    private scoreText1: GUI.TextBlock | null = null;
    private scoreText2: GUI.TextBlock | null = null;
    private overlayText: GUI.TextBlock | null = null;
    private overlaySubtext: GUI.TextBlock | null = null;
    private scorePlane1: BABYLON.Mesh | null = null;
    private scorePlane2: BABYLON.Mesh | null = null;

    constructor(canvas: HTMLCanvasElement, config: RenderConfig) {
        this.config = config;

        this.engine = new BABYLON.Engine(canvas, true, {
            preserveDrawingBuffer: true,
            stencil: true,
            failIfMajorPerformanceCaveat: false
        });
        this.scene = new BABYLON.Scene(this.engine);
        this.scene.clearColor = SCENE_CLEAR_COLOR;

        this.camera = new BABYLON.ArcRotateCamera(
            'camera',
            CAMERA_ALPHA,
            CAMERA_BETA,
            CAMERA_RADIUS,
            new BABYLON.Vector3(0, 0, 0),
            this.scene
        );
        this.camera.attachControl(canvas, true);
        this.camera.inputs.removeByType('ArcRotateCameraKeyboardMoveInput');
        this.camera.keysUp = [];
        this.camera.keysDown = [];
        this.camera.keysLeft = [];
        this.camera.keysRight = [];
        this.camera.lowerRadiusLimit = CAMERA_LOWER_RADIUS;
        this.camera.upperRadiusLimit = CAMERA_UPPER_RADIUS;
        this.camera.lowerBetaLimit = CAMERA_LOWER_BETA;
        this.camera.upperBetaLimit = CAMERA_UPPER_BETA;

        this.createLights();
        this.createArena();
        this.paddle1Mesh = this.createPaddle('paddle1');
        this.paddle2Mesh = this.createPaddle('paddle2');
        this.ballMesh = this.createBall();
        this.createUI();

        this.handleResize = () => {
            this.engine.resize();
        };
        window.addEventListener('resize', this.handleResize);
    }

    dispose() {
        window.removeEventListener('resize', this.handleResize);
        this.scene.dispose();
        this.engine.dispose();
    }

    render(state: GameState, mode: string, difficulty: string) {
        this.syncObstacles(state.obstacles || []);
        this.updatePositions(state);
        this.updateScores(state);
        this.updateOverlay(state, mode, difficulty);
        this.scene.render();
    }

    private createLights() {
        const ambientLight = new BABYLON.HemisphericLight(
            'ambientLight',
            new BABYLON.Vector3(0, 1, 0),
            this.scene
        );
        ambientLight.intensity = AMBIENT_LIGHT_INTENSITY;

        const light1 = new BABYLON.DirectionalLight(
            'light1',
            DIRECTIONAL_LIGHT1_DIRECTION,
            this.scene
        );
        light1.intensity = DIRECTIONAL_LIGHT_INTENSITY;
    }

    private createArena() {
        const halfHeight = this.config.HEIGHT / 2;
        const arenaBarMaterial = new BABYLON.StandardMaterial('arenaBarMat', this.scene);
        arenaBarMaterial.emissiveColor = ARENA_LINE_COLOR;
        arenaBarMaterial.disableLighting = true;
        arenaBarMaterial.alpha = ARENA_BAR_ALPHA;

        const barWidth = this.config.WIDTH;
        const barHeight = ARENA_BAR_HEIGHT;
        const barDepth = this.config.PADDLE_HEIGHT;

        const topBar = BABYLON.MeshBuilder.CreateBox('arenaBarTop', {
            width: barWidth,
            height: barHeight,
            depth: barDepth
        }, this.scene);
        topBar.position = new BABYLON.Vector3(0, halfHeight + barHeight / 2, 0);
        topBar.material = arenaBarMaterial;
        topBar.isPickable = false;

        const bottomBar = BABYLON.MeshBuilder.CreateBox('arenaBarBottom', {
            width: barWidth,
            height: barHeight,
            depth: barDepth
        }, this.scene);
        bottomBar.position = new BABYLON.Vector3(0, -halfHeight - barHeight / 2, 0);
        bottomBar.material = arenaBarMaterial;
        bottomBar.isPickable = false;

        const centerLineMaterial = new BABYLON.StandardMaterial('centerLineMat', this.scene);
        centerLineMaterial.emissiveColor = ARENA_LINE_COLOR;
        centerLineMaterial.disableLighting = true;

        const totalHeight = this.config.HEIGHT;
        const segmentCount = Math.floor(totalHeight / (CENTER_LINE_SEGMENT_LENGTH + CENTER_LINE_GAP));
        const startY = totalHeight / 2 - CENTER_LINE_SEGMENT_LENGTH / 2;

        for (let i = 0; i < segmentCount; i++) {
            const segment = BABYLON.MeshBuilder.CreateBox(`centerLine${i}`, {
                width: CENTER_LINE_THICKNESS,
                height: CENTER_LINE_SEGMENT_LENGTH,
                depth: CENTER_LINE_THICKNESS
            }, this.scene);
            segment.position = new BABYLON.Vector3(0, startY - i * (CENTER_LINE_SEGMENT_LENGTH + CENTER_LINE_GAP), 0);
            segment.material = centerLineMaterial;
            segment.isPickable = false;
        }
    }

    private createPaddle(name: string) {
        const paddle = BABYLON.MeshBuilder.CreateBox(name, {
            width: this.config.PADDLE_WIDTH,
            height: this.config.PADDLE_HEIGHT,
            depth: this.config.PADDLE_HEIGHT
        }, this.scene);
        const material = new BABYLON.StandardMaterial(`${name}Mat`, this.scene);
        material.diffuseColor = PADDLE_COLOR;
        material.emissiveColor = PADDLE_EMISSIVE;
        paddle.material = material;
        return paddle;
    }

    private createBall() {
        const ballSize = this.config.BALL_SIZE;
        const ball = BABYLON.MeshBuilder.CreateSphere('ball', {
            diameter: Math.max(ballSize, BALL_MIN_DIAMETER)
        }, this.scene);
        const material = new BABYLON.StandardMaterial('ballMat', this.scene);
        material.diffuseColor = BALL_DIFFUSE;
        material.emissiveColor = BALL_EMISSIVE;
        ball.material = material;
        return ball;
    }

    private createUI() {
        const scorePlaneWidth = this.config.WIDTH * SCORE_PLANE_WIDTH_RATIO;
        const scorePlaneHeight = this.config.HEIGHT * SCORE_PLANE_HEIGHT_RATIO;
        const scorePlaneY = this.config.HEIGHT / 2 + SCORE_PLANE_Y_OFFSET;

        this.scorePlane1 = BABYLON.MeshBuilder.CreatePlane('scorePlane1', {
            width: scorePlaneWidth,
            height: scorePlaneHeight
        }, this.scene);
        this.scorePlane1.position = new BABYLON.Vector3(-this.config.WIDTH * SCORE_PLANE_X_RATIO, scorePlaneY, 0);
        this.scorePlane1.billboardMode = BABYLON.Mesh.BILLBOARDMODE_ALL;
        this.scorePlane1.isPickable = false;

        const scoreTexture1 = GUI.AdvancedDynamicTexture.CreateForMesh(
            this.scorePlane1,
            SCORE_TEXTURE_WIDTH,
            SCORE_TEXTURE_HEIGHT
        );

        this.scoreText1 = new GUI.TextBlock();
        this.scoreText1.text = '0';
        this.scoreText1.color = SCORE_TEXT_COLOR;
        this.scoreText1.fontSize = SCORE_TEXT_SIZE;
        this.scoreText1.fontWeight = SCORE_TEXT_WEIGHT;
        scoreTexture1.addControl(this.scoreText1);

        this.scorePlane2 = BABYLON.MeshBuilder.CreatePlane('scorePlane2', {
            width: scorePlaneWidth,
            height: scorePlaneHeight
        }, this.scene);
        this.scorePlane2.position = new BABYLON.Vector3(this.config.WIDTH * SCORE_PLANE_X_RATIO, scorePlaneY, 0);
        this.scorePlane2.billboardMode = BABYLON.Mesh.BILLBOARDMODE_ALL;
        this.scorePlane2.isPickable = false;

        const scoreTexture2 = GUI.AdvancedDynamicTexture.CreateForMesh(
            this.scorePlane2,
            SCORE_TEXTURE_WIDTH,
            SCORE_TEXTURE_HEIGHT
        );

        this.scoreText2 = new GUI.TextBlock();
        this.scoreText2.text = '0';
        this.scoreText2.color = SCORE_TEXT_COLOR;
        this.scoreText2.fontSize = SCORE_TEXT_SIZE;
        this.scoreText2.fontWeight = SCORE_TEXT_WEIGHT;
        scoreTexture2.addControl(this.scoreText2);

        const overlayTexture = GUI.AdvancedDynamicTexture.CreateFullscreenUI('UI', true, this.scene);

        this.overlayText = new GUI.TextBlock();
        this.overlayText.color = OVERLAY_TEXT_COLOR;
        this.overlayText.fontSize = OVERLAY_TEXT_SIZE;
        this.overlayText.fontWeight = SCORE_TEXT_WEIGHT;
        this.overlayText.isVisible = false;
        overlayTexture.addControl(this.overlayText);

        this.overlaySubtext = new GUI.TextBlock();
        this.overlaySubtext.color = OVERLAY_SUBTEXT_COLOR;
        this.overlaySubtext.fontSize = OVERLAY_SUBTEXT_SIZE;
        this.overlaySubtext.top = OVERLAY_SUBTEXT_TOP;
        this.overlaySubtext.isVisible = false;
        overlayTexture.addControl(this.overlaySubtext);
    }

    private syncObstacles(obstacles: Obstacle[]) {
        if (this.obstacleMeshes.length === obstacles.length) {
            return;
        }
        for (const mesh of this.obstacleMeshes) {
            mesh.dispose();
        }
        this.obstacleMeshes = obstacles.map((_, index) => {
            const mesh = BABYLON.MeshBuilder.CreateBox(`obstacle${index}`, {
                width: OBSTACLE_BOX_SIZE,
                height: OBSTACLE_BOX_SIZE,
                depth: 10
            }, this.scene);
            const material = new BABYLON.StandardMaterial(`obstacleMat${index}`, this.scene);
            material.diffuseColor = OBSTACLE_COLOR;
            material.emissiveColor = OBSTACLE_EMISSIVE;
            mesh.material = material;
            return mesh;
        });
    }

    private updatePositions(state: GameState) {
        const toWorldX = (x: number) => (x / this.config.WIDTH - 0.5) * this.config.WIDTH;
        const toWorldY = (y: number) => (0.5 - y / this.config.HEIGHT) * this.config.HEIGHT;

        const ballCenterX = state.ball.x + this.config.BALL_SIZE / 2;
        const ballCenterY = state.ball.y + this.config.BALL_SIZE / 2;
        this.ballMesh.position.set(toWorldX(ballCenterX), toWorldY(ballCenterY), 0);

        const paddleCenter1 = state.paddle1.y + this.config.PADDLE_HEIGHT / 2;
        const paddleCenter2 = state.paddle2.y + this.config.PADDLE_HEIGHT / 2;
        this.paddle1Mesh.position.set(-this.config.WIDTH / 2 + this.config.PADDLE_WIDTH / 2, toWorldY(paddleCenter1), 0);
        this.paddle2Mesh.position.set(this.config.WIDTH / 2 - this.config.PADDLE_WIDTH / 2, toWorldY(paddleCenter2), 0);

        state.obstacles.forEach((obstacle, index) => {
            const mesh = this.obstacleMeshes[index];
            if (!mesh) {
                return;
            }
            const centerX = obstacle.x + obstacle.width / 2;
            const centerY = obstacle.y + obstacle.height / 2;
            const sizeX = (obstacle.width / this.config.WIDTH) * this.config.WIDTH;
            const sizeY = (obstacle.height / this.config.HEIGHT) * this.config.HEIGHT;
            mesh.position.set(toWorldX(centerX), toWorldY(centerY), 0);
            mesh.scaling.set(sizeX, sizeY, this.config.PADDLE_WIDTH);
        });
    }

    private updateScores(state: GameState) {
        if (this.scoreText1) {
            this.scoreText1.text = String(state.score.player1);
        }
        if (this.scoreText2) {
            this.scoreText2.text = String(state.score.player2);
        }
    }

    private updateOverlay(state: GameState, mode: string, difficulty: string) {
        if (!this.overlayText || !this.overlaySubtext) {
            return;
        }
        if (!state.started) {
            const title = mode === 'ai'
                ? `${t('game.status.vsAI')} - ${difficulty.toUpperCase()}`
                : mode === 'remote'
                ? t('game.status.onlineMatch')
                : t('game.status.localMultiplayer');
            const subtitle = mode === 'remote'
                ? t('game.status.waitingToStart')
                : t('game.status.pressSpace');
            this.overlayText.text = title;
            this.overlaySubtext.text = subtitle;
            this.overlayText.isVisible = true;
            this.overlaySubtext.isVisible = true;
        } else if (state.paused) {
            this.overlayText.text = t('game.status.paused');
            this.overlaySubtext.text = t('game.status.pressToContinue');
            this.overlayText.isVisible = true;
            this.overlaySubtext.isVisible = true;
        } else if (state.gameOver) {
            const winnerText = state.winner === 'player1'
                ? t('game.status.player1Wins')
                : t('game.status.player2Wins');
            this.overlayText.text = winnerText;
            this.overlaySubtext.text = '';
            this.overlayText.isVisible = true;
            this.overlaySubtext.isVisible = false;
        } else {
            this.overlayText.isVisible = false;
            this.overlaySubtext.isVisible = false;
        }
    }
}
