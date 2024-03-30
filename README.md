# CRC32
Fast Cyclic Redundancy Code (CRC) using 32 bit Polynomial. Encoding, Decoding methods along with supporting test and analysis suits

### Compiling
g++  -o crc32 crc32.cpp
### Test
./crc32
The input file data.txt is expected to be in the same directory. The file contains text (each alphabet is treated as 8 bit ASCII). Each line is treated as a new message input, the length of which can be set arbitrary (can be different across lines). The 32 bit CRC is computed individually for each line. The number of lines in data.txt is the number of codewords.  
### Input
data.txt contains messages, one message per line. The "output.txt" contains the message+CRC. Noise is added to this file. The probability of message flipping is controlled by the value of epsilon specified in main(). The noisy output is saved in "noisy.txt". Finally the CRC detection is performed on this noisy.txt and the results is saved in "results.txt"

### Directory structure
❯ tree
.
├── LICENSE
├── README.md
├── crc32
├── crc32.cpp
├── data.txt
├── dataIn.txt
├── delta.txt
├── noisy.txt
├── output.txt
└── result.txt
