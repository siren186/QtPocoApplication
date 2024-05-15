#include "stdafx.h"
#include "App.h"

int main(int argc, char *argv[])
{
    try
    {
        App app(argc, argv);
        return app.run();
    }
    catch (Poco::Exception&)
    {
        return Poco::Util::Application::EXIT_CONFIG;
    }
    catch (std::exception&)
    {
        return Poco::Util::Application::EXIT_SOFTWARE;
    }
}
