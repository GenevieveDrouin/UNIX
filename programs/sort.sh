#! /usr/bin/env bash
# sort (alphabetize)

# Read words from command line arguments or standard input
if [ "$#" -gt 0 ]; then
    read -r -a words <<< "$*"
else
    mapfile -t words < <(tr -s '[:space:]' '\n' < /dev/stdin)
fi

# Get the number of words
n=${#words[@]}

# Insertion sort
for ((i = 1; i < n; i++)); do
    key="${words[i]}"
    j=$((i - 1))
    while [[ j -ge 0 && "${words[j]}" > "$key" ]]; do
        words[j+1]="${words[j]}"
        ((j--))
    done
    words[j+1]="$key"
done

# Print sorted words
for w in "${words[@]}"; do
    echo "$w"
done