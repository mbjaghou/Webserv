NAME =  webserv

CC = c++

INCLUDE = ./headers/parsing_hpp/parsing.hpp ./headers/parsing_hpp/parse_location.hpp ./headers/parsing_hpp/servers.hpp  ./headers/http/server.hpp\
		./headers/http/Request.hpp ./headers/http/Response.hpp ./headers/http/Utils.hpp ./headers/http/codes.hpp\

FLAGS = -Wall -Werror -Wextra -std=c++98

SRC =	./src/Request.cpp ./src/Response.cpp ./src/Utils.cpp  ./src/server.cpp \
		./main.cpp ./parsing/parsing.cpp ./parsing/parse_location.cpp ./parsing/servers.cpp \

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	/bin/rm -f $(OBJ)

fclean : clean
	/bin/rm -f $(NAME)

re : fclean all