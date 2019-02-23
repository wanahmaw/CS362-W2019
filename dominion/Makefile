CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)
    
unit1:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest1.c rngs.c -o unittest1 -lm -g

unit2:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest2.c rngs.c -o unittest2 -lm -g

unit3:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest3.c rngs.c -o unittest3 -lm -g

unit4:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest4.c rngs.c -o unittest4 -lm -g

card1:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest1.c rngs.c -o cardtest1 -lm -g

card2:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest2.c rngs.c -o cardtest2 -lm -g

card3:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest3.c rngs.c -o cardtest3 -lm -g

card4:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest4.c rngs.c -o cardtest4 -lm -g

myTest:
	./unittest1 &> unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	./cardtest1 >> unittestresult.out
	./cardtest2 >> unittestresult.out
	./cardtest3 >> unittestresult.out
	./cardtest4 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
    
interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
    
    
# =======================================================================
# Unit Tests
limjas_unittest1: unittest1.c dominion.o rngs.o
	gcc -o limjas_unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

limjas_unittest2: unittest2.c dominion.o rngs.o
	gcc -o limjas_unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

limjas_unittest3: unittest3.c dominion.o rngs.o
	gcc -o limjas_unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

limjas_unittest4: unittest4.c dominion.o rngs.o
	gcc -o limjas_unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

# Card Tests
limjas_cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o limjas_cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

limjas_cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o limjas_cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

limjas_cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o limjas_cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

limjas_cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o limjas_cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)


# Make and run all tests:
assign2: limjas_unittest1 limjas_unittest2 limjas_unittest3 limjas_unittest4 limjas_cardtest1 limjas_cardtest2 limjas_cardtest3 limjas_cardtest4
	rm -f limjas_unittestresult.txt
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> limjas_unittestresult.txt
	echo -n "Unit Testing - Assign 2 - Run: " >> limjas_unittestresult.txt
	date >> limjas_unittestresult.txt
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> limjas_unittestresult.txt

	limjas_unittest1
	echo "=================================================" >> limjas_unittestresult.txt
	echo "limjas_unittest1" >> limjas_unittestresult.txt
	gcov ./dominion.c >> limjas_unittestresult.txt
	echo "=================================================" >> limjas_unittestresult.txt
	cat dominion.c.gcov >> limjas_unittestresult.txt
	echo >> limjas_unittestresult.txt

	limjas_unittest2
	echo "=================================================" >> limjas_unittestresult.txt
	echo "limjas_unittest2" >> limjas_unittestresult.txt
	gcov ./dominion.c >> limjas_unittestresult.txt
	echo "=================================================" >> limjas_unittestresult.txt
	cat dominion.c.gcov >> limjas_unittestresult.txt
	echo >> limjas_unittestresult.txt


	limjas_unittest3
	echo "=================================================" >> limjas_unittestresult.txt
	echo "limjas_unittest3" >> limjas_unittestresult.txt
	gcov ./dominion.c >> limjas_unittestresult.txt
	echo "=================================================" >> limjas_unittestresult.txt
	cat dominion.c.gcov >> limjas_unittestresult.txt
	echo >> limjas_unittestresult.txt


	limjas_unittest4
	echo "=================================================" >> limjas_unittestresult.txt
	echo "limjas_unittest4" >> limjas_unittestresult.txt
	gcov ./dominion.c >> limjas_unittestresult.txt
	echo "=================================================" >> limjas_unittestresult.txt
	cat dominion.c.gcov >> limjas_unittestresult.txt
	echo >> limjas_unittestresult.txt


	limjas_cardtest1
	echo "=================================================" >> limjas_unittestresult.txt
	echo "limjas_cardtest1" >> limjas_unittestresult.txt
	gcov ./dominion.c >> limjas_unittestresult.txt
	echo "=================================================" >> limjas_unittestresult.txt
	cat dominion.c.gcov >> limjas_unittestresult.txt
	echo >> limjas_unittestresult.txt


	limjas_cardtest2
	echo "=================================================" >> limjas_unittestresult.txt
	echo "limjas_cardtest2" >> limjas_unittestresult.txt
	gcov ./dominion.c >> limjas_unittestresult.txt
	echo "=================================================" >> limjas_unittestresult.txt
	cat dominion.c.gcov >> limjas_unittestresult.txt
	echo >> limjas_unittestresult.txt


	limjas_cardtest3
	echo "=================================================" >> limjas_unittestresult.txt
	echo "limjas_cardtest3" >> limjas_unittestresult.txt
	gcov ./dominion.c >> limjas_unittestresult.txt
	echo "=================================================" >> limjas_unittestresult.txt
	cat dominion.c.gcov >> limjas_unittestresult.txt
	echo >> limjas_unittestresult.txt


	limjas_cardtest4
	echo "=================================================" >> limjas_unittestresult.txt
	echo "limjas_cardtest4" >> limjas_unittestresult.txt
	gcov ./dominion.c >> limjas_unittestresult.txt
	echo "=================================================" >> limjas_unittestresult.txt
	cat dominion.c.gcov >> limjas_unittestresult.txt
	echo >> limjas_unittestresult.txt
