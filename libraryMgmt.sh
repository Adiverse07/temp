#!/bin/bash

DB_FILE="library.dat"

create_database() {
    if [ -e "$DB_FILE" ]; then
        echo "Database already exists"
        read -p "Press Enter to continue…" stay
    else
        touch "$DB_FILE"
        echo "Library database created successfully"
        read -p "Press Enter to continue…" stay
    fi
}

view_database() {
    if [ -e "$DB_FILE" ]; then
        echo -e "BookID\tTitle\tAuthor\tYear\tGenre\tAvailable"
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

    echo -n "Enter Book ID: "
    read bid
    if grep -q "^$bid" "$DB_FILE"; then
        echo "Error: Book ID already exists"
        return 1
    fi

    echo -n "Enter Title: "
    read title
    echo -n "Enter Author: "
    read author
    echo -n "Enter Publication Year: "
    read year
    echo -n "Enter Genre: "
    read genre
    echo -n "Is it Available? (Y/N): "
    read available

    echo -e "$bid\t${title//	/ }\t${author//	/ }\t$year\t$genre\t$available" >> "$DB_FILE"
    return 0
}

delete_record() {
    echo -n "Enter Book ID to delete: "
    read bid
    if [ -e "$DB_FILE" ]; then
        grep -v "^$bid" "$DB_FILE" > temp.dat && mv temp.dat "$DB_FILE"
        echo "Record deleted successfully"
    else
        echo "Database not found"
    fi
    read -p "Press Enter to continue…" stay
}

modify_record() {
    echo -n "Enter Book ID to modify: "
    read bid
    if [ ! -e "$DB_FILE" ]; then
        echo "Database not found"
        read -p "Press Enter to continue…" stay
        return
    fi

    old_record=$(grep "^$bid" "$DB_FILE")
    if [ -z "$old_record" ]; then
        echo "Record not found"
        read -p "Press Enter to continue…" stay
        return
    fi

    grep -v "^$bid" "$DB_FILE" > temp.dat

    IFS=$'\t' read -r old_bid old_title old_author old_year old_genre old_available <<< "$old_record"

    echo -n "Enter new Title [$old_title]: "
    read title;       title=${title:-$old_title}
    echo -n "Enter new Author [$old_author]: "
    read author;      author=${author:-$old_author}
    echo -n "Enter new Publication Year [$old_year]: "
    read year;        year=${year:-$old_year}
    echo -n "Enter new Genre [$old_genre]: "
    read genre;       genre=${genre:-$old_genre}
    echo -n "Is it Available? (Y/N) [$old_available]: "
    read available;   available=${available:-$old_available}

    echo -e "$bid\t$title\t$author\t$year\t$genre\t$available" >> temp.dat
    mv temp.dat "$DB_FILE"

    echo "Record updated successfully"
    read -p "Press Enter to continue…" stay
}

display_record() {
    echo -n "Enter Book ID to view: "
    read bid
    if [ -e "$DB_FILE" ]; then
        result=$(grep "^$bid" "$DB_FILE")
        if [ -n "$result" ]; then
            echo -e "BookID\tTitle\tAuthor\tYear\tGenre\tAvailable"
            echo -e "$result"
        else
            echo "No record found for Book ID: $bid"
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
    echo "=== Library Management System ==="
    echo "1. Create database"
    echo "2. View all books"
    echo "3. Insert new book"
    echo "4. Delete a book"
    echo "5. Modify book record"
    echo "6. Display book details"
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
