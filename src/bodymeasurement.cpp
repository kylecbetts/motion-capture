#include "bodymeasurement.h"

BodyMeasurement::BodyMeasurement(const QString &id, const QString &description, QObject *parent)
    : QObject{parent}
{
    m_id = id;
    m_label = toLabel(m_id);
    m_description = description;
}

QString BodyMeasurement::id() const
{
    return m_id;
}

QString BodyMeasurement::label() const
{
    return m_label;
}

QString BodyMeasurement::description() const
{
    return m_description;
}

QString BodyMeasurement::toLabel(const QString &id)
{
    if (id.isEmpty()) {
        return id;
    }
    QString label;
    label += id[0].toUpper();
    for (int i = 1; i < id.length(); ++i) {
        QChar currentChar = id[i];
        if (currentChar.isUpper()) {
            label += ' ';
        }
        label += currentChar;
    }
    return label;
}
