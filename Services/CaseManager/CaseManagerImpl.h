#pragma once

class CaseManagerImpl : public CaseManager
{
public:
    // CaseManager methods:
    virtual bool open(const char* fileName) override;
    virtual void close() override;
    virtual void callFromOtherSubSystem() override;

    // Poco::Util::Subsystem methods:
    virtual const char* name() const override;

protected:
    // Poco::Util::Subsystem methods:
    virtual void initialize(Poco::Util::Application& app) override;
    virtual void uninitialize() override;

private:
    Poco::Logger& logger() const;

private:
    Poco::Logger* m_logger;
};
