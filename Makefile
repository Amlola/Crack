all: Crk

Crk: main.o patcher.o
	g++ -g -o video.exe obj/main.o obj/patcher.o

main.o: src/main.cpp
	g++ -g -c src/main.cpp -o obj/main.o

patcher.o: src/patcher.cpp
	g++ -g -c src/patcher.cpp -o obj/patcher.o

clean:
	rm -rf obj/* video.exe