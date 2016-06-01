/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#ifndef PROFESSIONANDRELATED_H_INCLUDED
#define PROFESSIONANDRELATED_H_INCLUDED

#include "Base.h"

class Profession;
class Student;
class Clergyman;
class Businessman;
class Employee;
class Programmer;
class Sportsman;
class Translator;

enum class DegreeLevels
{
  BACHELOR, MASTER, DOCTOR
};
extern std::map<DegreeLevels, std::string> degreeLevelsStrings;

enum class Religions
{
  CHRISTIANITY, ISLAM, HINDUISM, BUDDHISM, FOLKRELIGION
};
extern std::map<Religions, std::string> religionsStrings;

class Profession : public Describable, public Cloneable
{
private:
  static std::string typeName;

  double professionalActivityDuration;  // years
  std::string workplaceAdress;
  std::list<std::string> foreignLanguages;
public:
  static void initialize();
  static std::string getTypeName();

  ~Profession();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const = 0;
  void setDescription() = 0;
};

class Student : public Profession
{
private:
  static std::string typeName;

  std::string highSchool;
  std::string faculty;
  std::string speciality;
  DegreeLevels levelOfStudies;
  int enrollmentYear;
  int semester;
  int expectedGraduationYear;
  int averageMark;
public:
  static void initialize();
  static std::string getTypeName();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

class Clergyman : public Profession
{
private:
  static std::string typeName;

  Religions religion;
  std::string placeOfWorship;
  std::string ecclesiasticalAddress;
public:
  static void initialize();
  static std::string getTypeName();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

class Businessman : public Profession
{
private:
  static std::string typeName;

  std::string organization;
  std::string branch;
  std::string organizationActivityDescription;
  int employeeNumber;
  int averageProfit;
  int averageEmployeeSalary;
public:
  static void initialize();
  static std::string getTypeName();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

class Employee : public Profession
{
private:
  static std::string typeName;

  std::string organization;
  std::string position;
  std::string education;
  std::list<std::string> additionalSkills;
  int salary;
public:
  static void initialize();
  static std::string getTypeName();

  ~Employee();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

class Programmer : public Employee
{
private:
  static std::string typeName;

  std::list<std::string> primaryTechnologies; // bezposrednio wykorzystywane w pracy
  std::list<std::string> additionalTechnologies; // dodatkowe znane przez programiste
public:
  static void initialize();
  static std::string getTypeName();

  ~Programmer();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

class Sportsman : public Employee
{
private:
  static std::string typeName;

  std::string kindOfSport;
  std::list<std::string> achievements;
public:
  static void initialize();
  static std::string getTypeName();

  ~Sportsman();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

class Translator : public Employee
{
private:
  static std::string typeName;

  std::list<std::string> languages;
public:
  static void initialize();
  static std::string getTypeName();

  ~Translator();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

#endif // PROFESSIONANDRELATED_H_INCLUDED
