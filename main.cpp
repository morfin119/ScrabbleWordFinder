#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

// Points for each letter in the game "Scrabble"
const std::unordered_map<char, int> LETTER_POINTS {
        // https://en.wikipedia.org/wiki/Scrabble_letter_distributions
        {'A', 1},
        {'B', 3},
        {'C', 3},
        {'D', 2},
        {'E', 1},
        {'F', 4},
        {'G', 2},
        {'H', 4},
        {'I', 1},
        {'J', 8},
        {'K', 5},
        {'L', 1},
        {'M', 3},
        {'N', 1},
        {'O', 1},
        {'P', 3},
        {'Q', 10},
        {'R', 1},
        {'S', 1},
        {'T', 1},
        {'U', 1},
        {'V', 4},
        {'W', 4},
        {'X', 8},
        {'Y', 4},
        {'Z', 10}
};

struct WordScoreIndex {
    int score;
    int index;
};

// Function to compute the frequency of each letter in the input word.
// Parameters:
//   word: The input word for which the letter frequency needs to be computed.
// Returns:
//   An unordered map that stores the frequency count of each letter present in the input word.
std::unordered_map<char, int> computeLetterFrequency(const std::string& word)
{
    std::unordered_map<char, int> letterFrequency;

    // Loop through each character in the string
    for (char character : word)
    {
        // Increment the letter frequency count for the current character
        letterFrequency[character] += 1;
    }

    return letterFrequency;
}

int main(int argc, char** argv)
{
    // Ensure that the user's input is valid, and display a straightforward help message if it is invalid.
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <hand_letters> <dictionary_file>" << std::endl;
        std::cout << "This program finds the word with the highest score that can be formed using the given hand letters."<< std::endl;
        return -1;
    }

    // Read the hand letters from the first command-line argument
    std::string handLetters = std::string(argv[1]);

    // Convert hand letters to uppercase
    std::transform(handLetters.begin(), handLetters.end(), handLetters.begin(), ::toupper);

    std::unordered_map<char, int> handLetterFrequency = computeLetterFrequency(handLetters);

    // Open the dictionary file
    std::ifstream file(argv[2]);
    if (!file)
    {
        // Display an error message if the dictionary file cannot be opened
        std::cout << "Error opening file: " << argv[2] << std::endl;
        return -1;
    }

    // Read the dictionary words and compute the letter frequency of each word
    std::vector<std::string> dictionary;
    std::vector<std::unordered_map<char, int>> dictionaryLetterFrequency;
    std::string word;
    while (std::getline(file, word))
    {
        // Remove any carriage return characters at the end of the line
        if (!word.empty() && word.back() == '\r')
        {
            word.pop_back();
        }

        // Convert the word to uppercase
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);

        // Store the word in the dictionary vector
        dictionary.push_back(word);

        // Calculate the letter frequency of the word and store it in the vector
        dictionaryLetterFrequency.push_back(computeLetterFrequency(word));
    }

    // Compute scores for each word in the dictionary based on the available letters in the hand.
    std::vector<WordScoreIndex> wordScoreIndices;

    // Iterate through each word in the dictionary and calculates its score.
    for (int i = 0; i < dictionaryLetterFrequency.size(); i++)
    {
        int score = 0;
        for (const auto& entry : dictionaryLetterFrequency[i])
        {
            char letter = entry.first;
            int frequency = entry.second;

            // If the word cannot be formed with the available letters in the hand,
            // its score is set to 0 and the loop breaks early for that word.
            if (handLetterFrequency[letter] < frequency)
            {
                score = 0;
                break;
            }

            // Calculate the score for the word based on letter frequency and points.
            score += frequency * LETTER_POINTS.at(letter);
        }
        // The computed scores are stored in the vector wordScoreIndices along with the corresponding
        // index of the word in the dictionary.
        wordScoreIndices.push_back({ score, i });
    }

    // Sort the words based on scores in descending order
    std::sort(wordScoreIndices.begin(), wordScoreIndices.end(), [](const struct WordScoreIndex& a, const struct WordScoreIndex& b) -> bool
    {
        return a.score > b.score;
    });

    // Print the word with the highest score
    std::string highestScoreWord = dictionary[wordScoreIndices[0].index];
    std::cout << highestScoreWord;

    return 0;
}