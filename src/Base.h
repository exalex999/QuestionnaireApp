/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include <iostream>
#include "TypeTracing.h"

// klasa bazowa dla pobrania i wypisywania danych ankietowych
class Describable
{
protected:
  // pozwala przeszukac w hierarchii zarejestrowanych typow wskazany typ, zapyta uzytkownika o wybor klasy bezposredio pochodnej i zwraca instancje klasy Typ dla wybranej klasy
  virtual const Type& askAboutAndGetDerived(const Type &base) const;
public:
  virtual ~Describable() = 0;

  // metoda wypisywania wczesniej pobranych danych w stumien fileStream, w kazdej linii robiac wstepne wciecia prefix
  virtual void getDescription(std::ostream& fileStream, const std::string& prefix) const = 0;
  virtual void setDescription() = 0;
};

#endif // BASE_H_INCLUDED
