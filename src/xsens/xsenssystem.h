#ifndef XSENSSYSTEM_H
#define XSENSSYSTEM_H

#include <QObject>
#include <QQmlEngine>
#include "xme/xmecontrol.h"
#include "motioncapturesystem.h"
#include "license.h"
#include "hardware.h"

class XsensSystem : public QObject, public MotionCaptureSystem
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(License * license READ license CONSTANT)
    Q_PROPERTY(QString version READ version CONSTANT)
    Q_PROPERTY(Hardware * hardware READ hardware CONSTANT)

public:
    explicit XsensSystem(QObject *parent = nullptr);

    License *license() const;
    Hardware *hardware() const;

    QString version() const;

private:
    License *m_license;
    Hardware *m_hardware;

    XmeControl *m_control;
    QString m_version;
};

#endif // XSENSSYSTEM_H
