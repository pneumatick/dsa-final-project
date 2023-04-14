#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <fstream>
#include <ctime>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <bits/stdc++.h>

//Pattern being passed is what we are trying to find, text is where we are searching
void rabinkarp(std::string pat, std::string txt)
{
    int patLen = pat.length();
    int textLen = txt.length();
    int patHash = 0; // hash value for pattern
    int textHash = 0; // hash value for txt
    int h = 1;
    int q = INT_MAX; //Prime number used as modulus to prevent collisions in hash values

    // The value of h would be "pow(d, patLen-1)%q"
    for (int i = 0; i < patLen - 1; i++)
        h = (h * 256) % q;

    // Calculate the hash value of pattern and first window of text
    for (int i = 0; i < patLen; i++) {
        patHash = (256 * patHash + pat[i]) % q;
        textHash = (256 * textHash + txt[i]) % q;
    }

    // Slide the pattern over text one by one
    for (int i = 0; i <= textLen - patLen; i++) {
        int temp;
        //Check if hash values of pattern and current window are equal
        if (patHash == textHash) {
            //Check if each individual character is equal
            for (int j = 0; j < patLen; j++) {
                temp = j;

                //If characters do not match then break
                if (txt[i + j] != pat[j]) {
                    break;
                }

                
            }

            if (temp == patLen - 1) {
                std::cout << i << std::endl;
            }

        }

        if (i < textLen - patLen) {
            textHash = (256 * (textHash - txt[i] * h) + txt[i + patLen]) % q;

            if (textHash < 0)
                textHash = (textHash + q);
        }
    }
}

int main(int argc, char* argv[])
{
    // Format: String File Name, Pattern to search for
    std::string input_file_name = argv[1];
    std::ifstream input_file_stream(input_file_name);
    std::string input_string;

    // Buffer to hold file contents as a string
    std::stringstream buffer;
    buffer << input_file_stream.rdbuf();
    input_string = buffer.str();
    input_file_stream.close();

    std::string pattern = argv[2];

    // Open the output file
    std::ofstream output_file;
    output_file.open(pattern + ".csv");

    // Used to iterate from 0 to max_char (incrementing by 100 each time) in 
    // order to see how long it takes to perform a search over an 
    // incrementally larger and larger text string.
    uint16_t max_char;
    max_char = (uint16_t) input_string.size();


    // Populates output file with runtime data
    unsigned long c_start, c_end;
    output_file << "input" << "," << "time" << '\n';
    for (int i = 0; i <= max_char; i += 100) {
	    std::string substring = input_string.substr(0, i);
        c_start = std::clock();
        rabinkarp(pattern, substring);
        c_end = std::clock();
        float time = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
        output_file << i << "," << std::fixed << time <<'\n';
    }
    output_file.close();

}