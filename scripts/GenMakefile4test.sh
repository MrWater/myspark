#!/bin/sh 


exe="EXE+="
target="all: \$(EXE)\n\t@\$(call mvbin, \$(EXE))\n\t@echo "finish"\n\n"

for file in `ls test_*.cpp`
do
    exe=${exe}" "${file%.*}
    target="${target}${file%.*}: ${file} \$(OBJ)\n\t\$(CXX) \$^ -o \$@ -I\$(INC) \$(LIB) \$(CFLAGS)\n\n"
done

echo -e "${exe}\n" > Makefile4test
echo -e $target >> Makefile4test
