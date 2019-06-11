include ../../config.mk

EXE=test_localfileio test_data
OBJ=LocalFileIO.o
INC=../
LIB=


.PHONY: clean install all

all: $(EXE) $(ALLTEST)
	@$(call mvbin, $(EXE))
	@echo "finish"

test_localfileio: test_localfileio.cpp $(OBJ)
	$(CXX) $^ -o $@ -I$(INC) $(LIB) $(CFLAGS)

test_data: test_data.cpp $(OBJ)
	$(CXX) $^ -o $@ -I$(INC) $(LIB) $(CFLAGS)

%.o: %.cpp
	$(CXX) -c $^ -I$(INC) $(LIB) $(CFLAGS)

install:
	echo "test install"

clean:
	rm -f $(OBJ)
	rm -f $(EXE)
	@$(call cleanbin)
