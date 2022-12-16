#! /bin/bash

$1&
echo "Open program $1"
echo "Wait 3s"
sleep 3
P=$(pgrep $1)
echo "Kill program $1"

kill -9 $P
