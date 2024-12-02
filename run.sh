#!/bin/bash

DAY_NUM=$1

# construct file path where day num has to take two spaces
#for example day 1 will be day01 and day 31 will be day31
FILE_PATH="day$(printf "%02d" $DAY_NUM)/"

INPUT_FILE="input.txt"

# Extract the base filename (with extension) using `basename`
BASE_NAME=$(basename "$FILE_PATH")

FILE_NAME=$FILE_PATH$BASE_NAME

echo "Compiling $FILE_NAME.cpp"
g++ -g -O3 -Wall -lm -o $FILE_NAME.o $FILE_NAME.cpp

./$FILE_NAME.o < $FILE_PATH$INPUT_FILE
