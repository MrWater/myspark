include ../../config.mk 

EXE=
OBJ=Server.o AIOServer.o
INC=../
LIB=-laio -lpthread


.PHONY: clean install all

%.o: %.cpp
	$(CXX) -c $^ -I$(INC) $(LIB) $(CFLAGS)

all: $(EXE)
	@$(call mvbin, $(EXE))
	@echo finish

install:
	echo "test install"

clean:
	rm -f $(OBJ)
	rm -f $(EXE)
	rm -f $(TEST_EXE)
	rm -f tags
	@$(call cleanbin)

include ./Makefile4test
