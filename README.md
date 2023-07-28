# Scrabble Word Finder

This program finds the word with the highest score that can be legally formed using the given hand letters. The word scores are calculated according to the points assigned to each letter in the game Scrabble.

## Usage

```
Usage: scrabble_word_finder <hand_letters> <dictionary_file>
```

## Description

The Scrabble Word Finder is a program that helps you find the word with the highest score that can be formed using the given hand letters. It reads a list of hand letters and a dictionary file containing a list of words. The program then computes the score for each word in the dictionary that can be legally formed using the available letters in the hand. The word scores are calculated based on the letter frequency and the points assigned to each letter in the game Scrabble.

### Example

1. Find the word with the highest score given the hand letters "TVEVILG", and the dictionary file "dictionary.txt":
   ```
   ./scrabble_word_finder DLUVESG dictionary.txt
   Output: VELDS
   ```
1. Find the word with the highest score given the hand letters "AEIPRSL", and the dictionary file "dictionary.txt":
   ```
   ./scrabble_word_finder AEIPRSL dictionary.txt
   Output: PARLIES
   ```

### Notes
- The program handles both upper and lowercase letters for letter frequency calculations.
- If the dictionary file contains words with return carriage characters at the end of the line, the program will handle them correctly while reading the words.
- A dictionary is included in the repo.
