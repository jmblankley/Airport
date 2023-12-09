CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lncurses

SRCS = myAirport.cpp AirportAnimator.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = fly

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)
