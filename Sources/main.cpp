#include <iostream>
#include <fstream>
#include <sstream>
/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#include "Person.h"

void InitializeAll()  // dodaje wszystkie typy w hierarchie
{
  Profession::initialize();
  Student::initialize();
  Clergyman::initialize();
  Businessman::initialize();
  Employee::initialize();
  Programmer::initialize();
  Sportsman::initialize();
  Translator::initialize();
  Hobby::initialize();
  ActiveHobby::initialize();
  PassiveHobby::initialize();
  Jogging::initialize();
  Swimming::initialize();
  Football::initialize();
  Reading::initialize();
  WatchingFilms::initialize();
  Gaming::initialize();
  MaritalStatus::initialize();
  Single::initialize();
  Married::initialize();
}

int main()
{
  std::list<Person> people;
  std::string input;
  bool ifYes = true;
  std::stringstream ss;
  std::ofstream ofs;
  InitializeAll();
  // wprowadzenie danych
  std::cout << "Please enter data about the people:" << std::endl;
  while(ifYes)
  {
    people.push_back(Person());
    people.back().setDescription();
    std::cout << "Do you want to add one more person? (Y/N)" << std::endl;
    while(true)
    {
      getline(std::cin, input);
      try
      {
        if(input == "Y" || input == "y")
          break;
        else if(input == "N" || input == "n")
        {
          ifYes = false;
          break;
        }
        else
          throw "Incorrect answer! Please press 'Y' to add one more person or 'N' otherwise.";
      }
      catch(const std::string& exc)
      {
        std::cout << exc << std::endl;
      }
    }
  }
  // wyprowadzenie danych
  ss << "Data about " << people.size() << (people.size() == 1 ? " person" : " people") << " collected:" << std::endl;
  auto person = people.cbegin();
  for (int i = 1; person != people.cend() ; ++i, ++person)
  {
    ss << i << ". ";
    person->getDescription(ss, "\t");
  }
  // ... w plik
  ofs.exceptions(std::ofstream::failbit | std::ofstream::badbit);
  while(true)
  {
    std::cout << "Please enter the path to the logfile:" << std::endl;
    getline(std::cin, input);
    try
    {
      ofs.open(input);
      ofs << ss.str();
      ofs.close();
      break;
    }
    catch(const std::ios_base::failure &fail)
    {
      std::cout << "Failed to write to the specified file! Error description:" << std::endl << fail.what() << std::endl << "Please try again." << std::endl;
    }
  }
  // ... ina konsole
  std::cout << ss.str() << std::endl;
  std::cout << "Writing to the file succeeded." << std::endl;
  return 0;
}
