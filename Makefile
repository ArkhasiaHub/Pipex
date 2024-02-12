NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g

LIBFT = ./libft/libft.a

all: ${NAME}

SRCS = ./srcs/check_file.c \
./srcs/command.c \
./srcs/path.c \
./srcs/pipex.c \
./srcs/pipex_utils.c \
./srcs/find_path.c

SRCS_BONUS = ./srcs_bonus/check_file_bonus.c \
./srcs_bonus/command_bonus.c \
./srcs_bonus/here_doc_bonus.c \
./srcs_bonus/path_bonus.c \
./srcs_bonus/pipex_bonus.c \
./srcs_bonus/pipex_utils_bonus.c \
./srcs_bonus/find_path_bonus.c

OBJS = ${SRCS:.c=.o}
OBJS_D = ${OBJS:.o=.d}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}
OBJS_BONUS_D = ${OBJS_BONUS:.o=.d}

${NAME}: ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBFT}

${NAME_BONUS}:  ${OBJS_BONUS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS_BONUS} -o ${NAME_BONUS} ${LIBFT}

${LIBFT}: FORCE
	make -C ./libft

-include ${OBJS_D} ${OBJS_BONUS_D}

bonus: ${NAME_BONUS}

clean:
	make -C ./libft clean
	rm -f ${OBJS} ${OBJS_D} ${OBJS_BONUS} ${OBJS_BONUS_D}

fclean: clean
	make -C ./libft fclean
	rm -f ${NAME} ${NAME_BONUS}

re: fclean all

FORCE:

.PHONY: clean fclean re all bonus FORCE
