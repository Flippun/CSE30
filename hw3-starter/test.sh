make
./extractor $@  > output
extractor-ref $@ > ref
diff -s output ref
