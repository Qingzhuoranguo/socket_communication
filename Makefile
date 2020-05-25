# -*- MakeFile -*-


Flags = -Wall -g

all: AAPS_test client

	
test: test.cpp
	g++ test.cpp -o test $(Flags)

client: client.cpp AAPS.o AAPS.hpp
	g++ -c client.cpp $(Flags)
	g++ client.o AAPS.o -o client $(Flags)



AAPS_test: AAPS_test.o AAPS.o UniqueID.o
	g++ AAPS_test.o AAPS.o UniqueID.o -o AAPS_test $(Flags)

AAPS_test.o: AAPS_test.cpp AAPS.hpp UniqueID/UniqueID.hpp
	g++ -c AAPS_test.cpp $(Flags)

AAPS.o:	AAPS.cpp
	g++ -c AAPS.cpp $(Flags)

UniqueID.o: UniqueID/UniqueID.cpp 
	g++ -c UniqueID/UniqueID.cpp $(Flags)

clean:
	rm -f *.o AAPS_test test server client