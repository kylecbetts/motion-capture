#include "sensor.h"

Sensor::Sensor(const XmeDeviceStatus *deviceStatus, QObject *parent)
    : QObject{parent}
{}

QString Sensor::serialNumber() const
{
    return m_serialNumber;
}

void Sensor::setserialNumber(const QString &newSerialNumber)
{
    if (m_serialNumber == newSerialNumber)
        return;
    m_serialNumber = newSerialNumber;
    emit serialNumberChanged();
}
