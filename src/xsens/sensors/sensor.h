#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include "xme/xmedevicestatus.h"

class Sensor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int bodyPartIndex READ bodyPartIndex CONSTANT)
    Q_PROPERTY(QString bodyPartName READ bodyPartName CONSTANT)
    Q_PROPERTY(QString serialNumber READ serialNumber CONSTANT)
    Q_PROPERTY(QString deviceName READ deviceName CONSTANT)
    Q_PROPERTY(int signalStrength READ signalStrength CONSTANT)

public:
    explicit Sensor(const XmeDeviceStatus *deviceStatus, const QString &bodyPartName, QObject *parent = nullptr);

    int bodyPartIndex() const;
    QString bodyPartName() const;
    QString serialNumber() const;
    QString deviceName() const;
    int signalStrength() const;

private:

    int m_bodyPartIndex;
    QString m_bodyPartName;
    QString m_serialNumber;
    QString m_deviceName;
    int m_signalStrength;
};

#endif // SENSOR_H
