#!/bin/bash

SOURCE_FILE="regression.cpp"

OUTPUT_FILE="regression"

echo "Compiling..."
g++ -std=c++14 -o $OUTPUT_FILE $SOURCE_FILE

if [ $? -eq 0 ]; then
    echo "Compilation successful. Executing..."
    ./$OUTPUT_FILE
else
    echo "Compilation failed."
fi
