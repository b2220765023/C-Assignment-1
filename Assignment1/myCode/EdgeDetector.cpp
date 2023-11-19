// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>
#include <vector>

// Default constructor
EdgeDetector::EdgeDetector() {

}

// Destructor
EdgeDetector::~EdgeDetector() {
    for (int i = 0; i < 3; i++){
        delete[] Gx[i];
        delete[] Gy[i];
    }
}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {
    Convolution convolutionGx (Gx,3,3,1,true);
    Convolution convolutionGy (Gy,3,3,1,true);

    int height = input_image.get_height();
    int width = input_image.get_width();


    ImageMatrix magnitude(height,width);
    ImageMatrix Ix = convolutionGx.convolve(input_image);
    ImageMatrix Iy = convolutionGy.convolve(input_image);

    double sum = 0.0;
    int count = 0;

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            double value = sqrt((Ix.get_data(i,j) * Ix.get_data(i,j)) +
                                   (Iy.get_data(i,j) * Iy.get_data(i,j)));
            magnitude.set_data(i,j,value);
            sum += value;
            count++;
        }
    }
    double threshold = sum / count;

    std::vector<std::pair<int, int>> edgePixels;

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (magnitude.get_data(i,j) > threshold){
                edgePixels.push_back(std::make_pair(i,j));
            }
        }
    }
    return edgePixels;
}