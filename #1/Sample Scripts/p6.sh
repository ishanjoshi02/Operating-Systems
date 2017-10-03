echo "Enter file name to check permission"
read file1
if test -r $file1
then
	echo "Read permission is set"
fi
if test -w $file1
then
	echo "Write permission is set"
fi
if test -x $file1
then
	echo "Execute permission is set"
fi
