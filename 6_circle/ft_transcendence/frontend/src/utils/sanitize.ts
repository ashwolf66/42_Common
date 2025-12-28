/**
 * HTML 이스케이프 함수 - XSS 공격 방어
 */
export function escapeHtml(text: string): string {
    const div = document.createElement('div');
    div.textContent = text;
    return div.innerHTML;
}

/**
 * 안전하게 HTML 속성 값 이스케이프
 */
export function escapeAttribute(text: string): string {
    return text
        .replace(/&/g, '&amp;')
        .replace(/"/g, '&quot;')
        .replace(/'/g, '&#x27;')
        .replace(/</g, '&lt;')
        .replace(/>/g, '&gt;');
}

/**
 * 사용자 입력 검증 및 정제
 */
export function sanitizeInput(input: string, maxLength: number = 1000): string {
    return input.trim().slice(0, maxLength);
}
