#!/bin/bash
co=1
g++ mat_ran.cpp -o mat_ran.out
gcc only_blas.c -o only_blas.out -I /opt/OpenBLAS/include/ -L /opt/OpenBLAS/lib -lopenblas -fopenmp
unset LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/opt/OpenBLAS/lib/
gcc -o mat_mul.out mat_mul.c -lflint -fopenmp
rm -f input/*
printf "#Size\t\tFlint\t\t\tBLAS\n"
item=2
while [ $item -le 1000 ]
do
	fil=`echo "input/input$co.in"`
	rm -f outputs/*
	(./mat_ran.out $item) > $fil
	co=$(($co+1))
	printf "$item\t\t"
	./mat_mul.out < $fil
	printf "\t\t"
	./only_blas.out < $fil
	printf "\n"
	diff -b outputs/mat_mul_only_blas.out outputs/mat_mul_output.out
	re=$?
	if [ $re -ne 0 ];
	then
		echo "Different Output !! Error"
		exit 127
	fi
	echo "Done with $item" >&2
	if [ $item -eq 2 ];
	then
		item=10
	else
		item=$(($item + 10))
	fi
done
rm -f input/*
rm -f outputs/*
