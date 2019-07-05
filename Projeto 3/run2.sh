g++ -Wall -Wextra -std=c++17 -pedantic -o projeto3 projeto3.cpp &&
time ./projeto3 --compressor -i text.txt -o text.igr &&
time ./projeto3 --decompressor -i text.igr -o text.txt &&
diff inputs/text.txt outputs/text.txt