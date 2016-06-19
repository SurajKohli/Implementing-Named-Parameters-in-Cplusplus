#! /bin/bash
OBJ_FLAG="-o"
C_FLAG="-c"

if [ $# -eq 0 ]
then
    echo "Usage : $0 [FILENAME] .. "
    echo "Run $0 -h for help"
    exit 0
fi
while getopts "ch" o;
do  case "$o" in
    c)  OBJ_FLAG="-c";;
    h) echo "Usage : $0 [FILENAME] .. "
       echo "Use -c for generating object file"
       exit 0
       ;;
    esac
done
make
rm -f tmp
rm -f tmp.cpp
if [ $OBJ_FLAG = "-c" ]
then
    bin/cnp $2 2>err.txt
    g++ -std=c++14 -c tmp.cpp
    exit 0;
else
    bin/cnp $1 2>err.txt
    g++ -std=c++14 tmp.cpp -o tmp  
fi

echo "";
echo "----------------------------------------------------------------";
echo "---------------------OUTPUT OF YOUR FILE------------------------";
echo "----------------------------------------------------------------";
./tmp
echo "";
echo "----------------------------------------------------------------";
echo "----------------------- END OF OUTPUT --------------------------";
echo "----------------------------------------------------------------";
