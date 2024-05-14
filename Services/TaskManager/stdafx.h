#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Poco
#include "Poco/Logger.h"
#include "Poco/Util/Subsystem.h"
#include "Poco/BasicEvent.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Util/Application.h"
#include "Poco/NotificationCenter.h"
#include "Poco/TaskManager.h"

// App services
#include "TaskManager/TaskManager.h"
#include "CaseManager/CaseManager.h"
#include "NotifManager/TaskResult.h"
