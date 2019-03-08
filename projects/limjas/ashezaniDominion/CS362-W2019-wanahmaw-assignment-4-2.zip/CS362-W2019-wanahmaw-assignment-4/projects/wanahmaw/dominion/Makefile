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

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	
randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)	

randomtestadventurer.out:  randomtestadventurer
	./randomtestadventurer 3 &> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	gcov -b refactor.c >> randomtestadventurer.out
	cat refactor.c.gcov >> randomtestadventurer.out	

randomtestcard1.out:  randomtestcard1
	./randomtestcard1 5 &> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	gcov -b refactor.c >> randomtestcard1.out
	cat refactor.c.gcov >> randomtestcard1.out

randomtestcard2.out:  randomtestcard2
	./randomtestcard2 3 &> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	gcov -b refactor.c >> randomtestcard2.out
	cat refactor.c.gcov >> randomtestcard2.out
    
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
    
# Random Tests
limjas_randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o limjas_randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

limjas_randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o limjas_randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
    
limjas_randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o limjas_randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

# Make and run all random tests:
randomtestresult: limjas_randomtestadventurer limjas_randomtestcard1 limjas_randomtestcard2
	rm -f randomtestresult.out 
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> randomtestresult.out
	echo -n "Random Testing - Assign 4 - Run: " >> randomtestresult.out
	date >> randomtestresult.out
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> randomtestresult.out
	
	limjas_randomtestadventurer
	echo "=================================================" >> randomtestresult.out
	echo "limjas_randomtestadventurer" >> randomtestresult.out
	limjas_randomtestadventurer >> randomtestresult.out
	gcov ./dominion.c >> randomtestresult.out
	echo "=================================================" >> randomtestresult.out
	cat dominion.c.gcov >> randomtestresult.out
	echo >> randomtestresult.out

	limjas_randomtestcard1
	echo "=================================================" >> randomtestresult.out
	echo "limjas_randomtestcard1" >> randomtestresult.out
	limjas_randomtestcard1 >> randomtestresult.out
	gcov ./dominion.c >> randomtestresult.out
	echo "=================================================" >> randomtestresult.out
	cat dominion.c.gcov >> randomtestresult.out
	echo >> randomtestresult.out


	limjas_randomtestcard2
	echo "=================================================" >> randomtestresult.out
	echo "limjas_randomtestcard2" >> randomtestresult.out
	limjas_randomtestcard2 >> randomtestresult.out
	gcov ./dominion.c >> randomtestresult.out
	echo "=================================================" >> randomtestresult.out
	cat dominion.c.gcov >> randomtestresult.out
	echo >> randomtestresult.out

# Make and run all tests:
unittestresult: limjas_unittest1 limjas_unittest2 limjas_unittest3 limjas_unittest4 limjas_cardtest1 limjas_cardtest2 limjas_cardtest3 limjas_cardtest4
	rm -f unittestresult.out 
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> unittestresult.out
	echo -n "Unit Testing - Assign 2 - Run: " >> unittestresult.out
	date >> unittestresult.out
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> unittestresult.out
	
	limjas_unittest1
	echo "=================================================" >> unittestresult.out
	echo "limjas_unittest1" >> unittestresult.out
	limjas_unittest1 >> unittestresult.out
	gcov ./dominion.c >> unittestresult.out
	echo "=================================================" >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	echo >> unittestresult.out

	limjas_unittest2
	echo "=================================================" >> unittestresult.out
	echo "limjas_unittest2" >> unittestresult.out
	limjas_unittest2 >> unittestresult.out
	gcov ./dominion.c >> unittestresult.out
	echo "=================================================" >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	echo >> unittestresult.out


	limjas_unittest3
	echo "=================================================" >> unittestresult.out
	echo "limjas_unittest3" >> unittestresult.out
	limjas_unittest3 >> unittestresult.out
	gcov ./dominion.c >> unittestresult.out
	echo "=================================================" >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	echo >> unittestresult.out


	limjas_unittest4
	echo "=================================================" >> unittestresult.out
	echo "limjas_unittest4" >> unittestresult.out
	limjas_unittest4 >> unittestresult.out
	gcov ./dominion.c >> unittestresult.out
	echo "=================================================" >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	echo >> unittestresult.out


	limjas_cardtest1
	echo "=================================================" >> unittestresult.out
	echo "limjas_cardtest1" >> unittestresult.out
	limjas_cardtest1 >> unittestresult.out
	gcov ./dominion.c >> unittestresult.out
	echo "=================================================" >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	echo >> unittestresult.out


	limjas_cardtest2
	echo "=================================================" >> unittestresult.out
	echo "limjas_cardtest2" >> unittestresult.out
	limjas_cardtest2 >> unittestresult.out
	gcov ./dominion.c >> unittestresult.out
	echo "=================================================" >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	echo >> unittestresult.out


	limjas_cardtest3
	echo "=================================================" >> unittestresult.out
	echo "limjas_cardtest3" >> unittestresult.out
	limjas_cardtest3 >> unittestresult.out
	gcov ./dominion.c >> unittestresult.out
	echo "=================================================" >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	echo >> unittestresult.out


	limjas_cardtest4
	echo "=================================================" >> unittestresult.out
	echo "limjas_cardtest4" >> unittestresult.out
	limjas_cardtest4 >> unittestresult.out
	gcov ./dominion.c >> unittestresult.out
	echo "=================================================" >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	echo >> unittestresult.out
