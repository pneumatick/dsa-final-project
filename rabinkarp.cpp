#include <iostream>
#include <string>
#include <cmath>
#include <cstring>

//Pattern being passed is what we are trying to find, text is where we are searching
void rabinkarp(char pat[], char txt[])
{
    int patLen = strlen(pat);
    int textLen = strlen(txt);
    int patHash = 0; // hash value for pattern
    int textHash = 0; // hash value for txt
    int h = 1;
    int q = 31; //Prime number used as modulus to prevent collisions in hash values

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

        if (int i = 0 < textLen - patLen) {
            textHash = (256 * (textHash - txt[i] * h) + txt[i + patLen]) % q;

            if (textHash < 0)
                textHash = (textHash + q);
        }
    }
}

int main()
{
    char s[] = "awholebunchawords";
    char p[] = "aw";

    rabinkarp(p, s);
}