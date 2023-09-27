#include "include.h"

static const Size FRAME_SIZE(1920, 1080);

int main() {
    Mat img(FRAME_SIZE, CV_8UC3);

    VideoWriter videoWriter("BPMHelperOutput.mp4", VideoWriter::fourcc('m', 'p', '4', 'v'), 25, FRAME_SIZE);
    // cv::VideoWriter videoWriter("BPMHelperOutput.webm", cv::VideoWriter::fourcc('v', 'p', '8', '0'), 25, FRAME_SIZE);
    
    if (!videoWriter.isOpened()) {
        cout << "ERROR!!!: cannot open/create file or codec error" << endl;
        return 1;
    }

    for (int i = 0; i < 50; ++i)
        videoWriter << img;

    return 0;
}
