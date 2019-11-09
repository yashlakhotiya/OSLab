echo "menu test program"
stop=0
while test $stop -eq 0
do
cat<<ENDOFMENU
1: PRINT THE DATE
2,3: PRINT THE CURRENT WORKING DIRECTORY
4: EXIT
ENDOFMENU
echo
echo "your choice?"
read reply
echo
case $reply in
"1")
date
;;
"2" | "3")
pwd
;;
"4")
stop=1
;;
*)
echo "Illegal choice"
;;
esac
done
