NAME =  Webserv

CC = c++

INCLUDE = ./parsing_hpp/parsing.hpp ./parsing_hpp/parse_location.hpp ./parsing_hpp/servers.hpp  ./server/server.hpp\
		./headers/http/Request.hpp ./headers/http/Response.hpp ./headers/http/Utils.hpp \

FLAGS = -Wall -Werror -Wextra -std=c++98

SRC =	./src/Request.cpp ./src/Response.cpp ./src/Utils.cpp  ./server/server.cpp \
		./server/main.cpp ./parsing/parsing.cpp ./parsing/parse_location.cpp ./parsing/servers.cpp \

OBJ = ./src/Request.o ./src/Response.o ./src/Utils.o  ./server/server.o \
		./server/main.o\ ./parsing/parsing.o ./parsing/parse_location.o ./parsing/servers.o \

all: $(NAME)

$(NAME): $(SRC) $(INCLUDE)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean :
	/bin/rm -f $(OBJ)

fclean : clean
	/bin/rm -f $(NAME)
re : fclean all