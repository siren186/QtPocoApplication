#pragma once

class CaseManager : public Poco::Util::Subsystem
{
public:
    Poco::BasicEvent<const std::string&> onOpen;
    Poco::BasicEvent<void> onClose;

public:
    virtual bool open(const char* fileName) = 0;
    virtual void close() = 0;
    virtual void callFromOtherSubSystem() = 0;
};
