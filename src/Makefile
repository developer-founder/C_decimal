CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

CHECK_CFLAGS := $(shell pkg-config --cflags check 2>/dev/null)
CHECK_LIBS := $(shell pkg-config --libs check 2>/dev/null)

SRCS = $(wildcard functions/**/*.c functions/*.c)
TEST_SRCS = $(wildcard tests/*.c)

OBJS = $(SRCS:.c=.o)

NAME = s21_decimal.a
TEST_NAME = test


all: $(NAME)


$(NAME): $(OBJS)
	ar rcs $@ $^


test: $(NAME)
	$(CC) $(CFLAGS) $(CHECK_CFLAGS) \
	$(TEST_SRCS) $(SRCS) \
	-o $(TEST_NAME) $(CHECK_LIBS)
	./$(TEST_NAME)


gcov_report:
	$(CC) $(CFLAGS) --coverage \
	$(SRCS) $(TEST_SRCS) \
	-o gcov_test $(CHECK_CFLAGS) $(CHECK_LIBS)

	./gcov_test

	lcov -t "s21_decimal" -o report.info -c -d .
	genhtml -o report report.info


clean:
	rm -rf $(OBJS) $(NAME) $(TEST_NAME) gcov_test \
	*.gcda *.gcno report report.info

re: clean all