//
//  OpenCVWrapper.m
//  OpenCVproject
//
//  Created by Anish Kumar Dubey on 03/08/19.
//  Copyright © 2019 Anish Kumar Dubey. All rights reserved.
//

#import "OpenCVWrapper.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs/ios.h>
#include "Xpro.cpp"
#include "Moon.cpp"
#include "CartoonFilter.cpp"
#include "PencilBlend.cpp"
#include "PencilEdge.cpp"
#include "KelvinFilter.cpp"
#include "ClarendonFilter.cpp"
#include "CannyFilter.cpp"
#include "SharpenFilter.cpp"
#include "CoolingFilter.cpp"
#include "WarmingFilter.cpp"
#include "IncreaseBrightness.cpp"
#include "DecreaseBrightness.cpp"
#include "ColorTransfer.cpp"
#include "Desaturation.cpp"
#include "GrayConversion.cpp"
#include "PostcardPrinter.cpp"
#include "RetroFilter.cpp"


using namespace cv;
using namespace std;

@implementation OpenCVWrapper

+ (NSString *)openCVVersionString {
    return [NSString stringWithFormat:@"OpenCV Version %s",  CV_VERSION];
}

+ (UIImage *)cartoonFilterWithOpenCV:(UIImage*)inputImage {
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    CartoonFilter cartoonFilter;
    cv::Mat output = cartoonFilter.makeCartoon(cvMat);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)pencilBlendWithOpenCV:(UIImage*)inputImage{
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    PencilBlend pencilBlend;
    cv::Mat output = pencilBlend.skethcPencilusingBlending(cvMat);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)pencilEdgeWithOpenCV:(UIImage*)inputImage{
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    PencilEdge pencilEdge;
    cv::Mat output = pencilEdge.sketchPencilUsingEdgeDetection(cvMat);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)xproFilterWithOpenCV:(UIImage*)inputImage{
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    Xpro xpro;
    cv::Mat output = xpro.xproo(cvMat, 3);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)moonFilterWithOpenCV:(UIImage*)inputImage{
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    Moon moon;
    cv::Mat output = moon.moon(cvMat);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)kelvinFilterWithOpenCV:(UIImage*)inputImage{
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    KelvinFilter kelvinFilter;
    cv::Mat output = kelvinFilter.kelvin(cvMat);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)clarendonFilterWithOpenCV:(UIImage*)inputImage{
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    ClarendonFilter clarendon;
    cv::Mat output = clarendon.clarendon(cvMat);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)cannyFilterWithOpenCV:(UIImage*)inputImage{
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    CannyFilter cannyFilter;
    cv::Mat output = cannyFilter.canny(cvMat);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)sharpenFilterWithOpenCV:(UIImage*)inputImage{
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    SharpenFilter sharpenFilter;
    cv::Mat output = sharpenFilter.sharpen(cvMat);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)coolingFilterWithOpenCV:(UIImage*)inputImage{
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    WarmingFilter warmingFilter;
    cv::Mat output = warmingFilter.warm(cvMat);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)warmingFilterWithOpenCV:(UIImage*)inputImage{
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    CoolingFilter coolingFilter;
    cv::Mat output = coolingFilter.cool(cvMat);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)increaseBrightnessWithOpenCV:(UIImage*)inputImage{
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    IncreaseBrightness increaseBrightness;
    cv::Mat output = increaseBrightness.increaseBrightness(cvMat);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)decreaseBrightnessWithOpenCV:(UIImage*)inputImage{
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    DecreaseBrightness descreaseBrightness;
    cv::Mat output = descreaseBrightness.decreaseBrightness(cvMat);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)colorTransferWithOpenCV:(UIImage*)inputImage : (UIImage*)image1{
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    cv::Mat cvMat3;
    UIImageToMat(image1, cvMat3);
    
    ////////
    
    ColorTransfer colorTransfer;
    cv::Mat output = colorTransfer.colorTransferFilter(cvMat, cvMat3);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)desaturationFilterWithOpenCV:(UIImage*)inputImage{
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    //Specifying saturation scale factor
    
    Desaturation desaturation;
    cv::Mat output = desaturation.desaturation(cvMat);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)grayImageWithOpenCV:(UIImage*)inputImage {
    
    cv::Mat cvMat;
    UIImageToMat(inputImage, cvMat);
    
    ////////
    
    GrayConversion grayConversion;
    cv::Mat output = grayConversion.grayConversion(cvMat);
    
    ///////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)postcardFilterWithOpenCV:(UIImage*)lena : (UIImage*)text : (UIImage*)texture {
    
    cv::Mat cvLena;
    UIImageToMat(lena, cvLena);
    
    cv::Mat cvText;
    UIImageToMat(text, cvText);
    
    cv::Mat cvTexture;
    UIImageToMat(texture, cvTexture);
    
    //////
    
    PostcardPrinter postcardPrinter;
    cv::Mat output = postcardPrinter.printPostcardAnish(cvLena, cvText, cvTexture);

    /////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

+ (UIImage *)retroFilterWithOpenCV:(UIImage*)inputImage : (UIImage*)fuzzyBorder : (UIImage*)scratches; {
    
    cv::Mat cvImage;
    UIImageToMat(inputImage, cvImage);
    
    cv::Mat cvFuzzy;
    UIImageToMat(fuzzyBorder, cvFuzzy);
    
    cv::Mat cvScratches;
    UIImageToMat(scratches, cvScratches);
    
    //////
    
    RetroFilter retrofilter;
    cv::Mat output = retrofilter.retro(cvImage, cvFuzzy, cvScratches);
    
    /////
    
    UIImage *finalImage = MatToUIImage(output);
    
    return finalImage;
}

@end
