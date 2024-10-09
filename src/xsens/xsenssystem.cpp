#include "xsenssystem.h"
#include "utils.h"

XsensSystem::XsensSystem(QObject *parent)
    : QObject{parent}
{
    initializeLicense();
    initializeControl();
    initializeSdkVersion();
    initializeComponents();
}

QString XsensSystem::sdkVersion() const
{
    return m_sdkVersion;
}

QString XsensSystem::licenseName() const
{
    return m_licenseName;
}

Sensors *XsensSystem::sensors() const
{
    return m_sensors;
}

void XsensSystem::initializeLicense()
{
    m_license = new XmeLicense();
    if (!XmeLicense::isConstructed()) {
        throw std::runtime_error("Fatal Error: Xsens license not initialized.");
    }
    if (!XmeLicense::isLicenseAvailable()) {
        throw std::runtime_error("Fatal Error: Xsens license cannot be used.");
    }
    m_licenseName = Utils::toQString(XmeLicense::getCurrentLicense());
}

void XsensSystem::initializeControl()
{
    if (!m_license) {
        throw std::runtime_error("Fatal Error: Xsens license not initialized.");
    }
    m_control = XmeControl::construct();
}

void XsensSystem::initializeSdkVersion()
{
    if (!m_control) {
        throw std::runtime_error("Fatal Error: Xsens control not initialized.");
    }
    m_sdkVersion = Utils::toQString(m_control->version().toSimpleString());
}

void XsensSystem::initializeComponents()
{
    if (!m_control) {
        throw std::runtime_error("Fatal Error: Xsens control not initialized.");
    }
    m_sensors = new Sensors(m_control);
}
