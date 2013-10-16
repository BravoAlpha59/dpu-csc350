LDFLAGS=-lGL -lGLU -lglut

PROG = hw3
HDRS = 
SRCS = $(PROG).cc

OBJS = $(SRCS:.cc=.o)

$(PROG):$(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(PROG)

$(PROG).o: $(PROG).cc

all:	$(PROG)

clean:
	-rm -f $(PROG) $(OBJS)