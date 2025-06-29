#!/bin/bash

# Format all C++ source files in the project
# Usage: ./format.sh

echo "Formatting C++ source files..."

# Find and format all .cpp and .hpp files
find src -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i

echo "Done! All source files have been formatted."
echo ""
echo "Files formatted:"
find src -name "*.cpp" -o -name "*.hpp" | sort
