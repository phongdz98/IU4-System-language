#!/bin/bash

DATA=$(last -F | grep $1 | head -n 1)
echo $1
echo "=============================="
LOGIN_DATE=$(echo "$DATA" | awk '{print $6, $5, $8, $7}')
LOGOUT_DATE=$(echo "$DATA" | awk '{print $12, $11, $14, $13}')
echo "Login date - $LOGIN_DATE"
echo "Logout date - $LOGOUT_DATE"
