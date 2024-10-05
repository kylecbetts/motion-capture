#ifndef XSENSCONTROLLER_H
#define XSENSCONTROLLER_H

#include <QObject>
#include <QStringList>
#include <QQmlEngine>
#include "xme.h"

class XsensController : public QObject, public XmeCallback
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString licenseName READ licenseName FINAL CONSTANT)
    Q_PROPERTY(QString version READ version FINAL CONSTANT)
    Q_PROPERTY(QObjectList bodyMeasurements READ bodyMeasurements FINAL CONSTANT)

public:
    explicit XsensController(QObject *parent = nullptr);

    QString licenseName() const;
    QString version() const;

    QObjectList bodyMeasurements() const;

private:
    QString toQString(const XsString& xsString);
    void initializeBodyMeasurements();

    XmeLicense *m_license;
    XmeControl *m_control;
    QString m_licenseName;
    QString m_version;
    QObjectList m_bodyMeasurements;
};

#endif // XSENSCONTROLLER_H
