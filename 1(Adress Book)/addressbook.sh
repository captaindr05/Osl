#!/bin/bash

create() {
 echo "Enter name of Address Book:"
 read name
 co=$(ls | grep $name | wc -w)
 if [ $co -gt 0 ]
 then
   echo "File already exists!"
 else
   touch $name
   echo "File created successfully!"
 fi
}

display() {
 echo "Enter name of Address Book:"
 read name
 if [ -f $name ]
 then
   echo "----- Contents of $name -----"
   cat $name
   echo "-----------------------------"
 else
   echo "File not found!"
 fi
}

insert() {
 echo "Enter name of Address Book:"
 read name
 if [ -f $name ]
 then
   echo "Enter person name:"
   read pname
   echo "Enter phone number:"
   read ph
   echo "$pname  $ph" >> $name
   echo "Record inserted!"
 else
   echo "File not found!"
 fi
}

delete() {
 echo "Enter name of Address Book:"
 read name
 if [ -f $name ]
 then
   echo "Enter person name to delete:"
   read pname
   grep -v "$pname" $name > temp && mv temp $name
   echo "Record deleted (if existed)."
 else
   echo "File not found!"
 fi
}

modify() {
 echo "Enter name of Address Book:"
 read name
 if [ -f $name ]
 then
   echo "Enter person name to modify:"
   read pname
   grep -v "$pname" $name > temp
   echo "Enter new name:"
   read newn
   echo "Enter new phone:"
   read newp
   echo "$newn  $newp" >> temp
   mv temp $name
   echo "Record modified!"
 else
   echo "File not found!"
 fi
}

while true
do
 echo "1.Create  2.Display  3.Insert  4.Delete  5.Modify  6.Exit"
 echo "Enter your choice:"
 read ch
 case $ch in
 1) create ;;
 2) display ;;
 3) insert ;;
 4) delete ;;
 5) modify ;;
 6) exit ;;
 *) echo "Invalid choice!" ;;
 esac
done
