#ifndef LICENSE_H
#define LICENSE_H

#include <QObject>
#include "xme/xmelicense.h"

class License : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAvailable READ isAvailable CONSTANT)
    Q_PROPERTY(QString type READ type CONSTANT)

public:
    explicit License(QObject *parent = nullptr);

    bool isAvailable() const;
    QString type() const;

private:
    bool m_isAvailable;
    QString m_type;

    XmeLicense *m_license;
};

#endif // LICENSE_H
