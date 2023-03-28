#!/bin/bash

# Get command line arguments
directory_to_copy=$1
backup_directory=$2

# Create the backup directory if it doesn't exist
if [ ! -d "$backup_directory" ]; then
  mkdir "$backup_directory"
fi

# Loop through each file in the directory
for file in "$directory_to_copy"/*; do
  # Check if the file is a regular file (not a directory)
  if [ -f "$file" ]; then
    # Check if the file has been modified since the last backup
    if [ "$file" -nt "$backup_directory/$(basename "$file")" ]; then
      # Copy the file to the backup directory
      cp "$file" "$backup_directory"
      echo "Backed up $file"
    fi
  fi
done

echo "Backup complete"
