#!/bin/bash

create_database() {
    if [ -e std.dat ]; then
        echo "Database already created"
        read stay
    else
        touch std.dat
        echo "Database created successfully"
    fi
}

view_database() {
    if [ -e std.dat ]; then
        echo -e "Rollno\tName\tM1\tM2\tM3\tM4\tM5\tTotal\tPercent"
        sort -n std.dat
        read stay
    else
        echo "Database not yet created"
        read stay
    fi
}

insert_data() {
    if [ -e std.dat ]; then
        echo "Enter student ROLL NO: "
        read roll
        if grep -q "^$roll" std.dat; then 
            echo "Error: roll no already exists"
            return 1
        fi

        echo "Enter student NAME:"
        read name
        echo "Enter marks1:"
        read m1
        echo "Enter marks2:"
        read m2
        echo "Enter marks3:"
        read m3
        echo "Enter marks4:"
        read m4
        echo "Enter marks5:"
        read m5

        total=$((m1 + m2 + m3 + m4 + m5))
        percent=$((100 * total / 500))
        echo -e "$roll\t$name\t$m1\t$m2\t$m3\t$m4\t$m5\t$total\t$percent" >> std.dat
        return 0
    else
        echo "Database not yet created"
        return 1
    fi
}

delete_record() {
    echo "Enter student ROLL NO to delete: "
    read roll
    if [ -e std.dat ]; then
        grep -v "^$roll" std.dat > temp.dat
        mv temp.dat std.dat
        echo "Record deleted successfully"
    else
        echo "Database not found"
    fi
}

modify_record() {
    echo "Enter student ROLL NO to modify: "
    read roll
    echo "Enter new student NAME: "
    read new_name

    if [ -e std.dat ]; then
        old_record=$(grep "^$roll" std.dat)
        if [ -z "$old_record" ]; then
            echo "Record not found"
            return
        fi

        grep -v "^$roll" std.dat > temp.dat

        # Extract fields
        IFS=$'\t' read -r old_roll old_name m1 m2 m3 m4 m5 total percent <<< "$old_record"

        echo -e "$roll\t$new_name\t$m1\t$m2\t$m3\t$m4\t$m5\t$total\t$percent" >> temp.dat
        mv temp.dat std.dat

        echo "Name updated successfully"
    else
        echo "Database not found"
    fi
}

display_result() {
    echo "Enter student ROLL NO to view result: "
    read roll
    if [ -e std.dat ]; then
        result=$(grep "^$roll" std.dat)
        if [ -n "$result" ]; then
            echo -e "Rollno\tName\tM1\tM2\tM3\tM4\tM5\tTotal\tPercent"
            echo -e "$result"
        else
            echo "No record found for Roll No: $roll"
        fi
    else
        echo "Database not found"
    fi
}

delete_database() {
    if [ -e std.dat ]; then
        rm std.dat
        echo "Database deleted successfully"
    else
        echo "Database not found"
    fi
}

# ----- Main Menu Loop -----
while true; do
    echo -e "\nStudent database........"
    echo -e "Enter your Choice:\n1. Create database\n2. View database\n3. Insert record\n4. Delete record\n5. Modify record\n6. Delete database\n7. Display result\n8. Exit"
    read ch

    case $ch in
        1) create_database ;;
        2) view_database ;;
        3)
            insert_data
            if [ $? -eq 0 ]; then
                echo "Record inserted successfully"
            else
                echo "Failed to insert record"
            fi
            ;;
        4) delete_record ;;
        5) modify_record ;;
        6) delete_database ;;
        7) display_result ;;
        8) exit ;;
        *)
            echo "Incorrect choice"
            ;;
    esac
done
