CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Werror -pedantic -O2 -fstack-protector-strong -fsanitize=address -fno-omit-frame-pointer

SRCS = main.cc Map.cc
OBJS = $(SRCS:.cc=.o)
HEADERS = fruits.h Map.h
TARGET = RPG41

LDLIBS = -lncurses

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) data.txt