DEBUG=0

ifeq ($(DEBUG), 1)
	OPTS=-O0 -g
else
	OPTS=-Ofast
endif

main: ldr.c
	gcc -o ldr ldr.c $(OPTS)

clean:
	rm ldr
