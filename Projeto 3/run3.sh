g++ -Wall -Wextra -std=c++17 -pedantic -o projeto3 projeto3.cpp &&
time ./projeto3 --compressor -i books.txt -o text2.igr &&
time ./projeto3 --decompressor -i text2.igr -o books.txt &&
diff inputs/books.txt outputs/books.txt