#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QJsonObject>

class Patient
{
public:
    Patient();
    Patient(const QString& name,
            const QString& gender,
            int age,
            const QString& diagnosis,
            const QString& treatment,
            const QString& imagePath,
            const QString& doctorNote);

    QString getName() const;
    QString getGender() const;
    int getAge() const;
    QString getDiagnosis() const;
    QString getTreatment() const;
    QString getImagePath() const;
    QString getDoctorNote() const;

    void setName(const QString& name);
    void setGender(const QString& gender);
    void setAge(int age);
    void setDiagnosis(const QString& diagnosis);
    void setTreatment(const QString& treatment);
    void setImagePath(const QString& path);
    void setDoctorNote(const QString& note);

    QJsonObject toJson() const;
    static Patient fromJson(const QJsonObject& obj);

private:
    QString name;       //이름
    QString gender;     //성별
    int age;            //나이
    QString diagnosis;  //진단
    QString treatment;  //치료
    QString imagePath;  //이미지 path(ftp쓸건지말건지...)
    QString doctorNote; //의사 소견
};

#endif // PATIENT_H
