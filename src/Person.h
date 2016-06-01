/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include "MaritalStatusAndRelated.h"
#include "ProfessionAndRelated.h"
#include "HobbyAndRelated.h"
#include "Date.h"

class Person : public Describable
{
private:
  std::string firstName;
  std::string lastName;
  Date *birthday;
  MaritalStatus *maritalStatus;
  Profession *profession;
  std::list<Hobby*> hobbies;
public:
  ~Person();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
};

#endif // PERSON_H_INCLUDED
