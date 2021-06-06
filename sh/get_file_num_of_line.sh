#!/bin/sh

#echo $#
if [ $# -ne 1 ];then
  echo "usage: ${0} {file}"
  exit
fi

file=${1}

num_of_line=`grep '' ${file}|wc -l`

#another method
#num_of_line_wc=`wc -l ${file} | awk '{print $1}'`

num_of_line_with_content=`grep . ${file}|wc -l`

echo 'num_of_line num_of_line_with_content'
echo "${num_of_line} ${num_of_line_with_content}"
