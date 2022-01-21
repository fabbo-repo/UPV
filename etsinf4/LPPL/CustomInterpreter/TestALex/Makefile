###############################################################################
OBJS = alex.c
#
cmc:	$(OBJS)  
	gcc -Wall -I./include $(OBJS) -lfl -o cmc
alex.c:	src/alex.l 
	flex -oalex.c src/alex.l 

clean:
	rm -f ./alex.c ./asin.c ./asin.h ./*.o  ./include/asin.h ./*~
###############################################################################
