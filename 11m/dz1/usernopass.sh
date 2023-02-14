#! /bin/bash

echo "$1::$2:$3:$4:$5:$6" >> /etc/passwd
echo "$1::$7:0:-1:-1:::" >> /etc/shadow
echo "$1:x:$3:" >>  /etc/group
cd /home
mkdir $1
chown $1:$1 $1
chmod o-rwx $1
