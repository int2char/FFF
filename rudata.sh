#!/bin/bash
#Program:
PATH="$PATH:/home/zhang/payback/scodWW"
#mkdir result 2>/dev/null
cd result
for node in 50 100 200 300 500 800 1000 2000
do
        mkdir $node 2>/dev/null
	cd $node
	echo "\n\n******************** $node ************************"
        task=0
        for iter in $( seq 1 6 )
	do
		task=$(($task+$node))
	done
        for Gnum in 0 2		
	do
		
 		echo "\n...................... $Gnum ........................"
		mkdir $Gnum 2>/dev/null
		cd $Gnum
		Gdata $node $task $Gnum
		cd ..
	done 
	cd ..
done
cd ..
