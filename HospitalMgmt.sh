#!/bin/bash

DB_FILE="hospital.dat"

create_database() {
    if [ -e "$DB_FILE" ]; then
        echo "Database already created"
        read -p "Press Enter to continue…" stay
    else
        touch "$DB_FILE"
        echo "Hospital database created successfully"
        read -p "Press Enter to continue…" stay
    fi
}

view_database() {
    if [ -e "$DB_FILE" ]; then
        echo -e "PatientID\tName\tAge\tGender\tDiagnosis\tDoctor"
        sort -n "$DB_FILE"
        read -p "Press Enter to continue…" stay
    else
        echo "Database not yet created"
        read -p "Press Enter to continue…" stay
    fi
}

insert_record() {
    if [ ! -e "$DB_FILE" ]; then
        echo "Database not yet created"
        return 1
    fi

    echo -n "Enter Patient ID: "
    read pid
    if grep -q "^$pid" "$DB_FILE"; then
        echo "Error: Patient ID already exists"
        return 1
    fi

    echo -n "Enter Name: "
    read name
    echo -n "Enter Age: "
    read age
    echo -n "Enter Gender (M/F/O): "
    read gender
    echo -n "Enter Diagnosis: "
    read diagnosis
    echo -n "Enter Attending Doctor: "
    read doctor

    echo -e "$pid\t$name\t$age\t$gender\t$diagnosis\t$doctor" >> "$DB_FILE"
    return 0
}

delete_record() {
    echo -n "Enter Patient ID to delete: "
    read pid
    if [ -e "$DB_FILE" ]; then
        grep -v "^$pid" "$DB_FILE" > temp.dat && mv temp.dat "$DB_FILE"
        echo "Record deleted successfully"
    else
        echo "Database not found"
    fi
    read -p "Press Enter to continue…" stay
}

modify_record() {
    echo -n "Enter Patient ID to modify: "
    read pid
    if [ ! -e "$DB_FILE" ]; then
        echo "Database not found"
        read -p "Press Enter to continue…" stay
        return
    fi

    old_record=$(grep "^$pid" "$DB_FILE")
    if [ -z "$old_record" ]; then
        echo "Record not found"
        read -p "Press Enter to continue…" stay
        return
    fi

    grep -v "^$pid" "$DB_FILE" > temp.dat

    IFS=$'\t' read -r old_pid old_name old_age old_gender old_diagnosis old_doctor <<< "$old_record"

    echo -n "Enter new Name [$old_name]: "
    read name;        name=${name:-$old_name}
    echo -n "Enter new Age [$old_age]: "
    read age;         age=${age:-$old_age}
    echo -n "Enter new Gender [$old_gender]: "
    read gender;      gender=${gender:-$old_gender}
    echo -n "Enter new Diagnosis [$old_diagnosis]: "
    read diagnosis;   diagnosis=${diagnosis:-$old_diagnosis}
    echo -n "Enter new Doctor [$old_doctor]: "
    read doctor;      doctor=${doctor:-$old_doctor}

    echo -e "$pid\t$name\t$age\t$gender\t$diagnosis\t$doctor" >> temp.dat
    mv temp.dat "$DB_FILE"

    echo "Record updated successfully"
    read -p "Press Enter to continue…" stay
}

display_record() {
    echo -n "Enter Patient ID to view: "
    read pid
    if [ -e "$DB_FILE" ]; then
        result=$(grep "^$pid" "$DB_FILE")
        if [ -n "$result" ]; then
            echo -e "PatientID\tName\tAge\tGender\tDiagnosis\tDoctor"
            echo -e "$result"
        else
            echo "No record found for Patient ID: $pid"
        fi
    else
        echo "Database not found"
    fi
    read -p "Press Enter to continue…" stay
}

delete_database() {
    if [ -e "$DB_FILE" ]; then
        rm "$DB_FILE"
        echo "Database deleted successfully"
    else
        echo "Database not found"
    fi
    read -p "Press Enter to continue…" stay
}

# ----- Main Menu Loop -----
while true; do
    clear
    echo "=== Hospital Management System ==="
    echo "1. Create database"
    echo "2. View all records"
    echo "3. Insert patient record"
    echo "4. Delete patient record"
    echo "5. Modify patient record"
    echo "6. Display patient record"
    echo "7. Delete entire database"
    echo "8. Exit"
    echo -n "Enter your choice [1-8]: "
    read ch

    case $ch in
        1) create_database ;;
        2) view_database ;;
        3)
            insert_record
            if [ $? -eq 0 ]; then
                echo "Record inserted successfully"
            else
                echo "Failed to insert record"
            fi
            read -p "Press Enter to continue…" stay
            ;;
        4) delete_record ;;
        5) modify_record ;;
        6) display_record ;;
        7) delete_database ;;
        8) echo "Goodbye!"; exit 0 ;;
        *)
            echo "Incorrect choice, try again."
            read -p "Press Enter to continue…" stay
            ;;
    esac
done
