#include "stdafx.h"
#include "AppWindow.h"

AppWindow::AppWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.actionOpen, &QAction::triggered, this, &AppWindow::onMenuOpen);
    connect(ui.actionClose, &QAction::triggered, this, &AppWindow::onMenuClose);
    connect(ui.actionNotify, &QAction::triggered, this, &AppWindow::onMenuNotify);
    connect(ui.actionQuitApp, &QAction::triggered, this, &AppWindow::onMenuQuitApp);

    // Global notification center
    Poco::NotificationCenter::defaultCenter().addObserver(Poco::NObserver<AppWindow, Notif::TaskResult>(*this, &AppWindow::onTaskResult));
}

AppWindow::~AppWindow()
{}

void AppWindow::onMenuOpen(bool)
{
    poco_information(Poco::Util::Application::instance().logger(), "onMenuOpen()");
    QString fileName = QFileDialog::getOpenFileName(this);
    if (fileName.isEmpty())
    {
        return;
    }

    auto& mgr = Poco::Util::Application::instance().getSubsystem<CaseManager>();
    mgr.open(fileName.toStdString().c_str());
}

void AppWindow::onMenuClose(bool)
{
    poco_information(Poco::Util::Application::instance().logger(), "onMenuClose()");
    auto& mgr = Poco::Util::Application::instance().getSubsystem<CaseManager>();
    mgr.close();
}

void AppWindow::onMenuNotify(bool)
{
    poco_information(Poco::Util::Application::instance().logger(), "onMenuClose()");
    auto& mgr = Poco::Util::Application::instance().getSubsystem<TaskManager>();
    mgr.runInBackground(10);
}

void AppWindow::onMenuQuitApp(bool)
{
    QMessageBox box(QMessageBox::Question, "Tip", "Quit ?", QMessageBox::Ok | QMessageBox::Cancel, this);
    if (QMessageBox::Ok != box.exec())
    {
        return;
    }

    QProgressDialog dialog("", nullptr, 0, 0, this);
    dialog.setWindowTitle("Quitting...");
    QFutureWatcher<void> watcher;
    connect(&watcher, &QFutureWatcher<void>::finished, &dialog, &QProgressDialog::accept);
    watcher.setFuture(QtConcurrent::run([&]()
        {
            Poco::Util::Application::instance().getSubsystem<CaseManager>().close();
            Poco::Thread::sleep(3000);
        }));
    dialog.exec();
    close();
}

void AppWindow::onTaskResult(const Poco::AutoPtr<Notif::TaskResult>& pNf)
{
    // Attention: This is running in notification sender thread...
    // Do not visit UI widgets
    poco_information(Poco::Util::Application::instance().logger(), "onTaskResult()");
    auto& m = pNf->getMap();
}
