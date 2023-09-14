#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const size_t size = 30;
const char delimiters[] = " -,\\|/;=<>";

bool isvowel(char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool isDelimiter(char c)
{
    for (int i = 0; delimiters[i] != '\0'; i++)
    {
        if (c == delimiters[i])
        {
            return true;
        }
    }
    return false;
}

void resetWord(char word[], int *pos, bool *good_word)
{
    *pos = 0;
    *good_word = false;
    memset(word, 0, size); /// Clear the array
}

int main()
{
    FILE *file = fopen("myfile.txt", "r");
    if (file == NULL)
    {
        printf("File does not exist.\n");
        return 1;
    }

    char word[size]; /// Array that contains the good word
    memset(word, 0, size); /// Clear the array before interactions
    int pos = 0; /// Position of char in word
    bool good_word = true;
    bool foundWord = false; /// Defines if we find at least one good word
    char character; /// We iterate each character in the file

    while (fscanf(file, "%c", &character) != EOF)
    {
        /// INFO: We have three cases for character to be:
        /// 1. If the character is delimiter, we check if we have good word and if yes,
        /// we print it and iterate over again, if no, we assume that the next word is good
        /// 2. If the character is not vowel, we make our word to be not good
        /// 3. If the character is vowel, we check if the word is good and then we add the char into array
        if (isDelimiter(character))
        {
            if (good_word && pos != 0) 
            {
                printf("%s\n", word);
                foundWord = true;
            }
            resetWord(word, &pos, &good_word);
            good_word = true;
        }
        else if (!isvowel(character))
        {
            resetWord(word, &pos, &good_word);
        }
        else if (good_word)
        {
            word[pos++] = character;
        }
    }

    if (!foundWord)
    {
        printf("No words found.\n");
    }

    fclose(file);
    return 0;
}