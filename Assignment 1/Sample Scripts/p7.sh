echo "Enter file or directory name"
read name1
if test -f $name1
then
	echo "It is a file"
fi
if test -d $name1
then
	echo "It is a directory"
fi 
