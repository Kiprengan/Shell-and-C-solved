Write a shell scripting that will back up a directory of files. It should perform the backup by copying each file from the given directory to a backup directory.
The program should take two command line arguments, one being the path of the directory to copy, the second being the name of the path to place backup.
If backup is peformed repeatedly, the program should recopy only those that have been modified since the last time they were backed up.
The program should ignore subdirectories; it needs to backup files only within the given directory.
