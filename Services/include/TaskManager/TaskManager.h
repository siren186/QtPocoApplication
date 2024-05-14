#pragma once

class TaskManager : public Poco::Util::Subsystem
{
public:
    virtual void runInBackground(int n) = 0;

public:
    // callbacks
    virtual void onCaseOpen(const std::string& fileName) = 0;
    virtual void onCaseClose() = 0;
};
