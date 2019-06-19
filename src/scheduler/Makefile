include ../../config.mk 

EXE=
OBJ=
INC=../
LIB=
CFLAGS+=-luuid


.PHONY: clean install all

include ./Makefile4test

%.o: %.cpp
	$(CXX) -c $^ -I$(INC) $(LIB) $(CFLAGS)

install:
	echo "test install"

clean:
	rm -f $(OBJ)
	rm -f $(EXE)
	rm -f tags
	@$(call cleanbin)
