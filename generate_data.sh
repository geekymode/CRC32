#!/bin/bash

# Output file name
output_file="output.txt"

# Number of lines
num_lines=10000

# Number of characters per line
num_characters=10

# Generate random characters
generate_random_characters() {
    head -c $num_characters /dev/urandom | base64 | tr -d '/+' | head -c $num_characters
}

# Create output file
touch $output_file

# Loop to generate lines
for ((i=1; i<=$num_lines; i++)); do
    # Generate random characters for each line
    line=$(generate_random_characters)
    # Append the line to the output file
    echo "$line" >> $output_file
done

echo "Textile with $num_lines lines, each containing $num_characters characters, has been generated in $output_file."

