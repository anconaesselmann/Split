// Implementation file for Date class
// Author: Axel Esselmann
// Last edited: 10/11/2011

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <string>
#include "date.h"

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/// Date class /////////////////////////////////////////////////////////////////
namespace dateAnconaEsselmann {
    Date::Date() {
        set(1,1,2000);
        outputFormat(ORDER_MDY, '/', STYLE_LONG, true); // sets the output format to MM/DD/YYYY
    }
    Date::Date(int NumericDate) {
        numericDate = NumericDate;
        outputFormat(ORDER_MDY, '/', STYLE_LONG, true); // sets the output format to MM/DD/YYYY
    }
    Date::Date(int month, int day, int year) {
        set(month, day, year);
        outputFormat(ORDER_MDY, '/', STYLE_LONG, true); // sets the output format to MM/DD/YYYY
    }
    Date::Date(std::string dateString) {
        using namespace std;
        
        char *cStr = new char [dateString.size()+1];
        strcpy(cStr, dateString.c_str());
        
        set(cStr);
        outputFormat(ORDER_MDY, '/', STYLE_LONG, true); // sets the output format to MM/DD/YYYY
    }
    Date::Date(const Date& copyDate) {
        numericDate = copyDate.numericDate;
        outputOrder = copyDate.outputOrder;
        outputSeperator = copyDate.outputSeperator;
        outputStyle = copyDate.outputStyle;
        outputFillZeros = copyDate.outputFillZeros;
    }
    Date& Date::operator =(const Date& copyDate) {
        if (this != & copyDate) {
            numericDate = copyDate.numericDate;
            outputOrder = copyDate.outputOrder;
            outputSeperator = copyDate.outputSeperator;
            outputStyle = copyDate.outputStyle;
            outputFillZeros = copyDate.outputFillZeros;
        }
        return *this;
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// MUTATOR FUNKTIONS //////////////////////////////////////////////////////
    bool Date::set(int month, int day, int year) {
        if (validDate(month, day, year)) {
            numericDate = commonDaysPrevYears(year) + leapDaysPrevYears(year) + daysThisYear( month, day, year);
            return true;
        } else {
            numericDate = 0;
            return false;
        }
    }   
    void Date::set(const Date &D) {
        numericDate = D.getNum();
    }
    void Date::set(char *dateString) {
        int month = 0,day = 0,year = 0,pos = 0;
        month =  getIntegerUntil(dateString, pos, '/');
        day = getIntegerUntil(dateString, pos, '/');
        year = getIntegerUntil(dateString, pos, '\0');
        set(month,day,year);
    }
    void Date::outputFormat(int Order, char Seperator, int Style, bool Zeros) {
        if (Order > 5) {
            outputOrder = 0;
        } else outputOrder = Order;
        outputSeperator = Seperator;
        if (Style == 1) {
            outputStyle = 1;
        } else outputStyle = 0;
        outputFillZeros = Zeros;
    }
    bool Date::day(int day) {
        int m = month();
        int y = year();
        return set(m, day, y);
    }
    bool Date::month(int month) {
        int d = day();
        int y = year();
        return set(month, d, y);
    }
    bool Date::year(int year) {
        int d = day();
        int m = month();
        return set(m, d, year);
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// ACCESSOR FUNKTIONS /////////////////////////////////////////////////////
    int Date::day() const {
        int number = numericDate;
        monthAndRemainder(number);
        return number;
    }
    int Date::month() const {
        int number = numericDate;
        return monthAndRemainder(number);
    }
    int Date::year() const {
        int number = numericDate;
        return yearAndRemainder(number);
    }
    int Date::getNum() const {
        return numericDate;
    }
    int Date::dayOfWeek() const {
        int dow = (abs(numericDate) % 7) - 2;
        if (dow < 1)
            dow = dow + 7;
        if (numericDate < 0) { //for dates before YEAR_ZERO
            dow = dow + (-2 * dow) + 10;
            if (dow > 7) {
                dow = dow - 7;
            }
        }
        return dow;
    }
    int Date::daysThisMonth() const {
        return daysThisMonth(month(),year());
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
    /// OTHER FUNKTIONS ////////////////////////////////////////////////////////
    bool Date::validDate(int month, int day, int year) const {
        if ((month <= 12) && (month >= 1) && (day <= daysThisMonth(month, year)) 
            && (day >= 1) ) 
            return true;
        else return false;
    }
    bool Date::validDate(const Date &D) const {
        return validDate(D.month(), D.day(), D.year());
    }
    bool Date::isLeapYear() const {
        return isLeapYear(year());
    }
    Date Date::next() const {
        return Date(numericDate + 1);
    }
    Date Date::prev() const {
        return Date(numericDate - 1);
    }
    Date Date::nextWeek() const {
        return Date(numericDate + 7);
    }
    Date Date::prevWeek() const {
        return Date(numericDate - 7);
    }
    Date Date::nextMonth() const {
        int d = day();
        int m = month() + 1;
        int y = year();
        Date newDate;
        
        if (m > 12) {
            m = 1;
            y = y + 1;
        }
        if (!newDate.set(m,d,y)) {
            d = daysThisMonth(m,y);
            newDate.set(m,d,y);
        }
        return newDate;
    }
    Date Date::prevMonth() const {
        int d = day();
        int m = month() - 1;
        int y = year();
        Date newDate;
        
        if (m < 1) {
            m = 12;
            y = y - 1;
        }
        if (!newDate.set(m,d,y)) {
            d = daysThisMonth(m,y);
            newDate.set(m,d,y);
        }
        return newDate;
    }
    Date Date::nextYear() const {
        int d = day();
        int m = month();
        int y = year() + 1;
        Date newDate;
        
        if (!newDate.set(m,d,y)) {
            d = daysThisMonth(m,y);
            newDate.set(m,d,y);
        }
        return newDate;
    }
    Date Date::prevYear() const {
        int d = day();
        int m = month();
        int y = year() - 1;
        Date newDate;
        
        if (!newDate.set(m,d,y)) {
            d = daysThisMonth(m,y);
            newDate.set(m,d,y);
        }
        return newDate;
    }
    Date Date::add(int numberOfDaysToAdd) const {
        return Date(numberOfDaysToAdd + numericDate);
    }
    Date Date::sub(int numberOfDaysToSubtract) const {
        return Date(numericDate - numberOfDaysToSubtract);
    }
    int Date::sub(const Date &DayToSubtract) const {
        return numericDate - DayToSubtract.getNum();
    }
    int Date::dayOfTheYear() const {
        return daysThisYear(month(), day(), year());
    }
    int Date::daysLeftThisYear() const {
        return -daysLeftThisYear(month(), day(), year());
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PRIVATE ////////////////////////////////////////////////////////////////
    bool Date::isLeapYear(int yearThis) const {
        if ( (yearThis % 4) == 0 ) {
            if ( ( (yearThis % 100) == 0 ) && !( (yearThis % 400) == 0 ) ) {
                return false;
            } else return true;
            
        } else return false;
    }
    int Date::commonDaysPrevYears(int yearThis) const {
        if (yearThis >= YEAR_ZERO) {
            return (yearThis - YEAR_ZERO) * 365;
        } else {
            return ( (yearThis - YEAR_ZERO) +1) * 365;
        }
    }
    int Date::leapDaysPrevYears(int yearThis) const {
        int yearPast = yearThis - 1;
        if (yearPast >= YEAR_ZERO) {
            int leapYears = 0;
            int comp = yearPast - YEAR_ZERO;
            for (int i = 0; i <= comp; i++) {
                if (isLeapYear(yearPast - i) ) {
                    leapYears++;
                }
            }
            return leapYears;
        } else {
            yearPast = yearThis + 1;
            int leapYears = 0;
            int comp = YEAR_ZERO - yearPast;
            for (int i = 0; i < comp; i++) {
                if (isLeapYear(yearPast + i) ) {
                    leapYears++;
                }
            }
            return -leapYears;
        }
        /*
         // This approach executes faster but I couldn't find a 
         //mistake I made that caused the result to be off by one
         int quatCentLeapDays = 0,centLeapDays = 0, remainingLeapDays = 0;
         quatCentLeapDays = ( (yearThis - YEAR_ZERO) / 400) * 97;
         centLeapDays = ( ( (yearThis - YEAR_ZERO) % 400) / 100 ) * 24;
         remainingLeapDays = ( ( ( (yearThis -YEAR_ZERO) % 400) % 100 ) / 4 );
         return quatCentLeapDays + centLeapDays + remainingLeapDays;*/
    }
    int Date::daysThisYear(int month, int day, int year) const {
        // returns how many days have passed in a year with the date mont/day
        int days = 0;
        if (year >= YEAR_ZERO) {
            switch (month) {
                case 1:
                    days = 0;
                    break;
                case 2:
                    days = 31;
                    break;
                case 3:
                    days = 59;
                    break;
                case 4:
                    days = 90; 
                    break;
                case 5:
                    days = 120; 
                    break;
                case 6:
                    days = 151; 
                    break;
                case 7:
                    days = 181; 
                    break;
                case 8:
                    days = 212; 
                    break;
                case 9:
                    days = 243; 
                    break;
                case 10:
                    days = 273;
                    break;
                case 11:
                    days = 304;
                    break;
                case 12:
                    days = 334;
                    break;
                default:
                    break;
            }
            if ( isLeapYear(year) && (month > 2) )
                days++;
            days = days + day;
            return days;
        } else { // year is less than YEAR_ZERO
            return daysLeftThisYear(month,day,year);
        }
        
    }
    int Date::daysLeftThisYear(int month, int day, int year) const {
        int days = 0;
        switch (month) {
            case 11:
                days = 31;
                break;
            case 10:
                days = 61;
                break;
            case 9:
                days = 92;
                break;
            case 8:
                days = 122;
                break;
            case 7:
                days = 153;
                break;
            case 6:
                days = 184;
                break;
            case 5:
                days = 214;
                break;
            case 4:
                days = 245;
                break;
            case 3:
                days = 275;
                break;
            case 2:
                days = 303;
                break;
            case 1:
                days = 334;
                break;
            default:
                break;
        }
        if (isLeapYear(year))
            if (month < 2) {
                days = days + 1;
            }
        days = days + (daysThisMonth(month, year) - day);
        if (month == 2) {// Why TF is this necessary???? 
            days = days + 3;
        }
        return -days;
    }
    int Date::daysThisMonth(int month, int year) const {
        int days = 31, test = month;
        if (test > 7) 
            test++;
        if ( (test%2) == 0) 
            days = 30;
        if (month == 2)
            if (isLeapYear(year)) {
                days = 29;
            } else days = 28;
        return days;
    }
    int Date::monthAndRemainder(int &remainder) const {
        int yearThis = yearAndRemainder(remainder);
        int returnMonth = 1;
        if (remainder > 31) { // at least february
            remainder = remainder - 31;
            returnMonth++;
            if (remainder > 28) {
                remainder = remainder - 28;
                if (isLeapYear(yearThis)) { // at least march
                    if (remainder > 1) {
                        remainder = remainder -1;
                        returnMonth++;
                    } else remainder = remainder + 28;
                } else returnMonth++;
                if (remainder > 31) { // at least april
                    remainder = remainder - 31;
                    returnMonth++;
                    if (remainder > 30) { // at least may
                        remainder = remainder - 30;
                        returnMonth++;
                        if (remainder > 31) { // at least june
                            remainder = remainder - 31;
                            returnMonth++;
                            if (remainder > 30) { // at least july
                                remainder = remainder - 30;
                                returnMonth++;
                                if (remainder > 31) { // at least august
                                    remainder = remainder - 31;
                                    returnMonth++;
                                    if (remainder > 31) { // at lst september
                                        remainder = remainder - 31;
                                        returnMonth++;
                                        if (remainder > 30) { // at lst oktober
                                            remainder = remainder - 30;
                                            returnMonth++;
                                            if (remainder > 31) { // at least november
                                                remainder = remainder - 31;
                                                returnMonth++;
                                                if (remainder > 30) {
                                                    remainder = remainder - 30;
                                                    returnMonth++;
                                                }
                                            }
                                        }   
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return returnMonth;
    }
    int Date::yearAndRemainder(int &remainder) const {
        int years,sub;
        int yearLength;
        remainder = abs(numericDate);
        if (numericDate > 0) {
            years = 0;
            yearLength = 365 + 1;
            sub = 0;
        } else {
            years = 1;
            yearLength = 365;
            sub = 1;
        }
        while ( ((remainder + sub) - yearLength) > 0 ) {
            remainder = remainder - yearLength;
            years++;
            if (isLeapYear(years))
                yearLength = 365 + 1;
            else yearLength = 365;
        }
        // if numericDate is negative the remainder and the return year have to be changed
        if (numericDate > 0) {
            return years + YEAR_ZERO;
        } else {
            int y = YEAR_ZERO - (years);
            remainder = 365 - remainder;
            if (isLeapYear(y)) { 
                ++remainder;
            }
            return y;
        }
    }
    int Date::char_to_int(char character) const {
        return character - '0';
    }
    int Date::getIntegerUntil(char *cStr, int &pos, char until) const {
        char *temp;
        int lengthReturnChar,returnInt;
        temp = new char[strlen(cStr)];
        getUntilChar(cStr, pos,until,lengthReturnChar,temp);
        getInvertedCstr(temp);
        pos = pos + lengthReturnChar;
        returnInt = invertedCstrToInt(temp);
        delete [] temp;
        return returnInt;
    } 
    int Date::getYearStyle() {
        if (outputStyle == STYLE_SHORT) {
            return year() - ( (year() / 100) * 100 );
        } else return year();
    }
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /////// getIntegerUntil() SUPPORT FUNKTIONS ////////////////////////////////
    int Date::lengthCstr(char *cStr) const {
        int i = 0;
        char next;
        do {
            next = cStr[i];
            i++;
        } while (next != '\0');
        return i;
    }
    char* Date::getUntilChar(char *cStr, int pos, char until, 
                             int &lengthReturnChar, char *returnChar) const {
        int i = pos;
        char next;
        do {
            next = cStr[i];
            i++;
        } while ( (next != until) && (next != '\0')  && (next != '\n')  && (next != ' ') );
        lengthReturnChar = i - pos;
        for (int i = 0; i < lengthReturnChar - 1; i++) {
            returnChar[i] = cStr[pos + i];
        }
        returnChar[lengthReturnChar - 1] = '\0';
        return returnChar;
    }
    char* Date::getInvertedCstr(char *cStr) const {
        // takes the string cStr and returns it inverted
        // updated on 10/04/11 DON'T USE OLDER VERSION! Memmory leak issues.
        char *front = cStr, *back = front + strlen(cStr) -1,temp;
        while (front < back) {
            temp = *front;
            *front = *back;
            *back = temp;
            front++;
            back--;
        }
        return cStr;
    }
    int Date::invertedCstrToInt(char *cStr) const {
        int returnInt = 0;
        for (int i = 0; i < ( lengthCstr(cStr) - 1); i++) {
            returnInt = returnInt + ( char_to_int(cStr[i]) * pow(10, i) );
        }
        return returnInt;
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// OUTPUT AND OVERLOADED OPERATORS ////////////////////////////////////////
    void Date::dayOfWeek(std::ostream &outs) {
        using namespace std;
        int remainder = dayOfWeek();
        switch (remainder) {
            case 7:
                outs << "Sunday";
                break;
            case 1:
                outs << "Monday";
                break;
            case 2:
                outs << "Tuesday";
                break;
            case 3:
                outs << "Wednesday";
                break;
            case 4:
                outs << "Thursday";
                break;
            case 5:
                outs << "Friday";
                break;
            case 6:
                outs << "Saturday";
                break;
                
            default:
                break;
        }
    }
    void Date::printLongUS(std::ostream &outs) {
        outs << month() << "/" << day() << "/" << year();
    }
    void Date::printShortUS(std::ostream &outs) {
        int YEAR = year() - ( (year() / 100) * 100 );
        if (YEAR != 0) {
            outs << month() << "/" << day() << "/" << YEAR;
        } else outs << month() << "/" << day() << "/00";
    }
    void Date::printLongGER(std::ostream &outs) {
        outs << day() << "." << month() << "." <<  year();
    }
    void Date::printShortGER(std::ostream &outs) {
        int YEAR = year() - ( (year() / 100) * 100 );
        if (YEAR != 0) {
            outs << day() << "." << month() << "." << YEAR;
        } else outs << month() << "/" << day() << "/00";
    }
    /*
    std::istream& operator >>(std::istream& ins, Date &D) {
        // uses <vector>, <iostrem>
        char next = ins.get();
        std::vector<char>v;         // is this too awkward?
        while (!isspace(next)) {
            v.push_back(next);
            next = ins.get();
        }
        v.push_back('\0');
        
        char *outputString;
        outputString = new char[v.size()+1]; // gets deleted before return
        for (int i = 0; i < v.size(); i++)
            outputString[i] = v[i];
        outputString[v.size()] = '\0';
        D.set(outputString);
        delete [] outputString;
        return ins;
    }*/
    std::istream& operator >>(std::istream& ins, Date& D) {
        // make >> dependent on what order the date is output and wht the spacer is!!!!!!!!!!!!!!!!!!!!!!!
        int year,month,day;
        ins >> year;
        ins.get();
        ins >> month;
        ins.get();
        ins >> day;
        D = Date(month, day, year);
        return ins;
    }
    
    std::ostream& operator <<(std::ostream& outs, Date D) {
        std::string DAY_ZEROS = "";
        std::string MONTH_ZEROS = "";
        std::string YEAR_ZEROS = "";
        
        if (D.outputStyle == STYLE_SHORT) {
            if (D.year() > 99) {
                if (D.getYearStyle() < 10) {
                    YEAR_ZEROS = "0";
                }
            }
        }
        if (D.outputFillZeros) {
            if (D.day() < 10)
                DAY_ZEROS = "0";
            if (D.month() < 10)
                MONTH_ZEROS = "0";
        }
        switch (D.outputOrder) {
            case ORDER_MDY:
                outs    << MONTH_ZEROS << D.month() 
                        << D.outputSeperator 
                        << DAY_ZEROS << D.day() 
                        << D.outputSeperator 
                        << YEAR_ZEROS << D.getYearStyle();
                break;
            case ORDER_DMY:
                outs    << DAY_ZEROS << D.day() 
                        << D.outputSeperator
                        << MONTH_ZEROS << D.month() 
                        << D.outputSeperator  
                        << YEAR_ZEROS << D.getYearStyle();
                break;
            case ORDER_YMD:
                outs    << YEAR_ZEROS << D.getYearStyle()
                        << D.outputSeperator
                        << MONTH_ZEROS << D.month() 
                        << D.outputSeperator 
                        << DAY_ZEROS << D.day();
                break;
            case ORDER_MYD:
                outs    << MONTH_ZEROS << D.month() 
                        << D.outputSeperator 
                        << YEAR_ZEROS << D.getYearStyle()
                        << D.outputSeperator 
                        << DAY_ZEROS << D.day();
                break;
            case ORDER_DYM:
                outs    << DAY_ZEROS << D.day() 
                        << D.outputSeperator 
                        << YEAR_ZEROS << D.getYearStyle()
                        << D.outputSeperator
                        << MONTH_ZEROS << D.month(); 
                break;
            case ORDER_YDM:
                outs    << YEAR_ZEROS << D.getYearStyle()
                        << D.outputSeperator
                        << DAY_ZEROS << D.day() 
                        << D.outputSeperator
                        << MONTH_ZEROS << D.month();
                break;
                
            default:
                break;
        }
        return outs;
    }
    bool operator ==(const Date &D1, const Date &D2) {
        if (D1.numericDate == D2.numericDate) {
            return true;
        } return false;
    }
    bool operator  >(const Date &D1, const Date &D2) {
        if (D1.numericDate > D2.numericDate) {
            return true;
        } return false;
    }
    bool operator >=(const Date &D1, const Date &D2) {
        if (D1.numericDate >= D2.numericDate) {
            return true;
        } return false;
    }
    bool operator  <(const Date &D1, const Date &D2) {
        if (D1.numericDate < D2.numericDate) {
            return true;
        } return false;
    }
    bool operator <=(const Date &D1, const Date &D2) {
        if (D1.numericDate <= D2.numericDate) {
            return true;
        } return false;
    }
    Date operator ++(Date &prev) {
        prev.numericDate = prev.numericDate + 1;
        return prev;
    }
    Date operator ++(Date &prev, int) {
        Date temp = prev.numericDate;
        prev.numericDate = prev.numericDate + 1;
        return temp;
    }
    Date operator --(Date &prev) {
        prev.numericDate = prev.numericDate - 1;
        return prev;
    }
    Date operator --(Date &prev, int) {
        Date temp = prev.numericDate;
        prev.numericDate = prev.numericDate - 1;
        return temp;
    }
    Date operator +(const Date &date, const int &numberOfDaysToAdd) {
        return Date(numberOfDaysToAdd + date.numericDate);
    }
    Date operator -(const Date &date, const int &numberOfDaysToSubtract) {
        return Date(date.numericDate - numberOfDaysToSubtract);
    }
    int  operator -(const Date &D1, const Date &D2) {
        return D1.numericDate - D2.numericDate;
    }
}