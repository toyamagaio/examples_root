#!/bin/bash

echo $#
if [ $# -ne 1 ];then
  echo 'usage: ./check_argv.sh {runnum}'
  exit
fi

if [ ${1} -lt 10 ];then
   run=000${1}
elif [ ${1} -lt 100 ];then
   run=00${1}
elif [ ${1} -lt 1000 ];then
   run=0${1}
else 
   run=${1}
fi

echo ${run}
