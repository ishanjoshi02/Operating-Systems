echo "Enter file or directory name"
read name1
if [ -f $name1 ]
then
	echo "It is a file"
else
	echo "It is a directory"
fi 
