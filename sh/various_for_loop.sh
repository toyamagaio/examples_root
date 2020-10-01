#!/bin/bash

echo "incriment"
min=0
max=10
for (( i=$min; i <= $max; i++ )); do
    echo $i
done
echo "/*******/"

echo "sequential num"
for i in `seq $min $max`; do
    echo $i
done
echo "/*******/"

echo "array"
array=(10 9 8 7 6 5 4 3 2 1 0)
file=aa.txt
for i in ${array[@]}; do
    echo $i
    echo "$i line" >> $file
done
echo "/*******/"

echo "from file (word by word)"
for i in $(cat $file); do
    echo $i
done
echo "/*******/"

echo "from file (line by line)"
while read line
do
  echo $line
done < $file
echo "/*******/"
rm -f $file

echo "specific number"
for i in 1 4 5; do
    echo $i
done
echo "/*******/"

echo "each files in local dir."
for file in `ls ./*`; do
    echo $file
done
echo "/*******/"
