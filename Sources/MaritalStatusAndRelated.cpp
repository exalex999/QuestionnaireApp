/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#include "MaritalStatusAndRelated.h"

std::string MaritalStatus::typeName = "marital status";
void MaritalStatus::initialize()
{
  hierarchy.addType(new Type(nullptr, true), MaritalStatus::getTypeName());
}

std::string MaritalStatus::getTypeName()
{
  return MaritalStatus::typeName;
}

MaritalStatus::~MaritalStatus()
{
  children.clear();
}

void MaritalStatus::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << prefix << "* children:";
  if(!this->children.size())
    fileStream << " none";
  fileStream << std::endl;
  auto iter = this->children.cbegin();
  for(int i = 1; iter != this->children.cend(); ++i, ++iter)
    fileStream << prefix << "\t" << i << ") " << *iter << std::endl;
  fileStream << prefix << "* paying some alimony: " << (this->payingAlimony ? "yes" : "no") << std::endl;
  if(this->payingAlimony)
    fileStream << prefix << "* alimony: $" << this->alimony << std::endl;
}
void MaritalStatus::setDescription()
{
  std::string input;
  std::cout << "Has the person got any children? (Y/N)" << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      if(input == "N" || input == "n")
        break;
      else if(input != "Y" && input != "y")
        throw "Incorrect answer! Answer must be 'Y' if yes or 'N' otherwise.";
    }
    catch(const char *exc)
    {
      std::cout << exc << std::endl;
      continue;
    }
    while(true)
    {
      std::cout << "child: ";
      getline(std::cin, input);
      try
      {
        std::string errMsg = "Incorrect name. It must contain only Latin letters, the first must be in uppercase, others in lowercase.";
        if(!input.length() || input[0] < 'A' || input[0] > 'Z')
          throw errMsg;
        for(unsigned i = 1; i < input.length(); i++)
          if(input[i] < 'a' || input[i] > 'z')
            throw errMsg;
        break;
      }
      catch(const std::string &exc)
      {
        std::cout << exc << std::endl;
      }
    }
    children.push_back(input);
    std::cout << "Has the person any more children? (Y/N)" << std::endl;
  }
  if(this->children.size())
  {
    std::cout << "Do you pay any alimony? (Y/N)" << std::endl;
    while(true)
    {
      getline(std::cin, input);
      try
      {
        if(input == "Y" || input == "y")
        {
          this->payingAlimony = true;
          while(true)
          {
            std::cout << "alimony (in dollars): ";
            getline(std::cin, input);
            try
            {
              this->alimony = std::stod(input);
              if(this->alimony <= 0)
                throw "";
              break;
            }
            catch(...)
            {
              std::cout << "Invalid answer! The answer must be a positive number." << std::endl;
            }
          }
        }
        else if(input == "N" || input == "n")
          this->payingAlimony = false;
        else
          throw "Incorrect answer!";
        break;
      }
      catch(const char *exc)
      {
        std::cout << exc << std::endl;
      }
    }
  }
  else
    this->payingAlimony = false;
}

std::string Single::typeName = "single";
void Single::initialize()
{
  hierarchy.addType(new Type(new Single(), false), Single::getTypeName(), MaritalStatus::getTypeName());
}

std::string Single::getTypeName()
{
  return Single::typeName;
}

void Single::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << MaritalStatus::getTypeName() << ": " << Single::getTypeName() << std::endl;
  MaritalStatus::getDescription(fileStream, prefix);
  fileStream << prefix << "* married before: " << (this->ifMarriedBefore ? "yes" : "no") << std::endl;
}
void Single::setDescription()
{
  std::string input;
  MaritalStatus::setDescription();
  std::cout << "Have you been married before? (Y/N)" << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      if(input == "Y" || input == "y")
        this->ifMarriedBefore = true;
      else if(input == "N" || input == "n")
        this->ifMarriedBefore = false;
      else
        throw "Incorrect answer!";
      break;
    }
    catch(const char *exc)
    {
      std::cout << exc << std::endl;
    }
  }
}
Cloneable* Single::copy() const
{
  return new Single();
}

std::string Married::typeName = "married";
void Married::initialize()
{
  hierarchy.addType(new Type(new Married(), false), Married::getTypeName(), MaritalStatus::getTypeName());
}

std::string Married::getTypeName()
{
  return Married::typeName;
}

Married::~Married()
{
  delete weddingDate;
}

void Married::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << MaritalStatus::getTypeName() << ": " << Married::getTypeName() << std::endl;
  MaritalStatus::getDescription(fileStream, prefix);
  fileStream << prefix << "* spouse: " << this->spouse << std::endl;
  fileStream << prefix << "* wedding date: " << *this->weddingDate << std::endl;
}
void Married::setDescription()
{
  std::string input;
  MaritalStatus::setDescription();
  while(true)
  {
    std::cout << "spouse: ";
    getline(std::cin, this->spouse);
    try
    {
      std::string errMsg = "Incorrect name. It must contain only Latin letters, the first must be in uppercase, others in lowercase.";
      if(!this->spouse.length() || this->spouse[0] < 'A' || this->spouse[0] > 'Z')
        throw errMsg;
      for(unsigned i = 1; i < this->spouse.length(); i++)
        if(this->spouse[i] < 'a' || this->spouse[i] > 'z')
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
    std::cout << "Please choose person's wedding day:" << std::endl;
    std::cout << "year: ";
    getline(std::cin, year);
    std::cout << "month: ";
    getline(std::cin, month);
    std::cout << "day: ";
    getline(std::cin, day);
    try
    {
      this->weddingDate = new Date(day, month, year);
      if(*this->weddingDate > Date::getCurrentDate())
      {
        delete this->weddingDate;
        throw "Wedding day cannot be later than today!";
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
}
Cloneable* Married::copy() const
{
  return new Married();
}
