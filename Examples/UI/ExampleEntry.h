#pragma once
#include "DeviceWindow.h"
int WINAPI wWinMain(HINSTANCE instance,HINSTANCE,PWSTR,int show){
    VIRTUALDEVICE_EXAMPLE_MODEL model;return Examples::Window(model,instance,show);
}
