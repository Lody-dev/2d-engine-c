NAME	:= so_long
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast 
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm
#SRCS := $(shell find ./src \( -iname "main.c" -o -iname "open_window.c" \))
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

%.o: %.c
	@gcc $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@gcc $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@make clean -C $(LIBFT)
	@rm $(LIBFT)/*.a
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re:	fclean
	make
