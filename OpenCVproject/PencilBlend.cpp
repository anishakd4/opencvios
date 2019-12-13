//
//  PencilBlend.cpp
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

class PencilBlend {
    std::string greeting;
public:
    PencilBlend(){
        
    };
    
    Mat applyColorDodgeBlening(Mat top, Mat bottom){
        
        Mat output;
        top.convertTo(top, CV_32F);
        bottom.convertTo(bottom, CV_32F);
        output.convertTo(output, CV_32F);
        divide(bottom, 255-top, output, 256.0);
        return output;
    };
    
    Mat skethcPencilusingBlending(Mat original, int kernelSize = 21){
        Mat img = original.clone();
        
        Mat imGray;
        cvtColor(img, imGray, COLOR_BGR2GRAY);
        
        //Inverting the image
        Mat imGrayInv = 255 - imGray;
        
        //Gaussian blurring
        Mat imGrayInvBlur;
        GaussianBlur(imGrayInv, imGrayInvBlur, cv::Size(kernelSize, kernelSize), 0);
        
        //Color dodge bleding
        Mat output = applyColorDodgeBlening(imGrayInvBlur, imGray);
        
        output.convertTo(output, CV_8UC3);
        
        //Convert to bgr
        cvtColor(output, output, COLOR_GRAY2BGR);
        
        return output;
    };
    
};

