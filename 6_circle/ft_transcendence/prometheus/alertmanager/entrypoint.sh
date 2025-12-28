#!/bin/sh

# Substitute environment variables in alertmanager.yml.template and write to alertmanager.yml
envsubst '${ALERTMANAGER_SLACK_WEBHOOK} ${ALERTMANAGER_SLACK_CHANNEL} ${ALERTMANAGER_SLACK_USERNAME}' < /etc/alertmanager/alertmanager.yml.template > /etc/alertmanager/alertmanager.yml

# Execute the passed command
exec "$@"
