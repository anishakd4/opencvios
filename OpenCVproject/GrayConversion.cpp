//
//  GrayConversion.cpp
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

class GrayConversion {
    std::string greeting;
public:
    GrayConversion(){
        
    };
    
    Mat grayConversion(Mat image){
        
        cv::Mat greyMat;
        cv::cvtColor(image, greyMat, COLOR_BGR2GRAY);
        
        return greyMat;
    };
    
};
