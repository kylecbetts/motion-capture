#include "xsenssystem.h"
#include "utils.h"

XsensSystem::XsensSystem(QObject *parent)
    : QObject{parent}
{
    m_license = new License();
    m_control = XmeControl::construct();
    XsString xsVersion = m_control->version().toSimpleString();
    m_version = Utils::toQString(xsVersion);
    m_hardware = new Hardware(m_control);
}

License *XsensSystem::license() const
{
    return m_license;
}

QString XsensSystem::version() const
{
    return m_version;
}

Hardware *XsensSystem::hardware() const
{
    return m_hardware;
}
