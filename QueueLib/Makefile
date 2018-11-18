CC       = gcc 
CFLAGS   = -Wall -g -O -fPIC
CXXFLAGS = 
INCLUDE  = -I ./
TARGET   = libmsgque.so
LIBPATH  = /usr/lib/

vpath %.h ./inc
 
OBJS     = msgqueue.o listApi.o
SRCS     = msgqueue.c listApi.c
 

all:$(OBJS)
	$(CC) -shared -fPIC -o $(TARGET) $(OBJS)
	cp $(TARGET) $(LIBPATH) -rf

clean:
	rm -f *.o *.so

$(OBJS):$(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $^
