#include "includeCredits.h"

#define IMG_PATH ".\\"
#define OUTPUT_PATH ".\\BPMHelper_credits_output\\"

int main() {
    Credits credits(IMG_PATH"text.png", IMG_PATH"zones.png");
    credits.setAppearVelocity(Vec2d(3000 / 103, 3000 / 103));
    credits.setDisappearDelay(76);

    credits.render(OUTPUT_PATH, 300);

    cout << "Program finished 0" << endl;
    return 0;
}
