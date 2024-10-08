#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include "xme/xmedevicestatus.h"

class Sensor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString serialNumber READ serialNumber NOTIFY serialNumberChanged)
public:
    explicit Sensor(const XmeDeviceStatus *deviceStatus, QObject *parent = nullptr);

    QString serialNumber() const;
    void setserialNumber(const QString &newSerialNumber);

signals:
    void serialNumberChanged();
private:
    QString m_serialNumber;
};

#endif // SENSOR_H
