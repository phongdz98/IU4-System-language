#! /bin/bash

$1&

P=$(pgrep $1)

kill -9 $P
