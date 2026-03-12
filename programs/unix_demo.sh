#! /usr/bin/env bash

### unix demo: watch 5:00 to 10:55
# https://www.youtube.com/watch?v=tc4ROCJYbm0&t=297s&ab_channel=AT%26TTechChannel

### recreate unix demo from video


### update unix_dict_new_words.text with 

# call build script to compile all C programs
./build.sh "$@"

# run C programs and bash scripts to text files output
./sentence | ./makewords | ./lowercase | ./sort | ./unique | ./mismatch > unix_c_output.text
./sentence.sh | ./makewords.sh | ./lowercase.sh | ./sort.sh | ./unique.sh | ./mismatch.sh > unix_bash_output.text

# run fsrecursive program and pipe to other C programs to text file output
./fsrecursive | ./lowercase | ./sort | ./unique > fsrecursion_unique_output.text