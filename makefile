DIR = `basename $(PWD)`

NAME1 = main

EXEC1 = $(NAME1).x

OBJS1 = $(NAME1).o

CFLAGS = -Wall -O -std=c++11
LFLAGS = -Wall -O

CO = g++
LD = $(CO)

AR = ar

ARFLAGS = rcs

LDLIBS = -lncurses

%.o: %.cpp %.h
	$(CO) $(CFLAGS) -c $<

%.o: %.cpp
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1)

$(EXEC1): $(OBJS1)
	$(LD) $(OBJS1) -o $@ $(LFLAGS) $(LDLIBS)



.PHONY: run
run1: $(EXEC1)
	./$(EXEC1)

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )