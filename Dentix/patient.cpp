#include "patient.h"

Patient::Patient()
    : name(""), gender(""), age(0), diagnosis(""), treatment(""), imagePath(""), doctorNote("") {}

Patient::Patient(const QString& name, const QString& gender, int age,
                 const QString& diagnosis, const QString& treatment, const QString& imagePath, const QString& doctorNote)
    : name(name), gender(gender), age(age), diagnosis(diagnosis), treatment(treatment), imagePath(imagePath), doctorNote(doctorNote) {}

QString Patient::getName() const { return name; }
QString Patient::getGender() const { return gender; }
int Patient::getAge() const { return age; }
QString Patient::getDiagnosis() const { return diagnosis; }
QString Patient::getTreatment() const { return treatment; }
QString Patient::getImagePath() const { return imagePath; }
QString Patient::getDoctorNote() const { return doctorNote; }

void Patient::setName(const QString& newName) { name = newName; }
void Patient::setGender(const QString& newGender) { gender = newGender; }
void Patient::setAge(int newAge) { age = newAge; }
void Patient::setDiagnosis(const QString& newDiagnosis) { diagnosis = newDiagnosis; }
void Patient::setTreatment(const QString& newTreatment) { treatment = newTreatment; }
void Patient::setImagePath(const QString& newPath) { imagePath = newPath; }
void Patient::setDoctorNote(const QString& newNote) { doctorNote = newNote; }


QJsonObject Patient::toJson() const {
    QJsonObject obj;
    obj["name"] = name;
    obj["gender"] = gender;
    obj["age"] = age;
    obj["diagnosis"] = diagnosis;
    obj["treatment"] = treatment;
    obj["imagePath"] = imagePath;
    obj["doctorNote"] = doctorNote;
    return obj;
}

Patient Patient::fromJson(const QJsonObject& obj) {
    QString name = obj["name"].toString();
    QString gender = obj["gender"].toString();
    int age = obj["age"].toInt();
    QString diagnosis = obj["diagnosis"].toString();
    QString treatment = obj["treatment"].toString();
    QString imagePath = obj["imagePath"].toString();
    QString doctorNote = obj["doctorNote"].toString();

    return Patient(name, gender, age, diagnosis, treatment, imagePath, doctorNote);
}
