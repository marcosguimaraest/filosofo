NAME = philo
LIB = philo.a

CC = cc
CFLAGS = -g $(INCLUDE_FLAG) -Wall -Wextra -Werror -pthread
INCLUDES_DIR = ./include/
OBJS_DIR = ./obj/
SRCS_DIR = ./src/
INCLUDE_FLAG =-I$(INCLUDES_DIR)

VPATH = $(INCLUDES_DIR):$(SRCS_DIR):$(OBJS_DIR)

H_SOURCE = philo.h
C_SOURCE = parse.c philo.c error.c fork.c routine.c table.c utils.c

MAIN = main.c

OBJS = $(C_SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(MAIN)
	@$(CC) $(CFLAGS) $(SRCS_DIR)$(MAIN) $(OBJS_DIR)$(LIB) -o $(NAME)
	@echo "Philo created!"

$(LIB): $(OBJS)
	@cd $(OBJS_DIR); \
	ar rc $(LIB) $(OBJS);
	@echo "Philo library created!"

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
	@mv $(<:.c=.o) $(OBJS_DIR)

clean:
	@cd $(OBJS_DIR); \
	rm -f -- $(OBJS) $(LIB) $(MAIN:.c=.o) $(BONUS_MAIN:.c=.o)
	@echo "Cleaned objects"

fclean: clean
	@rm -f -- $(NAME)
	@echo "Removed push_swap!"

re: fclean all

.PHONY: all clean fclean re 