#include <sstream>
#include <queue>
#include <vector>

#include "Credits.h"

#include "AverageCounter.h"

const int MARKER_OBJECT_R = 255;
const int MARKER_EDGE_G = 255;

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

void Credits::render(const std::string& outputPath, int frameLimit) {
    // imwrite(outputPath + "Test.png", imgText);

    for (int time = 1; renderFrame(outputPath, time) && --frameLimit; ++time);

}

bool Credits::renderFrame(const std::string& outputPath, const int& time) const {
    /// Rendering destroys imgLayout & imgText
    Mat imgLayout;
    Mat frame(this->imgText.size(), this->imgText.type());
    this->imgLayout.copyTo(imgLayout);
    frame.setTo(0);

    bool hasEnded = false;

    for (Point pixel(0, 0); pixel.x < imgLayout.cols; ++pixel.x) {
        for (pixel.y = 0; pixel.y < imgLayout.rows; ++pixel.y) {
            if (isPixelMarkerObject(imgLayout, pixel)) {
                hasEnded |= renderLine(frame, imgLayout, pixel, time);
            }
        }
    }

    imwrite(getOutputFileName(outputPath, time), frame);

    return hasEnded;
}

bool Credits::renderLine(Mat& frame, Mat& imgLayout, const Point& rootPixel, const int& time) const {
    Mat mask(imgText.size(), CV_8UC1); ///< 255 if pixel is contained by current layout
    mask.setTo(0);

    AverageCounter<Point> linePosition;

    bool isFrameNotEmpty = false;
    {
        queue<Point> bfsQueue;
        bfsQueue.emplace(rootPixel);

        // run bfs from "rootPixel" & mark internal pixels into "mask" & calculate central pixel
        while (!bfsQueue.empty()) {
            const vector<Point> neighbours({
                Point(0, -1),
                Point(+1, 0),
                Point(0, +1),
                Point(-1, 0) });

            for (const Point& shift : neighbours) {
                Point cur = bfsQueue.front() + shift;

                if (mask.at<unsigned char>(cur)) continue;
                if (isPixelMarkerEdge(imgLayout, cur)) continue;

                if (isPixelMarkerObject(imgLayout, cur)) linePosition += cur;

                mask.at<unsigned char>(cur) = 255;
                isFrameNotEmpty = true;

                bfsQueue.push(cur);
            }

            bfsQueue.pop();
        }

        linePosition = linePosition;
    }

    if (!isFrameNotEmpty) return false;

    Mat buffer(this->imgText.size(), this->imgText.type());
    // static int counter = 0;
    // buffer.setTo(Vec4b(counter, counter, counter, 255));
    // counter += 10;
    buffer.setTo(0);
    imgText.copyTo(buffer, mask);

    bool hasEnded = true;
    buffer *= calculateTransparency(linePosition, time, getPixelDisappearMul(imgLayout, linePosition), hasEnded);

    buffer.copyTo(frame, mask);

    imgLayout.setTo(0, mask);

    return !hasEnded;
}

double Credits::calculateTransparency(const Point& coord, const int& time, const double& disappearMultiplier, bool& hasEnded) const {
    int relativeShift =
        (double)coord.x / appearVelocity[0] +
        (double)coord.y / appearVelocity[1];
    return calculateTransparency(time - relativeShift, disappearMultiplier, hasEnded);
}

double Credits::calculateTransparency(const int& time, const double& disappearMultiplier, bool& hasEnded) const {
    hasEnded = false;

    const double halfDelay = disappearDelay / 2.;
    const double halfDelayMul = halfDelay / disappearMultiplier;

    if (time <= 0) {
        return 0;
    }
    if ((double)time <= halfDelay) {
        return (double)time / halfDelay;
    }
    if ((double)time <= (halfDelay + halfDelayMul)) {
        return 1. - ((double)time - halfDelay) / halfDelayMul;
    }

    hasEnded = true;
    return 0;
}

bool Credits::isPixelMarkerObject(const Mat& imgLayout, const Point& pixel) {
    if (imgLayout.at<Vec3b>(pixel)[2] == MARKER_OBJECT_R) return true;
    else return false;
}

bool Credits::isPixelMarkerEdge(const Mat& imgLayout, const Point& pixel) {
    if (imgLayout.at<Vec3b>(pixel)[1] == MARKER_EDGE_G) return true;
    else return false;
}

double Credits::getPixelDisappearMul(const Mat& imgLayout, const Point& pixel) {
    return (double)imgLayout.at<Vec3b>(pixel)[0] / 100.;
}

string Credits::getOutputFileName(const string& outputPath, const int& time) {
    stringstream res;
    res << outputPath << "BPMHelper_credits_frame_" << setfill('0') << setw(4) << time << ".png";
    string resStr;
    res >> resStr;
    return resStr;
}

