CXX = g++
CFLAGS = -Wall -g -lX11

SRCS = windowmanager.cpp architecture.cpp  
OBJS = $(SRCS:.cpp=.o)

default: khawm

%.o: %.cpp %.hpp 
	$(CXX) $(CFLAGS) -c $< -o $@

khawm: main.cpp $(OBJS)
	$(CXX) $(CFLAGS) $^ -o $@

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(SRCS) 
	$(CXX) -MM $^ > $@

run: khawm
	./khawm
clean:
	rm -f *.o 
