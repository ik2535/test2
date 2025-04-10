CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11 -lcurl -lsqlite3 -ljsoncpp

MarketDataJson: Util.o MarketData.o MarketDataJson.o
	$(CC) $(CFLAGS) -o MarketDataJson Util.o MarketData.o MarketDataJson.o

MarketDataJson.o: Util.h Stock.h MarketData.h MarketDataJson.cpp
	$(CC) $(CFLAGS) -c MarketDataJson.cpp

MarketData.o: Util.h Stock.h MarketData.h MarketData.cpp
	$(CC) $(CFLAGS) -c MarketData.cpp
	
Util.o: Util.h Util.cpp
	$(CC) $(CFLAGS) -c Util.cpp
	
clean:
	rm -rf MarketDataJson *.o
