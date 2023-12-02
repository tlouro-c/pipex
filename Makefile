# Sample Makefile
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR)
LIBFT = -L$(LIBFT_DIR) -lft
NAME = pipex

INCLUDE_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj
LIBFT_DIR = ./libft

SRC_FILES =  $(SRC_DIR)/main.c \
			 $(SRC_DIR)/main_process.c \
			 $(SRC_DIR)/child_process.c \
			 $(SRC_DIR)/close_pipes.c \
			 $(SRC_DIR)/exits.c \
			 $(SRC_DIR)/exits2.c \
			 $(SRC_DIR)/utils.c \
			 $(SRC_DIR)/organize_cmd.c \
			 $(SRC_DIR)/organize_cmd2.c \
			 $(SRC_DIR)/organize_cmd3.c

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: libft $(NAME)

libft:
	cd $(LIBFT_DIR) && make

$(NAME): $(OBJ_FILES)
	$(CC) $^ -o $@ $(LIBFT)

# Make sure dir exists
$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Create object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@if [ -d "$(OBJ_DIR)" ]; then 		rm -rf $(OBJ_DIR); 	fi

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_DIR)/libft.a

re: fclean all

.PHONY: all clean fclean re libft

