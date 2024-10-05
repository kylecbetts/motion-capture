#ifndef HARDWARE_H
#define HARDWARE_H

#include <QObject>
#include "sensorhub.h"
#include "xme/xmecallback.h"
#include "xme/xmecontrol.h"

class Hardware : public QObject, XmeCallback
{
    Q_OBJECT
    Q_PROPERTY(SensorHub *sensorHub READ sensorHub CONSTANT)

public:
    explicit Hardware(XmeControl *control, QObject *parent = nullptr);

    SensorHub *sensorHub() const;

protected:
    void onHardwareError(XmeControl *dev) override;

private:
    XmeControl *m_control;
    SensorHub *m_sensorHub;
};

#endif // HARDWARE_H
