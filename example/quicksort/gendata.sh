#!/bin/sh

NUM=10000
echo "#define NUM $NUM" > data.h
echo 'int array[NUM]={' >> data.h
while [ $NUM -gt 0 ]
do
    num=$RANDOM
    echo $num
    printf "$num," >> data.h
    NUM=$((NUM-1))
done
echo '};' >> data.h
