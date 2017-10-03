echo "Enter 1st number"
read num1
echo "Enter 2nd number"
read num2
sum=`expr $num1 + $num2`
mul=`expr $num1 \* $num2`
sub=`expr $num1 - $num2`
div=`expr $num1 / $num2`
echo "Summation = $sum"
echo "Subtraction = $sub"
echo "Multiplication = $mul"
echo "Division = $div"
