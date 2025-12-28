/**
 * 사용자 입력 검증 및 정제 유틸리티
 */

/**
 * 문자열에서 HTML 태그 제거
 */
function stripHtmlTags(str) {
    if (!str) return '';
    return str.replace(/<[^>]*>/g, '');
}

/**
 * 문자열 길이 제한 및 트림
 */
function sanitizeString(str, maxLength = 1000) {
    if (!str) return '';
    return stripHtmlTags(str).trim().slice(0, maxLength);
}

/**
 * 사용자 이름 검증
 */
function validateUsername(username) {
    if (!username) return { valid: false, error: 'Username is required' };
    
    const sanitized = sanitizeString(username, 20);
    
    if (sanitized.length < 3) {
        return { valid: false, error: 'Username must be at least 3 characters' };
    }
    
    if (sanitized.length > 20) {
        return { valid: false, error: 'Username must not exceed 20 characters' };
    }
    
    if (!/^[a-zA-Z0-9_]+$/.test(sanitized)) {
        return { valid: false, error: 'Username can only contain letters, numbers, and underscores' };
    }
    
    return { valid: true, value: sanitized };
}

/**
 * 이메일 검증
 */
function validateEmail(email) {
    if (!email) return { valid: false, error: 'Email is required' };
    
    const sanitized = sanitizeString(email, 254);
    
    // RFC 5322 기반 간단한 이메일 정규식
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    
    if (!emailRegex.test(sanitized)) {
        return { valid: false, error: 'Invalid email format' };
    }
    
    return { valid: true, value: sanitized.toLowerCase() };
}

/**
 * Display Name 검증
 */
function validateDisplayName(displayName) {
    if (!displayName) return { valid: true, value: null };
    
    const sanitized = sanitizeString(displayName, 50);
    
    if (sanitized.length > 50) {
        return { valid: false, error: 'Display name must not exceed 50 characters' };
    }
    
    return { valid: true, value: sanitized };
}

/**
 * 토너먼트 이름 검증
 */
function validateTournamentName(name) {
    if (!name) return { valid: false, error: 'Tournament name is required' };
    
    const sanitized = sanitizeString(name, 100);
    
    if (sanitized.length < 3) {
        return { valid: false, error: 'Tournament name must be at least 3 characters' };
    }
    
    if (sanitized.length > 100) {
        return { valid: false, error: 'Tournament name must not exceed 100 characters' };
    }
    
    return { valid: true, value: sanitized };
}

module.exports = {
    stripHtmlTags,
    sanitizeString,
    validateUsername,
    validateEmail,
    validateDisplayName,
    validateTournamentName
};
