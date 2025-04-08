NAME		= minishell
CC			= cc

CFLAGS 		= -Wall -Werror -Wextra 
CFLAGS		+= -I.
CFLAGS		+=	-Ilibft -I./ -I/opt/vagrant/embedded/include/readline -I/opt/vagrant/embedded/include
# CFLAGS		+= -g3
# CFLAGS		+= -fsanitize=address
# CFLAGS		+= -I/opt/vagrant/embedded/include/readline -I/opt/vagrant/embedded/include
# CFLAGS		+= -L/opt/vagrant/embedded/lib/ -lreadline -I/opt/vagrant/embedded/include/readline -I/opt/vagrant/embedded/include

SRCS		=  $(addprefix parsing/, main.c parsing.c syntax_stuff.c free_all.c init_1.c init_2.c\
				variable_stuff_v3.c tokenize_1.c tokenize_2.c operators.c remake_stuff.c) \
				$(addprefix parsing/utils/, ft_strdup.c remove_quotes.c ft_strtrim_free.c ft_substr_free.c \
				ft_strjoin_free.c ft_strcmp_l.c parse_utils.c rmv_spaces.c\
				ft_strncmp.c list_stuff_values.c list_stuff_cmds.c list_stuff_redir.c split_pipes.c) \
				execution/execution2/execution.c execution/execution2/heredoc.c execution/execution2/context.c execution/execution2/handling.c\
				$(addprefix execution/utils/, utils.c env_utils.c) \
				$(addprefix execution/, exec_bulidin.c) \
				$(addprefix execution/bulid_in/, cd.c   echo.c env.c  exit.c  export.c  pwd.c  unset.c)\

OBJ			= $(SRCS:.c=.o)

LIBFT		= aish_libft/libft.a

READLINE	=	-L/opt/vagrant/embedded/lib/ -lreadline 

all			:	${NAME}

%.o			:	%.c
			cc ${CFLAGS} -c $< -o $@

${LIBFT}	:
			make -C aish_libft

${NAME}		:	${LIBFT} ${OBJ}
			cc ${CFLAGS} ${OBJ} ${READLINE} -lreadline ${LIBFT} -o ${NAME}

clean		:
			make -C aish_libft clean
			rm -f ${OBJ}

fclean		:	clean
			rm -f ${LIBFT}
			rm -f ${NAME}

re			: fclean all

.PHONY		:	all clean fclean re
