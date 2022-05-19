all: ww

ww: ww.c
	gcc -g -Wall -Werror -fsanitize=address -gdwarf-2 ww.c -lm -o ww

clean: 
	rm -f ww
