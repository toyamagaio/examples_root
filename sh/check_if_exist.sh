#!/bin/bash

input_file="test.txt"

if [ -e $input_file ];then
        echo $input_file "exists"
else
    echo $input_file "doesn't exist"
fi
