###############################################################################
OBJS = alex.c  asin.c 
#
cmc:	$(OBJS)  
	gcc $(OBJS) -I./include -Wall -lfl -o cmc
asin.c:	src/asin.y
	bison -oasin.c -d src/asin.y
	mv asin.h include/
alex.c:	src/alex.l 
	flex -oalex.c src/alex.l 

clean:
	rm -f ./alex.c ./asin.c ./include/asin.h ./src/*.?~ ./include/*.?~
###############################################################################
