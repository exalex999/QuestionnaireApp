/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#include "TypeTracing.h"
#include <stdexcept>

TypeTracer hierarchy;

Cloneable::~Cloneable()
{}

Type::Type(Cloneable *instance, bool ifAbstract) : instance(instance), ifAbstract(ifAbstract)
{
  if(!((bool)instance ^ ifAbstract))  // albo typ dodawany musi byc abstrakcyjny (a wiec nie miec wlasnej przykladowej instancji), albo typ jest konkretny i musi miec wlasna przykladowa instancje
    throw std::invalid_argument("Pointer to the type instance must be non-zero and the type must be concrete at the same time or vice versa.");
}
Type::~Type()
{
  delete this->instance;
  this->derivedTypes.clear();
}
Cloneable* Type::createNewInstance() const
{
  if(this->ifAbstract)  // proba odwolania do instancji typu abstrakcyjnego
    throw AbstractTypeInitializationException();
  return this->instance->copy();
}
bool Type::isAbstract() const
{
  return this->ifAbstract;
}
std::map<std::string, Type*>::const_iterator Type::getDerivedTypesConstIterator() const
{
  return this->derivedTypes.cbegin();
}
const Type& Type::getDerivedType(const std::string& name) const
{
  if(!this->derivedTypes.count(name))
    throw std::out_of_range("Derived types array out of range.");
  return *this->derivedTypes.find(name)->second;
}
const Type& Type::searchDerivedType(const std::string& name) const
{
  for(auto type = this->derivedTypes.cbegin(); type != this->derivedTypes.cend(); type++)
  {
    if(type->first == name)
      return *type->second;
    try
    {
      return type->second->searchDerivedType(name); // przeszukiwanie wsrod klas pochodnych danej klasy pochodnej
    }
    catch(...)  // nie ma gdzie dalej sie zaglebiac
    {}
  }
  throw std::out_of_range("Type tree out of range.");
}
unsigned Type::getDerivedTypesNumber() const
{
  return this->derivedTypes.size();
}

TypeTracer::~TypeTracer()
{
  this->baseTypes.clear();
}

const Type& TypeTracer::searchType(const std::string& name) const
{
  for(auto type = this->baseTypes.cbegin(); type != this->baseTypes.cend(); type++)
  {
    if(type->first == name)
      return *type->second;
    try
    {
      return type->second->searchDerivedType(name); // zaglebianie sie w hierarchie
    }
    catch(const std::out_of_range&)
    {}
  }
  throw std::out_of_range("Type trees out of range."); // nie ma takiego typu w hierarchii
}
std::map<std::string, Type*>::const_iterator TypeTracer::getBaseTypesConstIterator() const
{
  return this->baseTypes.cbegin();
}
const Type& TypeTracer::getBaseType(const std::string& name) const
{
  if(!this->baseTypes.count(name))
    throw std::out_of_range("Base types array out of range.");
  return *this->baseTypes.find(name)->second;
}
unsigned TypeTracer::getBaseTypesNumber() const
{
  return this->baseTypes.size();
}
void TypeTracer::addType(Type *newType, std::string newTypeName, std::string baseTypeName)
{
  for(auto typeName = this->usedTypeNames.cbegin(); typeName != this->usedTypeNames.cend(); typeName++)
    if(*typeName == newTypeName)  // typ o takiej nazwie juz jest w hierarchii
      throw NonUniqueElementException();
  if(baseTypeName == "")
  {
    this->baseTypes[newTypeName] = newType;
  }
  else
  {
    try
    {
      const_cast<Type&>(this->searchType(baseTypeName)).derivedTypes[newTypeName] = newType;
    }
    catch(const std::out_of_range&) // nie znaleziono podanego typu
    {
      throw std::out_of_range("Type tree out of range.");
    }
  }
  this->usedTypeNames.push_back(newTypeName);
}

const char* NoDerivedTypesException::what() const throw()
{
  return "No derived types found.";
}

const char* AbstractTypeInitializationException::what() const throw()
{
  return "Abstract type instance cannot be initialized.";
}

const char* NonUniqueElementException::what() const throw()
{
  return "Non-unique element insertion.";
}
