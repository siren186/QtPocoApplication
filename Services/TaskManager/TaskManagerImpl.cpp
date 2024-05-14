#include "stdafx.h"
#include "TaskManagerImpl.h"
#include "Poco/Timer.h"

const char* TaskManagerImpl::name() const
{
    return "TaskManager";
}

void TaskManagerImpl::runInBackground(int n)
{
    poco_information(logger(), Poco::format("runInBackground(%d)", n));
    std::thread(asyncSendNotification, n).detach();
}

void TaskManagerImpl::onCaseOpen(const std::string& fileName)
{
    poco_information_f(logger(), "onCaseOpen(%s)", fileName);

    // Get one subsystem from another subsystem
    Poco::Util::Application::instance().getSubsystem<CaseManager>().callFromOtherSubSystem();
}

void TaskManagerImpl::onCaseClose()
{
    poco_warning(logger(), "onCaseClose()");
}

void TaskManagerImpl::initialize(Poco::Util::Application& app)
{
    m_logger = &Poco::Logger::get(name());
    poco_trace(logger(), "initialize()");
}

void TaskManagerImpl::uninitialize()
{
    poco_debug(logger(), "uninitialize()");
}

void TaskManagerImpl::asyncSendNotification(int n)
{
    Poco::NotificationCenter::defaultCenter().postNotification(new Notif::TaskResult(n));
}

Poco::Logger& TaskManagerImpl::logger() const
{
    return *m_logger;
}
