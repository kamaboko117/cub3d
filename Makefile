# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 14:20:20 by asaboure          #+#    #+#              #
#    Updated: 2021/07/09 17:36:29 by asaboure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCS	=	cub3D.c																\
			sources/error_management.c											\
			sources/game_loop.c													\
			sources/init.c														\
			sources/init2.c														\
			sources/init3.c														\
			sources/raycast.c													\
			sources/raycast2.c													\
			sources/sprite.c													\
			sources/sprite2.c													\
			sources/texture.c													\
			sources/parsing/parsing_checks1.c									\
			sources/parsing/parsing_checks2.c									\
			sources/parsing/parsing_layout.c									\
			sources/parsing/parsing_utils.c										\
			sources/parsing/parsing.c											\
			sources/parsing/parsing2.c											\
			sources/playermovement/collision.c									\
			sources/playermovement/playercamera.c								\
			sources/playermovement/playermovement.c								\
			sources/utils/displayutils.c										\
			sources/utils/drawline.c											\
			sources/utils/drawutils.c											\
			sources/utils/drawutils2.c											\
			sources/utils/free_functions.c										\
			sources/utils/utils1.c												\
			sources/utils/utils2.c

LIBFTSRCS = ft_memccpy.c														\
			ft_memchr.c															\
			ft_memcmp.c															\
			ft_memcpy.c															\
			ft_memmove.c														\
			ft_memset.c															\
			ft_putchar_fd.c														\
			ft_putendl_fd.c														\
			ft_putnbr_fd.c														\
			ft_putstr_fd.c														\
			ft_split.c															\
			ft_strchr.c															\
			ft_strdup.c															\
			ft_strjoin.c														\
			ft_strlcat.c														\
			ft_strlcpy.c														\
			ft_strlen.c															\
			ft_strmapi.c														\
			ft_strncmp.c														\
			ft_strnstr.c														\
			ft_strrchr.c														\
			ft_strtrim.c														\
			ft_substr.c															\
			ft_tolower.c														\
			ft_toupper.c														\
			ft_atoi.c															\
			ft_bzero.c															\
			ft_calloc.c															\
			ft_isalnum.c														\
			ft_isalpha.c														\
			ft_isascii.c														\
			ft_isdigit.c														\
			ft_isprint.c														\
			ft_itoa.c															\
			ft_putnbrbase_fd.c													\
			ft_putnbru_fd.c														\
			ft_putnbrubase_fd.c													\
			ft_numlen.c															\
			get_next_line.c														\
			get_next_line_utils.c												\
			ft_strjoin_free.c													\
			ft_strcmp.c					

LIBFTOBJS =${LIBFTSRCS:.c=.o}

BONUSSRCS	=

OBJS	= ${SRCS:.c=.o}

BONUSOBJS	= ${BONUSSRCS:.c=.o}

CC		= gcc

LIBFT	= ./libft/libft.a

CFLAGS	= -Wall -Wextra -Werror

LIBFT_DIR = ./libft

LIBS	= -lmlx -lXext -lX11 -lm -L${LIBFT_DIR} -lft

RM		= rm -f


.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${LIBFT} ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

${LIBFT}: 
	@make -sC ./libft -j

all:	${NAME}

bonus:

clean:
	 ${RM} ${OBJS} ${BONUSOBJS}

fclean:	clean
	${RM} ${NAME}

re:		fclean all

coffee:
	@clear
	@echo ""
	@echo "                   ("
	@echo "	                     )     ("
	@echo "               ___...(-------)-....___"
	@echo '           .-""       )    (          ""-.'
	@echo "      .-''''|-._             )         _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |                             |"
	@echo "     \  \   |                             |"
	@echo "      '\ '\ |                             |"
	@echo "        '\ '|                             |"
	@echo "        _/ /\                             /"
	@echo "       (__/  \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'
	@sleep 0.5
	@clear
	@echo ""
	@echo "                 ("
	@echo "	                  )      ("
	@echo "               ___..(.------)--....___"
	@echo '           .-""       )   (           ""-.'
	@echo "      .-''''|-._      (       )        _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |                             |"
	@echo "     \  \   |                             |"
	@echo "      '\ '\ |                             |"
	@echo "        '\ '|                             |"
	@echo "        _/ /\                             /"
	@echo "       (__/  \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'
	@sleep 0.5
	@clear
	@echo ""
	@echo "               ("
	@echo "	                  )     ("
	@echo "               ___..(.------)--....___"
	@echo '           .-""      )    (           ""-.'
	@echo "      .-''''|-._      (       )        _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |                             |"
	@echo "     \  \   |                             |"
	@echo "      '\ '\ |                             |"
	@echo "        '\ '|                             |"
	@echo "        _/ /\                             /"
	@echo "       (__/  \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'
	@sleep 0.5
	@clear
	@echo ""
	@echo "             (         ) "
	@echo "	              )        ("
	@echo "               ___)...----)----....___"
	@echo '           .-""      )    (           ""-.'
	@echo "      .-''''|-._      (       )        _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |                             |"
	@echo "     \  \   |                             |"
	@echo "      '\ '\ |                             |"
	@echo "        '\ '|                             |"
	@echo "        _/ /\                             /"
	@echo "       (__/  \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'i

.PHONY:		all clean fclean re coffee bonus
