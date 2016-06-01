/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#ifndef HOBBYANDRELATED_H_INCLUDED
#define HOBBYANDRELATED_H_INCLUDED

#include "Base.h"
#include "Date.h"

class Hobby;
class ActiveHobby;
class PassiveHobby;
class Jogging;
class Swimming;
class Football;
class Reading;
class WatchingFilms;
class Gaming;

enum class PassiveHobbyPlaces
{
  HOME, WITHFRIENDSATTHEIRHOME, INPARK, INTHEINTERESTCLUB, INTRANSPORT, OTHER
};
extern std::map<PassiveHobbyPlaces, std::string> passiveHobbyPlacesStrings;

enum class SwimmingStyles
{
  FRONTCRAWL, TRUDGEN, BUTTERFLYSTROKE, BREASTSTROKE, BACKSTROKE, SIDESTROKE, DOGPADDLE, SNORKELING, FINSWIMMING, OTHER
};
extern std::map<SwimmingStyles, std::string> swimmingStylesStrings;

enum class FootballPositions
{
  GOALKEEPER, DEFENDER, MIDFIELDER, FORWARD
};
extern std::map<FootballPositions, std::string> footballPositionsStrings;

enum class FictionAndFilmGenres
{
  ADVENTURE, CLASSIC, DETECTIVE, FANTASY, FOLKLORE, HISTORICALFICTION, HORROR, HUMOR, LEGEND, MYSTERY, MYTHOLOGY, REALISTICFICTION, THRILLER, WESTERN, OTHER
};
extern std::map<FictionAndFilmGenres, std::string> fictionAndFilmGenresStrings;

enum class ComputerGameGenres
{
  ACTION, SHOOTER, ADVENTURE, ROLEPLAYING, SIMULATION, STRATEGY, SPORTS, OTHER
};
extern std::map<ComputerGameGenres, std::string> computerGameGenresStrings;

struct Frequency
{
public:
  int times;
  MainTimePeriods period;

  Frequency(double times, MainTimePeriods period);
};

class Hobby : public Describable, public Cloneable
{
private:
  static std::string typeName;

  Frequency *engagementFrequency;
  double averageDuration;  // hours
public:

  static void initialize();
  static std::string getTypeName();

  ~Hobby();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const = 0;
  void setDescription() = 0;
};

class ActiveHobby : public Hobby
{
private:
  static std::string typeName;

  bool ifProfessional;
  std::string place;
public:
  static void initialize();
  static std::string getTypeName();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const = 0;
  void setDescription() = 0;
};

class PassiveHobby : public Hobby
{
private:
  static std::string typeName;

  PassiveHobbyPlaces place;
public:
  static void initialize();
  static std::string getTypeName();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const = 0;
  void setDescription() = 0;
};

class Jogging : public ActiveHobby
{
private:
  static std::string typeName;

  double averageSpeed; // m/h
public:
  static void initialize();
  static std::string getTypeName();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

class Swimming : public ActiveHobby
{
private:
  static std::string typeName;

  SwimmingStyles favoriteStyle;
public:
  static void initialize();
  static std::string getTypeName();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

class Football : public ActiveHobby
{
private:
  static std::string typeName;

  FootballPositions favoritePosition;
public:
  static void initialize();
  static std::string getTypeName();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

class Reading : public PassiveHobby
{
private:
  static std::string typeName;

  FictionAndFilmGenres favoriteGenre;
  std::string favoriteBook;
  std::string favoriteAuthor;
public:
  static void initialize();
  static std::string getTypeName();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

class WatchingFilms : public PassiveHobby
{
private:
  static std::string typeName;

  FictionAndFilmGenres favoriteGenre;
  std::string favoriteFilm;
  std::string favoriteDirector;
public:
  static void initialize();
  static std::string getTypeName();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

class Gaming : public PassiveHobby
{
private:
  static std::string typeName;

  ComputerGameGenres favoriteGenre;
  std::string favoriteGame;
public:
  static void initialize();
  static std::string getTypeName();

  void getDescription(std::ostream& fileStream, const std::string& prefix) const;
  void setDescription();
  Cloneable* copy() const;
};

#endif // HOBBYANDRELATED_H_INCLUDED
