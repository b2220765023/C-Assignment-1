#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    ImageSharpening sharpening;
    ImageMatrix sharpImage = sharpening.sharpen(img, 2);

    EdgeDetector edgeDetector;
    std::vector<std::pair<int,int>> edges = edgeDetector.detectEdges(sharpImage);

    DecodeMessage decodeMessage;
    std::string decodedMessage = decodeMessage.decodeFromImage(sharpImage,edges);

    return decodedMessage;
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    ImageSharpening sharpening;
    ImageMatrix sharpImage = sharpening.sharpen(img, 2);

    EdgeDetector edgeDetect;
    std::vector<std::pair<int,int>> edges = edgeDetect.detectEdges(sharpImage);


    EncodeMessage encoder;
    ImageMatrix encodedImage = encoder.encodeMessageToImage(img, message,edges);

    return encodedImage;
}
