NAME = ft_container
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

T_SRCS = ./test/test.cpp
T_OBJS = $(T_SRCS:.cpp=.o)
T_FILE = ftFile.txt stlFile.txt

all		: $(NAME)

$(NAME)	: $(OBJS)
	$(CXX) $(CXXFLAGS) -I. -o $(NAME) $(OBJS)

clean	:
	@rm -rf $(OBJS) $(T_OBJS)

fclean	: clean
	@rm -rf $(NAME) $(T_FILE)

test	: $(T_OBJS)
	$(CXX) $(CXXFLAGS) -I. -o $(NAME) $(T_OBJS)

re		: fclean all

.PHONY	: all clean fclean re
