#!/bin/bash

# Define compilation output file
OUTPUT="output"

# Compile the project files
echo "Compiling the project..."
g++ --std=c++17 -o $OUTPUT Graph/Graph.cpp Graph/WordPatternGraph.cpp Playing-modes/Automatic-Mode.cpp 

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
    echo "Running the program..."
    ./$OUTPUT
else
    echo "Compilation failed."
fi