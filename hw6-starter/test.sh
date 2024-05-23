make
./fpconvert $1  > output
/home/linux/ieng6/cs30wi24/public/bin/fpconvert-ref $1 > ref
diff -s output ref
