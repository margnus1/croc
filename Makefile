TARGET   := crocofinder
SRCS     := CrocGame.cpp Crawler.cpp main.cpp
OBJS     := ${SRCS:.cpp=.o}

CXX	 := g++
CXXFLAGS := -std=c++11 -Wall -ggdb

all: ${TARGET}

${TARGET}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ $^

${OBJS}: %.o: %.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

clean:
	rm -rfv ${OBJS} ${TARGET} *~ \#*\#
