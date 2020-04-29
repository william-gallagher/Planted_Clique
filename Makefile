DEBUG=0

ifeq ($(DEBUG), 1)
	OPTS=-O0 -g
else
	OPTS=-Ofast
endif

main: main.c
	gcc -o main main.c $(OPTS)

clean:
	rm main
