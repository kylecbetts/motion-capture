#ifndef SENSORHUB_H
#define SENSORHUB_H

#include <QObject>
#include "xstypes/xsdeviceid.h"

class SensorHub : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString serialNumber READ serialNumber CONSTANT)
    Q_PROPERTY(QString deviceId READ deviceId CONSTANT)
    Q_PROPERTY(QString deviceName READ deviceName CONSTANT)

public:
    explicit SensorHub(const XsDeviceId *device, QObject *parent = nullptr);

    QString serialNumber() const;
    QString deviceId() const;
    QString deviceName() const;

private:

    QString m_serialNumber;
    QString m_deviceId;
    QString m_deviceName;
};

#endif // SENSORHUB_H
