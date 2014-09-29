#!/bin/sh
# First arguement specifies the name of the source file
# Second arguement (optional) specifies whether you want to compile the executable or not.
# 	Pass 1 as second arguement to run the executable, anything else for only compiling. By default it just compiles.

input=$1;
if [ $# -eq 2 ]
then
    option=$2;
else
    option=0;
fi

# Sets the execuatable name
OUTPUT="-o `basename $input .cpp`.out"

# Sets the additional path to search for header files
INCLUDE="-I /opt/OpenBLAS/include/"

# Sets the additional path to search for library files
LIBRARY_PATH="-L /opt/OpenBLAS/lib"

# Sets the libraries to be linked"
LIBRARY="-lopenblas"

FLAG="-fopenmp"

# Compiling
g++ $input $OUTPUT $INCLUDE $LIBRARY_PATH $LIBRARY $FLAG

return_val=$?

# Checks for error in compiling and for user directive
if [ $return_val -eq 0 ] && [ $option -eq 1 ]
then
    unset LD_LIBRARY_PATH
    export LD_LIBRARY_PATH=/opt/OpenBLAS/lib/
    ./`basename $input .cpp`.out 
else
    echo "Compilation return value $return_val"
fi
