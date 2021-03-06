//
//  Pixels.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/3/12.
//  Copyright © 2016年 numberwolf. All rights reserved.
//
/**************************************************************************
 * Email：porschegt23@foxmail.com || numberwolf11@gmail.com
 * Github:https://github.com/numberwolf
 * APACHE 2.0 LICENSE
 * Copyright [2016] [Chang Yanlong]
 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 **************************************************************************/


#include "Pixels.hpp"

#warning 如果是非iOSDemo则用这个
BGR Pixels::getColorPixel(int x, int y) {
    BGR returnbgr;
    int my_width_step = this->my_pixels->widthStep;
    returnbgr.b = this->my_pixels->imageData[y*my_width_step+3*x];
    returnbgr.g = this->my_pixels->imageData[y*my_width_step+3*x+1];
    returnbgr.r = this->my_pixels->imageData[y*my_width_step+3*x+2];
//    return this->my_pixels + (y * this->width) + x;
    return returnbgr;
}

int Pixels::getRed(int x, int y) {
//    uchar *ptr = (uchar *) (
//                            ColorImage ->imageData + y * ColorImage->widthStep
//                            );
    return this->my_pixels->imageData[y*this->my_pixels->widthStep+3*x+2];
}

int Pixels::getGreen(int x, int y) {
    
    return this->my_pixels->imageData[y*this->my_pixels->widthStep+3*x+1];
}

int Pixels::getBlue(int x, int y) {
    
    return this->my_pixels->imageData[y*this->my_pixels->widthStep+3*x];
}

int Pixels::getGray(int x, int y) {
    return getRed(x, y)*GRAY_RED_POINT + getGreen(x, y)*GRAY_GREEN_POINT + getBlue(x, y)*GRAY_BLUE_POINT;
}

void Pixels::rgbMake(int x, int y, int R, int G, int B) {
    int my_width_step = this->my_pixels->widthStep;
    this->my_pixels->imageData[y*my_width_step+3*x] = B;
    this->my_pixels->imageData[y*my_width_step+3*x+1] = G;
    this->my_pixels->imageData[y*my_width_step+3*x+2] = R;
}

void Pixels::GrayPixels() {
    for (int x = 0; x < this->width; x++) {
        for (int y = 0; y < this->height; y++) {
            int GrayColor = this->getRed(x, y)*GRAY_RED_POINT + this->getGreen(x, y)*GRAY_GREEN_POINT + this->getBlue(x, y)*GRAY_BLUE_POINT;
            
            this->rgbMake(x, y, GrayColor, GrayColor, GrayColor);
        }
    }
}

int* Pixels::MountionsPic() {
    int *pic = new int[256];
    
    for(int i = 0;i < 256; i++) {
        pic[i] = 0;
    }
    
    for (int x = 0; x < this->width; x++) {
        for (int y = 0; y < this->height; y++) {
            int GrayColor = this->getRed(x, y)*GRAY_RED_POINT + this->getGreen(x, y)*GRAY_GREEN_POINT + this->getBlue(x, y)*GRAY_BLUE_POINT;
            this->rgbMake(x, y, GrayColor, GrayColor, GrayColor);
            
            pic[GrayColor]++;
        }
    }
    
    return pic;
}

