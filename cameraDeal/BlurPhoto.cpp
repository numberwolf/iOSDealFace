//
//  BlurPhoto.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/3/1.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#include <math.h>
#include "BlurPhoto.hpp"

#define e 2.71828
#define PI 3.1416

#pragma mark 高斯模糊
void BlurPhoto::GaussDeal(int **array, int **temp,int width, int height, int r) {
    
    // **array是二维数组，是rgb8888 最后的每个像素组成的数组
    double xaver = 0.0, x2aver = 0.0;
    
    for (int h = 0; h < height; h++) {
        
        xaver=0.0, x2aver=0.0;
        for (int w = 0 ; w < width; w++) {
            
            int *pixelsArr = new int[(2*r+1)*(2*r+1)]; // 存储半径内像素
            int *pixTemp = pixelsArr;
            
            int pixelSum = 0;
            int pix2Sum = 0;
            
            for (int j = 0; j <= (2*r); j++) {
                int y = h - r + j;
                
                for (int i = 0; i <= (2*r); i++) {
                    int x = w - r + i;
                    
                    // 除去中心点 和 越界点
                    if ( y < 0 || x < 0 || y >= height || x >= width || (y == h && x == w)) {
                        *pixTemp = 0;
                        pixTemp++;
                        continue;
                    }
                    
                    *pixTemp = temp[y][x];
                    
                    pixelSum += *pixTemp; // 总数
                    pix2Sum += (*pixTemp) * (*pixTemp); // 总数^2
                    
                    pixTemp++;
                }
            }
            
            /** change End **/
            
            // 开始计算方差
            xaver = (pixelSum - temp[h][w])/((2*r+1)*(2*r+1)-1);
            x2aver = (pix2Sum - temp[h][w]*temp[h][w])/((2*r+1)*(2*r+1)-1);
            
            double fc = sqrt(x2aver - xaver*xaver); // 得到方差
            
            // 开始计算权重
            double left = 1/(2*PI*fc*fc);
            
            double *weightArr = new double[(2*r+1)*(2*r+1)]; // 得到权重数组
            int weightArrNum = 0;
            double weightSum = 0.0;
            
            // 周围像素权重
            for (int j = 0; j <= (2*r); j++) {
                int y = r - j;
                int y_real = h - r + j; // 真坐标
                
                for (int i = 0; i <= (2*r); i++) {
                    int x = i - r;
                    int x_real = w - r + i; // 真坐标
                    
                    // 除去中心点
                    if ((x == 0 && y == 0) || y_real < 0 || x_real < 0 || y_real > height || x_real > width) {
                        weightArr[weightArrNum] = 0;
                        weightArrNum++;
                        continue;
                    }
                    
                    double right = pow(e, -(x*x + y*y)/(2*fc*fc));
                    double weight = left*right;
                    
                    weightArr[weightArrNum] = weight;
                    
                    weightArrNum++;
                }
            }
            
            for (int n = 0; n < ((2*r+1)*(2*r+1)); n++) {
                weightSum += weightArr[n];
            }
            
            weightArrNum = 0;
            
            int array_h_w_temp = 0;
            
            // 得到周围像素权重
            for (int j = 0; j <= (2*r); j++) {
                for (int i = 0; i <= (2*r); i++) {
                    weightArr[weightArrNum] /= weightSum;
                    *pixelsArr = (*pixelsArr) * weightArr[weightArrNum]; // 周围像素的 权值 * 像素
                    array_h_w_temp += *pixelsArr;
                    
                    weightArrNum++;
                    pixelsArr++;
                }
            }
            
            array[h][w] = array_h_w_temp;
            
            delete [] weightArr;
            //delete [] pixelsArr;
            
        }
    }
}
