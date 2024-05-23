gcc -std=gnu18 -Wall -Wextra -g -o scrambler scrambler.c
./scrambler $1 $2 $3 > output
scrambler $1 $2 $3 > ref
diff -s output ref
 
