#ifndef BODYMEASUREMENT_H
#define BODYMEASUREMENT_H

#include <QObject>

class BodyMeasurement : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id FINAL CONSTANT)
    Q_PROPERTY(QString label READ label FINAL CONSTANT)
    Q_PROPERTY(QString description READ description FINAL CONSTANT)

public:
    explicit BodyMeasurement(const QString &id, const QString &description, QObject *parent = nullptr);

    QString id() const;
    QString label() const;
    QString description() const;

private:
    QString toLabel(const QString &id);

    QString m_id;
    QString m_label;
    QString m_description;
};

#endif // BODYMEASUREMENT_H
