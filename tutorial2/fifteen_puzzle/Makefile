CXX = g++
CXXFLAGS = -c -Wall -g
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

$(info SRCS = $(SRCS)) 

%.o:%.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@ 
	
puzzle:$(OBJS)
	$(CXX) -o $@ $^
	
clean:
	rm -f $(OBJS) puzzle *~