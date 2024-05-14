#include "stdafx.h"
#include "CaseManagerImpl.h"

bool CaseManagerImpl::open(const char* fileName)
{
    poco_information_f(logger(), "open(%s)", fileName);
    if (fileName)
    {
        onOpen(fileName);
        return true;
    }
    return false;
}

void CaseManagerImpl::close()
{
    poco_warning(logger(), "close()");
    onClose();
}

const char* CaseManagerImpl::name() const
{
    return "CaseManager";
}

void CaseManagerImpl::callFromOtherSubSystem()
{
    poco_trace(logger(), "callFromOtherSubSystem()");
}

void CaseManagerImpl::initialize(Poco::Util::Application& app)
{
    m_logger = &Poco::Logger::get(name());
    poco_trace(logger(), "initialize()");
}

void CaseManagerImpl::uninitialize()
{
    onOpen.clear();
    onClose.clear();
    poco_trace(logger(), "uninitialize()");
}

Poco::Logger& CaseManagerImpl::logger() const
{
    return *m_logger;
}
