CXX= g++
CXXFLAGS = -Wall -O -std=c++0x -g `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJS = subject.o model.o controller.o DeckGUI.o view.o main.o Card.o Command.o ComputerPlayer.o Deck.o Game.o HumanPlayer.o Player.o Table.o
EXEC = straights

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC)

clean:
	rm $(EXEC) $(OBJS)

DeckGUI.o: DeckGUI.h DeckGUI.cc
model.o: subject.h model.h model.cc
subject.o: subject.h subject.cc
controller.o: controller.h model.h controller.cc
view.o: view.h observer.h controller.h model.h subject.h DeckGUI.h view.cc
main.o: view.h controller.h model.h main.cc
