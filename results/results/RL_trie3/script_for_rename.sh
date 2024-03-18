#!/bin/bash

# Navigate to the directory containing the files
#cd /path/to/your/folder

# Loop through each file in the directory


# Loop through each file in the directory
for file in *; do
    # Extract the desired part of the filename and replace '.champsimtrace.xz' with '.txt'
    new_name=$(echo "$file" | sed 's/^hashed_perceptron-no-karthik-no-no-no-no-no-lru-lru-lru-srrip-drrip-lru-lru-lru-1core-no---//; s/\.champsimtrace\.xz$/.txt/')

    # Rename the file
    mv "$file" "$new_name"
done



# Navigate to the directory containing the files
# cd /path/to/your/folder

# Loop through each file in the directory
#for file in *; do
    # Extract the desired part of the filename and replace '.champsimtrace.xz' with '.txt'
  #  new_name=$(echo "$file" | cut -d '-' -f4- | cut -d '.' -f1).txt

    # Rename the file
 #   mv "$file" "$new_name"
#done

