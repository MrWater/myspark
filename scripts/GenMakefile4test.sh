#!/bin/sh 


exe="TEST_EXE="
target="test: \$(TEST_EXE)\n\t@\$(call mvbin, \$(TEST_EXE))\n\t@echo "finish"\n\n"

for file in `ls test_*.cpp`
do
    exe=${exe}" "${file%.*}
    target="${target}${file%.*}: ${file} \$(OBJ)\n\t\$(CXX) \$^ -o \$@ -I\$(INC) \$(LIB) \$(CFLAGS)\n\n"
done

echo -e "${exe}\n" > Makefile4test
echo -e $target >> Makefile4test
