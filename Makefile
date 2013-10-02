# To use a differet crawler, invoke
# make [target] CRAWLER=<crawlersrc.cpp>
#
# Remember to include "Crawler.h" no matter the name of crawlersrc.

CRAWLER 	:= Crawler.cpp

TARGET  	:= croco
DEPS		:= ToString.h CrocGame.h Crawler.h
SRCS    	:= ToString.cpp CrocGame.cpp main.cpp ${CRAWLER}
ODIR		:= obj
_OBJS		:= ${SRCS:.cpp=.o}
OBJS		:= $(patsubst %,$(ODIR)/%,$(_OBJS))
TMPS		:= *~ \#*\#
CXX	        := g++
CXXFLAGS    	:= -std=c++11 -Wall -ggdb

all: ${TARGET}

${TARGET}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ $^

${ODIR}/%.o: %.cpp $(DEPS) $(ODIR)
	${CXX} ${CXXFLAGS} -c -o $@ $<

$(ODIR):
	mkdir -p $(ODIR)

.PHONY: clean

clean:
	rm -rfv $(ODIR)/*.o ${TARGET} $(TMPS)

# For flymake; use M-x flymake-mode in EMACS for on-the-fly compilation
check-syntax:
	${CXX} ${CXXFLAGS} -fsyntax-only ${CHK_SOURCES}
