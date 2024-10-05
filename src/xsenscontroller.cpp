#include "xsenscontroller.h"
#include "bodymeasurement.h"

XsensController::XsensController(QObject *parent)
    : QObject{parent}
{
    m_license = new XmeLicense();
    m_licenseName = toQString(m_license->getCurrentLicense());
    m_version = toQString(XmeControl::version().toSimpleString());
    m_control = XmeControl::construct();
    m_control->addCallbackHandler(this);
    initializeBodyMeasurements();
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

void XsensController::initializeBodyMeasurements()
{
    XsStringArray xsIds = m_control->bodyDimensionLabelList();
    for (XsSize i = 0; i < xsIds.size(); i++) {
        XsString xsId = xsIds.at(i);
        QString id = toQString(xsId);
        XsString xsDescription = m_control->bodyDimensionDescription(xsId);
        QString description = toQString(xsDescription);
        BodyMeasurement *measurement = new BodyMeasurement(id, description);
        m_bodyMeasurements.append(measurement);
    }
}

QString XsensController::version() const
{
    return m_version;
}

QObjectList XsensController::bodyMeasurements() const
{
    return m_bodyMeasurements;
}
