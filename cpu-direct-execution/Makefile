CC = gcc
CFLAGS = -Wall -Wextra -lm
SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)

all: ${BINS}

%: %.o
	@echo "Checking ..."
	${CC} $(CFLAGS) $< -o $@

%.o: %.c
	@echo "Creating object ..."
	${CC} -c $<

clean:
	@echo "Cleaning up ..."
	rm -rvf *.o ${BIN}
