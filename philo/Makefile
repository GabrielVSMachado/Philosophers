override NAME = philo
override ARCH = $(findstring Arch,$(file < /etc/os-release))
RM = rm -rf

ifeq (Arch,$(ARCH))
	CC := gcc
else
	CC := clang
endif

override SRCDIR = src
override OBJDIR = obj
override TESTDIR = TESTS

override LDLIBS = -pthread
override CFLAGS = -Wall -Wextra -Werror -g

LINT = norminette


override define VPATH
	$(SRCDIR)
	$(TESTDIR)
endef

override define SRC
	main.c
	check_input.c
	utils_libft.c
	init_table.c
	utils_actions.c
	actions.c
endef

override define SRCTEST
	$(filter-out main.c,$(SRC))
	tests_check_inputs.c
endef

override OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
override OBJTESTS = $(SRCTEST:%.c=$(OBJDIR)/%.o)

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
	$(RM) test

re: fclean all

test: $(OBJDIR) $(OBJTESTS)
	$(CC) $(INCLUDES) $(OBJTESTS) -o test -lcriterion
	@./test
	@$(MAKE) fclean > /dev/null

.PHONY: all clean fclean re
