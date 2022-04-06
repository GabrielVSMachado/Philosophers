override NAME = philo
override ARCH = $(findstring Arch,$(file < /etc/os-release))
RM = rm -rf

ifeq (Arch,$(ARCH))
	CC := gcc
else
	CC := clang
endif

override LDLIBS = -pthread
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

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDLIBS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDLIBS)

$(OBJDIR):
	mkdir -p $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
