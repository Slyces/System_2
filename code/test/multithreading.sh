a = $(( (RANDOM % 10) + 1 ))
b = $(( (RANDOM % 10) + 1 ))
c = $(( (RANDOM % 10) + 1 ))
d = $(( (RANDOM % 10) + 1 ))

./nachos -rs $a$b$c$d -x ../test/$1
