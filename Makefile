CFLAGS = -Wall -Wextra -I./src -ggdb

SRCS = $(wildcard src/*.c) 
DEPS = $(SRCS:.c=.d)
OBJS = $(SRCS:.c=.o)
-include $(DEPS)

TEST_SRCS = $(wildcard t/*.c)
TEST_DEPS = $(TEST_SRCS:.c=.d)
TEST_OBJS = $(TEST_SRCS:.c=.o)
-include $(TEST_DEPS)

TEST_EXES = level_test output_test
.PHONY: top clean_tmp clean

# Clean previous, build new archive, clean up temp files.
top: clean liblog.a clean_tmp

%.o : %.c
	$(CC) $(CFLAGS) -MMD -c -o $@ $<

liblog.a : $(OBJS)
	@$(AR) -cvq $@ $^

clean_tmp:
	rm -f $(OBJS) $(DEPS) $(TEST_OBJS) $(TEST_DEPS)
clean: clean_tmp
	rm -f liblog.a $(TEST_EXES)

output_test: liblog.a t/output_test.o
	$(CC) $(CFLAGS) $^ -o $@ -L./ -llog

level_test: liblog.a t/level_test.o
	$(CC) $(CFLAGS) $^ -o $@ -L./ -llog
