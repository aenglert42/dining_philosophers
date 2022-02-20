NAME := philo
SRC_DIR := ./src/
OBJ_DIR := ./obj/
HEADER_DIR := ./inc/
SRCS :=	1_philo.c \
		2_parse.c \
		3_allocate.c \
		4_threads_1.c \
		4_threads_2.c \
		4_threads_3_control.c \
		5_free.c \
		debug.c \
		errors.c \
		log.c \
		time.c \
		utils.c
CC := gcc
ifeq ($(DEBUG),1)
CFLAGS := -g -pthread -Wall -Wextra -Werror -D DEBUGGING=1 -I$(HEADER_DIR) -fsanitize=thread
else
CFLAGS := -g -pthread -Wall -Wextra -Werror -D DEBUGGING=0 -I$(HEADER_DIR)
endif
OBJS := $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))
HEADERS := $(HEADER_DIR)*.h
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
NC := \033[0m
DEPS := $(HEADERS)
MAKE += --no-print-directory

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(DEPS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "\n$(GREEN)creating: $(NAME)$(NC)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEPS) ofilemessage
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo ".\c"

ofilemessage:
	@echo "compiling $(NAME)-object-files: \c"

clean:
	@rm -rf $(OBJS) *.dSYM
	@echo "$(RED)$(NAME)-object-files deleted$(NC)"
	@echo "$(RED)$(NAME)-dSYM-files deleted$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) deleted$(NC)"

re: fclean all

test:


peace:
	@echo "\n"
	@echo "     .''.    .',"
	@echo "     |  |   /  /"
	@echo "     |  |  /  /"
	@echo "     |  | /  /"
	@echo "     |  |/  ;-._"
	@echo "     }  \` _/  / ;"
	@echo "     |  /\` ) /  /"
	@echo "     | /  /_/\_/\ "
	@echo "     |/  /      |"
	@echo "     (  ' \ '-  |"
	@echo "      \    \`.  /"
	@echo "       |      |"
	@echo "       |      |\n"

.INTERMEDIATE: ofilemessage

.PHONY: clean fclean all re