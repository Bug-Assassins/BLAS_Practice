#!/bin/bash
co=1
array=(2 10 25 50 100 150 200 250 256 300 350 400 450 500 550 575 589 600 800 900 1000 1500 2000)
g++ mat_ran.cpp -o mat_ran.out
gcc only_blas.c -o only_blas.out -I /opt/OpenBLAS/include/ -L /opt/OpenBLAS/lib -lopenblas -fopenmp
unset LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/opt/OpenBLAS/lib/
gcc -o mat_mul.out mat_mul.c -lflint -fopenmp
rm -f input/*
for item in ${array[*]}
do
	fil=`echo "input/input$co.in"`
	rm -f outputs/*
	(./mat_ran.out $item) > $fil
	co=$(($co+1))
	printf "$item\t"
	./mat_mul.out < $fil
	./only_blas.out < $fil
	diff -b outputs/mat_mul_only_blas.out outputs/mat_mul_output.out
	re=$?
	if [ $re -eq 0 ];
	then
		echo "Outputs are Equal"
	else
		echo "Different Output !! Error"
		exit 127
	fi
done
