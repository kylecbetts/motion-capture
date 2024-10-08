#ifndef XSENSSYSTEM_H
#define XSENSSYSTEM_H

#include <QObject>
#include <QQmlEngine>
#include "xme/xmecontrol.h"
#include "motioncapturesystem.h"
#include "license.h"
#include "sensors.h"

class XsensSystem : public QObject, public MotionCaptureSystem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString version READ version CONSTANT)

public:
    explicit XsensSystem(QObject *parent = nullptr);

    QString version() const;

public slots:
    License *license();
    Sensors *sensors();

private:
    void initializeLicense();
    void initializeVersion();

    License *m_license;
    XmeControl *m_control;
    QString m_version;
    Sensors *m_sensors;
};

#endif // XSENSSYSTEM_H
