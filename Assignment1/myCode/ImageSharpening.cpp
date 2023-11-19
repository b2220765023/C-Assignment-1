#include "ImageSharpening.h"
#include "Convolution.h"
#include "ImageMatrix.h"
// Default constructor
ImageSharpening::ImageSharpening() {

}

ImageSharpening::~ImageSharpening(){
    for (int i = 0; i < kernelHeight; i++) {
        delete[] blurringKernel[i];
    }
    delete[] blurringKernel;
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {

    blurringKernel = new double*[3];
    for (int i = 0; i < kernelHeight; i++) {
        blurringKernel[i] = new double[3];
        for (int j = 0; j < kernelWidth; j++){
            blurringKernel[i][j] = 1.0/9.0;
        }
    }
    Convolution convolve(blurringKernel,kernelHeight,kernelWidth,1,true);
    ImageMatrix BlurredImage = convolve.convolve(input_image);
    ImageMatrix SharpenedImg(input_image.get_height(),input_image.get_width());

    SharpenedImg.operator=(input_image.operator+(input_image.operator-(BlurredImage).operator*(k)));

    for (int i = 0; i < input_image.get_height(); i++){
        for (int j = 0; j < input_image.get_width(); j++){
            if (SharpenedImg.get_data()[i][j] > 255) {
                SharpenedImg.set_data(i,j,255);
            }
        }
    }
    return SharpenedImg;



}
