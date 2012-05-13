shrink : main.c
	gcc -std=c99 -Wall -o shrink main.c

testc : 
	shrink -c creerarbre.c test.shrink

testd : 
	shrink -d test.shrink lol.c

testdv : 
	make testd; vim lol.c

edit : 
	vim -S shrink.vim
