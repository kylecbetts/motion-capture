#ifndef SENSORHUB_H
#define SENSORHUB_H

#include <QObject>
#include "xme/xmecallback.h"
#include "xme/xmecontrol.h"

class SensorHub : public QObject, public XmeCallback
{
    Q_OBJECT
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY isConnectedChanged)
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(int channel READ channel NOTIFY channelChanged)
    Q_PROPERTY(QString modelId READ modelId NOTIFY modelIdChanged)
    Q_PROPERTY(QString modelName READ modelName NOTIFY modelNameChanged)

public:
    explicit SensorHub(XmeControl *control, QObject *parent = nullptr);

    bool isConnected() const;
    QString id() const;
    int channel() const;
    QString modelId() const;
    QString modelName() const;

signals:
    void isConnectedChanged();
    void idChanged();
    void channelChanged();
    void modelIdChanged();
    void modelNameChanged();

protected:
    void onHardwareError(XmeControl *dev) override;

private:
    void sync();

    void setisConnected(bool newIsConnected);
    void setId(const QString &newId);
    void setchannel(int newChannel);
    void setModelId(const QString &newModelId);
    void setModelName(const QString &newModelName);

    bool m_isConnected;
    QString m_id;
    int m_channel;
    QString m_modelId;
    QString m_modelName;

    XmeControl *m_control;
};

#endif // SENSORHUB_H
