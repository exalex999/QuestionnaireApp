/*///////////////////////////////
// Program: QuestionnaireApp  //
// Autor: Oleksandr Grygorenko //
// Prowadzacy: Piotr Witonski  //
// Projekt: #1601              //
// Zadanie: 3                  //
///////////////////////////////*/

#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <exception>
#include <string>
#include <map>
#include <iostream>

enum class MainTimePeriods
{
  DAY, WEEK, MONTH, YEAR
};
extern std::map<MainTimePeriods, std::string> mainTimePeriodsStrings;

class Date
{
private:
  int day;
  int month;
  int year;

public:
  static Date getCurrentDate();

  Date(int day, int month, int year);
  Date(const std::string& day, const std::string& month, const std::string& year);

  int getDay();
  int getMonth();
  int getYear();
  void setDay(int day);
  void setMonth(int month);
  void setYear(int year);

  bool operator<(const Date& date2) const;
  bool operator>(const Date& date2) const;
  bool operator<=(const Date& date2) const;
  bool operator>=(const Date& date2) const;
  bool operator==(const Date& date2) const;
  bool operator!=(const Date& date2) const;
  friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

class IncorrectDateFormatException : public std::exception
{
private:
  MainTimePeriods errorDateField;
public:
  IncorrectDateFormatException(MainTimePeriods errorDateField);

  MainTimePeriods getErrorDateField() const;
  const char* what() const throw();
};

#endif // DATE_H_INCLUDED
