/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#ifndef TYPETRACING_H_INCLUDED
#define TYPETRACING_H_INCLUDED

#include <map>
#include <list>
#include <string>
#include <exception>

class Cloneable;  // klasa bazowa pozwalajaca na utworzenie nowych instancji klas pochodnych pod powloka bazowej (przy odpowiednich implementacjach klas pochodnych)
class Type;       // klasa reprezentujaca typ (pozwalajaca na miedzy innymi tworzenie nowych instancji typu reprezenwowanego oraz uzyskania dostepu do klas pochodnych)
class TypeTracer; // klasa reprezentujaca hierarchie typow

extern TypeTracer hierarchy;  // hierarchia typow danego projektu

class Cloneable
{
public:
  virtual ~Cloneable() = 0;

  virtual Cloneable* copy() const = 0; // produkuje nowe (puste) instancje klasy dziedzicacej pod powloka klasy bazowej Cloneable
};

class Type
{
private:
  Cloneable *instance;  // przechowuje wrzozec instancji typu przechowywanego
  bool ifAbstract;
  std::map<std::string, Type*> derivedTypes;
public:
  Type(Cloneable *instance, bool ifAbstract);
  ~Type();

  Cloneable* createNewInstance() const; // produkuje nowa instancje typu przechowywanego
  bool isAbstract() const;
  std::map<std::string, Type*>::const_iterator getDerivedTypesConstIterator() const;
  const Type& getDerivedType(const std::string& name) const;  // zwraca bezposrednia klase pochodna od przechowywanej o danej nazwie
  const Type& searchDerivedType(const std::string& name) const; // zwraca klase pochodna (niekoniecznie bezposrednia, lecz takze za kilka poziomow dziedziczenia w hierarchii) od przechowywanej o danej nazwie
  unsigned getDerivedTypesNumber() const;

  friend class TypeTracer;
};

class TypeTracer
{
private:
  std::map<std::string, Type*> baseTypes;
  std::list<std::string> usedTypeNames; // przechowuje wszystkie nazwy typow hierarchii (aby nie pozwalac dodawac takie same typy)

public:
  ~TypeTracer();

  const Type& searchType(const std::string& name) const;  // przeszukiwanie typu o podanej nazwie w hierarchii
  std::map<std::string, Type*>::const_iterator getBaseTypesConstIterator() const;
  const Type& getBaseType(const std::string& name) const;
  unsigned getBaseTypesNumber() const;
  void addType(Type *newType, std::string newTypeName, std::string baseTypeName = ""); // dodaje nowy typ do hierarchii, dziedziczacy od typu o nazwie baseTypeName (przeciazanie bez podania nazwy bazowej powoduje dodanie typu do gornego poziomu hierarchii (klas bazowych))
};

// rzuca sie, kiedy sie chce odwolac do nieistniajacych klas pochodnych
class NoDerivedTypesException : public std::exception
{
public:
  const char* what() const throw();
};

// rzuca sie przy probie uzyskania instancji klasy abstrakcyjnej
class AbstractTypeInitializationException : public std::exception
{
public:
  const char* what() const throw();
};

// rzuca sie przy probie dodania do agregacji elementu juz dodanego (tu przy probie rejestracji typu juz zarejestrowanego)
class NonUniqueElementException : public std::exception
{
public:
  const char* what() const throw();
};

#endif // TYPETRACING_H_INCLUDED
