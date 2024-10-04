#include "xsenscontroller.h"

XsensController::XsensController(QObject *parent)
    : QObject{parent}
{
    m_license = new XmeLicense();
    m_licenseName = toQString(m_license->getCurrentLicense());
    m_version = toQString(XmeControl::version().toSimpleString());
    m_control = XmeControl::construct();
    m_control->addCallbackHandler(this);
    m_control->setConfiguration("FullBody");
    m_control->setScanMode(true);
}

QString XsensController::licenseName() const
{
    return m_licenseName;
}

QString XsensController::toQString(const XsString &xsString)
{
    std::string stdString = xsString.toStdString();
    QString qString = QString::fromStdString(stdString);
    return qString;
}

QString XsensController::version() const
{
    return m_version;
}
