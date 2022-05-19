all: wcat ww

wcat: wcat.c
	#gcc -g -Wall -Werror -fsanitize=address -gdwarf-2 wcat.c -lm -o wcat
	gcc -g -Wall -Werror wcat.c -o wcat
	
ww: ww.c
	gcc -g -Wall -Werror ww.c -o ww
	
clean: 
	rm -f wcat ww
