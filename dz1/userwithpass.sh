#! /bin/bash

S=$(tr -dc A-Za-z0-9 < /dev/urandom | head -c 10)

P=$(openssl passwd -5 -salt $S $2)
echo "$1:x:$3:$4:$5:$6:$7" >> /etc/passwd
echo "$1:$P:$8:0:99999:7:::" >> /etc/shadow
echo "$1:x:$4:" >> /etc/group

cd /home

mkdir $1
chown $1:$1 $1

chmod o-rwx $1 
