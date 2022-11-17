CXX:=g++
CXXFLAGS:=-g -Wall -std=c++20

RM:=rm
RMFLAGS:=-rf

SRC:=./src
OBJ:=./obj
EXAMPLES:=./examples

SRCS:=$(wildcard $(SRC)/*.cpp)
OBJS:=$(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))
HDRS:=$(wildcard $(SRC)/*.hpp)
INCLUDE:=-I$(SRC)

APP:=mitn

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

.PHONY: $(APP)
all: $(APP)
$(APP): $(APP).cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $< $(OBJS)

test:
	./$(APP)

clean:
	$(RM) $(RMFLAGS) $(OBJS) $(APP)