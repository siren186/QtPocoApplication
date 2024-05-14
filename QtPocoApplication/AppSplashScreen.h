#pragma once

class AppSplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    AppSplashScreen();

public Q_SLOTS:
    void alert(const QString& title, const QString& text, const QString& buttonText);
    int question(const QString& title, const QString& text, const QVariantMap& buttons);
};
