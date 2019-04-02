CC 		?= gcc
CXX		?= g++
CFLAGS		?= -g3 -Wall -rdynamic
CXXFLAGS 	?= -g3 -Wall -rdynamic

ECHO    	?= @

INCLUDE 	+= -I ../include/	

SRC =$(wildcard *.c ) $(wildcard *.cpp) 
OBJ =$(patsubst %.c, %.o,$(patsubst %.cpp,%.o,$(SRC)))

BIN =test 

.PHONY : everything objs clean veryclean rebuild

everything : $(BIN)

all : $(BIN)

objs : $(OBJ)

rebuild : veryclean everything

%.o:%.cpp
	$(ECHO)$(CXX) -o $@ $(INCLUDE) -c $< $(CXXFLAGS)

%.o:%.c
	$(ECHO)$(CC) -o $@ $(INCLUDE) -c $< $(CFLAGS)

$(BIN):$(OBJ)
	$(ECHO)$(CXX) -o $@ $^ 
	$(ECHO)rm -f $(OBJ)
	$(ECHO)rm -f *.o

clean:
	$(ECHO)rm -f $(BIN)
	$(ECHO)rm -f *.o

veryclean : clean
	rm -rf $(BIN)



