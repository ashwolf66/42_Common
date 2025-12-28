import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';
import { defineConfig } from 'vite';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const sslKeyPath = path.resolve(__dirname, './ssl/key.pem');
const sslCertPath = path.resolve(__dirname, './ssl/cert.pem');
const env = (globalThis as unknown as { process?: { env?: Record<string, string> } }).process?.env;

// Check if SSL files exist
const hasSSL = fs.existsSync(sslKeyPath) && fs.existsSync(sslCertPath);

export default defineConfig({
    server: {
        https: hasSSL ? {
            key: fs.readFileSync(sslKeyPath),
            cert: fs.readFileSync(sslCertPath)
        } : undefined,
        host: '0.0.0.0',
        port: 3000,
        strictPort: true,
        hmr: {
            protocol: hasSSL ? 'wss' : 'ws',
            host: env?.VITE_HMR_HOST,
            port: 3000
        },
        proxy: {
            '/api': {
                target: 'https://ft_backend:4000',
                changeOrigin: true,
                secure: false
            },
            '/ws': {
                target: 'wss://ft_backend:4000',
                ws: true,
                secure: false,
                changeOrigin: true
            },
            '/uploads': {
                target: 'https://ft_backend:4000',
                changeOrigin: true,
                secure: false
            }
        }
    },
    build: {
        outDir: 'dist',
        assetsDir: 'assets'
    }
});
