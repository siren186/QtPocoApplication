#include "stdafx.h"
#include "App.h"

int main(int argc, char *argv[])
{
    try
    {
        Poco::AutoPtr<App> app = new App(argc, argv);
        return app->run();
    }
    catch (std::exception&)
    {
        return Poco::Util::Application::EXIT_CONFIG;
    }
}
