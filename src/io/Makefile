include ../../config.mk

EXE=test_localfileio test_data
OBJ=LocalFileIO.o
INC=../
LIB=


.PHONY: clean install all

all: $(EXE)
	@$(call mvbin, $(EXE))
	@echo finish

%.o: %.cpp
	$(CXX) -c $^ -I$(INC) $(LIB) $(CFLAGS)

install:
	echo "test install"

clean:
	rm -f $(OBJ)
	rm -f $(EXE)
	rm -f $(TEST_EXE)
	rm -f tags
	@$(call cleanbin)

include ./Makefile4test
