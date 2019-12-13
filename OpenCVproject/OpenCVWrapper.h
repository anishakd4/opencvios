//
//  OpenCVWrapper.h
//  OpenCVproject
//
//  Created by Anish Kumar Dubey on 03/08/19.
//  Copyright © 2019 Anish Kumar Dubey. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface OpenCVWrapper : NSObject

+ (NSString *)openCVVersionString;
+ (UIImage *)cartoonFilterWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)pencilBlendWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)pencilEdgeWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)xproFilterWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)moonFilterWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)kelvinFilterWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)clarendonFilterWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)cannyFilterWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)sharpenFilterWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)coolingFilterWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)warmingFilterWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)increaseBrightnessWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)decreaseBrightnessWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)colorTransferWithOpenCV:(UIImage*)inputImage : (UIImage*)image1;
+ (UIImage *)desaturationFilterWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)grayImageWithOpenCV:(UIImage*)inputImage;
+ (UIImage *)postcardFilterWithOpenCV:(UIImage*)lena : (UIImage*)text : (UIImage*)texture;
+ (UIImage *)retroFilterWithOpenCV:(UIImage*)inputImage : (UIImage*)fuzzyBorder : (UIImage*)scratches;

@end

NS_ASSUME_NONNULL_END
