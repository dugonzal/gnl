#read -p  "ruta del archivo de prueba -< \n " archivo

clang -Wall -Werror -Wextra get_next_line.c -D BUFFER_SIZE=1 -o gnl; valgrind   --leak-check=full   --track-origins=yes -s ./gnl < test
