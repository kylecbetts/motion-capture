#include "hardware.h"
#include <QDebug>

Hardware::Hardware(XmeControl *control, QObject *parent)
    : QObject{parent}
{
    m_control = control;
    m_control->addCallbackHandler(this);
    m_control->setConfiguration("FullBody");
    m_sensorHub = new SensorHub(m_control);
    m_control->setScanMode(true);
}

void Hardware::onHardwareError(XmeControl *dev)
{
    if (dev == m_control) {
        qInfo() << "Hardware Error";
    }
}

SensorHub * Hardware::sensorHub() const
{
    return m_sensorHub;
}
