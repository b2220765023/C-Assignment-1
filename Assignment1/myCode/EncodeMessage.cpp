#include "EncodeMessage.h"
#include <bitset>

EncodeMessage::EncodeMessage() {
    // Constructor implementation
}

EncodeMessage::~EncodeMessage() {
    // Destructor implementation
}

std::vector<int> computeFibonacci(int n) {
    std::vector<int> fibonacciNumbers;
    if (n >= 1) {
        fibonacciNumbers.push_back(0);
    }
    if (n >= 2) {
        fibonacciNumbers.push_back(1);
    }
    for (int i = 2; i < n; i++) {
        int nextFib = fibonacciNumbers[i - 1] + fibonacciNumbers[i - 2];
        fibonacciNumbers.push_back(nextFib);
    }
    return fibonacciNumbers;
}

bool isPrime(int number) {

    if (number <= 1) {
        return false;
    }
    if (number <= 3) {
        return true;
    }
    if (number % 2 == 0 || number % 3 == 0) {
        return false;
    }
    for (int i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

std::vector<int> stringToASCII(const std::string& message) {
    std::vector<int> asciiValues;
    for (char c : message) {
        int ascii = static_cast<int>(c);
        asciiValues.push_back(ascii);
    }
    return asciiValues;
}

void applyCharacterTransform(std::vector<int>& asciiValues) {
    std::vector<int> fibonacciNumbers = computeFibonacci(asciiValues.size());
    for (size_t i = 0; i < asciiValues.size(); i++) {
        if (isPrime(asciiValues[i])) {
            asciiValues[i] += fibonacciNumbers[i];
            if (asciiValues[i] <= 32) {
                asciiValues[i] += 33;
            } else if (asciiValues[i] >= 127) {
                asciiValues[i] = 126;
            }
        }
    }
}

void rightCircularShift(std::vector<int>& asciiValues) {
    int shiftAmount = asciiValues.size() / 2;
    for (size_t i = 0; i < asciiValues.size(); i++) {
        int newIndex = (i + shiftAmount) % asciiValues.size();
        std::swap(asciiValues[i], asciiValues[newIndex]);
    }
}


std::string asciiToBinary(const std::vector<int>& asciiValues) {
    std::string binaryString;
    for (int ascii : asciiValues) {
        std::bitset<8> binary(ascii);
        binaryString += binary.to_string();
    }
    return binaryString;
}

ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix& img, const std::string& message, const std::vector<std::pair<int, int>>& positions) {
    std::vector<int> asciiValues = stringToASCII(message);
    applyCharacterTransform(asciiValues);

    rightCircularShift(asciiValues);

    std::string binaryString = asciiToBinary(asciiValues);

    ImageMatrix encodedImage = img;
    int binaryIndex = 0;
    for (const auto& position : positions) {

        double pixelValue = encodedImage.get_data(position.first, position.second);
        if ((int)pixelValue != (binaryString[binaryIndex] - '0')) {

            pixelValue = (pixelValue == 0.0) ? 1.0 : 0.0;
            encodedImage.set_data(position.first, position.second, pixelValue);
        }

        binaryIndex++;
    }

    return encodedImage;
}
