CFILES   = $(wildcard *.c)
HFILES   = $(wildcard *.h)
OBJFILES = $(CFILES:.c=.o)
DEPS     = $(CFILES:.c=.d)
OUT      = minish
CFLAGS   = -Wall -Wextra -std=gnu99 -ggdb

# Rule to generate the executable
$(OUT): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

# Include dependency files
-include $(DEPS)

# Rule to compile .c to .o and generate .d files
%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Clean rule
.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT) $(DEPS)

