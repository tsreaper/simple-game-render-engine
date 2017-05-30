#include <iostream>
#include "render/mainRender.h"
#include "logic/mainLogic.h"
#include "render/engine/windowManager.h"

using namespace std;

int main (int argc,  char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    MainRender::init();
    MainLogic::init();

    while (!WindowManager::isExiting())
    {
        MainLogic::run();
        MainRender::render();
    }

    MainLogic::cleanUp();
    MainRender::cleanUp();

    return 0;
}
