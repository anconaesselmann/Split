// Implementation file for Calender class
// Author: Axel Esselmann
// Last edited: 10/11/2011

#include <iostream>
#include "calender.h"

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/// Calender class /////////////////////////////////////////////////////////////
namespace dateAnconaEsselmann {    
    Calender::Calender() {
        rangeStart = 0;
        rangeEnd = 0;
        firstDOW = 1;
        view = 0;
    }
    Calender::Calender(const Date &Start, const Date &End) {
        set(Start, End);
        firstDOW = 1;
        view = 0; 
    }
    void Calender::set(const Date &Start, const Date &End) {
        if (End < Start) {
            rangeEnd = Start;
            rangeStart = End;
        } else {
            rangeStart = Start;
            rangeEnd = End;
        }
        firstDOW = 1;
    }
    void Calender::setFirstDOW(int DOW) {
        if ( (DOW <= 7) && (DOW >= 1) ) {
            firstDOW = DOW;
        } else firstDOW = 1;
    }
    void Calender::monthView() {
        view = 0;
    }
    void Calender::weekView() {
        view = 1;
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PRIVATE ////////////////////////////////////////////////////////////////
    void Calender::printWeek(const Date & firstDayInRange, 
                             const Date &lastDayInRange, const Date &begin, 
                             Date &firstDayOfNextWeek, std::ostream &outs) {
        int i = 0;
        if ( begin.month() == (firstDONextW(begin) -1).month() ) {
            printMOYshort(begin.month(),outs);
        } else {
            printMOYshort(begin.month(),outs);
            outs << " / ";
            printMOYshort((firstDONextW(begin)).month(),outs);
        }
        outs << " " <<begin.year() << ", Week " 
             << ( begin.dayOfTheYear() + (firstDONextW(begin) - (begin+2)) )/7 + 1
             << "\n___________________________\n";
        
        int subt = 0;
        if (firstDOW > begin.dayOfWeek()) {
            subt = begin.dayOfWeek() + 7 - firstDOW;
        } else subt = begin.dayOfWeek() - firstDOW;
        
        for (int n = 0; n < 7; n++) { // does this only work for positive dates?
            if ( n >= subt) {
                if ( ( (begin + (i + 1) ) > firstDayInRange ) 
                        && ( (begin + (i - 1) ) < lastDayInRange )  ) {
                    printDOW((begin + i).dayOfWeek(),outs);
                    outs << "  " << (begin + i).day() << "\n";
                } else { 
                    if ( (n + firstDOW) > 7) {  
                        printDOW((n + firstDOW) - 7,outs);
                    } else printDOW((n + firstDOW),outs);
                    outs << "\n";
                }
                i++;
            } else {
                if ( (n + firstDOW) > 7) {  
                    printDOW((n + firstDOW) - 7,outs);
                } else printDOW((n + firstDOW),outs);
                outs << "\n";
            }
        }
        outs << "___________________________\n";
        firstDayOfNextWeek = firstDONextW(begin);
    }
    Date Calender::firstDONextW(const Date &begin) {
        int subt = 0;
        if (firstDOW > begin.dayOfWeek()) {
            subt = begin.dayOfWeek() + 7 - firstDOW;
        } else subt = begin.dayOfWeek() - firstDOW;
        return begin + (7 - subt);
    }
    void Calender::displayWeekHeader(std::ostream &outs) {
        for (int i = firstDOW; i < 7 + firstDOW; i++) {
            if (i<=7) {
                printDOW(i,outs);
                outs << " ";
            } else {
                printDOW(i - 7,outs);
                outs << " ";
            }
            
        }
        endl(outs);
    }
    void Calender::displayWeek(const Date & firstDayInRange, const 
                               Date &lastDayInRange, const Date &begin, 
                               Date &firstDayOfNextWeek, std::ostream &outs) {
        int i = 0;
        
        int subt = 0;
        if (firstDOW > begin.dayOfWeek()) {
            subt = begin.dayOfWeek() + 7 - firstDOW;
        } else subt = begin.dayOfWeek() - firstDOW;
        
        for (int n = 0; n < 7; n++) { // does this only work for positive dates?
            if ( n >= subt) {
                if ( ( (begin + (i + 1) ) > firstDayInRange ) 
                        && ( (begin + (i - 1) ) < lastDayInRange )  ) {
                    if ((begin + i).day() < 10) {
                        outs << " ";
                    }
                    outs << (begin + i).day() << "  ";
                } else outs << "    ";
                i++;
            } else outs << "    ";
        }
        firstDayOfNextWeek = firstDONextW(begin);
    }
    void Calender::printDOW(const int &day, std::ostream &outs) {
        switch (day) {
            case 7:
                outs << "Sun";
                break;
            case 1:
                outs << "Mon";
                break;
            case 2:
                outs << "Tue";
                break;
            case 3:
                outs << "Wed";
                break;
            case 4:
                outs << "Thu";
                break;
            case 5:
                outs << "Fri";
                break;
            case 6:
                outs << "Sat";
                break;
                
            default:
                break;
        }
    }
    void Calender::printMOY(const int &month, std::ostream &outs) {
        switch (month) {
            case 1:
                outs << "January";
                break;
            case 2:
                outs << "February";
                break;
            case 3:
                outs << "March";
                break;
            case 4:
                outs << "April";
                break;
            case 5:
                outs << "May";
                break;
            case 6:
                outs << "June";
                break;
            case 7:
                outs << "July";
                break;
            case 8:
                outs << "August";
                break;
            case 9:
                outs << "September";
                break;
            case 10:
                outs << "October";
                break;
            case 11:
                outs << "November";
                break;
            case 12:
                outs << "December";
                break;
                
            default:
                break;
        }
    }
    void Calender::printMOYshort(const int &month, std::ostream &outs) {
        switch (month) {
            case 1:
                outs << "Jan";
                break;
            case 2:
                outs << "Feb";
                break;
            case 3:
                outs << "Mar";
                break;
            case 4:
                outs << "Apr";
                break;
            case 5:
                outs << "May";
                break;
            case 6:
                outs << "Jun";
                break;
            case 7:
                outs << "Jul";
                break;
            case 8:
                outs << "Aug";
                break;
            case 9:
                outs << "Sep";
                break;
            case 10:
                outs << "Oct";
                break;
            case 11:
                outs << "Nov";
                break;
            case 12:
                outs << "Dec";
                break;
                
            default:
                break;
        }
    }
    void Calender::printMonth(const Date &firstDayInRange, 
                              Date &firstDayOfNextMonth, std::ostream &outs) {
        Date lastDayOfMonth;
        Date fistDayOfNextWeek = firstDayInRange;
        int month = firstDayInRange.month();
        int year = firstDayInRange.year();
        
        // set the last day of the month for this funktion to use
        lastDayOfMonth.set(month, firstDayInRange.daysThisMonth(), year);
        if (lastDayOfMonth > rangeEnd) {
            lastDayOfMonth = rangeEnd;
        }
        
        // Printing the hearder for the month
        outs << "\t";
        printMOY(month, outs);
        outs << ", " << year << "\n___________________________\n";
        displayWeekHeader(outs);
        outs << "___________________________\n";
        
        // printing each week for the month
        while (lastDayOfMonth >= fistDayOfNextWeek) { //only for positive???
            displayWeek(firstDayInRange, lastDayOfMonth, fistDayOfNextWeek,
                        fistDayOfNextWeek,outs);
            endl(outs);
        }
        
        // returning the first day of the next month (I might turn this into a 
        // class property of Date, just like first day of next week? store start 
        // week with day in private of date?)
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
        firstDayOfNextMonth.set(month, 1, year);
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// OVERLOADED OPERATORS ///////////////////////////////////////////////////
    std::ostream& operator <<(std::ostream &outs, Calender &cal) {
        // output to ostream. The default output is one month after the other.
        // When weekView() is called, output will be one week after the other. 
        // Calling monthView() activates the default agian
        Date firstDayOfNextMonth = cal.rangeStart; 
        switch (cal.view) {
            case 0: // displays the calender month by month 
                while (firstDayOfNextMonth <= cal.rangeEnd) {
                    cal.printMonth(firstDayOfNextMonth,firstDayOfNextMonth,outs);
                    endl(outs);
                }
                break;
            case 1: // displays the calender week by week
                while (firstDayOfNextMonth <= cal.rangeEnd) {
                    cal.printWeek(firstDayOfNextMonth, cal.rangeEnd, 
                                  firstDayOfNextMonth, firstDayOfNextMonth, outs);
                    endl(outs);
                }
                break;            
                
            default:
                break;
        }
        return outs;
    }
    std::istream& operator >>(std::istream &ins, Calender &cal) {
        // input from isteram. Currently >> can read dates in the 
        // form MM/DD/YYYY or M/D/YYYY or either combinaiton of the two.
        // To do: jan 1st yyyy, january 1, yyyy, combinations of 
        // the two, dd.mm.yyyy, d.m.yyyy
        Date rangeStart, rangeEnd;
        ins >> rangeStart >> rangeEnd;
        cal.set(rangeStart, rangeEnd);
        return ins;
    }
}