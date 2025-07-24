#ifndef PATIENTSEARCHFILTER_H
#define PATIENTSEARCHFILTER_H
#include <QString>
#include <QJsonObject>

struct PatientSearchFilter {
    QString name;
    int age;
    QString gender;
    QString diagnosis;
    QString treatment;
    QString imagePath;

    static PatientSearchFilter fromJson(const QJsonObject& obj) {
        PatientSearchFilter f;

        if (obj.contains("name"))
            f.name = obj["name"].toString();
        if (obj.contains("age"))
            f.age = obj["name"].toInt();
        if (obj.contains("gender"))
            f.gender = obj["gender"].toString();
        if (obj.contains("diagnosis"))
            f.diagnosis = obj["diagnosis"].toString();
        if (obj.contains("treatment"))
            f.treatment = obj["treatment"].toString();
        if (obj.contains("treatment"))
            f.imagePath = obj["imagePath"].toString();

        return f;

    }
};

#endif // PATIENTSEARCHFILTER_H
