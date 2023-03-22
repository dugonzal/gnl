#read -p  "ruta del archivo de prueba -< \n "archivo

gcc -Wall -Werror -Wextra get_next_line.c -o gnl; valgrind   --leak-check=full   --track-origins=yes -s ./gnl < test
