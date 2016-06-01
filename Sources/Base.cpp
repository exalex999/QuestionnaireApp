/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#include <stdexcept>
#include "Base.h"

const Type& Describable::askAboutAndGetDerived(const Type &base) const
{
  if(!base.getDerivedTypesNumber()) // nie ma klas pochodnych => wyjatek
    throw NoDerivedTypesException();
  if(base.getDerivedTypesNumber() == 1) // jedna klasa pochodna => nie pytac nic uzytkownika
    return *base.getDerivedTypesConstIterator()->second;
  std::cout << "Select one of the following (1-" << base.getDerivedTypesNumber() + !base.isAbstract() << "):" << std::endl;
  auto derived = base.getDerivedTypesConstIterator();
  for(int i = 1; i <= (int)base.getDerivedTypesNumber(); i++, derived++)
  {
    std::cout << i << ") " << derived->first << std::endl;
  }
  if(!base.isAbstract())  // jesli klasa bazowa nie jest abstrakcyjna, to dac uzytkownikowi mozliwosc nie zaglebiac sie dalej w hierarcjie
    std::cout << base.getDerivedTypesNumber() + 1 << ") no option above is true / I don't want to specify" << std::endl;
  std::string input;
  int selection;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      selection = std::stoi(input);
      if(selection < 1 || selection > (int)base.getDerivedTypesNumber() + !base.isAbstract())
        throw std::invalid_argument("selection");
      break;
    }
    catch(...)
    {
      std::cout << "Invalid selection!" << std::endl;
    }
  }
  if(selection == (int)base.getDerivedTypesNumber() + 1)  // nie zaglebiamy sie dalej w hierarchie
    return base;
  derived = base.getDerivedTypesConstIterator();
  for(int i = 0; i < selection - 1; i++)
    derived++;
  try
  {
    return this->askAboutAndGetDerived(*derived->second); // zaglebiamy sie dalej w hierarchie
  }
  catch(const NoDerivedTypesException&)
  {
    return *derived->second;  // nie ma klas pochodnych => nie zaglebiamy sie dalej
  }
}

Describable::~Describable()
{}
