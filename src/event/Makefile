include ../../config.mk 

EXE=
OBJ=
INC=../
LIB=
CFLAGS+=-lpthread


.PHONY: clean install all

include ./Makefile4test

install:
	echo "test install"

clean:
	rm -f $(OBJ)
	rm -f $(EXE)
	rm -f tags
	@$(call cleanbin)
