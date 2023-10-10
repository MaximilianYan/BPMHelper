#include "include.h"

static const Size FRAME_SIZE(1920, 1080);

int main() {
    BPMHelper bpmHelper(FRAME_SIZE, 25., 94.);

    {
        double begin = 3.060104;
        double end = 4 * 60 + 54.10407;
        int n = 114;
        double bpm = 60 / ((end - begin) / n / 4);
        cout << "bpm = " << bpm << endl;

        // double delta = 0.00004;
        double delta = 0.0001;
        cout << "r+-  = " << fixed << 2. * delta / (end - begin) * bpm << endl;

        bpmHelper.setBpm(bpm);
    }

    bpmHelper.setDuration(5 * 60 + 51 + 14 / 25); ///< video duration in seconds

    switch (bpmHelper.render(cout)) {
    case BPMHelper::RENDER_ERROR::FILE_ERR:
        cout << "ERROR!!!: cannot open/create file or codec error" << endl;
        return 1;
        break;
    case BPMHelper::RENDER_ERROR::OK:
        break;
    }

    cout << "Program finished 0" << endl;
    return 0;
}
