#include "includeCredits.h"

#define IMG_PATH ".\\"
#define OUTPUT_PATH ".\\BPMHelper_credits_output\\"

int main() {
    Credits credits(IMG_PATH"text.png", IMG_PATH"zones.png");

    credits.render(OUTPUT_PATH);

    cout << "Program finished 0" << endl;
    return 0;
}
