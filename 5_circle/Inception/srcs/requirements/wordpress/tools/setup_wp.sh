#!/bin/bash

echo "mariadb to be ready..."
sleep 10

export HTTP_HOST="jacha.42.fr"

read_secret() { [ -f "$1" ] && tr -d '\r\n' < "$1"; }
export DB_PASSWORD="${DB_PASSWORD:-$(read_secret /run/secrets/db_password)}"
export WP_ADMIN_PASSWORD="${WP_ADMIN_PASSWORD:-$(read_secret /run/secrets/wp_admin_password)}"
export WP_USER_PASSWORD="${WP_USER_PASSWORD:-$(read_secret /run/secrets/wp_user_password)}"


if [ ! -f /var/www/html/wp-config.php ]; then
    echo "Downloading WordPress core..."
    wp core download --allow-root
    
    echo "Creating wp-config.php..."
    wp config create \
        --dbname="$DB_NAME" \
        --dbuser="$DB_USER" \
        --dbpass="$DB_PASSWORD" \
        --dbhost="$DB_HOST:3306" \
        --dbcharset="utf8" \
        --extra-php \
        --allow-root \
        --skip-check << 'EOF'
define('WP_ALLOW_REPAIR', true);
define('WP_DEBUG', true);

// 댓글 관리자 승인 없이 게시
define('WP_COMMENT_MODERATION', 0);

// SSL/HTTPS 설정
if (isset($_SERVER['HTTP_X_FORWARDED_PROTO']) && $_SERVER['HTTP_X_FORWARDED_PROTO'] === 'https') {
    $_SERVER['HTTPS'] = 'on';
}

// HTTPS URL 강제 설정
define('WP_HOME','https://' . $_SERVER['HTTP_HOST']);
define('WP_SITEURL','https://' . $_SERVER['HTTP_HOST']);

// 관리자 페이지 SSL 강제
define('FORCE_SSL_ADMIN', true);

// 쿠키 보안 설정
ini_set('session.cookie_secure', 1);
ini_set('session.cookie_httponly', 1);

// CLI에서 HTTP_HOST 설정
if (!isset($_SERVER['HTTP_HOST'])) {
    $_SERVER['HTTP_HOST'] = 'jacha.42.fr';
}
EOF

    echo "Generating security keys..."
    wp config shuffle-salts --allow-root
    
    echo "Installing WordPress..."
    wp core install \
        --url="https://jacha.42.fr" \
        --title="jacha WordPress" \
        --admin_user="$WP_ADMIN_USER" \
        --admin_password="$WP_ADMIN_PASSWORD" \
        --admin_email="$WP_ADMIN_EMAIL" \
        --skip-email \
        --allow-root

    if [ ! -z "$WP_USER" ] && [ ! -z "$WP_USER_PASSWORD" ] && [ ! -z "$WP_USER_EMAIL" ]; then
        echo "Creating regular user..."
        wp user create "$WP_USER" "$WP_USER_EMAIL" \
            --user_pass="$WP_USER_PASSWORD" \
            --role=author \
            --allow-root
    else
        echo "No additional user configured. Only admin user created."
    fi
    
    echo "WordPress installation completed!"
else
    echo "WordPress is already installed."
fi

echo "Setting up file permissions..."
chown -R www-data:www-data /var/www/html/
find /var/www/html -type d -exec chmod 755 {} \;
find /var/www/html -type f -exec chmod 644 {} \;

echo "Starting PHP-FPM..."
exec php-fpm8.2 --nodaemonize
