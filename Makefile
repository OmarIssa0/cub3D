NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I$(LIBFT_DIR) -I$(MLX_DIR)/include
# LIBS = -I/MLX/include -L/MLX/libmlx42.a -lmlx42 -ldl -lglfw -lpthread -lm -lX11
MLX_DIR = ./MLX42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX_LIB = $(MLX_BUILD_DIR)/libmlx42.a
LIBS = -I./MLX42/include -L$(MLX_BUILD_DIR) -lmlx42 -ldl -lglfw -lpthread -lm -lX11
LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = src/main.c				\
	src/read_map/read_map.c		\
	src/utils/exit_and_print.c	\
	src/free/free_game.c		\
	src/read_map/check_map.c	\
	src/free/free_struct.c		\
	src/read_map/get_values.c	\
	src/validity/map_validity.c	\
	src/game/init_game.c		\
	src/read_map/get_textures.c	\
	src/read_map/get_color.c	\
	src/read_map/utils_color.c	\
	src/read_map/2d_array.c		\
	src/game/2d.c				\

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

N		=	\033[m
R		=	\033[0;31m
G		=	\033[0;32m
Y		=	\033[0;33m
B		=	\033[0;34m
P		=	\033[0;35m
T		=	\033[0;36m

all : $(MLX_LIB) $(LIBFT) $(NAME)

$(MLX_LIB):
	@cmake -S $(MLX_DIR) -B $(MLX_BUILD_DIR)
	@cmake --build $(MLX_BUILD_DIR) -j4
	@printf "$(T)%b $(G)%b$(N)\n" "Built" "MLX42"
	@printf "$(Y)%b $(G)%b $(Y)%b$(N)\n" "###############################" "MLX42 ready" "#####"

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@printf "$(Y)%b $(G)%b $(Y)%b$(N)\n" "###############################" "$(NAME) ready" "#####"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(Y)%b $(G)%10b $(R)%-34b $(Y)%b$(N)\n" "#" "compiling" "$@" "#"

$(LIBFT) :
	@$(MAKE) -C $(LIBFT_DIR)  --no-print-directory

clean :
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@rm -rf $(MLX_BUILD_DIR)

fclean : clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory


re : fclean all

.PHONY : all clean fclean re