target : bayes.o parse.o
	 gcc parse.c bayes.c -Wall -o parse -lm -g
parse.o : parse.c
	 gcc parse.c header.h -c -g
bayes.o : bayes.c
	 gcc bayes.c header.h -c -lm -g
clean:
	rm -rf *.o target
