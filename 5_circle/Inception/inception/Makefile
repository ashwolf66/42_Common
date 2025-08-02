COMPOSE=docker compose
COMPSE_FILE=srcs/docker-compose.yml

.PHONY: all up down build clean fclean re

all	: up

up	:
	$(COMPOSE) -f $(COMPOSE_FILE) up -d

down	:
	$(COMPOSE) -f $(COMPOSE_FILE) down

buid	:
	$(COMPOSE) -f $(COMPOSE_FILE) build

clean	:
	$(COMPOSE) -f $(COMPOSE_FILE) down
	$(COMPOSE) -f $(COMPOSE_FILE) rm -rf

fclean	: clean
	sudo rm -rf /home/${USER}/data/*

re	: fclean up
