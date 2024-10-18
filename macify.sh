#!/bin/bash

# Directory containing the files (change this to your directory)
DIRECTORY="src"

# Loop through each file in the directory
for file in "$DIRECTORY"/*; do
    # Replace #ifndef with %ifnotdef
    sed -i '' 's/#ifndef/%ifndef/g' "$file"
    
    # Replace #endif with %endif
    sed -i '' 's/#endif/%endif/g' "$file"
done