GXX = g++
CFLAGS = 

architecture.o: architecture.cpp architecture.hpp
	$(GXX) $(CFLAGS) -c architecture.cpp -o architecture.o	
khawm: main.cpp architecture.o
	$(GXX) $(CFLAGS) main.cpp architecture.o -o khawm
run: khawm
	./khawm
clean:
	rm -f *.o 
