# This Program was written by:
#  
#
# Garrett O'Hara cssc1136 RedId: 822936303
#
# CS 480 | Professor Shen | April 2022

CXX=g++
CXXFLAGS=-std=c++11 -g
CFLAGS = -c -Wall -Iinclude 
THREADING = -pthread

paging : consumer.o producer.o rideshare.o broker.o
	$(CXX) $(CXXFLAGS) $(THREADING)  $^

# only with linux -o rideshare

rideshare.o : ridesharing.h io.h io.c rideshare.cpp

consumer.o : consumer.h consumer.cpp

producer.o : producer.h producer.cpp

broker.o : borker.h broker.cpp

clean :
	rm *.o