#ifndef XSENSSYSTEM_H
#define XSENSSYSTEM_H

#include <QObject>
#include <QQmlEngine>
#include "xme/xmecontrol.h"
#include "xme/xmelicense.h"

#include "sensors.h"

class XsensSystem : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString sdkVersion READ sdkVersion CONSTANT)
    Q_PROPERTY(QString licenseName READ licenseName CONSTANT)
    Q_PROPERTY(Sensors * sensors READ sensors CONSTANT)

public:
    explicit XsensSystem(QObject *parent = nullptr);

    QString sdkVersion() const;
    QString licenseName() const;

    Sensors *sensors() const;

private:
    void initializeLicense();
    void initializeControl();
    void initializeSdkVersion();
    void initializeComponents();

    QString m_sdkVersion;
    QString m_licenseName;
    Sensors *m_sensors = nullptr;

    XmeLicense *m_license;
    XmeControl *m_control;
};

#endif // XSENSSYSTEM_H
