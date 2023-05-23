# delete files except .c , .h , .cpp, .bin or Makefile
# Author: Kei Mukoyama
# Date: 2023-05-23

find . -type f ! -name "*.c" ! -name "*.h" ! -name "*.cpp" ! -name "*.bin" ! -name "Makefile" ! -name "*.sh" -delete