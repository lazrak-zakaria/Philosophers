# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 17:42:44 by zlazrak           #+#    #+#              #
#    Updated: 2023/03/07 14:17:31 by zlazrak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo

OBJS= philosopher.o philosopher_utils.o philosopher_utils2.o 
CFLAGS= -Wall -Werror -Wextra #-fsanitize=thread
all : ${NAME}


${NAME} : ${OBJS}
	cc ${CFLAGS} ${OBJS}  -o ${NAME} 

clean :
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

re : fclean all
