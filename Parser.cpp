#include <stdlib.h>
#include <vector>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "visualSpace/cloud.cpp"
#include "visualSpace/perspective.cpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <filesystem>
#include <algorithm>

int main() {

    pointCloud GeneratedPoints;
    std::string directory_path = "../dataset";

    std::vector<std::filesystem::directory_entry> files;
    for (const auto& file_iterator : std::filesystem::directory_iterator(directory_path)) {
        if (std::filesystem::is_regular_file(file_iterator)) {
            files.push_back(file_iterator);
        }
    }

    std::sort(files.begin(), files.end(), [](const auto& a, const auto& b) {
        auto extractNumber = [](const std::string& filename) -> int {
            size_t open  = filename.rfind('(');
            size_t close = filename.rfind(')');
            if (open != std::string::npos && close != std::string::npos && close > open) {
                return std::stoi(filename.substr(open + 1, close - open - 1));
            }
            return -1;
        };
        return extractNumber(a.path().stem().string()) < extractNumber(b.path().stem().string());
    });

    int z_position = 0;
    for (const auto& file_iterator : files) {
        cv::Mat src = cv::imread(file_iterator.path().string(), cv::IMREAD_GRAYSCALE);

        for(int x_position = 0; x_position < img.rows; x_position++) {
            for(int y_position = 0; y_position < img.cols; y_position++) {
                cv::Vec3b& pixel = img.at<cv::Vec3b>(i, j);
                // Access channels: pixel[0] (Blue), pixel[1] (Green), pixel[2] (Red)
                Point newPoint;
                newPoint.x = x_position;
                newPoint.y = y_position;
                newPoint.z = z_position;
                
                newPoint.r = pixel[2];
                newPoint.g = pixel[1];
                newPOint.b = pixel[0];

                newPoint.opacity = 1;
                newPoint.concern = 0;

                GeneratedPoints.addPoint(newPoint);
            }
        }

        if (src.empty()) {
            std::cout << "Image not detected: " << file_iterator.path() << std::endl;
            continue;
        }
    }

    return 0;
}