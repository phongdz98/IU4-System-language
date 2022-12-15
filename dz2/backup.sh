#! /bin/bash

. ./config.conf
declare -a filelist
counter=0

for file in $dump_target/*; do
filelist[${#filelist[@]}+1]=$(echo "$file");
done

if [ ${#filelist[@]} -gt $dump_max ]
then
IFS=$'\n' sorted=($(sort <<< "${filelist[*]}")) ; unset IFS
for i in $(seq $(expr ${#sorted[@]} - $dump_max)); do
rm -f ${sorted[$counter]}
let counter+=1
done
fi
