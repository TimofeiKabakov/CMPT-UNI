#!/bin/bash

# read the given file line by line in the following format partB.bash version < inputfile 
while read -r line; do
	# check for the incorrect input
	if [[ "$line" =~ [A-Za-z] || "$line" =~ "-" ]];
	then
		echo "Error: incorrect arguments in input file, must be positive integers!"
	else
		# set the delimiter to space so that each integer can be read into a array seperately
		IFS=' '
		read -a dec <<< "$line"
		OSname=$(uname)
		#echo $OSname
		if [ "$1" = winThreads ]
		then
			if [ "$OSname" != "Linux" ]
			then
				./winThreads ${dec[0]} ${dec[1]} ${dec[2]}
			else
				echo "This file only runs on windows"
			fi
		elif [ "$1" = posixThreads ]
		then
			if [ "$OSname" == "Linux" ]
			then
				./posixThreads ${dec[0]} ${dec[1]} ${dec[2]}
			else
				echo "This file only runs on Linux"
			fi
		fi
	fi
done
