// crc32.cpp
// Program to perform CRC encoding and decoding using a pre-specified 32bit polynomial
// The CRC polynomail is specified in the main() function	
// CRC32 crc(0xC9D204F5); // New Polynomial UHR
//   epsilon = 0.001; // Example error probability bsc(epsilon) where epsilon \in [0,1/2]
// Author: Rethna Pulikkoonattu
//


#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <random>

class CRC32 {
private:
    uint32_t crcTable[256];
    uint32_t polynomial;

public:
    CRC32(uint32_t poly) : polynomial(poly) {
        generateCRCTable();
    }

    void generateCRCTable() {
        for (int i = 0; i < 256; ++i) {
            uint32_t crc = static_cast<uint32_t>(i);
            for (int j = 0; j < 8; ++j) {
                crc = (crc >> 1) ^ ((crc & 1) ? polynomial : 0);
            }
            crcTable[i] = crc;
        }
    }

    uint32_t calculateCRC(const char* data, size_t length) {
        uint32_t crc = 0xFFFFFFFF;
        // for (size_t i = 0; i < length; ++i) {
        //     crc = (crc >> 8) ^ crcTable[(crc ^ data[i]) & 0xFF];
        // }
        for (const char* ptr = data; ptr < data + length; ++ptr) {
    crc = (crc >> 8) ^ crcTable[(crc ^ static_cast<uint32_t>(static_cast<unsigned char>(*ptr))) & 0xFF];
}

        return ~crc;
    }

    void appendMessageCRC(const std::string& input_filename, const std::string& output_filename) {
        std::ifstream input_file(input_filename);
        std::ofstream output_file(output_filename);

        if (!input_file || !output_file) {
            std::cerr << "Error: Failed to open files." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(input_file, line)) {
            // Calculate CRC of the line
            size_t message_length = line.size();
            uint32_t checksum = calculateCRC(line.c_str(), message_length);

            // Append CRC to the message
            std::vector<char> data_with_crc(line.begin(), line.end());
            data_with_crc.insert(data_with_crc.end(), reinterpret_cast<const char*>(&checksum), reinterpret_cast<const char*>(&checksum) + sizeof(uint32_t));

            // Write message with CRC to the output file
            output_file.write(reinterpret_cast<const char*>(data_with_crc.data()), static_cast<std::streamsize>(data_with_crc.size()));


            output_file << std::endl;
        }

        input_file.close();
        output_file.close();
    }

    void introduceErrors(const std::string& input_filename, const std::string& output_filename, const std::string& delta_filename, double epsilon) {
        std::ifstream input_file(input_filename);
        std::ofstream output_file(output_filename, std::ios::app);
        std::ofstream delta_file(delta_filename, std::ios::app);

        if (!input_file || !output_file || !delta_file) {
            std::cerr << "Error: Failed to open files." << std::endl;
            return;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 1.0);

        std::string line;
        while (std::getline(input_file, line)) {
            std::string modified_line = line;

            size_t changes = 0;

            // Introduce errors with probability epsilon
            // for (char& ch : modified_line) {
            //     if (dis(gen) < epsilon) {
            //         ch = ch ^ 1;
            //         changes++;
            //     }
            // }
for (std::string::iterator it = modified_line.begin(); it != modified_line.end(); ++it) {
    char& ch = *it;
    if (dis(gen) < epsilon) {
        ch = ch ^ 1;
        changes++;
    }
}
            // Write modified line to output file
            output_file << modified_line << std::endl;

            // Write number of changes to delta file
            delta_file << changes << std::endl;
        }

        input_file.close();
        output_file.close();
        delta_file.close();
    }

    void performCRC(const std::string& input_filename, const std::string& result_filename) {
        std::ifstream input_file(input_filename);
        std::ofstream result_file(result_filename);

        if (!input_file || !result_file) {
            std::cerr << "Error: Failed to open files." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(input_file, line)) {
            // Extract message and CRC value from the line
            std::string message = line.substr(0, line.size() - sizeof(uint32_t)); // Extract the message
            uint32_t expectedCRC = *reinterpret_cast<const uint32_t*>(&line[line.size() - sizeof(uint32_t)]);

            // Calculate CRC for the message
            size_t message_length = message.size();
            uint32_t calculatedCRC = calculateCRC(message.c_str(), message_length);

            // Check CRC and write result
            if (calculatedCRC == expectedCRC) {
                result_file << "PASS" << std::endl;
            } else {
                result_file << "FAIL" << std::endl;
            }
        }

        input_file.close();
        result_file.close();
    }
};

int main() {
    // Example polynomial: 0xEDB88320
    // CRC32 crc(0xEDB88320);
    // CRC32 crc(0x82608edb); // IEEE 802.11
    CRC32 crc(0xC9D204F5); // New Polynomial UHR

    // Step 1: Calculate CRC and append to output.txt
    crc.appendMessageCRC("data.txt", "output.txt");

    // Step 2: Introduce errors to output.txt and append to noisy.txt
    double epsilon = 0.001; // Example error probability
    crc.introduceErrors("output.txt", "noisy.txt", "delta.txt", epsilon);

    // Step 3: Check CRC of each line in noisy.txt and produce the result in result.txt
    crc.performCRC("noisy.txt", "result.txt");

    return 0;
}

