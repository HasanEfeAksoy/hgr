#include <iostream>
#include "hgr.h"


void update();

int main() {
    hgr::drawWindow(hgr::vec2(400.0f, 400.0f), "HGR (Hasan Graphics) Window", hgr::vec3(50.0f, 120.0f, 190.0f), update);

    return 0;
}


void update() {
}