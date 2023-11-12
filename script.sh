#Compilamos para el tipo C invoca función de Asembler

#Primero se ensambla el código de Asembler
nasm -f elf32 Enmascarar.asm -o enmascarar.o

#Luego se compilan ambos a través de GCC
gcc -m32 -o tp enmascarar.o Enmascarar.c

#Se ejecuta el archivo pasandole los parámetros requeridos
./tp "img/img1_1600x1200.rgb" "img/img2_1600x1200.rgb" "img/masc_1600x1200.rgb"

#Usamos Graphick Magic para convertir Imagen a png
gm convert resultado.rgb resultado.png
#overleaf
#Mostramos el resultado en el Visor de Imágenes.
gpicview resultado.png

exit
