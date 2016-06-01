/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#include <ctime>
#include "Date.h"

std::map<MainTimePeriods, std::string> mainTimePeriodsStrings = {{MainTimePeriods::DAY, "day"},
                                                                 {MainTimePeriods::WEEK, "week"},
                                                                 {MainTimePeriods::MONTH, "month"},
                                                                 {MainTimePeriods::YEAR, "year"}};

Date Date::getCurrentDate()
{
  time_t t = time(nullptr);
  struct tm *now = localtime(&t);
  return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
}

Date::Date(int day, int month, int year)
{
  try
  {
    this->setDay(day);
    this->setMonth(month);
    this->setYear(year);
  }
  catch(const IncorrectDateFormatException&)
  {
    throw;
  }
}
Date::Date(const std::string& day, const std::string& month, const std::string& year)
{
  int i_day, i_month, i_year;
  try
  {
    i_day = std::stoi(day);
  }
  catch(...)
  {
    throw IncorrectDateFormatException(MainTimePeriods::DAY);
  }
  try
  {
    i_month = std::stoi(month);
  }
  catch(...)
  {
    throw IncorrectDateFormatException(MainTimePeriods::MONTH);
  }
  try
  {
    i_year = std::stoi(year);
  }
  catch(...)
  {
    throw IncorrectDateFormatException(MainTimePeriods::YEAR);
  }
  this->setDay(i_day);
  this->setMonth(i_month);
  this->setYear(i_year);
}
int Date::getDay()
{
  return this->day;
}
int Date::getMonth()
{
  return this->month;
}
int Date::getYear()
{
  return this->year;
}
void Date::setDay(int day)
{
  if(day < 1 || day > 31)
    throw IncorrectDateFormatException(MainTimePeriods::DAY);
  this->day = day;
}
void Date::setMonth(int month)
{
  if(month < 1 || month > 12)
    throw IncorrectDateFormatException(MainTimePeriods::MONTH);
  this->month = month;
}
void Date::setYear(int year)
{
  if(year < 1)
    throw IncorrectDateFormatException(MainTimePeriods::YEAR);
  this->year = year;
}

bool Date::operator<(const Date& date2) const
{
  return (this->year < date2.year || (this->year == date2.year && (this->month < date2.month || (this->month == date2.month && this->day < date2.day))));
}
bool Date::operator>(const Date& date2) const
{
  return (this->year > date2.year || (this->year == date2.year && (this->month > date2.month || (this->month == date2.month && this->day > date2.day))));
}
bool Date::operator<=(const Date& date2) const
{
  return (this->year < date2.year || (this->year == date2.year && (this->month < date2.month || (this->month == date2.month && this->day <= date2.day))));
}
bool Date::operator>=(const Date& date2) const
{
  return(this->year > date2.year || (this->year == date2.year && (this->month > date2.month || (this->month == date2.month && this->day >= date2.day))));
}
bool Date::operator==(const Date& date2) const
{
  return (this->year == date2.year && this->month == date2.month && this->day == date2.day);
}
bool Date::operator!=(const Date& date2) const
{
  return !(*this == date2);
}
std::ostream& operator<<(std::ostream& os, const Date& date)
{
  os << date.day << "." << date.month << "." << date.year;
  return os;
}

IncorrectDateFormatException::IncorrectDateFormatException(MainTimePeriods errorDateField) : errorDateField(errorDateField)
{}

MainTimePeriods IncorrectDateFormatException::getErrorDateField() const
{
  return this->errorDateField;
}
const char* IncorrectDateFormatException::what() const throw()
{
  return ("Invalid date format! Error field: " + mainTimePeriodsStrings[this->errorDateField]).c_str();
}
