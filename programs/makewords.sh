
#! /usr/bin/env bash
# makewords (make one word per line, same as linebreaker from Lab2)

# Read from stdin if no arguments are given; otherwise use arguments
if [ "$#" -gt 0 ]; then
    read -r -a words <<< "$*"
else
    mapfile -t words < <(tr -s '[:space:]' '\n' < /dev/stdin)
fi

# Process each word and print it on a new line
for w in "${words[@]}"; do
    if [[ -n "$w" ]]; then
        echo "$w"
    fi
done