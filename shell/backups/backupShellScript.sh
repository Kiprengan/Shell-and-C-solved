#!/bin/bash
# This first line specify that this is bash script
#This is my shell script program that backup files from a specified directory to desired backup directory, in the event it is done repeatedly it backs up only modified files, also it only backs up files from the directory and ignores subdirectories, source directory for backup and destination / backup directory will be specified as command line arguments. My name is Khadijah Muhammad
# Getting command line arguments
source_directory_to_be_backed_up=$1
# First argument is the given directory to be backed up
destination_directory_for_backup=$2
# Second argument is the directory that will work as backup location 
# Create the backup directory if it doesn't exist
if [ ! -d "$destination_directory_for_backup" ]; then
	mkdir "$destination_directory_for_backup"
fi

# Loop through each file in the directory
for file in "$source_directory_to_be_backed_up"/*; do
  # Check if the file is a regular file (not a directory)
  if [ -f "$file" ]; then
    # Check if the file has been modified since the last backup
    if [ "$file" -nt "$destination_directory_for_backup/$(basename "$file")" ]; then
      # Copy the file to the backup directory and nt stands for new than which is a argument to check if file has been modified
      cp "$file" "$destination_directory_for_backup"
      echo "Backed up $file"
    fi
  fi
done

echo "Backup complete"
