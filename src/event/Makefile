include ../../config.mk 

EXE=
OBJ=
INC=../
LIB=
CFLAGS+=-lpthread


.PHONY: clean install all

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
