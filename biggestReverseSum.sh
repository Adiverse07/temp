#!/bin/bash
echo "running"
while true; do
  echo ""
  echo "===== MENU ====="
  echo "a) Find biggest of three numbers"
  echo "b) Reverse a number"
  echo "c) Print a word N times"
  echo "d) Sum of digits of a 4-digit number"
  echo "e) Exit"
  echo "Enter your choice:"
  read choice

  case $choice in
    a)
      echo "Enter 3 numbers:"
      read n1 n2 n3
      if [ "$n1" -ge "$n2" ] && [ "$n1" -ge "$n3" ]; then
        echo "Biggest: $n1"
      elif [ "$n2" -ge "$n1" ] && [ "$n2" -ge "$n3" ]; then
        echo "Biggest: $n2"
      else
        echo "Biggest: $n3"
      fi
      ;;

    b)
      echo "Enter a number to reverse:"
      read num
      rev=0
      while [ $num -gt 0 ]; do
        digit=$((num % 10))
        rev=$((rev * 10 + digit))
        num=$((num / 10))
      done
      echo "Reversed number: $rev"
      ;;

    c)
      echo "Enter a number (N):"
      read N
      echo "Enter a word:"
      read word
      for ((i=1; i<=N; i++)); do
        echo "$word"
      done
      ;;

    d)
      echo "Enter a 4-digit number:"
      read num
      sum=0
      while [ $num -gt 0 ]; do
        digit=$((num % 10))
        sum=$((sum + digit))
        num=$((num / 10))
      done
      echo "Sum of digits: $sum"
      ;;

    e)
      echo "Exiting..."
      exit 0
      ;;

    *)
      echo "Invalid choice"
      ;;
  esac
done
