#pragma once
#include "AppWindow.h"

class App : public Poco::Util::Application
{
public:
    App(int argc, char* argv[]);

protected:
    // Poco::Util::Application methods:
    virtual void initialize(Poco::Util::Application& self) override;
    virtual void uninitialize() override;
    virtual int main(const std::vector<std::string>& args) override;

private:
    void addSubSystems();

private:
    QtSingleApplication m_qApp;
};
