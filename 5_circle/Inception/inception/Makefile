NAME=inception
COMPOSE=docker compose
COMPOSE_FILE=srcs/docker-compose.yml

.PHONY: all up down build clean fclean re

all: up

up:
	$(COMPOSE) -f $(COMPOSE_FILE) up --build -d

down:
	$(COMPOSE) -f $(COMPOSE_FILE) down

build:
	$(COMPOSE) -f $(COMPOSE_FILE) build

clean:
	$(COMPOSE) -f $(COMPOSE_FILE) down -v --remove-orphans

fclean: clean
	sudo rm -rf /home/${USER}/data/wp_files/*
	sudo rm -rf /home/${USER}/data/db_data/*

re: fclean up
