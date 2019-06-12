include ../../config.mk 

EXE=test_safelist
OBJ=
INC=../
LIB=-lpthread
CFLAGS+=


.PHONY: clean install all

all: $(EXE)
	@$(call mvbin, $(EXE))
	@echo "finish"

test_safelist: test_safelist.cpp $(OBJ)
	$(CXX) $^ -o $@ -I$(INC) $(LIB) $(CFLAGS)

%.o: %.cpp
	$(CXX) -c $^ -I$(INC) $(LIB) $(CFLAGS)

install:
	echo "test install"

clean:
	rm -f $(OBJ)
	rm -f $(EXE)
	@$(call cleanbin)
