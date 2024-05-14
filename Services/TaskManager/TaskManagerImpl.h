#pragma once

class TaskManagerImpl : public TaskManager
{
public:
    // TaskManager methods:
    virtual void runInBackground(int n) override;
    virtual void onCaseOpen(const std::string& fileName) override;
    virtual void onCaseClose() override;

    // Poco::Util::Subsystem methods:
    virtual const char* name() const override;

protected:
    // Poco::Util::Subsystem methods:
    virtual void initialize(Poco::Util::Application& app) override;
    virtual void uninitialize() override;

private:
    static void asyncSendNotification(int n);

private:
    Poco::Logger& logger() const;

private:
    Poco::Logger* m_logger;
    Poco::TaskManager* m_taskMgr;
};
