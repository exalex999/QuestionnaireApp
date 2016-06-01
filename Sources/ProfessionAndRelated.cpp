/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#include "ProfessionAndRelated.h"

std::map<DegreeLevels, std::string> degreeLevelsStrings = {{DegreeLevels::BACHELOR, "bachelor"},
                                                           {DegreeLevels::MASTER, "master"},
                                                           {DegreeLevels::DOCTOR, "doctor"}};
std::map<Religions, std::string> religionsStrings = {{Religions::CHRISTIANITY, "christianity"},
                                                     {Religions::ISLAM, "islam"},
                                                     {Religions::HINDUISM, "hinduism"},
                                                     {Religions::BUDDHISM, "buddhism"},
                                                     {Religions::FOLKRELIGION, "folk religion"}};

std::string Profession::typeName = "profession";
void Profession::initialize()
{
  hierarchy.addType(new Type(nullptr, true), Profession::getTypeName());
}

std::string Profession::getTypeName()
{
  return Profession::typeName;
}

Profession::~Profession()
{
  foreignLanguages.clear();
}

void Profession::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << prefix << "* professional activity since (years): " << this->professionalActivityDuration << std::endl;
  fileStream << prefix << "* workplace address: " << this->workplaceAdress << std::endl;
  fileStream << prefix << "* foreign languages the person speaks:";
  if(!this->foreignLanguages.size())
    fileStream << " none";
  fileStream << std::endl;
  auto lang = this->foreignLanguages.cbegin();
  for(int i = 1; lang != this->foreignLanguages.cend(); ++i, ++lang)
    fileStream << prefix << "\t" << i << ") " << *lang << std::endl;
}
void Profession::setDescription()
{
  std::string input;
  while(true)
  {
    std::cout << "professional activity since (years): ";
    getline(std::cin, input);
    try
    {
      this->professionalActivityDuration = std::stod(input);
      if(this->professionalActivityDuration < 0)
        throw "";
      break;
    }
    catch(...)
    {
      std::cout << "Invalid answer! The answer must be a non-negative number." << std::endl;
    }
  }
  std::cout << "workplace address: ";
  getline(std::cin, this->workplaceAdress);
  std::cout << "Does the person speak any foreign language? (Y/N)" << std::endl;
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
      std::cout << "foreign language the person speaks: ";
      try
      {
        getline(std::cin, input);
        for(unsigned i = 0; i < input.size(); ++i)
          if((input[i] < 'A' || input[i] > 'Z') && (input[i] < 'a' || input[i] > 'z'))
            throw "Incorrect language! The language name must contain only Latin letters!";
        for(auto lang = this->foreignLanguages.cbegin(); lang != this->foreignLanguages.cend(); lang++)
          if(*lang == input)
            throw "The language's already been inputed!";
      }
      catch(const char *exc)
      {
        std::cout << exc << std::endl;
        continue;
      }
      this->foreignLanguages.push_back(input);
      break;
    }
    std::cout << "Does the person speak any more foreign languages? (Y/N)" << std::endl;
  }
}

std::string Student::typeName = "student";
void Student::initialize()
{
  hierarchy.addType(new Type(new Student(), false), Student::getTypeName(), Profession::getTypeName());
}

std::string Student::getTypeName()
{
  return Student::typeName;
}

void Student::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << Profession::getTypeName() << ": " << Student::getTypeName() << std::endl;
  Profession::getDescription(fileStream, prefix);
  fileStream << prefix << "* high school: " << this->highSchool << std::endl;
  fileStream << prefix << "* faculty: " << this->faculty << std::endl;
  fileStream << prefix << "* speciality: " << this->speciality << std::endl;
  fileStream << prefix << "* level of studies: " << ::degreeLevelsStrings[this->levelOfStudies] << std::endl;
  fileStream << prefix << "* year of enrollment: " << this->enrollmentYear << std::endl;
  fileStream << prefix << "* current semester: " << this->semester << std::endl;
  fileStream << prefix << "* expected graduation year: " << this->expectedGraduationYear << std::endl;
  fileStream << prefix << "* average mark: " << this->averageMark << std::endl;
}
void Student::setDescription()
{
  std::string input;
  int tmp;
  Profession::setDescription();
  std::cout << "high school: ";
  getline(std::cin, this->highSchool);
  std::cout << "faculty: ";
  getline(std::cin, this->faculty);
  std::cout << "speciality: ";
  getline(std::cin, this->speciality);
  std::cout << "Please select the level of studies (1-" << degreeLevelsStrings.size() << "):" << std::endl;
  auto levelOfStudies = degreeLevelsStrings.cbegin();
  for(unsigned i = 1; i <= degreeLevelsStrings.size(); i++, levelOfStudies++)
    std::cout << i << ") " << levelOfStudies->second << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      tmp = std::stoi(input);
      if(tmp < 1 || tmp > (int)degreeLevelsStrings.size())
        throw "";
    }
    catch(...)
    {
      std::cout << "Incorrect answer!" << std::endl;
      std::cout << "Please select the level of studies (1-" << degreeLevelsStrings.size() << "):" << std::endl;
      continue;
    }
    auto levelOfStudies = degreeLevelsStrings.cbegin();
    for(int i = 1; i < tmp; i++)
      levelOfStudies++;
    this->levelOfStudies = levelOfStudies->first;
    break;
  }
  while(true)
  {
    std::cout << "year of enrollment: ";
    getline(std::cin, input);
    try
    {
      this->enrollmentYear = std::stoi(input);
      if(this->enrollmentYear < 1)
        throw "";
      break;
    }
    catch(...)
    {
      std::cout << "Invalid answer! The answer must be a positive integer." << std::endl;
    }
  }
  while(true)
  {
    std::cout << "current semester: ";
    getline(std::cin, input);
    try
    {
      this->semester = std::stoi(input);
      if(this->semester < 1 || this->semester > 20)
        throw "";
      break;
    }
    catch(...)
    {
      std::cout << "Invalid answer! The answer must be a positive integer not greater than 20." << std::endl;
    }
  }
  while(true)
  {
    std::cout << "expected graduation year: ";
    getline(std::cin, input);
    try
    {
      this->expectedGraduationYear = std::stoi(input);
      if(this->expectedGraduationYear < 1)
        throw "";
      break;
    }
    catch(...)
    {
      std::cout << "Invalid answer! The answer must be a positive integer." << std::endl;
    }
  }
  while(true)
  {
    std::cout << "average mark: ";
    getline(std::cin, input);
    try
    {
      this->averageMark = std::stoi(input);
      if(this->averageMark < 0 || this->averageMark > 5)
        throw "";
      break;
    }
    catch(...)
    {
      std::cout << "Invalid answer! The answer must be a non-negative integer not greater than 5." << std::endl;
    }
  }
}
Cloneable* Student::copy() const
{
  return new Student();
}

std::string Clergyman::typeName = "clergyman";
void Clergyman::initialize()
{
  hierarchy.addType(new Type(new Clergyman(), false), Clergyman::getTypeName(), Profession::getTypeName());
}

std::string Clergyman::getTypeName()
{
  return Clergyman::typeName;
}

void Clergyman::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << Profession::getTypeName() << ": " << Clergyman::getTypeName() << std::endl;
  Profession::getDescription(fileStream, prefix);
  fileStream << prefix << "* religion: " << ::religionsStrings[this->religion] << std::endl;
  fileStream << prefix << "* place of worship name: " << this->placeOfWorship << std::endl;
  fileStream << prefix << "* ecclesiastical address: " << this->ecclesiasticalAddress << std::endl;
}
void Clergyman::setDescription()
{
  std::string input;
  int tmp;
  Profession::setDescription();
  std::cout << "Please select the religion (1-" << religionsStrings.size() << "):" << std::endl;
  auto religion = religionsStrings.cbegin();
  for(unsigned i = 1; i <= religionsStrings.size(); i++, religion++)
    std::cout << i << ") " << religion->second << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      tmp = std::stoi(input);
      if(tmp < 1 || tmp > (int)religionsStrings.size())
        throw "";
    }
    catch(...)
    {
      std::cout << "Incorrect answer!" << std::endl;
      std::cout << "Please select " << Clergyman::getTypeName() << "'s (1-" << religionsStrings.size() << "):" << std::endl;
      continue;
    }
    auto religion = religionsStrings.cbegin();
    for(int i = 1; i < tmp; i++)
      religion++;
    this->religion = religion->first;
    break;
  }
  std::cout << "place of worship name: ";
  getline(std::cin, this->placeOfWorship);
  std::cout << "ecclesiastical address: ";
  getline(std::cin, this->ecclesiasticalAddress);
}
Cloneable* Clergyman::copy() const
{
  return new Clergyman();
}

std::string Employee::typeName = "employee";
void Employee::initialize()
{
  hierarchy.addType(new Type(new Employee(), false), Employee::getTypeName(), Profession::getTypeName());
}

std::string Employee::getTypeName()
{
  return Employee::typeName;
}

Employee::~Employee()
{
  additionalSkills.clear();
}

void Employee::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << Profession::getTypeName() << ": " << Employee::getTypeName() << std::endl;
  Profession::getDescription(fileStream, prefix);
  fileStream << prefix << "* organization: " << this->organization << std::endl;
  fileStream << prefix << "* position: " << this->position << std::endl;
  fileStream << prefix << "* professional education: " << this->education << std::endl;
  fileStream << prefix << "* additional skills:";
  if(!this->additionalSkills.size())
    fileStream << " none";
  fileStream << std::endl;
  auto skill = this->additionalSkills.cbegin();
  for(unsigned i = 1; i <= this->additionalSkills.size(); i++, skill++)
    fileStream << prefix << "\t" << i << ") " << *skill << std::endl;
  fileStream << prefix << "* salary: $" << this->salary << std::endl;
}
void Employee::setDescription()
{
  std::string input;
  Profession::setDescription();
  std::cout << "organization: ";
  getline(std::cin, this->organization);
  std::cout << "position: ";
  getline(std::cin, this->position);
  std::cout << "professional education: ";
  getline(std::cin, this->education);
  std::cout << "Has the " + Employee::getTypeName() + " got any additional skills? (Y/N)" << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      if(input == "N" || input == "n")
        break;
      else if(input != "Y" && input != "y")
        throw "Incorrect answer!";
      std::cout << "additional skill: ";
      getline(std::cin, input);
      this->additionalSkills.push_back(input);
      std::cout << "Has the " + Employee::getTypeName() + " got any more additional skills? (Y/N)" << std::endl;
    }
    catch(const char *exc)
    {
      std::cout << exc << std::endl;
    }
  }
  while(true)
  {
    std::cout << "salary (in dollars): ";
    getline(std::cin, input);
    try
    {
      this->salary = std::stoi(input);
      if(this->salary <= 0)
        throw "";
      break;
    }
    catch(...)
    {
      std::cout << "Invalid answer! The answer must be a positive integer." << std::endl;
    }
  }
}
Cloneable* Employee::copy() const
{
  return new Employee();
}

std::string Businessman::typeName = "businessman";
void Businessman::initialize()
{
  hierarchy.addType(new Type(new Businessman(), false), Businessman::getTypeName(), Profession::getTypeName());
}

std::string Businessman::getTypeName()
{
  return Businessman::typeName;
}

void Businessman::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << Profession::getTypeName() << ": " << Businessman::getTypeName() << std::endl;
  Profession::getDescription(fileStream, prefix);
  fileStream << prefix << "* organization: " << this->organization << std::endl;
  fileStream << prefix << "* branch: " << this->branch << std::endl;
  fileStream << prefix << "* organization activity description: " << this->organizationActivityDescription << std::endl;
  fileStream << prefix << "* employee number: " << this->employeeNumber << std::endl;
  fileStream << prefix << "* average profit (in dollars): " << this->averageProfit << std::endl;
  fileStream << prefix << "* average employee salary (in dollars): " << this->averageEmployeeSalary << std::endl;
}
void Businessman::setDescription()
{
  std::string input;
  Profession::setDescription();
  std::cout << "organization: ";
  getline(std::cin, this->organization);
  std::cout << "branch: ";
  getline(std::cin, this->branch);
  std::cout << "organization activity description: ";
  getline(std::cin, this->organizationActivityDescription);
  while(true)
  {
    std::cout << "employee number: ";
    getline(std::cin, input);
    try
    {
      this->employeeNumber = std::stod(input);
      if(this->employeeNumber <= 0)
        throw "";
      break;
    }
    catch(...)
    {
      std::cout << "Invalid answer! The answer must be a positive integer." << std::endl;
    }
  }
  while(true)
  {
    std::cout << "average profit (in dollars): ";
    getline(std::cin, input);
    try
    {
      this->averageProfit = std::stod(input);
      break;
    }
    catch(...)
    {
      std::cout << "Invalid answer! The answer must be a positive integer." << std::endl;
    }
  }
  while(true)
  {
    std::cout << "average employee salary (in dollars): ";
    getline(std::cin, input);
    try
    {
      this->averageEmployeeSalary = std::stod(input);
      if(this->averageEmployeeSalary <= 0)
        throw "";
      break;
    }
    catch(...)
    {
      std::cout << "Invalid answer! The answer must be a positive integer." << std::endl;
    }
  }
}
Cloneable* Businessman::copy() const
{
  return new Businessman();
}

std::string Programmer::typeName = "programmer";
void Programmer::initialize()
{
  hierarchy.addType(new Type(new Programmer(), false), Programmer::getTypeName(), Employee::getTypeName());
}

std::string Programmer::getTypeName()
{
  return Programmer::typeName;
}

Programmer::~Programmer()
{
  this->primaryTechnologies.clear();
  this->additionalTechnologies.clear();
}

void Programmer::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  Employee::getDescription(fileStream, prefix);
  fileStream << prefix << "* " << Employee::getTypeName() << " -> " << Programmer::getTypeName() << ":" << std::endl;
  fileStream << prefix << "\t* primary technologies required to do the job:" << std::endl;
  auto iter = this->primaryTechnologies.cbegin();
  for(unsigned i = 1; i <= this->primaryTechnologies.size(); i++, iter++)
    fileStream << prefix << "\t\t" << i << ") " << *iter << std::endl;
  fileStream << prefix << "\t* additional technologies known:";
  if(!this->additionalTechnologies.size())
    fileStream << " none";
  fileStream << std::endl;
  iter = this->additionalTechnologies.cbegin();
  for(unsigned i = 1; i <= this->additionalTechnologies.size(); i++, iter++)
    fileStream << prefix << "\t\t" << i << ") " << *iter << std::endl;
}
void Programmer::setDescription()
{
  std::string input;
  Employee::setDescription();
  std::cout << "primary technology required to do the job: ";
  getline(std::cin, input);
  this->primaryTechnologies.push_back(input);
  while(true)
  {
    std::cout << "Does the " + Programmer::getTypeName() + " know any more primary technologies required to do the job? (Y/N)" << std::endl;
    getline(std::cin, input);
    try
    {
      if(input == "N" || input == "n")
        break;
      else if(input != "Y" && input != "y")
        throw "Incorrect answer!";
      std::cout << "primary technology required to do the job: ";
      getline(std::cin, input);
      this->primaryTechnologies.push_back(input);
    }
    catch(const char *exc)
    {
      std::cout << exc << std::endl;
    }
  }
  std::cout << "Does the " + Programmer::getTypeName() + " know any additional technologies? (Y/N)" << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      if(input == "N" || input == "n")
        break;
      else if(input != "Y" && input != "y")
        throw "Incorrect answer!";
      std::cout << "additional technology: ";
      getline(std::cin, input);
      this->additionalTechnologies.push_back(input);
      std::cout << "Does the " + Programmer::getTypeName() + " know any more additional technologies? (Y/N)" << std::endl;
    }
    catch(const char *exc)
    {
      std::cout << exc << std::endl;
    }
  }
}
Cloneable* Programmer::copy() const
{
  return new Programmer();
}

std::string Sportsman::typeName = "sportsman";
void Sportsman::initialize()
{
  hierarchy.addType(new Type(new Sportsman(), false), Sportsman::getTypeName(), Employee::getTypeName());
}

std::string Sportsman::getTypeName()
{
  return Sportsman::typeName;
}

Sportsman::~Sportsman()
{
  this->achievements.clear();
}

void Sportsman::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  Employee::getDescription(fileStream, prefix);
  fileStream << prefix << "* " << Employee::getTypeName() << " -> " << Sportsman::getTypeName() << ":" << std::endl;
  fileStream << prefix << "\t* kind of sport: " << this->kindOfSport << std::endl;
  fileStream << prefix << "\t* sport achievements:";
  if(!this->achievements.size())
    fileStream << " none";
  fileStream << std::endl;
  auto iter = this->achievements.cbegin();
  for(unsigned i = 1; i <= this->achievements.size(); i++, iter++)
    fileStream << prefix << "\t\t" << i << ") " << *iter << std::endl;
}
void Sportsman::setDescription()
{
  std::string input;
  Employee::setDescription();
  std::cout << "kind of sport: ";
  getline(std::cin, this->kindOfSport);
  std::cout << "Has the " + Sportsman::getTypeName() + " any sport achievements? (Y/N)" << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      if(input == "N" || input == "n")
        break;
      else if(input != "Y" && input != "y")
        throw "Incorrect answer!";
      std::cout << "sport achievements: ";
      getline(std::cin, input);
      this->achievements.push_back(input);
      std::cout << "Has the " + Sportsman::getTypeName() + " any more sport achievements? (Y/N)" << std::endl;
    }
    catch(const char *exc)
    {
      std::cout << exc << std::endl;
    }
  }
}
Cloneable* Sportsman::copy() const
{
  return new Sportsman();
}

std::string Translator::typeName = "translator";
void Translator::initialize()
{
  hierarchy.addType(new Type(new Translator(), false), Translator::getTypeName(), Employee::getTypeName());
}

std::string Translator::getTypeName()
{
  return Translator::typeName;
}

Translator::~Translator()
{
  this->languages.clear();
}

void Translator::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  Employee::getDescription(fileStream, prefix);
  fileStream << prefix << "* " << Employee::getTypeName() << " -> " << Translator::getTypeName() << ":" << std::endl;
  fileStream << prefix << "\t* used languages:" << std::endl;
  auto iter = this->languages.cbegin();
  for(unsigned i = 1; i <= this->languages.size(); i++, iter++)
    fileStream << prefix << "\t\t" << i << ") " << *iter << std::endl;
}
void Translator::setDescription()
{
  std::string input;
  Employee::setDescription();
  std::cout << "used language: ";
  getline(std::cin, input);
  this->languages.push_back(input);
  while(true)
  {
    std::cout << "Does the " + Translator::getTypeName() + " translate any more languages? (Y/N)" << std::endl;
    getline(std::cin, input);
    try
    {
      if(input == "N" || input == "n")
        break;
      else if(input != "Y" && input != "y")
        throw "Incorrect answer!";
      std::cout << "used language: ";
      getline(std::cin, input);
      this->languages.push_back(input);
    }
    catch(const char *exc)
    {
      std::cout << exc << std::endl;
    }
  }
}
Cloneable* Translator::copy() const
{
  return new Translator();
}
