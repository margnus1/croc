# To use a differet crawler, invoke
# make [target] CRAWLER=<crawlersrc.cpp>
#
# Remember to include "Crawler.h" no matter the name of crawlersrc.

CRAWLER 	:= Crawler4.cpp

TARGET  	:= croco
DEPS		:= ToString.h CrocGame.h Crawler.h dijkstra.h \
                   console.h markov.h
SRCS    	:= ToString.cpp CrocGame.cpp main.cpp ${CRAWLER} \
                   ProgressBar.cpp dijkstra.cpp console.cpp markov.cpp
ODIR		:= obj
_OBJS		:= ${SRCS:.cpp=.o}
OBJS		:= $(patsubst %,$(ODIR)/%,$(_OBJS))
TMPS		:= *~ \#*\#
CXX	        := clang++
CXXFLAGS    	:= -std=c++11 -Wall -ggdb
LDFLAGS         := -Wall -ggdb -lrt

all: ${TARGET}

${TARGET}: ${OBJS}
	${CXX} ${LDFLAGS} -o $@ $^

$(OBJS): | $(ODIR)

${ODIR}/%.o: %.cpp $(DEPS)
	${CXX} -c ${CXXFLAGS} $< -o $@ 

$(ODIR):
	mkdir -p $(ODIR)

.PHONY: clean

clean:
	rm -rfv $(ODIR)/*.o ${TARGET} $(TMPS)

# For flymake; use M-x flymake-mode in EMACS for on-the-fly compilation
check-syntax:
	${CXX} ${CXXFLAGS} -fsyntax-only ${CHK_SOURCES}
