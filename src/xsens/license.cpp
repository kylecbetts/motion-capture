#include "license.h"
#include "utils.h"
#include <QDebug>

License::License(QObject *parent)
    : QObject{parent}
{
    m_license = new XmeLicense();
    if (!XmeLicense::isConstructed()) {
        throw std::runtime_error("Fatal Error: Xsens license not initialized.");
    }
    m_isAvailable = XmeLicense::isLicenseAvailable();
    XsString xsType = XmeLicense::getCurrentLicense();
    m_type = Utils::toQString(xsType);
}

bool License::isAvailable() const
{
    return m_isAvailable;
}

QString License::type() const
{
    return m_type;
}
