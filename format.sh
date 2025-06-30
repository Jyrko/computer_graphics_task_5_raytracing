echo "Formatting C++ source files..."

find src -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i

echo "Done! All source files have been formatted."
echo ""
echo "Files formatted:"
find src -name "*.cpp" -o -name "*.hpp" | sort
