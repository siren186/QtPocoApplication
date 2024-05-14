#pragma once

namespace Notif {

class TaskResult : public Poco::Notification
{
public:
    TaskResult(int n)
    {
        for (int i = 0; i < n; i++)
        {
            m_map[std::to_string(i)] = std::to_string(i);
        }
    }

    const std::map<std::string, std::string>& getMap() const
    {
        return m_map;
    }

private:
    std::map<std::string, std::string> m_map;
};

} // end of namespace Notif
