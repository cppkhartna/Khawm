GXX = g++
CFLAGS = -lX11 

architecture.o: architecture.cpp architecture.hpp
	$(GXX) $(CFLAGS) -c architecture.cpp -o architecture.o	
windowmanager.o: windowmanager.cpp windowmanager.hpp architecture.hpp 
	$(GXX) $(CFLAGS) -c windowmanager.cpp -o windowmanager.o	
khawm: main.cpp architecture.o windowmanager.o
	$(GXX) $(CFLAGS) main.cpp architecture.o windowmanager.o -o khawm
run: khawm
	./khawm
clean:
	rm -f *.o 
