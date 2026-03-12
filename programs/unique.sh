#! /usr/bin/env bash
# unique (remove duplicate words from already sorted input)

# Read from standard input if no arguments, otherwise read from arguments
# Use uniq to remove adjacent duplicate lines
if [ "$#" -gt 0 ]; then
    printf '%s\n' "$@" | uniq
else
    tr -s '[:space:]' '\n' | uniq
fi