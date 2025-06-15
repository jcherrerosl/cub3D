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

SRCS = \
	$(SRC_DIR)/checkers.c               \
	$(SRC_DIR)/draw_gun.c               \
	$(SRC_DIR)/events.c                 \
	$(SRC_DIR)/general_utils.c          \
	$(SRC_DIR)/init.c                   \
	$(SRC_DIR)/init_textures.c          \
	$(SRC_DIR)/main.c                   \
	$(SRC_DIR)/mouse_input.c            \
	$(SRC_DIR)/movement.c               \
	$(SRC_DIR)/movement_separator.c     \
	$(SRC_DIR)/movement_separator2.c    \
	$(SRC_DIR)/parse_map.c              \
	$(SRC_DIR)/parse_map_utils.c        \
	$(SRC_DIR)/parse_textures.c         \
	$(SRC_DIR)/raycasting.c             \
	$(SRC_DIR)/raycasting_init.c        \
	$(SRC_DIR)/raycasting_utils.c       \
	$(SRC_DIR)/render.c                 \
	$(SRC_DIR)/render_utils.c

OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

COMPILED_FLAG = .compiled
TOTAL = $(shell echo $(SRCS) | wc -w | tr -d " ")
TOTAL_PLUS = $(shell echo $$(($(TOTAL) + 3)))

all: $(COMPILED_FLAG)

$(COMPILED_FLAG): $(NAME)

$(NAME): $(LIBFT_DIR)/libft.a $(LIBFT_DIR)/ft_printf/libftprintf.a $(MLX_DIR)/libmlx.a $(OBJS)
	@$(MAKE) --no-print-directory reset_progress
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo $$(( $(TOTAL_PLUS) - 1 )) > .progress_count
	@LAST=$$(cat .last_compiled 2>/dev/null || echo "") && \
	$(MAKE) --no-print-directory update_progress TARGET="$$LAST"
	@rm -f .progress_count .last_compiled
	@echo "\n\033[1;32m✔️ Build completed successfully\033[0m"
	@touch $(COMPILED_FLAG)

reset_progress:
	@echo 0 > .progress_count

update_progress:
	@if [ ! -f .progress_count ]; then echo 0 > .progress_count; fi; \
	count=$$(cat .progress_count); \
	count=$$((count + 1)); \
	echo $$count > .progress_count; \
	total=$(TOTAL_PLUS); \
	percent=$$((100 * count / total)); \
	width=40; \
	filled=$$((percent * width / 100)); \
	bar=$$(printf "%$${filled}s" | tr " " "#"); \
	spaces=$$(printf "%$$(($$width - $$filled))s"); \
	printf "\r\033[1;32mBuilding %-30s [%s%s] %d%%\033[0m" $(TARGET) "$$bar" "$$spaces" "$$percent"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(BUILD_DIR)
	@echo "$<" > .last_compiled
	@$(MAKE) --no-print-directory update_progress TARGET="$<"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory > /dev/null 2>&1
	@$(MAKE) --no-print-directory update_progress TARGET="libft.a"

$(LIBFT_DIR)/ft_printf/libftprintf.a:
	@$(MAKE) -C $(LIBFT_DIR)/ft_printf --no-print-directory > /dev/null 2>&1
	@$(MAKE) --no-print-directory update_progress TARGET="ftprintf.a"

$(MLX_DIR)/libmlx.a:
	@$(MAKE) -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1 || true
	@$(MAKE) --no-print-directory update_progress TARGET="libmlx.a"

clean:
	@rm -rf $(BUILD_DIR) $(COMPILED_FLAG) .progress_count .last_compiled
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(LIBFT_DIR)/ft_printf clean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null 2>&1
	@$(MAKE) --no-print-directory clean_message

clean_message:
	@echo "\033[0;34mCleaned!\033[0m"

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(LIBFT_DIR)/ft_printf fclean --no-print-directory
	@rm -f $(NAME)
	@rm -rf $(BUILD_DIR) $(COMPILED_FLAG) .progress_count .last_compiled
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null 2>&1
	@echo "\033[0;34mFully cleaned! 🗑️\033[0m"

re: fclean all

commit: fclean
	@git add .
	@./commit.sh
	@INPUT_VAR=$$(cat input.txt) && git commit -m "$(shell date +"%Y-%m-%d %H:%M:%S"):  $$INPUT_VAR" && rm -f input.txt
	@git push origin HEAD:main

valgrind:
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re commit valgrind update_progress reset_progress clean_message
