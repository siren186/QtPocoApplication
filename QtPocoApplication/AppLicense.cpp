#include "stdafx.h"
#include "AppLicense.h"

bool AppLicense::check()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return true;
}
