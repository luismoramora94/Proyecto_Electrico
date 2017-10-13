All:
	gcc -lm spa.c spa_tester_v2.c spa.h -o spa_tester_v2
	./spa_tester_v2
	rm spa_tester_v2
	rm spa_tester_v2.o
