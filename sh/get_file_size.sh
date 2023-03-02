#!/bin/sh

echo $#
if [ $# -ne 1 ];then
  echo 'usage: ./get_file_size.sh {target_dir}'
  exit
fi

#print only small size files (<100kB)
ls -l ${1} | awk '$5 <= 10000000 { print $9}'
#ls -l ${1} | awk '$5 >= 1000000 { print }'
