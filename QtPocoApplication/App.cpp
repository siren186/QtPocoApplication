#include "stdafx.h"
#include "App.h"
#include "AppSplashScreen.h"
#include "AppLicense.h"


App::App(int argc, char* argv[])
    : Poco::Util::Application(argc, argv)
    , m_qApp("{21197D28-953C-4337-94EA-7502DACF6845}", argc, argv)
{
    // Application process singleton
    if (m_qApp.isRunning())
    {
        m_qApp.sendMessage("Application is already running");
        throw Poco::ApplicationException("Application is already running");
    }
}

void App::initialize(Poco::Util::Application& self)
{
    // For background initialization
    // Use QEventLoop + QFutureWatcher + QMetaObject::invokeMethod

    AppSplashScreen splash;
    splash.show();

    QEventLoop eventLoop;
    QFutureWatcher<void> watcher;

    watcher.connect(&watcher, &QFutureWatcher<void>::finished, &eventLoop, &QEventLoop::quit);
    watcher.setFuture(QtConcurrent::run([&]()
        {
            // Background initialization...

            auto tp = std::chrono::high_resolution_clock::now();

            if (!AppLicense::check())
            {
                // Switch to UI thread and wait
                QMetaObject::invokeMethod(&splash, "alert", Qt::BlockingQueuedConnection,
                    Q_ARG(const QString&, "tip"),
                    Q_ARG(const QString&, "Bad license !"),
                    Q_ARG(const QString&, "Ok"));
                throw Poco::ApplicationException("Bad application license");
            }

            // Switch to UI thread and wait for UI result
            int ret = QMessageBox::NoButton;
            QVariantMap buttons{ {"Yes", QMessageBox::Ok}, {"No", QMessageBox::Cancel} };
            QMetaObject::invokeMethod(&splash, "question", Qt::BlockingQueuedConnection,
                Q_RETURN_ARG(int, ret),
                Q_ARG(const QString&, "Continue..."),
                Q_ARG(const QString&, "Do you want continue ?"),
                Q_ARG(const QVariantMap&, buttons));
            if (ret != QMessageBox::Ok)
            {
                throw Poco::ApplicationException("User canceled");
            }

            // Set application global properties here
            config().setString("application.about.version", "1.0.0");

            loadConfiguration();
            addSubSystems();
            Poco::Util::Application::initialize(*this);

            // Make sure splash screen shows enough time
            auto elapsed = std::chrono::high_resolution_clock::now() - tp;
            auto wait = std::chrono::seconds(3) - elapsed;
            if (wait.count() > 0)
            {
                std::this_thread::sleep_for(wait);
            }
        }));

    eventLoop.exec();

    try
    {
        watcher.waitForFinished();
    }
    catch (...)
    {
        throw;
    }
}

void App::uninitialize()
{
    Poco::Util::Application::uninitialize();
}

int App::main(const std::vector<std::string>& args)
{
    AppWindow w;
    m_qApp.setActivationWindow(&w);
    w.show();
    return m_qApp.exec();
}

void App::addSubSystems()
{
    auto dir = Poco::Path::forDirectory(config().getString("application.dir")).toString();

    Poco::ClassLoader<CaseManager> caseMgrDLL;
    caseMgrDLL.loadLibrary(dir + "CaseManager.dll");
    auto caseMgr = caseMgrDLL.create("CaseManagerImpl");
    addSubsystem(caseMgr);

    Poco::ClassLoader<TaskManager> taskMgrDLL;
    taskMgrDLL.loadLibrary(dir + "TaskManager.dll");
    auto taskMgr = taskMgrDLL.create("TaskManagerImpl");
    addSubsystem(taskMgr);

    caseMgr->onOpen += Poco::Delegate<TaskManager, const std::string&, false>(taskMgr, &TaskManager::onCaseOpen);
    caseMgr->onClose += Poco::delegate(taskMgr, &TaskManager::onCaseClose);
}
