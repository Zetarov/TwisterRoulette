CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++11
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
EXEC=roulette.out

$(EXEC): $(OBJ)
	$(CXX) $^ $(LDFLAGS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^

launch: $(EXEC)
	./$^

clean:
	rm *.o*

commit:
	cat commit >> changelog
	date >> changelog
	echo "*****************" >> changelog
	git add changelog
	git commit -F commit

.PHONY: clean commit
