/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#include "Person.h"

Person::~Person()
{
  if(this->birthday)
    delete this->birthday;
  if(this->maritalStatus)
    delete this->maritalStatus;
  if(this->profession)
    delete this->profession;
  for(auto iter = this->hobbies.begin(); iter != this->hobbies.end(); iter++)
    delete *iter;
  this->hobbies.clear();
}

void Person::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << "Person:" << std::endl;
  fileStream << prefix << "* first name: " << this->firstName << std::endl;
  fileStream << prefix << "* last name: " << this->lastName << std::endl;
  fileStream << prefix << "* birthday: " << *this->birthday << std::endl;
  fileStream << prefix << "* ";
  this->maritalStatus->getDescription(fileStream, prefix + "\t");
  fileStream << prefix << "* ";
  this->profession->getDescription(fileStream, prefix + "\t");
  fileStream << prefix << "* Hobbies:";
  if(!hobbies.size())
    fileStream << " none";
  fileStream << std::endl;
  auto hobby = this->hobbies.cbegin();
  for (int i = 1; hobby != hobbies.cend() ; ++i, ++hobby)
  {
    fileStream << prefix << "\t" << i << ") ";
    (*hobby)->getDescription(fileStream, prefix + "\t\t");
  }
}
void Person::setDescription()
{
  std::string input;
  while(true)
  {
    std::cout << "first name: ";
    getline(std::cin, this->firstName);
    try
    {
      std::string errMsg = "Incorrect first name. It must contain only Latin letters, the first must be in uppercase, others in lowercase.";
      if(!this->firstName.length() || this->firstName[0] < 'A' || this->firstName[0] > 'Z')
        throw errMsg;
      for(unsigned i = 1; i < this->firstName.length(); i++)
        if(this->firstName[i] < 'a' || this->firstName[i] > 'z')
          throw errMsg;
      break;
    }
    catch(const std::string &exc)
    {
      std::cout << exc << std::endl;
    }
  }
  while(true)
  {
    std::cout << "last name: ";
    getline(std::cin, this->lastName);
    try
    {
      std::string errMsg = "Incorrect last name. It must contain only Latin letters, the first must be in uppercase, others in lowercase.";
      if(!this->lastName.length() || this->lastName[0] < 'A' || this->lastName[0] > 'Z')
        throw errMsg;
      for(unsigned i = 1; i < this->lastName.length(); i++)
        if(this->lastName[i] < 'a' || this->lastName[i] > 'z')
          throw errMsg;
      break;
    }
    catch(const std::string &exc)
    {
      std::cout << exc << std::endl;
    }
  }
  std::string day, month, year;
  while(true)
  {
    std::cout << "Please choose person's birthday:" << std::endl;
    std::cout << "year: ";
    getline(std::cin, year);
    std::cout << "month: ";
    getline(std::cin, month);
    std::cout << "day: ";
    getline(std::cin, day);
    try
    {
      this->birthday = new Date(day, month, year);
      if(*this->birthday > Date::getCurrentDate())
      {
        delete this->birthday;
        throw "Birthday cannot be later than today!";
      }
      break;
    }
    catch(const std::exception& exc)
    {
      std::cout << exc.what() << std::endl;
    }
    catch(const char *exc)
    {
      std::cout << exc << std::endl;
    }
  }
  std::cout << "Please choose person's " << MaritalStatus::getTypeName() << ":" << std::endl;
  this->maritalStatus = dynamic_cast<MaritalStatus*>(this->askAboutAndGetDerived(hierarchy.getBaseType(MaritalStatus::getTypeName())).createNewInstance());
  this->maritalStatus->setDescription();
  std::cout << "Please choose person's " << Profession::getTypeName() << ":" << std::endl;
  this->profession = dynamic_cast<Profession*>(this->askAboutAndGetDerived(hierarchy.getBaseType(Profession::getTypeName())).createNewInstance());
  this->profession->setDescription();
  std::cout << "Has the person got any hobbies? (Y/N)" << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      if(input == "N" || input == "n")
        break;
      else if(input != "Y" && input != "y")
        throw "Incorrect answer!";
      std::cout << "Please specify person's " << Hobby::getTypeName() << ":" << std::endl;
      this->hobbies.push_back(dynamic_cast<Hobby*>(this->askAboutAndGetDerived(hierarchy.getBaseType(Hobby::getTypeName())).createNewInstance()));
      this->hobbies.back()->setDescription();
      std::cout << "Has the person got any more hobbies? (Y/N)" << std::endl;
    }
    catch(const char *exc)
    {
      std::cout << exc << std::endl;
    }
  }
}
