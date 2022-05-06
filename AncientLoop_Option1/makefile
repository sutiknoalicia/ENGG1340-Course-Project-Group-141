FLAGS = -pedantic-errors -std=c++11

board.o: board.cpp board.h
	g++ $(FLAGS) -c $<

battle.o: battle.cpp battle.h
	g++ $(FLAGS) -c $<

mainStruct.o: mainStruct.cpp mainStruct.h
	g++ $(FLAGS) -c $<

menu.o: menu.cpp menu.h
	g++ $(FLAGS) -c $<

saveload.o: saveload.cpp saveload.h
	g++ $(FLAGS) -c $<

shop.o: shop.cpp shop.h
	g++ $(FLAGS) -c $<

main.o: main.cpp
	g++ $(FLAGS) -c $<

AL: main.o board.o battle.o mainStruct.o menu.o saveload.o shop.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f AL board.o battle.o mainStruct.o menu.o saveload.o shop.o main.o
