// Header file for Calender class
// Author: Axel Esselmann
// Last edited: 10/11/2011

#ifndef CALENDER_H
#define CALENDER_H
#include "date.h"
namespace dateAnconaEsselmann {
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// Calender class /////////////////////////////////////////////////////////
    class Calender { 
        
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PUBLIC /////////////////////////////////////////////////////////////////
    public:
        Calender();
        // zero argument constructor
        Calender(const Date &Start, const Date &End);
        // constructor that initializes the calender with a range that has a 
        // start Date and an end Date.
        void set(const Date &Start, const Date &End);
        // Sets the calender to a range that has a start Date and an end Date.
        // If the two were reversed, they are switched.
        void setFirstDOW(int DOW);
        // sets the day of week with which each line of the calender begins
        // mon = 1 ... sun = 7;
        // inappropriate numerical input sets the firstDOW to mon.
        void monthView();
        // sets the output to a monthly view
        void weekView();
        // sets the output to a weekly view
        friend std::ostream& operator <<(std::ostream &outs, Calender &cal);
        // output to ostream. The default output is one month after the other.
        // When weekView() is called, output will be one week after the other. 
        // Calling monthView() activates the default agian
        friend std::istream& operator >>(std::istream &ins, Calender &cal);
        // input from isteram. Currently >> can read dates in the 
        // form MM/DD/YYYY or M/D/YYYY or either combinaiton of the two.
        // To do: jan 1st yyyy, january 1, yyyy, combinations of 
        // the two, dd.mm.yyyy, d.m.yyyy
        
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PRIVATE ////////////////////////////////////////////////////////////////
    private:
        void printWeek(const Date & firstDayInRange, const Date &lastDayInRange, 
                       const Date &begin, Date &firstDayOfNextWeek, 
                       std::ostream &outs);
        // is called with << when weekView() has been called.
        Date firstDONextW(const Date &begin);
        // returns the first day of the next week
        void displayWeekHeader(std::ostream &outs);
        // Displays the days of week for the month view
        void displayWeek(const Date & firstDayInRange, 
                         const Date &lastDayInRange, const Date &begin, 
                         Date &firstDayOfNextWeek, std::ostream &outs);
        void printDOW(const int &day, std::ostream &outs);
        // Prints the Day Of Week
        void printMOY(const int &month, std::ostream &outs);
        // Prints the written out month
        void printMOYshort(const int &month, std::ostream &outs);
        // Prints a three letter abreviation of the month
        void printMonth(const Date &firstDayInRange, Date &firstDayOfNextMonth, 
                        std::ostream &outs);
        // Prints all days of a month, including a week header
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// VARIABLES //////////////////////////////////////////////////////////
        Date rangeStart;
        Date rangeEnd;
        int firstDOW;
        int view; // 0: view by month, 1: view by week;
    };
}
#endif
