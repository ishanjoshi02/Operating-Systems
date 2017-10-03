fileName="MyAddressBook"
opt=1
while [ "$opt" -lt 6 ]
do 
	echo -e "Choose one of the Following\n1. Create a New Address Book\n2. View Records\n3. Insert new Record\n4. Delete a Record\n5. Modify a Record\n6. Exit"
	read opt
	case $opt in 

	1)
		if [ -f $fileName ] ; then
			rm $fileName
		fi
		cont=1
		while [ "$cont" -gt 0 ]
		do 
			echo "Enter Name"
			read name
			echo "Enter Phone Number of $name"
			read number
			echo "Enter Address of $name"
			read address
			echo -e "$name\t$number\t$address\n" | cat >> $fileName
			echo "Enter 0 to Stop"
			read cont
		done
		;;

	2)	
		cat $fileName
		;;
	3)
		echo "Enter Name"
		read name
		echo "Enter Phone Number of $name"
		read number
		echo "Enter Address of $name"
		read address
		echo -e "$name\t$number\t$address\n" | cat >> $fileName
		;;
	4) 
		echo "Name/Phone Number"
		read pattern
		temp="temp"
		grep -v $pattern $fileName | cat >> $temp
		rm $fileName
		cat $temp | cat >> $fileName
		rm $temp
		;;
	5)
		echo "Name/Phone Number"
		read pattern
		temp="temp"
		grep -v $pattern $fileName | cat >> $temp
		rm $fileName
		cat $temp | cat >> $fileName
		rm $temp
		echo "Enter Name"
		read name
		echo "Enter Phone Number of $name"
		read number
		echo "Enter Address of $name"
		read address
		echo -e "$name\t$number\t$address\n" | cat >> $fileName
		;;		
	esac
done
