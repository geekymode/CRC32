#!/bin/bash

# Loop 100 times
for ((i=1; i<=100000; i++))
do
    # Execute the executable
    ./crc32
    
    # Optionally, you can add a sleep command to add a delay between executions
    # sleep 1  # Wait for 1 second between each execution
done
