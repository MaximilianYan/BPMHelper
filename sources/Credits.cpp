#include <sstream>

#include "Credits.h"

const int OBJECT_MARKER_R = 255;

using namespace std;
using namespace cv;

Credits::Credits() :
    imgText(), imgLayout(),
    appearVelocity(0, 0) {
}

Credits::Credits(const std::string& fileNameText, const std::string& fileNameLayout) : Credits() {
    upload(fileNameText, fileNameLayout);
}

void Credits::upload(const string& fileNameText, const string& fileNameLayout) {
    imgText = imread(fileNameText, IMREAD_UNCHANGED);
    imgLayout = imread(fileNameLayout);
}

void Credits::setAppearVelocity(const Vec2d& appearVelocity) {
    this->appearVelocity = appearVelocity;
}

void Credits::setDisappearDelay(const double& disappearDelay) {
    this->disappearDelay = disappearDelay;
}

void Credits::render(const std::string& outputPath) {
    // imwrite(outputPath + "Test.png", imgText);

    for (int time = 0; renderFrame(outputPath, time); ++time);

}

bool Credits::renderFrame(const std::string& outputPath, const int& time) {
    /// Rendering destroys imgLayout & imgText
    Mat imgLayout;
    Mat frame(this->imgText.size(), this->imgText.type());
    this->imgLayout.copyTo(imgLayout);

    bool isFrameNotEmpty = false;

    for (Point pixel(0, 0); pixel.x < imgLayout.cols; ++pixel.x) {
        for (pixel.y = 0; pixel.y < imgLayout.rows; ++pixel.y) {
            if (isPixelObjectMarker(imgLayout, pixel)) {
                isFrameNotEmpty |= renderLine(frame, imgLayout, pixel, time);
            }
        }
    }

    return isFrameNotEmpty;
}

bool Credits::renderLine(Mat& frame, Mat& imgLayout, const Point& rootPixel, const int& time) {

}

bool Credits::isPixelObjectMarker(const cv::Mat& imgLayout, const Point& pixel) {
    if (imgLayout.at<Vec3b>(pixel)[2] == OBJECT_MARKER_R) return true;
    else return false;
}
