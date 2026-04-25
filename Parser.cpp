#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <filesystem>
#include <algorithm>

int main() {
    std::string directory_path = "../dataset";
    for (auto file_iterator = std::filesystem::directory_iterator(directory_path)){
        cv::Mat src = cv::imread(file_iterator, cv::IMREAD_GRAYSCALE);
        if (src.empty()) {
            std::cout << "Image not detected" << std::endl;
            return -1;
        }

        cv::Mat alpha;
        cv::threshold(src, alpha, 0, 255, cv::THRESH_BINARY);
        std::vector<cv::Mat> bgra = { src, src, src, alpha };

        cv::Mat dst;
        cv::merge(bgra, dst);

        cv::imwrite("../processed/" + file_iterator, dst);
    }

    return 0;
}
