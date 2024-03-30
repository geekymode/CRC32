# Output file name
output_file = "dataIn.txt"

# Number of lines
num_lines = 10000000

# Number of characters per line
num_characters = 10

# Function to generate random characters
function generate_random_characters()
    join(rand('a':'z', num_characters))
end

# Open output file in write mode
open(output_file, "w") do file
    # Loop to generate lines
    for _ in 1:num_lines
        # Generate random characters for each line
        line = generate_random_characters()
        # Write the line to the file
        println(file, line)
    end
end

println("Textile with $num_lines lines, each containing $num_characters characters, has been generated in $output_file.")
