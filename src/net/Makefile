include ../../config.mk 

EXE=
OBJ=
INC=../
LIB=


.PHONY: clean install all

include ./Makefile4test

%.o: %.cpp
	$(CXX) -c $^ -I$(INC) $(LIB) $(CFLAGS)

install:
	echo "test install"

clean:
	rm -f $(OBJ)
	rm -f $(EXE)
	@$(call cleanbin)

