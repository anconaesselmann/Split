// Header file for Date class
// Author: Axel Esselmann
// Last edited: 10/11/2011

#ifndef DATE_H
#define DATE_H
#include <string>
namespace dateAnconaEsselmann {
    const int COUNTRY_US = 0;
    const int COUNTRY_GERMANY = 1;
    
    const int ORDER_MDY = 0;
    const int ORDER_DMY = 1;
    const int ORDER_YMD = 2;
    const int ORDER_MYD = 3;
    const int ORDER_DYM = 4;
    const int ORDER_YDM = 5;
    
    const int STYLE_LONG = 0;
    const int STYLE_SHORT = 1;
    
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
    /// Date class /////////////////////////////////////////////////////////////
    //
    // Date class has a day of week, day, month and year
    class Date {
        
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PUBLIC /////////////////////////////////////////////////////////////////
    public:
        /// CONSTRUCTORS ///////////////////////////////////////////////////////
        Date();
        // sets the date to Jan 1st 2000
        Date(int NumericDate);
        // Initializes Date with one integer value (the numeric date) The num-
        // eric date is based on the year 1600. A one is Jan 1st 1600, a 140941 
        // is Nov 19 1985, etc. This constructor is for testing purposes only, 
        // the enduser would have no use for this constructor, since he/she 
        // would have to know about the inner workings of the class Date
        Date(int month, int day, int year);
        // Initializes Date with three valid variables.
        Date(std::string dateString);
        // Initializes the date with a cstring date of format MM/DD/YYYY
        Date(const Date& copyDate);
        //
        Date& operator =(const Date& copyDate);
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// MUTATOR FUNKTIONS //////////////////////////////////////////////////
        bool set(int month, int day, int year);
        // sets Date to new variables.
        // sets the date to 12/31/1599 if the date entered was not correct and 
        // returns false  
        void set(const Date &D);
        // sets Date to the new date D
        void set(char *dateString);
        // converts a cstring of format MM/DD/YYYY to a date. 
        // Does not check for incorrect characters yet!!!!!
        void outputFormat(int Order, char Seperator, int Style, bool Zeros);
// update this definition!!!!!!!!!!!!!!!!
        bool day(int day);
        //sets the day of a date
        bool month(int month);
        // sets the month of the date
        bool year(int year);
        // sets the year of the date
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// ACCESSOR FUNKTIONS /////////////////////////////////////////////////
        int day() const;
        //returns the day of the date
        int month() const;
        // retuns the month of the date
        int year() const; 
        // returns the year of a date
        int getNum() const; 
        // returns the numeric Date (Jan 1st 1600 = 1)
        // This retriever funktion is useless to the enduser, 
        // it is included in the public section for testin purposes only.
        int dayOfWeek() const;
        // returns the day of the week as an integer.
        // Monday = 1, Tuesday = 2, Wednesday = 3, Thursday = 4, 
        // Friday = 5, Saturday = 6, Sunday = 7
        int daysThisMonth() const;
        // returns how many days are in the month of the date that called this 
        // function
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
        /// OTHER FUNKTIONS ////////////////////////////////////////////////////
        bool validDate(int month, int day, int year) const;
        // Validates a date and returns false if the date is not valid 
        bool validDate(const Date &D) const;
        // returns true if a date D is valid
        bool isLeapYear() const;
        // returns true if the year is a leap year (Not tested for dates BC yet,
        // for those this funktion might still be unreliable?
        Date next() const;
        // retrieves the next valid date as a Date class instance
        Date prev() const; 
        // retrieves the previous valid date as a Date class instance
        Date nextWeek() const; 
        // retrieves the next date with the same DOW
        Date prevWeek() const;
        // retrieves the previous date with the same DOW
        Date nextMonth() const;
        // retrieves the next date with the same day in the next month. If the
        // next month does not have the day because it is a shorter month the 
        // function will return the last day of the month
        Date prevMonth() const;
        // retrieves the next date with the same day in the previous month. If 
        // the next month does not have the day because it is a shorter month 
        // the function will return the last day of the month.
        Date nextYear() const; 
        // retrieves the next date with the same day in the next year
        Date prevYear() const; 
        // retrieves the previous date with the same day in the previous year
        Date add(int numberOfDaysToAdd) const;
        // adds a number of days to the date and returns the new date as a Date 
        Date sub(int numberOfDaysToSubtract) const;
        // subtracts a number of days from the date and returns the new Date
        int  sub(const Date &DayToSubtract) const;
        // subtracts a date from the date that called this function. 
        // Returns the number of days that seperate the two dates.
        int dayOfTheYear() const;
        // Returns how many days came before this date in this year
        int daysLeftThisYear() const;
        // returns how many days are left in the year
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
        /// OUTPUT FUNKTIONS ///////////////////////////////////////////////////
        void print(std::ostream &outs);
        void printLongUS(std::ostream &outs);
        // outputs Date: MM/DD/YYYY
        void printShortUS(std::ostream &outs);
        // outputs Date: MM/DD/YY
        void printLongGER(std::ostream &outs);
        // outputs Date: DD.MM.YYYY
        void printShortGER(std::ostream &outs);
        // outputs Date: DD.MM.YY
        void dayOfWeek(std::ostream &outs);
        // outputs the day of week written out (Monday, Tuesday...)
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// OVERLOADED OPERATORS ///////////////////////////////////////////////
        friend Date operator +(const Date &date, const int &numberOfDaysToAdd);
        // adds a number of days to a Date and returns a Date
        friend Date operator -(const Date &date, 
                               const int &numberOfDaysToSubtract);
        // subracts a number of days from a Date and returns a Date
        friend int  operator -(const Date &D1, const Date &D2);
        // adds a Date from a Date and returns the number of days between the 2
        friend bool operator ==(const Date &D1, const Date &D2);
        // tests if two Dates are equal
        friend bool operator  >(const Date &D1, const Date &D2);
        // tests if a Date is greater than another
        friend bool operator >=(const Date &D1, const Date &D2);
        // tests if a Date is greater than or equal to another
        friend bool operator  <(const Date &D1, const Date &D2);
        // tests if a Date is smaller than another
        friend bool operator <=(const Date &D1, const Date &D2);
        // tests if a Date is smaller than or equal to another
        friend Date operator ++(Date &prev);
        // prescript increment of Date, goes to the next valid Date
        friend Date operator ++(Date &prev, int);
        // postscript increment of Date goes to the next valid Date
        friend Date operator --(Date &prev);
        // prescript decrement of Date, goes to the previous valid Date
        friend Date operator --(Date &prev, int);
        // postscript decrement of Date, goes to the previous valid Date
        friend std::ostream& operator <<(std::ostream& outs, Date D);
        // overloads the insertin operator to output a date. Outputs in the 
        // Country and Style settings that were selected with outputFormat()
        
        
        friend std::istream& operator >>(std::istream& ins, Date& D);
        
        
        
        //friend std::istream& operator >>(std::istream& ins, Date &D);
        // overloads the extraction operator to accept a date in the forms
        // M/D/YYYY, MM/DD/YYYY or any combinations of the two
        
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PRIVATE ////////////////////////////////////////////////////////////////
    private:
        bool isLeapYear(int yearThis) const;
        // returns true if the year is a leap year (not sure if this still works 
        // for dates BC)
        int commonDaysPrevYears(int yearThis) const;
        // returns the days that have passed between Jan 1st 1600 and Jan 1st of 
        // yearThis
        int   leapDaysPrevYears(int yearThis) const;
        // returns the leap days that have passed between Jan 1st 1600 and 
        // Jan 1st of yearThis
        int daysThisYear(int month, int day, int year) const;
        // returns how many days have passed in a year with the date mont/day
        int daysLeftThisYear(int month, int day, int year) const;
        int daysThisMonth(int month, int year) const;
        // retrieves the number of days the month entered has
        
        int monthAndRemainder(int &remainder) const;
        // retuns the month of the date
        int  yearAndRemainder(int &remainder) const; 
        // retuns the year of the date
        
        int char_to_int(char character) const;
        // converts a character to an integer
        
        int getIntegerUntil(char *cStr, int &pos, char until) const;
        // takes a cstring and extracts an integer starting at pos until the 
        // character "until" is reached.
        // does not check if the character pesides "until" are actually integers
        // broke when soemthing other than '/'... Investigate! 
        // (\0 caused the issue...)
        /////// getIntegerUntil() SUPPORT FUNKTIONS ////////////////////////////
        int lengthCstr(char *cStr) const; 
        // returns the length of a cstring, including the null termination 
        // character
        char *getUntilChar(char *cStr, int pos, char until, 
                           int &lengthReturnChar, char *returnChar) const;
        // extracts a string from a Cstring starting with position pos, 
        // until the character "until" is reached or the end of the cstring.
        char *getInvertedCstr(char *cStr) const;
        // takes the string cStr and returns it inverted
        // updated on 10/04/11 DON'T USE OLDER VERSION! Memmory leak issues.
        int invertedCstrToInt(char *cStr) const;
        // takes the cString cStr and returns an inverted integer
        int getYearStyle();
        // gives a truncated version of year (YY in stead of YYYY)
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// VARIABLES AND CONSTANTS ////////////////////////////////////////////
        int numericDate;
        
        int outputOrder;
        char outputSeperator;
        int outputStyle; // length
        bool outputFillZeros; // true for filler zeros
        
        
        enum { YEAR_ZERO = 1600 }; //can be any value divisible by 400
    };
}
#endif