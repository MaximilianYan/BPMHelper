#include "BPMHelper.h"

using namespace std;
using namespace cv;

const string OUTPUT_FILE_NAME = "BPMHelperOutput.mp4";
const int OUTPUT_FILE_FOURCC = VideoWriter::fourcc('m', 'p', '4', 'v');

BPMHelper::BPMHelper(cv::Size FRAME_SIZE, double fps, double bpm) :
    FRAME_SIZE(FRAME_SIZE),
    fps(fps), bpf(0.), durationF(0.) {

    setBpm(bpm);
}

BPMHelper::BPMHelper(cv::Size FRAME_SIZE) : BPMHelper(FRAME_SIZE, 0., 0.) {}

BPMHelper::BPMHelper() : BPMHelper(cv::Size(1920, 1080)) {}

BPMHelper::~BPMHelper() {
}

void BPMHelper::setBpm(double bpm) {
    double bps = bpm / 60.; ///< beats per second
    this->bpf = bps / fps; ///< beats per frame
}

void BPMHelper::setDuration(double duration) {
    this->durationF = ceil(fps * duration);
}

BPMHelper::RENDER_ERROR BPMHelper::render(ostream& logOutput) {
    Mat buffer(FRAME_SIZE, CV_8UC3);                                                ///< buffer image
    VideoWriter videoWriter(OUTPUT_FILE_NAME, OUTPUT_FILE_FOURCC, fps, FRAME_SIZE); ///< output file

    if (!videoWriter.isOpened()) {
        return RENDER_ERROR::FILE_ERR;
    }

    vector<Mat> beatImg(4); ///< images for beats

    for (int i = 0; i < 4; ++i) {
        beatImg[i].create(FRAME_SIZE, CV_8UC3);

        beatImg[i].setTo(0);
        rectangle(beatImg[i], Rect(
            Point2i(
                i % 4 == 0 || i % 4 == 3 ? 0 : FRAME_SIZE.width * 2 / 3,
                i % 4 == 0 || i % 4 == 1 ? 0 : FRAME_SIZE.height * 2 / 3),
            Point2i(
                i % 4 == 0 || i % 4 == 3 ? FRAME_SIZE.width * 2 / 3 : FRAME_SIZE.width,
                i % 4 == 0 || i % 4 == 1 ? FRAME_SIZE.height * 2 / 3 : FRAME_SIZE.height)),
            Scalar(0, 255, 0), FILLED);
    }

    int logNFrame = durationF / 10; ///< frames per log line

    for (int frameN = 0; frameN < durationF; ++frameN) {

        int beatN = (int)(round(bpf * (double)frameN)) % 4;
        videoWriter << beatImg[beatN];

        if (!(frameN % logNFrame)) {
            logOutput << 10 * frameN / logNFrame << "% ";
        }
    }
    logOutput << endl;

    return OK;
}
