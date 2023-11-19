#include <iostream>

#include "Convolution.h"

// Default constructor 
Convolution::Convolution() {
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad){
    this->kernelHeight = kh;
    this->kernelWidth = kw;
    this->stride = stride_val;
    this->padding = pad;
    this->kernel = customKernel;

    kernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        kernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            kernel[i][j] = customKernel[i][j];
        }
    }
}

// Destructor
Convolution::~Convolution() {
    if (kernel != nullptr) {
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] kernel[i];
        }
        delete[] kernel;
    }
}

// Copy constructor
Convolution::Convolution(const Convolution &other){
    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;
    stride = other.stride;
    padding = other.padding;

    // Allocate memory for the custom kernel and copy its values
    kernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        kernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            kernel[i][j] = other.kernel[i][j];
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this != &other) {
        // Deallocate existing memory for the kernel
        if (kernel != nullptr) {
            for (int i = 0; i < kernelHeight; ++i) {
                delete[] kernel[i];
            }
            delete[] kernel;
        }

        kernelHeight = other.kernelHeight;
        kernelWidth = other.kernelWidth;
        stride = other.stride;
        padding = other.padding;

        // Allocate memory for the custom kernel and copy its values
        kernel = new double*[kernelHeight];
        for (int i = 0; i < kernelHeight; ++i) {
            kernel[i] = new double[kernelWidth];
            for (int j = 0; j < kernelWidth; ++j) {
                kernel[i][j] = other.kernel[i][j];
            }
        }
    }
    return *this;
}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    int input_height = input_image.get_height();
    int input_width = input_image.get_width();

    if (padding) {

        int output_height = (input_height - kernelHeight + 2) / stride + 1;
        int output_width = (input_width - kernelWidth + 2) / stride + 1;

        ImageMatrix pad_out = ImageMatrix(output_height,output_width);
        ImageMatrix pad_image = ImageMatrix(input_height + 2,input_width + 2);

        for (int i = 0; i < input_height + 2; i++) {
            for (int j = 0; j < input_width + 2; j++) {
                if (i == 0 || i == input_height + 1 || j == 0 || j == input_width + 1) {
                    pad_image.set_data(i, j, 0);
                } else {
                    pad_image.set_data(i, j, input_image.get_data(i - 1, j - 1));
                }
            }
        }
        ImageMatrix output_image(output_height, output_width);


        for (int i = 0; i < output_height; i++) {
            for (int j = 0; j < output_width; j++) {
                double sum = 0.0;
                for (int ki = 0; ki < kernelHeight; ki++) {
                    for (int kj = 0; kj < kernelWidth; kj++) {
                        int input_i = i * stride + ki;
                        int input_j = j * stride + kj;
                        sum += pad_image.get_data(input_i, input_j) * kernel[ki][kj];
                    }
                }
                pad_out.set_data(i, j, sum);
            }
        }

        return pad_out;
    } else {
        int output_height = (input_height - kernelHeight) / stride + 1;
        int output_width = (input_width - kernelWidth) / stride + 1;

        ImageMatrix output_image(output_height, output_width);

        for (int i = 0; i < output_height; i++) {
            for (int j = 0; j < output_width; j++) {
                double sum = 0.0;
                for (int ki = 0; ki < kernelHeight; ki++) {
                    for (int kj = 0; kj < kernelWidth; kj++) {
                        int input_i = i * stride + ki;
                        int input_j = j * stride + kj;
                        sum += input_image.get_data(input_i, input_j) * kernel[ki][kj];
                    }
                }
                output_image.set_data(i, j, sum);
            }
        }

        return output_image;
    }
}


