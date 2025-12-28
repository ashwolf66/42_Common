import {
  getAvailableLanguages,
  getCurrentLanguage,
  getLanguageLabel,
  setLanguage,
  t,
  type Language,
} from "../l10n/index";

type DomRefs = {
  root: HTMLElement;
  select: HTMLSelectElement;
  label: HTMLLabelElement;
};

function optionTemplate(lang: Language): string {
  const selected = lang === getCurrentLanguage() ? " selected" : "";
  return `<option value="${lang}"${selected}>${getLanguageLabel(lang)}</option>`;
}

export function createLanguageSwitcher(wrapperClass?: string): string {
  const options = getAvailableLanguages().map((lang) => optionTemplate(lang)).join("");
  const innerHtml = `
    <div class="flex items-center gap-2"
         data-language-switcher>
      <label for="language-select" class="font-medium text-gray-300 text-sm">${t("language.selectLabel")}</label>
      <select id="language-select" class="px-2 py-1 text-sm bg-gray-800 text-white border border-gray-700 rounded focus:outline-none focus:border-primary-400">
        ${options}
      </select>
    </div>
  `;
  if (wrapperClass) {
    return `<div class="${wrapperClass}">${innerHtml}</div>`;
  }
  return innerHtml;
}

export function initLanguageSwitcher(): () => void {
  const dom = pickDom();
  if (!dom) {
    console.warn("[language-switcher] Root not found");
    return () => { };
  }
  return attachUiHandlers(dom);
}

function pickDom(): DomRefs | null {
  const root = document.querySelector<HTMLElement>(`[data-language-switcher]`);
  if (!root)
    return null;
  const select = root.querySelector<HTMLSelectElement>("#language-select");
  const label = root.querySelector<HTMLLabelElement>("label");
  if (!select || !label)
    return null;
  return { root, select, label };
}

function attachUiHandlers(dom: DomRefs): () => void {
  const render = () => {
    dom.label.textContent = t("language.selectLabel");
    for (const option of Array.from(dom.select.options)) {
      const value = option.value as Language;
      option.textContent = getLanguageLabel(value);
      option.selected = value === getCurrentLanguage();
    }
  };

  render();
  const onChange = (event: Event) => {
    const value = (event.target as HTMLSelectElement).value as Language;
    setLanguage(value);
  };
  dom.select.addEventListener("change", onChange);
  return () => {
    dom.select.removeEventListener("change", onChange);
  };
}
