# Bacon's Cipher 

This C++ program translates text between English and Bacon's cipher. [Bacon's cipher](https://en.wikipedia.org/wiki/Bacon%27s_cipher) is a substitution cipher where each letter is replaced by a unique sequence of 5 characters consisting of 'A' or 'B'. This program allows you to convert English text to Bacon's cipher and vice versa.

## Features

- **English to Bacon's Cipher Translation**: Converts English text into its equivalent Bacon's cipher code.
- **Bacon's Cipher to English Translation**: Converts Bacon's cipher code back into English text.
- **Verbose Mode**: Optionally displays the input and output on the console.

## Usage

```sh
<executable> <input file> <-bc|-e> <output file> [-v]
```

```sh
./baconize.exe englishInput.txt -bc englishOutput.txt
```

```sh
./baconize.exe baconInput.txt -e baconOutput.txt
```
