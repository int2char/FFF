Gdata:*.cpp *.h 
	g++ -g -o Gdata -std=c++11 *.h *.cpp
clean:
	rm -f *.gch *.o Gdata *.out core*  *.txt -r result
