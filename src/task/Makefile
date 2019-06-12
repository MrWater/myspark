include ../../config.mk 

EXE=test_task
OBJ=
INC=../
LIB=-luuid


.PHONY: clean install all

all: $(EXE)
	@$(call mvbin, $(EXE))
	@echo "finish"

test_task: test_task.cpp $(OBJ)
	$(CXX) $^ -o $@ -I$(INC) $(LIB) $(CFLAGS)

%.o: %.cpp
	$(CXX) -c $^ -I$(INC) $(LIB) $(CFLAGS)

install:
	@echo "test install"

clean:
	rm -f $(OBJ)
	rm -f $(EXE)
	@$(call cleanbin)
