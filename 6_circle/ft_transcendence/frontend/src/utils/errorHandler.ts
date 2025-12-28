// utils/errorHandler.ts
// Utility to translate backend error codes to localized messages

import { t } from '../l10n';

interface ErrorResponse {
  errorCode?: string;
  error?: string; // fallback for old-style errors
  message?: string;
}

/**
 * Translates backend error code to localized error message
 * @param errorCode - Error code from backend (e.g., "MISSING_REQUIRED_FIELDS")
 * @param category - Error category (e.g., "auth", "users", "tournaments")
 * @param params - Optional parameters for string interpolation
 * @returns Localized error message
 */
export function translateError(
  errorCode: string,
  category: string,
  params?: Record<string, string | number>
): string {
  const key = `errors.${category}.${errorCode}`;
  const translated = t(key, params);

  // If translation key not found, return the error code itself
  if (translated === key) {
    return errorCode.replace(/_/g, ' ').toLowerCase();
  }

  return translated;
}

/**
 * Extracts and translates error from API response
 * @param error - Error response from API
 * @returns Localized error message
 */
export function getErrorMessage(error: any): string {
  // Handle axios error structure
  const data: ErrorResponse = error?.response?.data || error;

  // If errorCode is present, translate it
  if (data.errorCode) {
    // Try to infer category from error code
    const category = inferCategory(data.errorCode);
    return translateError(data.errorCode, category);
  }

  // Fallback to old-style error message
  if (data.error) {
    return data.error;
  }

  if (data.message) {
    return data.message;
  }

  // Generic fallback
  return t('errors.generic.INTERNAL_SERVER_ERROR');
}

/**
 * Infers error category from error code
 * @param errorCode - Error code string
 * @returns Category name
 */
function inferCategory(errorCode: string): string {
  // Auth related errors
  if (errorCode.includes('CREDENTIALS') ||
      errorCode.includes('LOGIN') ||
      errorCode.includes('REGISTER') ||
      errorCode.includes('2FA') ||
      errorCode.includes('TOKEN') ||
      errorCode.includes('PASSWORD')) {
    return 'auth';
  }

  // User related errors
  if (errorCode.includes('USER') ||
      errorCode.includes('AVATAR') ||
      errorCode.includes('EMAIL') ||
      errorCode.includes('DISPLAY_NAME') ||
      errorCode.includes('USERNAME')) {
    return 'users';
  }

  // Game related errors
  if (errorCode.includes('GAME') ||
      errorCode.includes('MATCH')) {
    return 'games';
  }

  // Tournament related errors
  if (errorCode.includes('TOURNAMENT') ||
      errorCode.includes('ALIAS')) {
    return 'tournaments';
  }

  // Friend related errors
  if (errorCode.includes('FRIEND')) {
    return 'friends';
  }

  // Middleware related errors
  if (errorCode.includes('TOKEN') ||
      errorCode.includes('ACCESS')) {
    return 'middleware';
  }

  // Default to generic
  return 'generic';
}

/**
 * Creates a user-friendly error message from various error types
 * @param error - Any error object
 * @returns User-friendly error message
 */
export function formatErrorMessage(error: any): string {
  if (typeof error === 'string') {
    return error;
  }

  if (error?.response?.data) {
    return getErrorMessage(error);
  }

  if (error?.message) {
    return error.message;
  }

  return t('errors.generic.INTERNAL_SERVER_ERROR');
}
