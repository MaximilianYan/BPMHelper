#include "includeCredits.h"

#define IMG_PATH ".\\"
#define OUTPUT_PATH ".\\BPMHelper_credits_output\\"

int main() {
    Credits credits(IMG_PATH"text.png", IMG_PATH"zones.png");
    credits.setAppearVelocity(Vec2d(100, 100));
    credits.setDisappearDelay(10);

    credits.render(OUTPUT_PATH, 20);

    cout << "Program finished 0" << endl;
    return 0;
}
