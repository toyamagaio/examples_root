#!/bin/sh

echo $#
if [ $# -ne 1 ];then
  echo 'usage: ./get_file_size.sh {target_dir}'
  exit
fi

#print only small size files (<100kB)
ls -l ${1} | awk '$5 <= 1000000 { print }'
#ls -l ${1} | awk '$5 >= 1000000 { print }'
