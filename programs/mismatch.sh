#! /usr/bin/env bash
# mismatch (read unix_dict.text from disk and compare this to the data in stdin, 

#dictionary file
DICT="unix_dict.text"

# check if dictionary file exists
if [ ! -f "$DICT" ]; then
    echo "Dictionary file $DICT not found!"
    exit 1
fi

# read words from stdin or from command line arguments
if [ "$#" -gt 0 ]; then
    read -r -a words <<< "$*"
else
    mapfile -t words < <(tr -s '[:space:]' '\n' < /dev/stdin)
fi

# compare each word to the dictionary (case insensitive)
for w in "${words[@]}"; do
    if ! grep -iq "^$w\$" "$DICT"; then
        echo "$w"
    fi
done