CXX = g++
CXXFLAGS = -Wall -g

proj4: proj4.cpp Cipher.o Atbash.o Scytale.o Ong.o CipherTool.o
	$(CXX) $(CXXFLAGS) proj4.cpp Cipher.o Atbash.o Scytale.o Ong.o CipherTool.o -o proj4

CipherTool.o: CipherTool.h CipherTool.cpp Cipher.h Atbash.h Scytale.h Ong.h
	$(CXX) $(CXXFLAGS) -c CipherTool.cpp

Atbash.o: Atbash.h Atbash.cpp Cipher.h
	$(CXX) $(CXXFLAGS) -c Atbash.cpp

Scytale.o: Scytale.h Scytale.cpp Cipher.h
	$(CXX) $(CXXFLAGS) -c Scytale.cpp

Ong.o: Ong.h Ong.cpp Cipher.h
	$(CXX) $(CXXFLAGS) -c Ong.cpp

Cipher.o: Cipher.h Cipher.cpp
	$(CXX) $(CXXFLAGS) -c Cipher.cpp

clean:
	rm *~

run:
	./proj4
