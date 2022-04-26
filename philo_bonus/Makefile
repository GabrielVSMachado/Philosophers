NAME = philo_bonus
RM = rm -rf
override CFLAGS = -Wall -Wextra -Werror -g

override CC = gcc

OBJDIR = obj
override SRCDIR = src

vpath %.c $(SRCDIR)

override define SRC
	main.c
endef

override OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean all fclean re
