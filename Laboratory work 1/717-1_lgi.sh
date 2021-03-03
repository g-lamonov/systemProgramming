#!/bin/bash

echo -e "\e[36mDeveloper: Lamonov Gennady"
echo -e "\e[36mTitle: File information"
echo -e "\e[36mDescription: This script will output the  information about the file: file name, file type, file size, file owner, access rights, creation date of the file.\n"
filename=""
choice="yes"

while true
do
	echo -e "\e[39mEnter the name of the file:"
	read filename
	if [ -e $filename ] 
		then
			echo ""
			echo "File information"
			echo "File name: "; stat -c%n $filename
			echo "Type file: "; stat -c%F $filename
			echo "File size in bytes: "; stat -c%s $filename
			echo "Owner of a file: "; stat -c%U $filename
			echo "Access rights: "; ls -l $filename | cut -c -10
			echo "Creation date: "; stat -c%z $filename
			echo ""
		else 
			echo "This file does not exist" >/dev/stderr
			echo ""
	fi
	while true
    	do
		echo "Want to find the file again? (y\N)"
		read choice
		case "$choice" in
				"Y" | "y" | "yes" | "Yes") echo "";  break;;
				"N" | "n" | "no" | "No") echo ""; echo "See you soon!"; exit $?;;
				* ) echo "Error. You need to enter y or N" >/dev/stderr;;
            	esac
    	done
done