include ../../config.mk 

EXE=test_exception
OBJ=
INC=../
LIB=
CFLAGS+=-luuid


.PHONY: clean install all

all: $(EXE)
	@$(call mvbin, $(EXE))
	@echo "finish"

test_exception: test_exception.cpp $(OBJ)
	$(CXX) $^ -o $@ -I$(INC) $(LIB) $(CFLAGS)

%.o: %.cpp
	$(CXX) -c $^ -I$(INC) $(LIB) $(CFLAGS)

install:
	echo "test install"

clean:
	rm -f $(OBJ)
	rm -f $(EXE)
	@$(call cleanbin)
