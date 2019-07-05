g++ -Wall -Wextra -std=c++17 -pedantic -o projeto3 projeto3.cpp &&
time ./projeto3 --compressor -i Stavechurch-heddal.bmp -o image.igr &&
time ./projeto3 --decompressor -i image.igr -o Stavechurch-heddal.bmp &&
vimdiff inputs/Stavechurch-heddal.bmp outputs/Stavechurch-heddal.bmp