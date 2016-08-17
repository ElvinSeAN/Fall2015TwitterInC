gcc_mysql2:	flitter.c
	gcc -L/usr/lib flitter.c -o flitter -lmysqlclient
