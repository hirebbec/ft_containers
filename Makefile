VECTOR_NAME		= vector
VECTOR_SRCS		= mains/main_vector.cpp
VECTOR_HEADERS	= vector/vector.hpp iterators/random_iterator.hpp utils/*.hpp
VECTOR_OBJETS	= $(VECTOR_SRCS:.cpp=.o)
#####
MAP_NAME		= map
MAP_SRCS		= mains/main_map.cpp
MAP_HEADERS		= map/map.hpp iterators/tree_iterator.hpp utils/*.hpp
MAP_OBJETS		= $(MAP_SRCS:.cpp=.o)
#####
STACK_NAME		= stack_test
STACK_SRCS		= mains/main_stack.cpp
STACK_HEADERS	= stack/stack.hpp iterators/random_iterator.hpp utils/*.hpp
STACK_OBJETS	= $(STACK_SRCS:.cpp=.o)
#####
SET_NAME		= set_test
SET_SRCS		= mains/main_set.cpp
SET_HEADERS		= set/set.hpp iterators/random_iterator.hpp utils/*.hpp
SET_OBJETS		= $(SET_SRCS:.cpp=.o)
#####
CC				= g++
CFLAGS			= -Wall -Wextra -Werror -std=c++98	   

all: vector stack map

vector: $(VECTOR_OBJETS) $(VECTOR_HEADERS)
	@$(CC) $(VECTOR_SRCS) $(CFLAGS) -D flag=0 -o my_vector
	@$(CC) $(VECTOR_SRCS) $(CFLAGS) -D flag=1 -o STL_vector
	@mkdir -p exe_files
	@mkdir -p log_files
	@./my_vector 1>my_vector_log 2>my_vector_log
	@./STL_vector 1>STL_vector_log 2>STL_vector_log
	@diff STL_vector_log my_vector_log
	@mv my_vector_log ./log_files
	@mv STL_vector_log ./log_files 
	@mv my_vector ./exe_files
	@mv STL_vector ./exe_files

stack: $(STACK_OBJETS) $(STACK_HEADERS)
	@$(CC) $(STACK_SRCS) $(CFLAGS) -D flag=0 -o my_stack
	@$(CC) $(STACK_SRCS) $(CFLAGS) -D flag=1 -o STL_stack
	@mkdir -p exe_files
	@mkdir -p log_files
	@./my_stack 1>my_stack_log 2>my_stack_log
	@./STL_stack 1>STL_stack_log 2>STL_stack_log
	@diff STL_stack_log my_stack_log
	@mv my_stack_log ./log_files
	@mv STL_stack_log ./log_files 
	@mv my_stack ./exe_files
	@mv STL_stack ./exe_files

map: $(MAP_OBJETS) $(MAP_HEADERS)
	@$(CC) $(MAP_SRCS) $(CFLAGS) -D flag=0 -o my_map
	@$(CC) $(MAP_SRCS) $(CFLAGS) -D flag=1 -o STL_map
	@mkdir -p exe_files
	@mkdir -p log_files
	@./my_map 1>my_map_log 2>my_map_log
	@./STL_map 1>STL_map_log 2>STL_map_log
	@diff STL_map_log my_map_log
	@mv my_map_log ./log_files
	@mv STL_map_log ./log_files 
	@mv my_map ./exe_files
	@mv STL_map ./exe_files

set: $(SET_OBJETS) $(SET_HEADERS)
	@$(CC) $(SET_SRCS) $(CFLAGS) -D flag=0 -o my_set
	@$(CC) $(SET_SRCS) $(CFLAGS) -D flag=1 -o STL_set
	@mkdir -p exe_files
	@mkdir -p log_files
	@./my_set 1>my_set_log 2>my_set_log
	@./STL_set 1>STL_set_log 2>STL_set_log
	@diff STL_set_log my_set_log
	@mv my_set_log ./log_files
	@mv STL_set_log ./log_files 
	@mv my_set ./exe_files
	@mv STL_set ./exe_files


.cpp.o:
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(VECTOR_OBJETS) $(STACK_OBJETS) $(MAP_OBJETS)

fclean: clean
	rm -rf exe_files log_files

re: fclean all

bonus: set

.PHONY: all clean fclean re bonus