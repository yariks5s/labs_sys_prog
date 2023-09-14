#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isvowel(char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool isDelimiter(char c)
{
    return c == ' ' || c == '-' || c == ',' || c == '\\' || c == '|' || c == '/' || c == ';' || c == '=' || c == '<' || c == '>';
}

/// 1. we need to find locations of all deli
int main() {
    // Define the size of the char array.
    const int size = 30;

    // Open the file in read mode.
    fstream file("myfile.txt", ios::in);

    // If the file does not exist, exit the program.
    if (!file) {
        cout << "File does not exist." << endl;
        return 1;
    }

    // Initialize variables.
    bool foundWord = false; /// Checks if we have any good words found
    char word[size]; /// Result word to be outputted
    char character; /// Every character checks for delimiter and if the character is vowel
    int i = 0; /// Counter for word

        bool good_word = true;
        if (file.is_open())
        {
            while(file.good())
            {
                file.get(character);
                if (isDelimiter(character))
                {
                    if (good_word && i != 0)
                    {
                        std::cout << word << endl;
                        foundWord = true;
                        good_word = false;
                        continue;
                    }
                    good_word = true;
                    i = 0;
                    continue;
                }
                if (!isvowel(character))
                {
                    good_word = false;
                    i = 0;
                    continue;
                }
                else if (good_word)
                {
                    word[i] = character;
                    ++i;
                }
            }
        }

    // Close the file.
    file.close();

    return 0;
}
