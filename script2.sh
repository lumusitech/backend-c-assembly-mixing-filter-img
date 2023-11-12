#Compilamos para el tipo C invoca función de Asembler

#Primero se ensambla el código de Asembler




nasm -f elf32 Enmascarar.asm -o enmascarar.o


gcc -m32 -o tp enmascarar.o Enmascarar.c

#echo $1

#cd $1

numdirec=0


for i in $( ls -d */ )
do




echo $i

count=0


for x in $(ls $i)
do

if [ "$count" -eq 0 ]; then
	var1=$x

fi



if [ "$count" -eq 2 ]; then
	var3=$x
fi



if [ "$count" -eq 1 ]; then
	var2=$x
fi


count=$((count+1)) 



done


#Luego se compilan ambos a través de GCC
#Se ejecuta el archivo pasandole los parámetros requeridos


./tp "$i$var1"  "$i$var2" "$i$var3"


mv resultado.rgb resultado$numdirec.rgb


sleep 10


numdirec=$((numdirec+1)) 


done






exit


 