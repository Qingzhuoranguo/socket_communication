# -*- MakeFile -*-


Flags = -Wall -g -pthread

all: stable server client test  

stable:
	mkdir stable

test: test.cpp
	g++ test.cpp -o stable/test $(Flags)

client: client.cpp AAPS.o AAPS.hpp
	g++ -c client.cpp $(Flags)
	g++ client.o AAPS.o -o stable/client $(Flags)

server: server.o AAPS.o UniqueID.o
	g++ server.o AAPS.o UniqueID.o -o stable/server $(Flags)


server.o: server.cpp AAPS.hpp UniqueID/UniqueID.hpp
	g++ -c server.cpp $(Flags)

AAPS.o:	AAPS.cpp
	g++ -c AAPS.cpp $(Flags)

UniqueID.o: UniqueID/UniqueID.cpp 
	g++ -c UniqueID/UniqueID.cpp $(Flags)


clean:
	rm -f *.o server test client
	rm -rf stable

semiclean:
	rm -f *.o
	