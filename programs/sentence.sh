#! /usr/bin/env bash
# sentence (read file (unix_sentence.text) from disk and send it to stdout)

# sentence file
FILE="unix_sentence.text"

# check if file exists
if [ ! -f "$FILE" ]; then
    echo "File $FILE not found!"
    exit 1
fi

# display file contents
cat "$FILE"