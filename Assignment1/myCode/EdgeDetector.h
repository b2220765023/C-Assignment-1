    #ifndef EDGE_DETECTOR_H
    #define EDGE_DETECTOR_H

    #include "ImageMatrix.h"
    #include "Convolution.h"
    #include <vector>

    class EdgeDetector {
        public:
            EdgeDetector(); 
            ~EdgeDetector(); 
            
            std::vector<std::pair<int, int>> detectEdges(const ImageMatrix& input_image);

        private:
            // add your private member variables and functions
            double* Gx[3] = {
                    new double[3]{-1.0, 0.0, 1.0},
                    new double[3]{-2.0, 0.0, 2.0},
                    new double[3]{-1.0, 0.0, 1.0}
            };
            double* Gy[3] = {
                    new double[3]{-1, -2, -1},
                    new double[3]{0, 0, 0},
                    new double[3]{1, 2, 1}
            };
    };

    #endif // EDGE_DETECTOR_H


