override NAME = philo
RM = rm -rf

CC := gcc

override SRCDIR = src
override OBJDIR = obj

override LDLIBS = -pthread
override CFLAGS = -Wall -Wextra -Werror

override define VPATH
	$(SRCDIR)
endef

override define SRC
	main.c
	check_input.c
	utils_libft.c
	init_table.c
	utils_actions.c
	actions.c
	routine.c
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
