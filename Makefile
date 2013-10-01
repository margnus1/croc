TARGET  := crocofinder
SRCS    := CrocGame.cpp Crawler.cpp main.cpp 
OBJS    := ${SRCS:.cpp=.o} 

CXX	:= clang++

all: ${TARGET}

${TARGET}: ${OBJS}
	${CXX} -o $@ $^

${OBJS}: %.o: %.cpp
	${CXX} -c -o $@ $<

clean:
	rm -rfv ${OBJS} ${TARGET} *~ \#*\#