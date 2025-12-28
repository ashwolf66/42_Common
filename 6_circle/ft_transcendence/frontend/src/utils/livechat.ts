// Live chat WebSocket logic handler

import { escapeHtml } from './sanitize';
import { t } from '../l10n/index';

type DomRefs = {
  globalBox: HTMLDivElement;
  input: HTMLInputElement;
  form: HTMLFormElement;
  sendButton: HTMLButtonElement;
};

type ChatMessage = {
  type: string;
  from?: string;
  to?: string;
  text?: string;
  url?: string;
  roomName?: string | null;
  gameMode?: string | null;
  prefix?: string;
  subfix?: string;
  username?: string;
  user?: string;
  status?: string;
  users?: Array<{ username: string }>;
  reason?: string;
  action?: string;
  tournamentId?: number | string;
  name?: string;
  ts?: number;
  matchCount?: number;
  winner?: string;
  round?: number;
  score?: string;
  currentRound?: number;
  totalRounds?: number;
  winnersCount?: number;
  player1?: string;
  player2?: string;
  winnerScore?: number;
  loserScore?: number;
};

export function initChatLogic(
  alias: string,
  dom: DomRefs,
  options?: { onUserClick?: (username: string, event: MouseEvent) => void }
) {
  let ws: WebSocket | null = null;
  let reconnectTimer: ReturnType<typeof setTimeout> | null = null;

  const connect = () => {
    const host = window.location.host;
    const token = localStorage.getItem('auth_token');

    if (!token) {
      console.error('No auth token found. Please login first.');
      window.location.href = '/login';
      return;
    }

    const wsUrl = `wss://${host}/ws/livechat?token=${encodeURIComponent(token)}`;
    ws = new WebSocket(wsUrl);

    ws.onopen = () => {
      console.log('WebSocket connected');
      // Send join message to receive presence snapshot and notify others
      // Username is already authenticated via token, but we still send join to trigger presence updates
      ws?.send(JSON.stringify({ type: 'join', payload: {} }));
    };

    ws.onmessage = (event) => {
      try {
        const msg: ChatMessage = JSON.parse(event.data);
        handleMessage(msg);
      } catch (error) {
        console.error('Failed to parse message:', error);
      }
    };

    ws.onerror = (error) => {
      console.error('WebSocket error:', error);
    };

    ws.onclose = () => {
      console.log('WebSocket closed');
      ws = null;
      // Attempt reconnection after 3 seconds
      reconnectTimer = setTimeout(() => {
        console.log('Attempting to reconnect...');
        connect();
      }, 3000);
    };
  };

  const handleMessage = (msg: ChatMessage) => {
    switch (msg.type) {
      case 'chat':
        appendChatMessage(msg.from || 'Unknown', msg.text || '');
        break;
      case 'dm':
        appendDirectMessage(msg.from || '', msg.to || '', msg.text || '');
        break;
      case 'enter':
        const username = msg.username || msg.from || '';
        const action = msg.action || 'joined';
        let enterMessage = '';

        if (action === 'joined') {
          enterMessage = `🟢 ${t('chat.system.userJoined', { user: username })}`;
        } else if (action === 'left') {
          enterMessage = `🔴 ${t('chat.system.userLeft', { user: username })}`;
        } else {
          // Fallback for old format
          enterMessage = `${msg.prefix || ''} ${username} ${msg.subfix || ''}`;
        }

        appendSystemMessage(enterMessage);
        break;
      case 'invite':
        appendInviteMessage(msg);
        break;
      case 'tournament':
        appendTournamentMessage(msg);
        break;
      case 'sys':
        appendSystemMessage(msg.text || '');
        break;
      case 'presence_snapshot':
        // Handle online users list if needed
        break;
      case 'presence_update':
        // Handle user online/offline status if needed
        break;
      case 'error':
        handleError(msg.reason || 'unknown_error', msg);
        break;
      case 'block_update':
        const blockUsername = msg.username || '';
        const blockAction = msg.action || '';
        let blockMessage = '';

        if (blockAction === 'blocked') {
          blockMessage = t('chat.system.userBlocked', { user: blockUsername });
        } else if (blockAction === 'unblocked') {
          blockMessage = t('chat.system.userUnblocked', { user: blockUsername });
        } else if (blockAction === 'already_blocked') {
          blockMessage = t('chat.system.alreadyBlocked', { user: blockUsername });
        } else if (blockAction === 'not_blocked') {
          blockMessage = t('chat.system.notBlocked', { user: blockUsername });
        } else {
          blockMessage = `Block update: ${blockAction} - ${blockUsername}`;
        }

        appendSystemMessage(blockMessage);
        break;
      case 'block_notice':
        const blocker = msg.from || '';
        appendSystemMessage(t('chat.system.blockedBy', { user: blocker }));
        break;
      case 'unblock_notice':
        const unblocker = msg.from || '';
        appendSystemMessage(t('chat.system.unblockedBy', { user: unblocker }));
        break;
      default:
        console.log('Unknown message type:', msg.type);
    }
  };

  const appendChatMessage = (from: string, text: string) => {
    const messageDiv = document.createElement('div');
    messageDiv.className = 'mb-2';
    messageDiv.innerHTML = `
      <button type="button" class="font-bold username-link cursor-pointer hover:underline text-primary-400 bg-transparent border-none" data-username="${escapeHtml(from)}">
        ${escapeHtml(from)}
      </button>
      <span class="text-gray-500">: </span>
      <span class="text-gray-200">${escapeHtml(text)}</span>
    `;
    const button = messageDiv.querySelector('.username-link') as HTMLButtonElement | null;
    if (button && options?.onUserClick) {
      button.addEventListener('click', (event) => {
        options.onUserClick?.(from, event as MouseEvent);
      });
    }
    dom.globalBox.appendChild(messageDiv);
    dom.globalBox.scrollTop = dom.globalBox.scrollHeight;
  };

  const appendDirectMessage = (from: string, to: string, text: string) => {
    const messageDiv = document.createElement('div');
    messageDiv.className = 'mb-2 bg-blue-900 bg-opacity-30 p-2 rounded border border-blue-700';
    const currentUser = alias;
    const isFromMe = from === currentUser;
    const displayText = isFromMe
      ? `[DM to ${escapeHtml(to)}]: ${escapeHtml(text)}`
      : `[DM from ${escapeHtml(from)}]: ${escapeHtml(text)}`;
    messageDiv.innerHTML = `<span class="text-blue-300 text-sm">${displayText}</span>`;
    dom.globalBox.appendChild(messageDiv);
    dom.globalBox.scrollTop = dom.globalBox.scrollHeight;
  };

  const appendSystemMessage = (text: string) => {
    const messageDiv = document.createElement('div');
    messageDiv.className = 'mb-2 text-center';
    messageDiv.innerHTML = `<span class="text-gray-400 text-sm italic">${escapeHtml(text)}</span>`;
    dom.globalBox.appendChild(messageDiv);
    dom.globalBox.scrollTop = dom.globalBox.scrollHeight;
  };

  const appendInviteMessage = (msg: ChatMessage) => {
    const from = msg.from || '';
    const to = msg.to || '';
    const roomName = msg.roomName || '';
    const gameMode = msg.gameMode || 'classic';
    const url = msg.url || '/game/remote';

    // Get current user to check if this invite is for them
    let currentUser: { username?: string } = {};
    try {
      const rawUser = localStorage.getItem('user');
      if (rawUser) currentUser = JSON.parse(rawUser);
    } catch {
      currentUser = {};
    }

    const isRecipient = currentUser.username === to;
    const isSender = currentUser.username === from;

    const messageDiv = document.createElement('div');
    messageDiv.className = 'mb-2 bg-gradient-to-r from-purple-900/30 to-blue-900/30 p-3 rounded border border-purple-700';

    let content = '';
    if (isRecipient) {
      // Message for recipient - show accept button
      content = `
        <div class="font-semibold text-purple-300 mb-1">🎮 ${escapeHtml(from)} ${t('chat.invite.invitedYou')}</div>
        <div class="text-xs text-gray-400 mb-2">${t('chat.invite.roomLabel')} <span class="font-bold text-purple-400">${escapeHtml(roomName)}</span></div>
        <div class="text-xs text-gray-400 mb-2">${t('chat.invite.gameMode')}: <span class="font-bold">${escapeHtml(gameMode)}</span></div>
        <button class="btn btn-primary btn-sm invite-accept-btn" data-room="${escapeHtml(roomName)}" data-url="${escapeHtml(url)}">
          ✓ ${t('chat.invite.accept')}
        </button>
      `;
    } else if (isSender) {
      // Message for sender - show sent confirmation
      content = `
        <div class="font-semibold text-purple-300 mb-1">🎮 ${t('chat.invite.sentTo', { user: escapeHtml(to) })}</div>
        <div class="text-xs text-gray-400 mb-2">${t('chat.invite.roomLabel')} <span class="font-bold text-purple-400">${escapeHtml(roomName)}</span></div>
        <div class="text-xs text-gray-400 mb-2">${t('chat.invite.gameMode')}: <span class="font-bold">${escapeHtml(gameMode)}</span></div>
        <a href="${escapeHtml(url)}" class="btn btn-secondary btn-sm" data-link>
          ${t('chat.invite.joinRoom')}
        </a>
      `;
    }

    messageDiv.innerHTML = content;

    // Add click handler for accept button (recipient only)
    if (isRecipient) {
      const acceptBtn = messageDiv.querySelector('.invite-accept-btn') as HTMLButtonElement;
      if (acceptBtn) {
        acceptBtn.addEventListener('click', () => {
          const url = acceptBtn.dataset.url || '/game/remote';
          const router = (window as any).router;
          if (router) {
            router.navigateTo(url);
          } else {
            window.location.href = url;
          }
        });
      }
    }

    dom.globalBox.appendChild(messageDiv);
    dom.globalBox.scrollTop = dom.globalBox.scrollHeight;
  };

  const appendTournamentMessage = (msg: ChatMessage) => {
    const name = msg.name || '';
    const url = msg.url || (msg.tournamentId ? `/tournament/${msg.tournamentId}` : '/tournament');
    const messageDiv = document.createElement('div');
    messageDiv.className = 'mb-2 bg-gray-750 p-3 rounded border border-gray-700';
    const action = msg.action || 'updated';
    let text = '';
    if (action === 'created') {
      text = t('chat.tournament.created', {
        name: escapeHtml(name),
        user: escapeHtml(msg.user || msg.username || '')
      });
    } else if (action === 'started') {
      text = t('chat.tournament.started', {
        name: escapeHtml(name),
        matchCount: msg.matchCount || 0
      });
    } else if (action === 'joined') {
      text = t('chat.tournament.joined', {
        name: escapeHtml(name),
        user: escapeHtml(msg.username || '')
      });
    } else if (action === 'finished') {
      text = t('chat.tournament.finished', {
        tournamentName: escapeHtml(name),
        winner: escapeHtml(msg.winner || '')
      });
    } else if (action === 'match_finished') {
      text = t('chat.tournament.matchFinished', {
        tournamentName: escapeHtml(name),
        round: msg.round || '',
        player1: escapeHtml(msg.player1 || ''),
        player2: escapeHtml(msg.player2 || ''),
        winner: escapeHtml(msg.winner || ''),
        winnerScore: msg.winnerScore || '',
        loserScore: msg.loserScore || ''
      });
    } else if (action === 'round_advanced') {
      text = t('chat.tournament.roundCompleted', {
        tournamentName: escapeHtml(name),
        round: msg.currentRound ? msg.currentRound - 1 : '',
        winnersCount: msg.winnersCount || '',
        nextRound: msg.currentRound || ''
      });
    } else {
      text = t('chat.tournament.updated', { name: escapeHtml(name) });
    }
    messageDiv.innerHTML = `
      <div class="font-semibold text-primary-300 mb-1">🏆${text}</div>
      <a href="${escapeHtml(url)}" class="btn btn-secondary btn-sm" data-link>
        ${t('chat.tournament.view')}
      </a>
    `;
    dom.globalBox.appendChild(messageDiv);
    dom.globalBox.scrollTop = dom.globalBox.scrollHeight;
  };

  const handleError = (reason: string, msg: ChatMessage) => {
    let errorText = '';

    switch (reason) {
      case 'invalid_username':
        errorText = t('chat.errors.invalidUsername');
        break;
      case 'session_replaced':
        errorText = t('chat.errors.sessionReplaced');
        break;
      case 'not_authenticated':
        errorText = t('chat.errors.notAuthenticated');
        break;
      case 'invalid_dm_target':
        errorText = t('chat.errors.invalidDmTarget');
        break;
      case 'invalid_invite_target':
        errorText = t('chat.errors.invalidInvite');
        break;
      case 'themselfves':
        errorText = t('chat.errors.cannotMessageSelf');
        break;
      case 'user_is_not_online':
        errorText = t('chat.errors.userNotOnline', { user: msg.to || '' });
        break;
      case 'you_blocked_user':
        errorText = t('chat.errors.youBlockedUser', { user: msg.to || '' });
        break;
      case 'blocked_by_user':
        errorText = t('chat.errors.blockedByUser', { user: msg.to || '' });
        break;
      case 'invalid_block_target':
        errorText = t('chat.errors.invalidBlockTarget');
        break;
      case 'server_error':
        errorText = t('chat.errors.serverError', { message: (msg as any).message || '' });
        break;
      case 'invalid_message_format':
        errorText = t('chat.errors.invalidMessageFormat');
        break;
      case 'missing_message_type':
        errorText = t('chat.errors.missingMessageType');
        break;
      case 'unknown_message_type':
        errorText = t('chat.errors.unknownMessageType');
        break;
      default:
        errorText = t('chat.errors.generic', { reason });
        break;
    }
    appendSystemMessage(`❌ ${errorText}`);
  };

  const sendMessage = (text: string): boolean => {
    if (!ws || ws.readyState !== WebSocket.OPEN) {
      appendSystemMessage(`❌ ${t('chat.errors.notConnected')}`);
      return false;
    }
    const message = { type: 'chat', payload: { username: alias, text } };
    console.log('Sending message:', message);
    ws.send(JSON.stringify(message));
    return true;
  };

  const sendInvite = (to: string) => {
    if (!ws || ws.readyState !== WebSocket.OPEN) {
      appendSystemMessage(t('chat.errors.notConnected'));
      return false;
    }
    const message = {
      type: 'invite',
      payload: {
        to
      }
    };
    ws.send(JSON.stringify(message));
    appendSystemMessage(t('chat.actions.inviteSent', { target: to }));
    return true;
  };

  const inviteToGame = (username: string) => {
    sendInvite(username);
  };

  const dispose = () => {
    if (reconnectTimer) {
      clearTimeout(reconnectTimer);
    }
    if (ws) {
      ws.send(JSON.stringify({ type: 'leave', payload: { username: alias } }));
      ws.close();
      ws = null;
    }
  };

  connect();

  return {
    sendMessage,
    inviteToGame,
    dispose
  };
}
