#! /usr/bin/env bash

### compile all c code in the current directory

### Hints:
### how do you get the current directory in bash?
### how do you store the output of variables in bash?

# get current directory and list of .c files
current_dir="$(pwd)"
c_files=(*.c)
fio_files=(../fio/*.c)

# check if there are any .c files
if [ ! -e "${c_files[0]}" ]; then
    echo "Oops, we found no C code in the directory: $current_dir" >&2
    exit 1
fi 

# compile each .c file to an executable with the same name
for c_file in "${c_files[@]}"; do
    exe_file="${c_file%.c}"
    gcc -Wall -Werror -o "$exe_file" "$c_file" "${fio_files[@]}"
done