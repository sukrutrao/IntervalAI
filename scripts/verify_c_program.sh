#! /bin/bash

if [ "$#" -lt 1 ]
then
    echo "This script needs path to C program as an argument"
    exit 1
fi

filename=$1

../cbmc/src/goto-cc/goto-cc $filename -o ${filename::-2}.goto
if [ "$#" -eq 2 ]
then
	../build/IntervalAI -m $2 ${filename::-2}.goto
else
	../build/IntervalAI ${filename::-2}.goto
fi