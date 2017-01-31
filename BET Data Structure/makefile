proj4.x: proj4_driver.o
	g++ -o proj4.x proj4_driver.o bet.o

proj4_driver.o: proj4_driver.cpp bet.cpp
	g++ -c -std=c++11 proj4_driver.cpp bet.cpp

clean:
	rm *.o *.x

