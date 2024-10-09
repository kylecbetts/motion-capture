#include "sensor.h"
#include "utils.h"
#include <QDebug>

Sensor::Sensor(const XmeDeviceStatus *deviceStatus, const QString &bodyPartName, QObject *parent)
    : QObject{parent}
{
    if (deviceStatus == nullptr) {
        throw std::runtime_error("Fatal Error: nullptr passed as XmeDeviceStatus.");
    }
    const XsDeviceId *device = &deviceStatus->m_deviceId;
    m_bodyPartIndex = deviceStatus->m_segmentId;
    m_bodyPartName = bodyPartName;
    m_serialNumber = Utils::toQString(device->toString());
    m_deviceName = Utils::toQString(device->typeName());
    m_signalStrength = deviceStatus->m_radioQuality;
}

int Sensor::bodyPartIndex() const
{
    return m_bodyPartIndex;
}

QString Sensor::bodyPartName() const
{
    return m_bodyPartName;
}

QString Sensor::serialNumber() const
{
    return m_serialNumber;
}

QString Sensor::deviceName() const
{
    return m_deviceName;
}

int Sensor::signalStrength() const
{
    return m_signalStrength;
}
