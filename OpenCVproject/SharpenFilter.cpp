//
//  SharpenFilter.cpp
//  OpenCVproject
//
//  Created by Anish Kumar Dubey on 05/08/19.
//  Copyright © 2019 Anish Kumar Dubey. All rights reserved.
//

#include <stdio.h>
#include<opencv2/opencv.hpp>
#include<math.h>
#include "string"

using namespace std;
using namespace cv;

class SharpenFilter {
    std::string greeting;
public:
    SharpenFilter(){
        
    };
    
    Mat sharpen(Mat image){
        Mat output, output2;
        
        //The sharpening kernel is defined using double as the datatype to so as to prevent overflow
        Mat sharpen = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
        
        //Use 2d filter using the shaprpen kernel. -1 os used to keep the depth of the resultant image same as the osurce image
        filter2D(image, output, -1, sharpen);
        
        return output;
    }
    
};
