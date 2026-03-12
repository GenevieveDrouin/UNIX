#! /usr/bin/env bash
# lowercase (make all characters lowercase)

if [ "$#" -gt 0 ]; then
    # Convert arguments directly
    printf '%s\n' "$@" | tr '[:upper:]' '[:lower:]'
else
    # Convert stdin efficiently
    tr '[:upper:]' '[:lower:]'
fi