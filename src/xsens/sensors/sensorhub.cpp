#include "sensorhub.h"
#include <QDebug>
#include "utils.h"

SensorHub::SensorHub(const XsDeviceId *device, QObject *parent)
    : QObject{parent}
{
    if (device == nullptr) {
        throw std::runtime_error("Fatal Error: nullptr passed as XsDeviceId.");
    }
    m_serialNumber = Utils::toQString(device->toString());
    m_deviceId = Utils::toQString(device->productCode());
    m_deviceName = Utils::toQString(device->typeName());
}

QString SensorHub::serialNumber() const
{
    return m_serialNumber;
}

QString SensorHub::deviceId() const
{
    return m_deviceId;
}

QString SensorHub::deviceName() const
{
    return m_deviceName;
}
