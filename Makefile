
CXX = c++
CFLAGS = -std=c++11
CCSOURCE = main.cpp cmdline.cpp Expr.cpp
HEADERS = cmdline.hpp catch.h expr.hpp
CCOBJECTS= main.o cmdline.o Expr.o

build:	msdscript

msdscript: $(CCSOURCE) $(HEADERS)
		$(CXX) $(CFLAGS) -o msdscript $(CCSOURCE)

main.o:	main.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -c main.cpp

cmdline.o: cmdline.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -c cmdline.cpp

clean:
	rm -f *.o *.out msdscript
