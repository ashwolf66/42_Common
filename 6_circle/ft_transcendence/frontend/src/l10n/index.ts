// front/src/l10n/index.ts
// l10n is short for localization.
// Lightweight localization helper with string interpolation support.

import enTranslations from "./locales/en.json";
import koTranslations from "./locales/ko.json";
import esTranslations from "./locales/es.json";

export type Language = "en" | "ko" | "es";

type TranslationValue = string | TranslationMap;
type TranslationMap = { [key: string]: TranslationValue };

type TranslationParams = Record<string, string | number>;

const STORAGE_KEY = "language";
const DEFAULT_LANGUAGE: Language = "ko";

const translations: Record<Language, TranslationMap> = {
  en: enTranslations as TranslationMap,
  ko: koTranslations as TranslationMap,
  es: esTranslations as TranslationMap,
};

const languageOrder: Language[] = ["en", "ko", "es"];

const languageLabels: Record<Language, string> = {
  en: "English",
  ko: "한국어",
  es: "Español",
};

let currentLanguage: Language = DEFAULT_LANGUAGE;
const listeners = new Set<() => void>();

export function initL10n() {
  let lang: Language = DEFAULT_LANGUAGE;

  try {
    lang = (localStorage.getItem(STORAGE_KEY) as Language) ?? DEFAULT_LANGUAGE;
  } catch {
    // storage 접근 불가 상황 시크릿모드 에서 브라우저가 로컬 스토리지에 접근할 수 없게 막는 경우
  }
  currentLanguage = lang;
  document.documentElement.lang = lang;
}

export function t(key: string, params?: TranslationParams): string {
  const lang: Language = currentLanguage ?? DEFAULT_LANGUAGE;
  const segments = key.split(".");
  let node: TranslationValue | undefined = translations[lang];
  for (const segment of segments) {
    if (!node || typeof node === "string") return key;
    node = node[segment];
  }
  if (typeof node !== "string") return key;
  if (!params) return node;
  return node.replace(/\{(\w+)\}/g, (_, token) => {
    const value = params[token];
    return value === undefined ? `{${token}}` : String(value);
  });
}

export function setLanguage(lang: Language) {
  if (lang === currentLanguage) return;
  currentLanguage = lang;
  try {
    localStorage.setItem(STORAGE_KEY, lang);
  } catch {
    // Ignore persistence errors
  }
  document.documentElement.lang = lang;
  for (const listener of listeners) {
    listener();
  }
}

export function getCurrentLanguage(): Language {
  return currentLanguage;
}

export function getAvailableLanguages(): Language[] {
  return [...languageOrder];
}

export function getLanguageLabel(lang: Language): string {
  return languageLabels[lang] ?? lang;
}

export function onLanguageChange(listener: () => void): () => void {
  listeners.add(listener);
  return () => listeners.delete(listener);
}
