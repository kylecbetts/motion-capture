#include "sensors.h"
#include <QDebug>
#include "utils.h"
#include "sensor.h"

Sensors::Sensors(XmeControl *control, QObject *parent)
    : QObject{parent}
{
    initializeControl(control);
    initializeArrangementOptions();
    initializeCurrentArrangement();
}

bool Sensors::allConnected() const
{
    return m_allConnected;
}

SensorHub *Sensors::sensorHub() const
{
    return m_sensorHub;
}

int Sensors::wirelessChannel() const
{
    return m_wirelessChannel;
}

QString Sensors::currentArrangement() const
{
    return m_currentArrangement;
}

QVariantMap Sensors::requiredSensors() const
{
    return m_requiredSensors;
}

void Sensors::requestCurrentArrangementChange(const QString &newCurrentArrangement)
{
    if (!m_arrangementOptions.contains(newCurrentArrangement)) {
        return;
    }
    m_control->setConfiguration(Utils::toXsString(newCurrentArrangement));
}

void Sensors::requestPowerOffDevices()
{
    m_control->switchOffHardware();
}

void Sensors::onConfigurationChangeComplete(XmeControl *dev)
{
    if (dev != m_control) {
        return;
    }
    qInfo() << "Configuration Change Complete.";
    setCurrentArrangement();
}

void Sensors::onConfigurationChangeFailed(XmeControl *dev)
{
    if (dev != m_control) {
        return;
    }
    qInfo() << "Configuration Change Failed.";
}

void Sensors::onHardwareDisconnected(XmeControl *dev)
{
    if (dev != m_control) {
        return;
    }
    qInfo() << "Hardware Disconnected.";
    updateState();
    setAllConnected(false);
}

void Sensors::onHardwareError(XmeControl *dev)
{
    if (dev != m_control) {
        return;
    }
    qInfo() << "Hardware Error.";
    updateState();
    setAllConnected(false);
}

void Sensors::onHardwareReady(XmeControl *dev)
{
    if (dev != m_control) {
        return;
    }
    qInfo() << "Hardware Ready.";
    updateState();
    setAllConnected(true);
}

void Sensors::onHardwareWarning(XmeControl *dev, XsResultValue resultValue, const XsString *additionalMessage)
{
    if (dev != m_control) {
        return;
    }
    qInfo() << "Hardware Warning " << resultValue << ": " << Utils::toQString(*additionalMessage) << ".";
}

void Sensors::onLowBatteryLevel(XmeControl *dev)
{
    if (dev != m_control) {
        return;
    }
    qInfo() << "Low Battery.";
}

void Sensors::updateState()
{
    const XmeStatus status = m_control->status();
    const XmeSuitStatus *suitStatus = &status.suitStatus();
    setWirelessChannel(suitStatus->m_wirelessChannel);
    updateSensorHub(&suitStatus->m_masterDevice);
    updateSensors(suitStatus);
}

void Sensors::updateSensorHub(const XmeDeviceStatus *deviceStatus)
{
    if (deviceStatus->m_validity != XDV_Ok) {
        setSensorHub(nullptr);
        return;
    }
    const XsDeviceId *device = &deviceStatus->m_deviceId;
    SensorHub *sensorHub = new SensorHub(device);
    setSensorHub(sensorHub);
}

void Sensors::updateSensors(const XmeSuitStatus *suitStatus)
{
    if (m_sensorHub == nullptr) {
        for (auto i = m_requiredSensors.cbegin(), end = m_requiredSensors.cend(); i != end; ++i) {
            m_requiredSensors.insert(i.key(), QVariant());
        }
        emit requiredSensorsChanged();
        return;
    }
    XmeDeviceStatusArray connectedDevices = suitStatus->m_sensors;
    for (XsSize i = 0; i < connectedDevices.size(); i++) {
        XmeDeviceStatus *deviceStatus = &connectedDevices.at(i);
        int segmentId = deviceStatus->m_segmentId;
        QString segmentName = Utils::toQString(m_control->segmentName(segmentId));
        Sensor *sensor = new Sensor(deviceStatus, segmentName);
        m_requiredSensors.insert(QString::number(segmentId), QVariant::fromValue(sensor));
    }
    XsIntArray missingSegments = suitStatus->m_missingSensors;
    for (XsSize i = 0; i < missingSegments.size(); i++) {
        QString segmentId = QString::number(missingSegments.at(i));
        m_requiredSensors.insert(segmentId, QVariant());
    }
    emit requiredSensorsChanged();
}


void Sensors::setAllConnected(bool newAllConnected)
{
    if (m_allConnected == newAllConnected)
        return;
    m_allConnected = newAllConnected;
    emit allConnectedChanged();
}

void Sensors::setSensorHub(SensorHub *newSensorHub)
{
    if (m_sensorHub == newSensorHub)
        return;
    m_sensorHub = newSensorHub;
    emit sensorHubChanged();
}

void Sensors::setWirelessChannel(int newWirelessChannel)
{
    if (m_wirelessChannel == newWirelessChannel)
        return;
    m_wirelessChannel = newWirelessChannel;
    emit wirelessChannelChanged();
}

void Sensors::setCurrentArrangement()
{
    QString newCurrentArrangement = Utils::toQString(m_control->configuration());
    if (m_currentArrangement == newCurrentArrangement)
        return;
    m_currentArrangement = newCurrentArrangement;
    emit currentArrangementChanged();
    setRequiredSensors();
    m_control->setScanMode(true);
}

void Sensors::setRequiredSensors()
{
    QVariantMap newRequiredSensors;
    XsString xsCurrentArrangement = Utils::toXsString(m_currentArrangement);
    XsIntArray segmentIds = m_control->sensorSegmentsForConfiguration(xsCurrentArrangement);
    for (XsSize i = 0; i < segmentIds.size(); i++) {
        QString segmentId = QString::number(segmentIds.at(i));
        newRequiredSensors.insert(segmentId, QVariant());
    }
    m_requiredSensors = newRequiredSensors;
    emit requiredSensorsChanged();
}

void Sensors::initializeControl(XmeControl *control)
{
    m_control = control;
    m_control->addCallbackHandler(this);
}

void Sensors::initializeArrangementOptions()
{
    XsStringArray arrangements = m_control->configurationList();
    for (XsSize i = 0; i < arrangements.size(); i++) {
        QString arrangement = Utils::toQString(arrangements.at(i));
        m_arrangementOptions.insert(arrangement);
    }
}

void Sensors::initializeCurrentArrangement()
{
    XsStringArray arrangements = m_control->configurationList();
    if (arrangements.size() < 1) {
        throw std::runtime_error("Fatal Error: No sensor arrangements available.");
    }
    requestCurrentArrangementChange(Utils::toQString(arrangements.at(0)));
}


