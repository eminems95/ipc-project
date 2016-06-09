#!/bin/bash

echo "Running Main program"

	echo "=================================================================="
	echo "CPU load:"
	uptime
	echo "Shared memory information:"
	ipcs | grep "0x00000859"
	echo "=================================================================="
	sleep 3

./Main

for(( i=0;i<5;i++ ))
do
	echo "=================================================================="
	echo "CPU load:"
	uptime
	echo "Shared memory information:"
	ipcs | grep "0x00000859"
	echo "=================================================================="
	sleep 1
done
