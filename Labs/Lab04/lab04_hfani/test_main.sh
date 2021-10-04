#!/bin/bash
echo "start building main program:"
echo "compiling to assembly lines ..."
cc main.c -S 
cc increment.c -S
echo "translating to opcodes ..."
cc main.s -c
cc increment.s -c
echo "statically linking all required opcodes ..."
cc main.o increment.o -o main
echo "build successfully done!"
#echo "running the main program"
#./main
#echo "running the main for input 4:"
#./main <<< 4
#echo "running the main for input 10:"
#./main <<< 10
while read input 
do 
	echo "test the main program for $input"
	./main <<< $input

done < "./test_inputs.txt"

