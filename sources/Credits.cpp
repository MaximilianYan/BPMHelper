#include <sstream>

#include "Credits.h"

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
    imwrite(outputPath + "Test.png", imgText);
}