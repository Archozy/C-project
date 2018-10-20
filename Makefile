# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL2

all: firstFunctionOCR predifinefunction

firstFunctionOCR: firstFunctionOCR.o
predifinefunction: predifinefunction.o


clean:
	${RM} *.o
	${RM} *.d
	${RM} firstFunctionOCR
	${RM} predifinefunction

# END