#! /bin/bash
. ./config.conf
tar -zcvf $dump_target/$(date +%s).tar.gz $source_name
echo "archive $(date +%s).tar.gz is created!"
rm -rf "$source_name"
echo "directory $source_name is deleted!"
./backup.sh

