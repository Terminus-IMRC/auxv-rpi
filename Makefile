CFLAGS += -pipe -W -Wall -Wextra -g -O2

all: main

.PHONY: clean
clean:
	$(RM) main
