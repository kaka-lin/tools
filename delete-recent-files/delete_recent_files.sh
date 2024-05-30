#!/bin/bash

FILE="recent_files.txt"
DELETED_FILE="deleted_files.txt"
SIZE=""
NAME=""
DELETED_SIZE=1000 # 1M
while read -r line; do
    SIZE=$(echo $line | cut -d' ' -f1)
    NAME=$(echo $line | cut -d' ' -f2)
    if [[ $SIZE -lt $DELETED_SIZE && $NAME != *".sh"* && $NAME != *".txt"* ]]; then
        echo $line
        rm -r $NAME
    fi
done < "${FILE}" > $DELETED_FILE
