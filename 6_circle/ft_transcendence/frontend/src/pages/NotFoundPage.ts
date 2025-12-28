import { t } from '../l10n/index';

export class NotFoundPage {
    async render() {
        return `
            <div class="min-h-screen flex items-center justify-center px-4">
                <div class="text-center">
                    <h1 class="text-9xl font-bold text-primary-400">404</h1>
                    <h2 class="text-3xl font-bold mt-4 mb-2">${t("notFound.title")}</h2>
                    <p class="text-gray-400 mb-8">${t("notFound.description")}</p>
                    <a href="/" data-link class="btn btn-primary">${t("notFound.goHome")}</a>
                </div>
            </div>
        `;
    }
}
