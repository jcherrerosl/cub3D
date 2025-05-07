NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address,leak -g

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
LIBFT_DIR = libft
MLX_DIR = minilibx-linux
ASSETS_DIR = assets/img

INCLUDE = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) 
MLX_LIB = -L$(MLX_DIR) -lmlx
LIBFT_LIB = -L$(LIBFT_DIR) -lft
X11_LIB = -lXext -lX11 -lm
LIBS = $(MLX_LIB) $(LIBFT_LIB) -L$(LIBFT_DIR)/ft_printf -lftprintf $(X11_LIB)

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a 
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_DIR)/libft/libftprintf.a:
	@$(MAKE) -C $(LIBFT_DIR)/ft_printf

$(MLX_DIR)/libmlx.a:
	@$(MAKE) -C $(MLX_DIR) || true

all: $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -rf $(BUILD_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -f $(NAME)
	@rm -rf $(BUILD_DIR)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re