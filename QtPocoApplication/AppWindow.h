#pragma once
#include "ui_QtPocoApplication.h"

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    AppWindow(QWidget *parent = nullptr);
    ~AppWindow();

private Q_SLOTS:
    void onMenuOpen(bool);
    void onMenuClose(bool);
    void onMenuNotify(bool);
    void onMenuQuitApp(bool);

private:
    void onTaskResult(const Poco::AutoPtr<Notif::TaskResult>& pNf);

private:
    Ui::QtPocoApplicationClass ui;
};
