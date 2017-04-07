#include <stdio.h>
#include <stdlib.h>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"


cv::Mat pixelation_img (cv::Mat img_original, int window) {
    cv::Mat img_final = img_original.clone();

    for (int i = 0; i < img_original.rows; i+=window-1) {
        for (int j = 0; j < img_original.cols; j+=window-1) {
            int sum[3] = {0,0,0};
            int count = 0;

            for (int x = i - window/2; x <= i + window/2; x++) {
                for (int y = j - window/2; y <= j + window/2; y++) {

                    if (x >= 0 && x < img_original.rows && y >= 0 && y < img_original.cols) {
                        count++;
                        for (int z  = 0; z < 3; z++) {
                            sum[z] += img_original.at<cv::Vec3b>(x,y)[z];
                        }
                    }
                }
            }

            for (int x = i - window/2; x <= i + window/2; x++) {
                for (int y = j - window/2; y <= j + window/2; y++) {
                    if (x >= 0 && x < img_original.rows && y >= 0 && y < img_original.cols) {

                        for (int z = 0; z < 3; z++) {
                            img_final.at<cv::Vec3b>(x,y)[z] = (int)sum[z]/count;
                        }
                    }
                }
            }
        }
    }

    cv::imwrite ("teste.png", img_final);
    return img_final;
}

int main (int argc, char* argv[]) {
    cv::Mat img = cv::imread (argv[1]);

    pixelation_img (img, 20);

    return 0;
}
