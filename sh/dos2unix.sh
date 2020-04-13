#!/bin/bash

#change newline charactors of files at dos dir from CRLF to LF.

files="dos/*"
for a_file in $files; do
#nkf -Lu ${dos_file} > ${unix_file}
dos_file_name=$a_file
unix_file_name=`echo $a_file | sed "s@dos/@@"`
#echo $a_file | sed "s/dos/uni/"
  echo $a_file $dos_file_name $unix_file_name
nkf -Lu $dos_file_name > $unix_file_name
done
