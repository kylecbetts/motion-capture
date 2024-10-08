#include "xsenssystem.h"
#include "utils.h"

XsensSystem::XsensSystem(QObject *parent)
    : QObject{parent}
{
    initializeLicense();
    m_control = XmeControl::construct();
    initializeVersion();
    m_sensors = new Sensors(m_control);
}

QString XsensSystem::version() const
{
    return m_version;
}

License *XsensSystem::license()
{
    return m_license;
}

Sensors *XsensSystem::sensors()
{
    return m_sensors;
}

void XsensSystem::initializeLicense()
{
    m_license = new License();
    if (!m_license->isAvailable()) {
        throw std::runtime_error("Fatal Error: Xsens license cannot be used.");
    }
}

void XsensSystem::initializeVersion()
{
    XsString xsVersion = m_control->version().toSimpleString();
    m_version = Utils::toQString(xsVersion);
}
