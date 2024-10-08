#ifndef SENSORS_H
#define SENSORS_H

#include <QObject>
#include <QSet>
#include "xme/xmecallback.h"
#include "xme/xmecontrol.h"
#include "sensorhub.h"

class Sensors : public QObject, public XmeCallback
{
    Q_OBJECT
    Q_PROPERTY(SensorHub *sensorHub READ sensorHub NOTIFY sensorHubChanged)
    Q_PROPERTY(int wirelessChannel READ wirelessChannel NOTIFY wirelessChannelChanged)
    Q_PROPERTY(QString currentArrangement READ currentArrangement NOTIFY currentArrangementChanged)

public:
    explicit Sensors(XmeControl *control, QObject *parent = nullptr);

    SensorHub *sensorHub() const;
    int wirelessChannel() const;
    QString currentArrangement() const;

public slots:
    void requestCurrentArrangementChange(const QString &newCurrentArrangement);

signals:
    void sensorHubChanged();
    void wirelessChannelChanged();
    void currentArrangementChanged();

protected:
    void onConfigurationChangeComplete(XmeControl *dev) override;
    void onConfigurationChangeFailed(XmeControl *dev) override;
    void onHardwareDisconnected(XmeControl *dev) override;
    void onHardwareError(XmeControl *dev) override;
    void onHardwareReady(XmeControl *dev) override;
    void onHardwareWarning(XmeControl *dev, XsResultValue resultValue, XsString const *additionalMessage) override;
    void onLowBatteryLevel(XmeControl *dev) override;

private:
    void updateState();
    void updateSensorHub(const XmeDeviceStatus *deviceStatus);

    void setSensorHub(SensorHub *newSensorHub);
    void setWirelessChannel(int newWirelessChannel);
    void setCurrentArrangement();

    void initializeControl(XmeControl *control);
    void initializeArrangementOptions();
    void initializeCurrentArrangement();

    XmeControl *m_control;
    SensorHub *m_sensorHub = nullptr;
    int m_wirelessChannel;
    QSet<QString> m_arrangementOptions;
    QString m_currentArrangement;
};

#endif // SENSORS_H
