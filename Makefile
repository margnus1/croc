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
CXX		:= clang++

all: ${TARGET}

${TARGET}: ${OBJS}
	${CXX} -o $@ $^

${ODIR}/%.o: %.cpp $(DEPS) $(ODIR)
	${CXX} -c -o $@ $<

$(ODIR):
	mkdir -p $(ODIR)

.PHONY: clean

clean:
	rm -rfv $(ODIR)/*.o ${TARGET} $(TMPS)