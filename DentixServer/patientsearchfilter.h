#ifndef PATIENTSEARCHFILTER_H
#define PATIENTSEARCHFILTER_H
#include <QString>
#include <QJsonObject>

struct PatientSearchFilter {
    QString name;
    QString gender;
    QString diagnosis;
    QString treatment;

    static PatientSearchFilter fromJson(const QJsonObject& obj) {
        PatientSearchFilter f;

        if (obj.contains("name"))
            f.name = obj["name"].toString();

        if (obj.contains("gender"))
            f.gender = obj["gender"].toString();

        if (obj.contains("diagnosis"))
            f.diagnosis = obj["diagnosis"].toString();

        if (obj.contains("treatment"))
            f.treatment = obj["treatment"].toString();

        return f;
    }
};

#endif // PATIENTSEARCHFILTER_H
