override NAME = philo
override ARCH = $(findstring Arch,$(file < /etc/os-release))
RM = rm -rf

ifeq (Arch,$(ARCH))
	CC := gcc
else
	CC := clang
endif

override LIBFTDIR = libft
override LIBFT = $(LIBFTDIR)/libft.a

override LDFLAGS = -L $(LIBFTDIR)
override LDLIBS = -lft -pthread
override CFLAGS = -Wall -Wextra -Werror

LINT = norminette

override SRCDIR = src
override OBJDIR = obj

override define VPATH
	$(SRCDIR)
endef

override define SRC
	main.c
endef

override OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJDIR) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJDIR):
	mkdir -p $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) $(OBJDIR)
	$(MAKE) fclean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
