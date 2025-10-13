NAME	:= 2d-engine-c
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: libmlx libft $(NAME)
	@echo "🚀 Build complete: $(NAME)"

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build > /dev/null 2>&1
	@make -C $(LIBMLX)/build -j4 > /dev/null 2>&1
	@echo "🖼️ MLX42 compiled"

libft:
	@make -C $(LIBFT) > /dev/null 2>&1
	@echo "📚 libft compiled"

%.o: %.c
	@gcc $(CFLAGS) -o $@ -c $< $(HEADERS) > /dev/null 2>&1
	@printf "⚙️ Compiled %s\n" $(notdir $<)

$(NAME): $(OBJS)
	@gcc $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) > /dev/null 2>&1
	@echo "📝 Source files compiled"
	@echo "✅ Executable created: $(NAME)"

clean:
	@make clean -C $(LIBFT) > /dev/null 2>&1
	@rm -f $(LIBFT)/*.a
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build
	@echo "🧹 Cleaned object files and libraries"

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️ Executable removed"

re: fclean all
