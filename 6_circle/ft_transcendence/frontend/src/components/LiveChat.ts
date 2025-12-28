// front/src/components/LiveChat.ts
// 템플릿 + DOMpick + UI 이벤트 initChatLogic 처리

import { t } from "../l10n/index";
import { initChatLogic } from "../utils/livechat";
import { escapeHtml } from "../utils/sanitize";
import ApiService from "../services/ApiService";

type DomRefs = {
  globalBox: HTMLDivElement;
  input: HTMLInputElement;
  form: HTMLFormElement;
  sendButton: HTMLButtonElement;
};

export function createChatComponent(): string {
  return `
    <div id="chat-wrap" class="flex flex-col h-[400px]">
      <h3 class="text-xl font-semibold mb-3 text-primary-400">
        💬 ${t("chat.title")}
      </h3>
      <div class="flex-1 flex flex-col">
        <div class="relative flex-1 overflow-hidden bg-gray-800 rounded border border-gray-700">
          <div
            id="chat-box"
            class="absolute inset-0 overflow-y-auto p-3 break-words"
          ></div>
        </div>
        <form id="chat-form" class="mt-3 flex gap-2">
          <input
            id="chat-input"
            placeholder="✍️ ${t("chat.placeholder")}"
            class="flex-1 min-w-0 px-3 py-2 bg-gray-800 text-white border border-gray-700 rounded focus:outline-none focus:border-primary-400 placeholder:text-sm placeholder:text-gray-400"
          />
          <button
            id="chat-button"
            class="px-4 py-2 bg-primary-600 hover:bg-primary-700 text-white rounded font-medium transition-colors"
            type="submit"
          >
            📤 ${t("chat.send")}
          </button>
        </form>
      </div>
    </div>
  `;
}

export function mountLiveChat(alias: string) {
  const dom = pickDom();
  if (!dom) {
    console.warn("[chat] Required DOM elements missing; live chat disabled");
    return () => { };
  }
  // 비즈니스 로직 초기화
  let chatLogic: ReturnType<typeof initChatLogic>;
  chatLogic = initChatLogic(alias, dom, {
    onUserClick: (username, event) => {
      showUserContextMenu(username, event, chatLogic);
    }
  });
  // UI 이벤트 핸들러 등록
  attachUiHandlers(dom, chatLogic);
  return chatLogic.dispose;
}

function pickDom(): DomRefs | null {
  const globalBox = document.getElementById("chat-box") as HTMLDivElement;
  const input = document.getElementById("chat-input") as HTMLInputElement;
  const form = document.getElementById("chat-form") as HTMLFormElement;
  const sendButton = document.getElementById("chat-button") as HTMLButtonElement;

  if (!globalBox || !input || !form || !sendButton) {
    return null;
  }

  return {
    globalBox,
    input,
    form,
    sendButton,
  };
}

function showUserContextMenu(username: string, event: MouseEvent, chatLogic: ReturnType<typeof initChatLogic>) {
  // 기존 메뉴 제거
  const existingMenu = document.getElementById("user-context-menu");
  if (existingMenu)
    existingMenu.remove();

  // Prevent default context menu
  event.preventDefault();
  event.stopPropagation();

  let currentUser: { username?: string } = {};
  try {
    const rawUser = localStorage.getItem('user');
    if (rawUser) currentUser = JSON.parse(rawUser);
  } catch {
    currentUser = {};
  }
  const isSelf = username === currentUser.username;

  // 컨텍스트 메뉴 생성
  const menu = document.createElement("div");
  menu.id = "user-context-menu";
  menu.className = "fixed z-50 bg-white border border-gray-300 rounded-lg shadow-lg p-2 space-y-1 min-w-[180px]";

  // Calculate position relative to viewport
  const menuWidth = 180;
  const menuHeight = 100;
  let left = event.clientX;
  let top = event.clientY;

  // Adjust if menu would go off-screen
  if (left + menuWidth > window.innerWidth) {
    left = window.innerWidth - menuWidth - 10;
  }
  if (top + menuHeight > window.innerHeight) {
    top = window.innerHeight - menuHeight - 10;
  }

  menu.style.left = `${left}px`;
  menu.style.top = `${top}px`;
  menu.innerHTML = `
    <div class="app-livechat-user">
      ${escapeHtml(username)}
    </div>
    <button data-action="profile" class="app-livechat-item" ${isSelf ? 'disabled' : ''}>
      👤 ${t("chat.menu.viewProfile")}
    </button>
    <button data-action="invite" class="app-livechat-item" ${isSelf ? 'disabled' : ''}>
      🎮 ${t("chat.menu.inviteToGame")}
    </button>
  `;
  document.body.appendChild(menu);

  console.log('[LiveChat] Context menu created for user:', username);

  // 메뉴 버튼 클릭 핸들러
  menu.addEventListener("click", async (e) => {
    e.stopPropagation();
    const button = (e.target as HTMLElement).closest("button");
    if (!button)
      return;

    const action = button.dataset.action;
    console.log('[LiveChat] Menu action clicked:', action, 'for user:', username);

    if (action === "profile") {
      if (isSelf) {
        console.log('[LiveChat] Cannot view own profile from chat');
        menu.remove();
        return;
      }
      const targetId = await resolveUserId(username);
      if (!targetId) {
        alert(t('friends.noUsersFound'));
        menu.remove();
        return;
      }
      sessionStorage.setItem("profileTargetId", String(targetId));
      console.log('[LiveChat] Navigating to profile for:', username, 'id:', targetId);
      // Use router navigation
      const router = (window as any).router;
      if (router) {
        router.navigateTo("/profile");
      } else {
        window.location.href = "/profile";
      }
    } else if (action === "invite") {
      if (isSelf) {
        alert(t("chat.menu.cannotInviteSelf"));
        menu.remove();
        return;
      }
      console.log('[LiveChat] Inviting user to game:', username);
      chatLogic.inviteToGame(username);
    }
    menu.remove();
  });

  // 외부 클릭 시 메뉴 닫기
  const closeMenu = (e: MouseEvent) => {
    if (!menu.contains(e.target as Node)) {
      menu.remove();
      document.removeEventListener("click", closeMenu);
    }
  };
  setTimeout(() => document.addEventListener("click", closeMenu), 0);
}

function attachUiHandlers(dom: DomRefs, chatLogic: ReturnType<typeof initChatLogic>) {
  // 메시지 전송
  dom.form.addEventListener("submit", (event) => {
    event.preventDefault();
    const raw = dom.input.value.trim();
    if (!raw)
      return;
    const success = chatLogic.sendMessage(raw);
    if (success) {
      dom.input.value = "";
    }
  });

  // 유저명 클릭은 메시지 렌더링 시 개별 버튼에서 처리
}

async function resolveUserId(username: string): Promise<number | null> {
  if (!username || username.length < 1) return null;

  try {
    const response = await ApiService.get(`/users/search?q=${encodeURIComponent(username)}`);
    const users = response.users || [];
    const exactMatch = users.find((user: any) => user.username === username);
    const fallback = exactMatch || (users.length === 1 ? users[0] : null);
    return fallback?.id ?? null;
  } catch (error) {
    console.error('[LiveChat] Failed to resolve user ID:', error);
    return null;
  }
}
