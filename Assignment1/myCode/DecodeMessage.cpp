// DecodeMessage.cpp
#include <string>
#include "DecodeMessage.h"

std::string binaryToASCII(const std::string& binaryString) {
    std::string asciiString;
    std::string paddedBinary = binaryString;

    while (paddedBinary.length() % 7 != 0) {
        paddedBinary.insert(0, "0");
    }

    for (size_t i = 0; i < paddedBinary.length(); i += 7) {
        std::string binarySegment = paddedBinary.substr(i, 7);
        int asciiValue = std::stoi(binarySegment, nullptr, 2);

        if (asciiValue <= 32) {
            asciiValue += 33;
        } else if (asciiValue >= 127) {
            asciiValue = 126;
        }

        char asciiChar = char (asciiValue);
        asciiString += asciiChar;
    }
    return asciiString;
}


// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}


std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    std::string binaryString;

    for (const auto& pixel : edgePixels) {
        double pixelValue = image.get_data(pixel.first, pixel.second);
        int num = (int) pixelValue;
        if (num & 1) {           //pixelValue is either 1 or 0, so we can think it like bool value.
            binaryString += "1";
        } else {
            binaryString += "0";
        }
    }
    std::string decodedMessage = binaryToASCII(binaryString);

    return decodedMessage;
}
