#!/bin/bash

# Define compilation output file
OUTPUT="output"

# Compile the project files
echo "Compiling the project..."
g++ --std=c++17 -o $OUTPUT Graph/Graph.cpp Graph/WordPatternGraph.cpp Playing-modes/Analytics-Mode.cpp Playing-modes/Automatic-Mode.cpp Playing-modes/Playing-Mode.cpp console.cpp

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
    echo "Running the program..."
    ./$OUTPUT
else
    echo "Compilation failed."
fi