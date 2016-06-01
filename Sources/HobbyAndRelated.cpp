/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#include "HobbyAndRelated.h"

std::map<PassiveHobbyPlaces, std::string> passiveHobbyPlacesStrings = {{PassiveHobbyPlaces::HOME, "home"},
                                                                       {PassiveHobbyPlaces::WITHFRIENDSATTHEIRHOME, "with friends at their home"},
                                                                       {PassiveHobbyPlaces::INPARK, "in park"},
                                                                       {PassiveHobbyPlaces::INTHEINTERESTCLUB, "in the interest club"},
                                                                       {PassiveHobbyPlaces::INTRANSPORT, "in transport"},
                                                                       {PassiveHobbyPlaces::OTHER, "other"}};
std::map<SwimmingStyles, std::string> swimmingStylesStrings = {{SwimmingStyles::FRONTCRAWL, "frontclawl"},
                                                               {SwimmingStyles::TRUDGEN, "trudgen"},
                                                               {SwimmingStyles::BUTTERFLYSTROKE, "butterflystroke"},
                                                               {SwimmingStyles::BREASTSTROKE, "breaststroke"},
                                                               {SwimmingStyles::BACKSTROKE, "backstroke"},
                                                               {SwimmingStyles::SIDESTROKE, "sidestroke"},
                                                               {SwimmingStyles::DOGPADDLE, "dog paddle"},
                                                               {SwimmingStyles::SNORKELING, "snorkeling"},
                                                               {SwimmingStyles::FINSWIMMING, "finswimming"},
                                                               {SwimmingStyles::OTHER, "other"}};
std::map<FootballPositions, std::string> footballPositionsStrings = {{FootballPositions::GOALKEEPER, "goalkeeper"},
                                                                     {FootballPositions::DEFENDER, "defender"},
                                                                     {FootballPositions::MIDFIELDER, "midfielder"},
                                                                     {FootballPositions::FORWARD, "forward"}};
std::map<FictionAndFilmGenres, std::string> fictionAndFilmGenresStrings = {{FictionAndFilmGenres::ADVENTURE, "adventure"},
                                                                           {FictionAndFilmGenres::CLASSIC, "classic"},
                                                                           {FictionAndFilmGenres::DETECTIVE, "detective"},
                                                                           {FictionAndFilmGenres::FANTASY, "fantasy"},
                                                                           {FictionAndFilmGenres::FOLKLORE, "folklore"},
                                                                           {FictionAndFilmGenres::HISTORICALFICTION, "historical fiction"},
                                                                           {FictionAndFilmGenres::HORROR, "horror"},
                                                                           {FictionAndFilmGenres::HUMOR, "humor"},
                                                                           {FictionAndFilmGenres::LEGEND, "legend"},
                                                                           {FictionAndFilmGenres::MYSTERY, "mystery"},
                                                                           {FictionAndFilmGenres::MYTHOLOGY, "mythology"},
                                                                           {FictionAndFilmGenres::REALISTICFICTION, "realistic fiction"},
                                                                           {FictionAndFilmGenres::THRILLER, "thriller"},
                                                                           {FictionAndFilmGenres::WESTERN, "western"},
                                                                           {FictionAndFilmGenres::OTHER, "other"}};
std::map<ComputerGameGenres, std::string> computerGameGenresStrings = {{ComputerGameGenres::ACTION, "action"},
                                                                       {ComputerGameGenres::SHOOTER, "shooter"},
                                                                       {ComputerGameGenres::ADVENTURE, "adventure"},
                                                                       {ComputerGameGenres::ROLEPLAYING, "role playing"},
                                                                       {ComputerGameGenres::SIMULATION, "simulation"},
                                                                       {ComputerGameGenres::STRATEGY, "strategy"},
                                                                       {ComputerGameGenres::SPORTS, "sports"},
                                                                       {ComputerGameGenres::OTHER, "other"}};

Frequency::Frequency(double times, MainTimePeriods period) : times(times), period(period)
{}

std::ostream& operator<<(std::ostream& os, const Frequency& fr)
{
  os << fr.times << " times a " << ::mainTimePeriodsStrings[fr.period];
  return os;
}

std::string Hobby::typeName = "hobby";
void Hobby::initialize()
{
  hierarchy.addType(new Type(nullptr, true), Hobby::getTypeName());
}

std::string Hobby::getTypeName()
{
  return Hobby::typeName;
}

Hobby::~Hobby()
{
  delete engagementFrequency;
}

void Hobby::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << prefix << "* frequency of engagement in the hobby: " << *this->engagementFrequency << std::endl;
  fileStream << prefix << "* average duration of engagement in the hobby (hours): " << this->averageDuration << std::endl;
}
void Hobby::setDescription()
{
  std::string input;
  MainTimePeriods fr_period;
  int tmp;
  std::cout << "How often is the person usually engaged in the hobby?" << std::endl;
  std::cout << "Please select one of the following (1-" << mainTimePeriodsStrings.size() << "):" << std::endl;
  auto period = mainTimePeriodsStrings.cbegin();
  for(unsigned i = 1; i <= mainTimePeriodsStrings.size(); i++, period++)
    std::cout << i << ") every " << period->second << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      tmp = std::stoi(input);
      if(tmp < 1 || tmp > (int)mainTimePeriodsStrings.size())
        throw "";
    }
    catch(...)
    {
      std::cout << "Incorrect answer!" << std::endl;
      continue;
    }
    period = mainTimePeriodsStrings.cbegin();
    for(int i = 1; i < tmp; i++)
      period++;
    fr_period = period->first;
    break;
  }
  while(true)
  {
    std::cout << "How many times a " << mainTimePeriodsStrings[fr_period] << " is the person usually engaged in the hobby?" << std::endl;
    getline(std::cin, input);
    try
    {
      tmp = std::stod(input);
      if(tmp < 1)
        throw "";
      break;
    }
    catch(...)
    {
      std::cout << "Invalid answer! The answer must be a positive number." << std::endl;
    }
  }
  engagementFrequency = new Frequency(tmp, fr_period);
  while(true)
  {
    std::cout << "average duration of engagement in the hobby (hours): ";
    getline(std::cin, input);
    try
    {
      this->averageDuration = std::stod(input);
      if(this->averageDuration <= 0)
        throw "";
      break;
    }
    catch(...)
    {
      std::cout << "Invalid answer! The answer must be a positive number." << std::endl;
    }
  }
}

std::string ActiveHobby::typeName = "active hobby";
void ActiveHobby::initialize()
{
  hierarchy.addType(new Type(nullptr, true), ActiveHobby::getTypeName(), Hobby::getTypeName());
}

std::string ActiveHobby::getTypeName()
{
  return ActiveHobby::typeName;
}

void ActiveHobby::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << prefix << "* (erlier) professional engagement: " << (this->ifProfessional ? "yes" : "no") << std::endl;
  fileStream << prefix << "* place of the " + ActiveHobby::getTypeName() + ": " << this->place << std::endl;
}
void ActiveHobby::setDescription()
{
  std::string input;
  std::cout << "Have you ever been professionally engaged in the " << ActiveHobby::getTypeName() << "? (Y/N)" << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      if(input == "Y" || input == "y")
        this->ifProfessional = true;
      else if(input == "N" || input == "n")
        this->ifProfessional = false;
      else
        throw "Incorrect answer!";
      break;
    }
    catch(const char *exc)
    {
      std::cout << exc << std::endl;
    }
  }
  std::cout << "place of the " + ActiveHobby::getTypeName() + ": ";
  getline(std::cin, this->place);
}

std::string PassiveHobby::typeName = "passive hobby";
void PassiveHobby::initialize()
{
  hierarchy.addType(new Type(nullptr, true), PassiveHobby::getTypeName(), Hobby::getTypeName());
}

std::string PassiveHobby::getTypeName()
{
  return PassiveHobby::typeName;
}

void PassiveHobby::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << prefix << "* place of the " << PassiveHobby::getTypeName() << ": " << passiveHobbyPlacesStrings[this->place] << std::endl;
}
void PassiveHobby::setDescription()
{
  std::string input;
  int tmp;
  std::cout << "Please select the place of the " << PassiveHobby::getTypeName() << ": (1-" << passiveHobbyPlacesStrings.size() << "):" << std::endl;
  auto place = passiveHobbyPlacesStrings.cbegin();
  for(unsigned i = 1; i <= passiveHobbyPlacesStrings.size(); i++, place++)
    std::cout << i << ") " << place->second << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      tmp = std::stoi(input);
      if(tmp < 1 || tmp > (int)passiveHobbyPlacesStrings.size())
        throw "";
    }
    catch(...)
    {
      std::cout << "Incorrect answer!" << std::endl;
      continue;
    }
    auto place = passiveHobbyPlacesStrings.cbegin();
    for(int i = 1; i < tmp; i++)
      place++;
    this->place = place->first;
    break;
  }
}

std::string Jogging::typeName = "jogging";
void Jogging::initialize()
{
  hierarchy.addType(new Type(new Jogging(), false), Jogging::getTypeName(), ActiveHobby::getTypeName());
}

std::string Jogging::getTypeName()
{
  return Jogging::typeName;
}

void Jogging::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << Hobby::getTypeName() + " -> " + ActiveHobby::getTypeName() + ": " + Jogging::getTypeName() << std::endl;
  Hobby::getDescription(fileStream, prefix);
  ActiveHobby::getDescription(fileStream, prefix);
  fileStream << prefix << "* average jogging speed (m/h): " << this->averageSpeed << std::endl;
}
void Jogging::setDescription()
{
  std::string input;
  Hobby::setDescription();
  ActiveHobby::setDescription();
  while(true)
  {
    std::cout << "average jogging speed (m/h): ";
    getline(std::cin, input);
    try
    {
      this->averageSpeed = std::stod(input);
      if(this->averageSpeed <= 0)
        throw "";
      break;
    }
    catch(...)
    {
      std::cout << "Invalid answer! The answer must be a positive number." << std::endl;
    }
  }
}
Cloneable* Jogging::copy() const
{
  return new Jogging();
}

std::string Swimming::typeName = "swimming";
void Swimming::initialize()
{
  hierarchy.addType(new Type(new Swimming(), false), Swimming::getTypeName(), ActiveHobby::getTypeName());
}

std::string Swimming::getTypeName()
{
  return Swimming::typeName;
}

void Swimming::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << Hobby::getTypeName() << " -> " << ActiveHobby::getTypeName() << ": " << Swimming::getTypeName() << std::endl;
  Hobby::getDescription(fileStream, prefix);
  ActiveHobby::getDescription(fileStream, prefix);
  fileStream << prefix << "* favorite swimming style: " << ::swimmingStylesStrings[this->favoriteStyle] << std::endl;
}
void Swimming::setDescription()
{
  std::string input;
  int tmp;
  Hobby::setDescription();
  ActiveHobby::setDescription();
  std::cout << "Please select person's favorite swimming style (1-" << ::swimmingStylesStrings.size() << "):" << std::endl;
  auto iter = ::swimmingStylesStrings.cbegin();
  for(unsigned i = 1; i <= ::swimmingStylesStrings.size(); i++, iter++)
    std::cout << i << ") " << iter->second << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      tmp = std::stoi(input);
      if(tmp < 1 || tmp > (int)swimmingStylesStrings.size())
        throw "";
    }
    catch(...)
    {
      std::cout << "Incorrect answer!" << std::endl;
      std::cout << "Please select person's swimming style (1-" << ::swimmingStylesStrings.size() << "):" << std::endl;
      continue;
    }
    auto iter = ::swimmingStylesStrings.cbegin();
    for(int i = 1; i < tmp; i++)
      iter++;
    this->favoriteStyle = iter->first;
    break;
  }
}
Cloneable* Swimming::copy() const
{
  return new Swimming();
}

std::string Football::typeName = "football";
void Football::initialize()
{
  hierarchy.addType(new Type(new Football(), false), Football::getTypeName(), ActiveHobby::getTypeName());
}

std::string Football::getTypeName()
{
  return Football::typeName;
}

void Football::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << Hobby::getTypeName() + " -> " + ActiveHobby::getTypeName() + ": " + Football::getTypeName() << std::endl;
  Hobby::getDescription(fileStream, prefix);
  ActiveHobby::getDescription(fileStream, prefix);
  fileStream << prefix << "* favorite football position: " << ::footballPositionsStrings[this->favoritePosition] << std::endl;
}
void Football::setDescription()
{
  std::string input;
  int tmp;
  Hobby::setDescription();
  ActiveHobby::setDescription();
  std::cout << "Please select person's favorite football position (1-" << ::footballPositionsStrings.size() << "):" << std::endl;
  auto iter = ::footballPositionsStrings.cbegin();
  for(unsigned i = 1; i <= ::footballPositionsStrings.size(); i++, iter++)
    std::cout << i << ") " << iter->second << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      tmp = std::stoi(input);
      if(tmp < 1 || tmp > (int)footballPositionsStrings.size())
        throw "";
    }
    catch(...)
    {
      std::cout << "Incorrect answer!" << std::endl;
      std::cout << "Please select person's favorite football position (1-" << ::footballPositionsStrings.size() << "):" << std::endl;
      continue;
    }
    auto iter = ::footballPositionsStrings.cbegin();
    for(int i = 1; i < tmp; i++)
      iter++;
    this->favoritePosition = iter->first;
    break;
  }
}
Cloneable* Football::copy() const
{
  return new Football();
}

std::string Reading::typeName = "reading";
void Reading::initialize()
{
  hierarchy.addType(new Type(new Reading(), false), Reading::getTypeName(), PassiveHobby::getTypeName());
}

std::string Reading::getTypeName()
{
  return Reading::typeName;
}

void Reading::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << Hobby::getTypeName() + " -> " + PassiveHobby::getTypeName() + ": " + Reading::getTypeName() << std::endl;
  Hobby::getDescription(fileStream, prefix);
  PassiveHobby::getDescription(fileStream, prefix);
  fileStream << prefix << "* favorite genre: " << ::fictionAndFilmGenresStrings[this->favoriteGenre] << std::endl;
  fileStream << prefix << "* favorite book: " << this->favoriteBook << std::endl;
  fileStream << prefix << "* favorite author: " << this->favoriteAuthor << std::endl;
}
void Reading::setDescription()
{
  std::string input;
  int tmp;
  Hobby::setDescription();
  PassiveHobby::setDescription();
  std::cout << "Please select person's favorite book genre (1-" << ::fictionAndFilmGenresStrings.size() << "):" << std::endl;
  auto iter = ::fictionAndFilmGenresStrings.cbegin();
  for(unsigned i = 1; i <= ::fictionAndFilmGenresStrings.size(); i++, iter++)
    std::cout << i << ") " << iter->second << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      tmp = std::stoi(input);
      if(tmp < 1 || tmp > (int)fictionAndFilmGenresStrings.size())
        throw "";
    }
    catch(...)
    {
      std::cout << "Incorrect answer!" << std::endl;
      std::cout << "Please select person's favorite book genre (1-" << ::fictionAndFilmGenresStrings.size() << "):" << std::endl;
      continue;
    }
    auto iter = ::fictionAndFilmGenresStrings.cbegin();
    for(int i = 1; i < tmp; i++)
      iter++;
    this->favoriteGenre = iter->first;
    break;
  }
  std::cout << "favorite book: ";
  getline(std::cin, this->favoriteBook);
  std::cout << "favorite author: ";
  getline(std::cin, this->favoriteAuthor);
}
Cloneable* Reading::copy() const
{
  return new Reading();
}

std::string WatchingFilms::typeName = "watching films";
void WatchingFilms::initialize()
{
  hierarchy.addType(new Type(new WatchingFilms(), false), WatchingFilms::getTypeName(), PassiveHobby::getTypeName());
}

std::string WatchingFilms::getTypeName()
{
  return WatchingFilms::typeName;
}

void WatchingFilms::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << Hobby::getTypeName() + " -> " + PassiveHobby::getTypeName() + ": " + WatchingFilms::getTypeName() << std::endl;
  Hobby::getDescription(fileStream, prefix);
  PassiveHobby::getDescription(fileStream, prefix);
  fileStream << prefix << "* favorite genre: " << ::fictionAndFilmGenresStrings[this->favoriteGenre] << std::endl;
  fileStream << prefix << "* favorite film: " << this->favoriteFilm << std::endl;
  fileStream << prefix << "* favorite director: " << this->favoriteDirector << std::endl;
}
void WatchingFilms::setDescription()
{
  std::string input;
  int tmp;
  Hobby::setDescription();
  PassiveHobby::setDescription();
  std::cout << "Please select person's favorite film genre (1-" << ::fictionAndFilmGenresStrings.size() << "):" << std::endl;
  auto iter = ::fictionAndFilmGenresStrings.cbegin();
  for(unsigned i = 1; i <= ::fictionAndFilmGenresStrings.size(); i++, iter++)
    std::cout << i << ") " << iter->second << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      tmp = std::stoi(input);
      if(tmp < 1 || tmp > (int)fictionAndFilmGenresStrings.size())
        throw "";
    }
    catch(...)
    {
      std::cout << "Incorrect answer!" << std::endl;
      std::cout << "Please select person's favorite film genre (1-" << ::fictionAndFilmGenresStrings.size() << "):" << std::endl;
      continue;
    }
    auto iter = ::fictionAndFilmGenresStrings.cbegin();
    for(int i = 1; i < tmp; i++)
      iter++;
    this->favoriteGenre = iter->first;
    break;
  }
  std::cout << "favorite film: ";
  getline(std::cin, this->favoriteFilm);
  std::cout << "favorite director: ";
  getline(std::cin, this->favoriteDirector);
}
Cloneable* WatchingFilms::copy() const
{
  return new WatchingFilms();
}

std::string Gaming::typeName = "gaming";
void Gaming::initialize()
{
  hierarchy.addType(new Type(new Gaming(), false), Gaming::getTypeName(), PassiveHobby::getTypeName());
}

std::string Gaming::getTypeName()
{
  return Gaming::typeName;
}

void Gaming::getDescription(std::ostream& fileStream, const std::string& prefix) const
{
  fileStream << Hobby::getTypeName() + " -> " + PassiveHobby::getTypeName() + ": " + Gaming::getTypeName() << std::endl;
  Hobby::getDescription(fileStream, prefix);
  PassiveHobby::getDescription(fileStream, prefix);
  fileStream << prefix << "* favorite genre: " << ::computerGameGenresStrings[this->favoriteGenre] << std::endl;
  fileStream << prefix << "* favorite game: " << this->favoriteGame << std::endl;
}
void Gaming::setDescription()
{
  std::string input;
  int tmp;
  Hobby::setDescription();
  PassiveHobby::setDescription();
  std::cout << "Please select person's favorite game genre (1-" << ::computerGameGenresStrings.size() << "):" << std::endl;
  auto iter = ::computerGameGenresStrings.cbegin();
  for(unsigned i = 1; i <= ::computerGameGenresStrings.size(); i++, iter++)
    std::cout << i << ") " << iter->second << std::endl;
  while(true)
  {
    getline(std::cin, input);
    try
    {
      tmp = std::stoi(input);
      if(tmp < 1 || tmp > (int)computerGameGenresStrings.size())
        throw "";
    }
    catch(...)
    {
      std::cout << "Incorrect answer!" << std::endl;
      std::cout << "Please select person's favorite game genre (1-" << ::computerGameGenresStrings.size() << "):" << std::endl;
      continue;
    }
    auto iter = ::computerGameGenresStrings.cbegin();
    for(int i = 1; i < tmp; i++)
      iter++;
    this->favoriteGenre = iter->first;
    break;
  }
  std::cout << "favorite game: ";
  getline(std::cin, this->favoriteGame);
}
Cloneable* Gaming::copy() const
{
  return new Gaming();
}
