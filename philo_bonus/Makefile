NAME = philo_bonus
RM = rm -rf
override CFLAGS = -Wall -Wextra -Werror

override CC = gcc

OBJDIR = obj
override SRCDIR = src
override LDLIBS = -pthread

vpath %.c $(SRCDIR)

override define SRC
	main.c
	check_input.c
	init_content.c
	utils_libft.c
	utils_actions.c
	actions.c
	process.c
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

.PHONY: clean all fclean re
