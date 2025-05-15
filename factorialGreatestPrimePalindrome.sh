
#pract 2_2 factorial,greatest,prime,number palindrome,string palindrome

#!/bin/bash
echo "running"
while true
do
  echo ""
  echo "-------- MENU --------"
  echo "a) Find Factorial"
  echo "b) Find Greatest of Three Numbers"
  echo "c) Check Prime Number"
  echo "d) Check Number Palindrome"
  echo "e) Check String Palindrome"
  echo "f) Exit"
  echo "----------------------"

  read -p "Enter your choice (a-f): " choice

  case $choice in
    a)
      read -p "Enter a number: " num
      awk -v n="$num" 'BEGIN {
        fact = 1
        for (i = 1; i <= n; i++) {
          fact = fact * i
        }
        print "Factorial of", n, "is", fact
      }'
      ;;

    b)
      read -p "Enter first number: " a
      read -p "Enter second number: " b
      read -p "Enter third number: " c
      awk -v x="$a" -v y="$b" -v z="$c" 'BEGIN {
        max = x
        if (y > max) max = y
        if (z > max) max = z
        print "Greatest number is", max
      }'
      ;;

    c)
      read -p "Enter a number: " num
      awk -v n="$num" 'BEGIN {
        isPrime = 1
        if (n <= 1) isPrime = 0
        for (i = 2; i <= int(n/2); i++) {
          if (n % i == 0) {
            isPrime = 0
            break
          }
        }
        if (isPrime)
          print n, "is a prime number"
        else
          print n, "is not a prime number"
      }'
      ;;

    d)
      read -p "Enter a number: " num
      awk -v n="$num" 'BEGIN {
        original = n
        reverse = 0
        while (n > 0) {
          digit = n % 10
          reverse = reverse * 10 + digit
          n = int(n / 10)
        }
        if (reverse == original)
          print original, "is a palindrome"
        else
          print original, "is not a palindrome"
      }'
      ;;

    e)
      read -p "Enter a string: " str
      awk -v s="$str" 'BEGIN {
        rev = ""
        for (i = length(s); i > 0; i--) {
          rev = rev substr(s, i, 1)
        }
        if (rev == s)
          print s, "is a palindrome"
        else
          print s, "is not a palindrome"
      }'
      ;;

    f)
      echo "Exiting the program. Goodbye!"
      break
      ;;

    *)
      echo "Invalid choice! Please choose between a to f."
      ;;
  esac
done