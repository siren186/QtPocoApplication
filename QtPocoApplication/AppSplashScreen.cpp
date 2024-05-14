#include "stdafx.h"
#include "AppSplashScreen.h"

AppSplashScreen::AppSplashScreen()
{
    QPixmap pixmap(qApp->applicationDirPath() + "\\resources\\images\\appsplashscreen.png");
    setPixmap(pixmap);
}

void AppSplashScreen::alert(const QString& title, const QString& text, const QString& buttonText)
{
    QMessageBox box(QMessageBox::Warning, title, text, QMessageBox::Ok, this);
    box.setButtonText(QMessageBox::Ok, buttonText);
    box.exec();
}

int AppSplashScreen::question(const QString& title, const QString& text, const QVariantMap& buttons)
{
    QMessageBox::StandardButtons flags = QMessageBox::NoButton;
    for (auto it = buttons.begin(); it != buttons.end(); ++it)
    {
        flags |= (QMessageBox::StandardButton)it.value().toUInt();
    }

    QMessageBox box(QMessageBox::Question, title, text, QMessageBox::NoButton, this);
    box.setStandardButtons(flags);

    for (auto it = buttons.begin(); it != buttons.end(); ++it)
    {
        box.setButtonText((QMessageBox::StandardButton)it.value().toUInt(), it.key());
    }

    return box.exec();
}
