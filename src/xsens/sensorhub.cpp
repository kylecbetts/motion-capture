#include "sensorhub.h"
#include "utils.h"

SensorHub::SensorHub(XmeControl *control, QObject *parent)
    : QObject{parent}
{
    m_control = control;
    m_control->addCallbackHandler(this);
}

bool SensorHub::isConnected() const
{
    return m_isConnected;
}

int SensorHub::channel() const
{
    return m_channel;
}

QString SensorHub::id() const
{
    return m_id;
}

QString SensorHub::modelId() const
{
    return m_modelId;
}

QString SensorHub::modelName() const
{
    return m_modelName;
}

void SensorHub::onHardwareError(XmeControl *dev)
{
    if (dev == m_control) {
        sync();
    }
}

void SensorHub::sync()
{
    XmeSuitStatus suitStatus = m_control->status().suitStatus();
    XmeDeviceStatus deviceStatus = suitStatus.m_masterDevice;
    if (deviceStatus.m_validity != XDV_Ok) {
        setisConnected(false);
        return;
    }
    XsDeviceId device = deviceStatus.m_deviceId;
    setisConnected(true);
    setId(Utils::toQString(device.toString()));
    setModelId(Utils::toQString(device.productCode()));
    setModelName(Utils::toQString(device.typeName()));
    setchannel(suitStatus.m_wirelessChannel);
}

void SensorHub::setisConnected(bool newIsConnected)
{
    if (m_isConnected == newIsConnected)
        return;
    m_isConnected = newIsConnected;
    emit isConnectedChanged();
}

void SensorHub::setId(const QString &newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

void SensorHub::setchannel(int newChannel)
{
    if (m_channel == newChannel)
        return;
    m_channel = newChannel;
    emit channelChanged();
}

void SensorHub::setModelId(const QString &newModelId)
{
    if (m_modelId == newModelId)
        return;
    m_modelId = newModelId;
    emit modelIdChanged();
}

void SensorHub::setModelName(const QString &newModelName)
{
    if (m_modelName == newModelName)
        return;
    m_modelName = newModelName;
    emit modelNameChanged();
}
