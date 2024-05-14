#pragma once

// C++ headers


// Windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Qt
#include <QtWidgets>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QtConcurrent/QtConcurrent>

// qt-solutions
#include <QtSingleApplication>

// Poco
#include "Poco/Util/Application.h"
#include "Poco/ClassLoader.h"
#include "Poco/Delegate.h"
#include "Poco/NotificationCenter.h"
#include "Poco/Notification.h"
#include "Poco/NObserver.h"

// App services
#include "CaseManager/CaseManager.h"
#include "TaskManager/TaskManager.h"
#include "NotifManager/TaskResult.h"
