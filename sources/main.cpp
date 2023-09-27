#include "include.h"

static const Size FRAME_SIZE(1920, 1080);

int main() {
    double fps = 25.;       ///< frames per second

    double bpm = 94.;       ///< beats per minute
    {
        double begin = 3.060104;
        double end = 4 * 60 + 54.10407;
        int n = 114;
        bpm = 60 / ((end - begin) / n / 4);
        cout << "bpm = " << bpm << endl;

        // double delta = 0.00004;
        double delta = 0.0001;
        cout << "r+-  = " << fixed << 2. * delta / (end - begin) * bpm << endl;
    }

    double bps = bpm / 60.; ///< beats per second
    double bpf = bps / fps; ///< beats per frame

    double lengthS = 5 * 60; ///< video duration in seconds
    int lengthF = ceil(fps * lengthS); ///< video suration in frames

    Mat img(FRAME_SIZE, CV_8UC3); ///< buffer image
    VideoWriter videoWriter("BPMHelperOutput.mp4", VideoWriter::fourcc('m', 'p', '4', 'v'), 25, FRAME_SIZE); ///< output file

    // cv::VideoWriter videoWriter("BPMHelperOutput.webm", cv::VideoWriter::fourcc('v', 'p', '8', '0'), 25, FRAME_SIZE);

    if (!videoWriter.isOpened()) {
        cout << "ERROR!!!: cannot open/create file or codec error" << endl;
        return 1;
    }

    vector<Mat> beatImg(4);

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

    double donePart = 0;

    for (int frameN = 0; frameN < lengthF; ++frameN) {
        int beatN = (int)(round(bpf * (double)frameN)) % 4;
        videoWriter << beatImg[beatN];

        if (!(frameN % int(1e2))) {
            while (double(frameN) / lengthF + 0.1 > donePart) {
                // cout << int(donePart * 10.) * 10 << "% ";
                cout <<  (int)(ceil(donePart * 10.) * 10.) << "% ";
                donePart += 0.1;
            }
        }
    }
    cout << endl;


    cout << "Program finished 0" << endl;
    return 0;
}
