#!/bin/bash

# Function to create a database
create_database() {
    echo -n "Enter the name of your database: "
    read db_filename

    if [[ -z "$db_filename" ]]; then
        echo "Database name cannot be empty!"
        return
    fi

    if [[ -f "$db_filename" ]]; then
        echo "Database file '$db_filename' already exists!"
    else
        touch "$db_filename" && echo "Database file '$db_filename' created successfully!" || echo "Failed to create database file!"
    fi
}

# Function to insert a record into the database
insert_record() {
    echo -n "Enter the name of the database to insert record: "
    read db_filename

    if [[ ! -f "$db_filename" ]]; then
        echo "Database file '$db_filename' does not exist. Create one before inserting records!"
        return
    fi

    echo "Enter details of the user:"
    read -p "Name: " name
    read -p "Email: " email
    read -p "Mobile: " mobile
    read -p "Address: " address

    if [[ -z "$name" || -z "$email" || -z "$mobile" || -z "$address" ]]; then
        echo "All fields are required!"
        return
    fi

    record="${name},${email},${mobile},${address}"

    echo "$record" >> "$db_filename" && echo "Record inserted successfully!" || echo "Failed to insert record!"
}

# Function to search for a record in the database
search_record() {
    echo -n "Enter the name of the database to search record (with extension): "
    read db_filename

    if [[ ! -f "$db_filename" ]]; then
        echo "Database file '$db_filename' does not exist."
        return
    fi

    echo -n "Enter the name to search in the address book: "
    read search_id

    if [[ -z "$search_id" ]]; then
        echo "Search name cannot be empty!"
        return
    fi

    if grep -q "^$search_id," "$db_filename"; then  
        record=$(grep "^$search_id," "$db_filename")
        IFS=',' read -r name email mobile address <<< "$record"
        echo "Record found! Details are as follows:"
        echo "Name: $name"
        echo "Email: $email"
        echo "Mobile Number: $mobile"
        echo "Address: $address"
    else
        echo "No record with name: $search_id!"
    fi
}

# Function to modify a record in the database
modify_record() {
    echo -n "Enter the name of the database to modify record (with file extension): "
    read db_filename

    if [[ ! -f "$db_filename" ]]; then
        echo "Database with filename '$db_filename' does not exist"
        return
    fi

    echo -n "Enter the User Name to modify: "
    read search_id

    if [[ -z "$search_id" ]]; then
        echo "Search name cannot be empty!"
        return
    fi

    if grep -q "^$search_id," "$db_filename"; then
        record=$(grep "^$search_id," "$db_filename")
        IFS=',' read -r name email mobile address <<< "$record"
        
        echo "Record found with following details:"
        echo "Name: $name"
        echo "Email: $email"
        echo "Mobile Number: $mobile"
        echo "Address: $address"

        echo "Enter new modified details (leave unmodified details blank)"
        read -p "Name [$name]: " new_name
        read -p "Email [$email]: " new_email
        read -p "Mobile Number [$mobile]: " new_mobile
        read -p "Address [$address]: " new_address

        new_name=${new_name:-$name}
        new_email=${new_email:-$email}
        new_mobile=${new_mobile:-$mobile}
        new_address=${new_address:-$address}

        new_record="${new_name},${new_email},${new_mobile},${new_address}"

        sed -i "s/^$record$/$new_record/" "$db_filename" && echo "Record updated successfully!" || echo "Failed to update record!"
    else
        echo "No matching record with name: $search_id"
    fi
}

# Function to delete a record from the database
delete_record() {
    echo -n "Enter the name of the database to delete record (with file extension): "
    read db_filename

    if [[ ! -f "$db_filename" ]]; then
        echo "Database with filename '$db_filename' does not exist"
        return
    fi

    echo -n "Enter the User Name to delete: "
    read search_id

    if [[ -z "$search_id" ]]; then
        echo "Search name cannot be empty!"
        return
    fi

    if grep -q "^$search_id," "$db_filename"; then
        sed -i "/^$search_id,/d" "$db_filename" && echo "Record deleted successfully!" || echo "Failed to delete record!"
    else
        echo "No matching record with name: $search_id"
    fi
}


# Function to display the menu
show_menu() {
    echo "+------------------+"
    echo "|     Main Menu    |"
    echo "+------------------+"
    echo "|1. Create Database|"
    echo "|2. Insert Record  |"
    echo "|3. Search Record  |"
    echo "|4. Modify Record  |"
    echo "|5. Delete Record  |"
    echo "|6. Exit           |"
    echo "+------------------+"
}

# Function to handle menu choices
handle_choice() {
    case $1 in
    1) create_database ;;
    2) insert_record ;;
    3) search_record ;;
    4) modify_record ;;
    5) delete_record ;;
    6) echo "Exiting..."; exit 0 ;;
    *) echo "Invalid choice. Please try again!" ;;
    esac
}

# Main loop
while true; do
    show_menu
    read -p "Enter your choice: " choice
    handle_choice "$choice"
    echo ""
done