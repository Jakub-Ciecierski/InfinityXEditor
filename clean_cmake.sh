#make clean 2> /dev/null

find . -name "Makefile" -not -path "./dependencies/*" \
        -exec rm -rf 2> /dev/null {} \;
find . -name "CMakeCache.txt" -not -path "./dependencies/*" \
        -exec rm -rf 2> /dev/null {} \;
find . -name "cmake_install.cmake" -not -path "./dependencies/*" \
        -exec rm -rf 2> /dev/null {} \;
find . -type d -name "CMakeFiles" -not -path "./dependencies/*" \
        -exec rm -rf 2> /dev/null {} \;

