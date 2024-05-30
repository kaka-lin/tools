#!/bin/bash

FILE="recent_files.txt"

# Get the current date
current_date=$(date +%Y-%m-%d)

# Get the date one month ago
one_month_ago=$(date -d "$current_date - 1 month" +%Y-%m-%d)

# List all files and folders in the current directory
ls -1 | while read file; do

  # echo $file

  # Get the file's modification time
  modification_time=$(stat -c "%y" "$file")

  # Check if the file was modified within the past month
  if [[ "$modification_time" > "$one_month_ago" ]]; then

    # Get the file or folder size
    file_size=$(du -s "$file")

    # Print the file or folder name and size
    echo "$file_size"
  fi
done > $FILE
