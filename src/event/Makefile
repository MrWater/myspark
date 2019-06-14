include ../../config.mk 

EXE=test_ps
OBJ=
INC=../
LIB=
CFLAGS+=-lpthread


.PHONY: clean install all

all: $(EXE)
	@$(call mvbin, $(EXE))
	@echo "finish"

test_ps: test_ps.cpp $(OBJ)
	$(CXX) $^ -o $@ -I$(INC) $(LIB) $(CFLAGS)

%.o: %.cpp
	$(CXX) -c $^ -I$(INC) $(LIB) $(CFLAGS)

install:
	echo "test install"

clean:
	rm -f $(OBJ)
	rm -f $(EXE)
	@$(call cleanbin)
