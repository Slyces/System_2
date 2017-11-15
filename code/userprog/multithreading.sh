#!/bin/sh
a=$(( ( RANDOM % 9 ) + 1 ))
b=$(( ( RANDOM % 9 ) + 1 ))
c=$(( ( RANDOM % 9 ) + 1 ))
d=$(( ( RANDOM % 9 ) + 1 ))

./nachos -rs "$a$b$c$d" -x $1
