/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#ifndef MARITALSTATUSANDRELATED_H_INCLUDED
#define MARITALSTATUSANDRELATED_H_INCLUDED

#include "Base.h"
#include "Date.h"

class MaritalStatus;
class Single;
class Married;

class MaritalStatus : public Describable, public Cloneable
{
private:
  static std::string typeName;

  std::list<std::string> children;
  bool payingAlimony;
  double alimony;
public:
  static void initialize();
  static std::string getTypeName();

  ~MaritalStatus();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const = 0;
  void setDescription() = 0;
};

class Single : public MaritalStatus
{
private:
  static std::string typeName;

  bool ifMarriedBefore;
public:
  static void initialize();
  static std::string getTypeName();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

class Married : public MaritalStatus
{
private:
  static std::string typeName;

  std::string spouse;
  Date *weddingDate;
public:
  static void initialize();
  static std::string getTypeName();

  ~Married();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

#endif // MARITALSTATUSANDRELATED_H_INCLUDED
