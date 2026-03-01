// main.cpp
// Date: 1/20/2026
// Author: Zachary Miles


#include <iostream>
#include <string>
#include <limits>

using std::string;

// Global variables to store the current time
static unsigned int g_hour = 0;
static unsigned int g_minute = 0;
static unsigned int g_second = 0;

// Getter functions
unsigned int getHour() { return g_hour; }
unsigned int getMinute() { return g_minute; }
unsigned int getSecond() { return g_second; }

// Setter functions
void setHour(unsigned int h) { g_hour = h; }
void setMinute(unsigned int m) { g_minute = m; }
void setSecond(unsigned int s) { g_second = s; }

// Adds a 0 in front of single digit numbers
string twodigitString (unsigned int n) {
    if (n < 10) {
        return "0" + std::to_string(n);
    }
    return std::to_string(n);
}

// Returns a string with n copies of character c
string nCharString (size_t n, char c) {
    return string(n, c);
}

// Formats time in 24-hour format
string formatTime24 (unsigned int h, unsigned int m, unsigned int s) {
    return twodigitString(h) + ":" + twodigitString(m) + ":" + twodigitString(s);
}

// Formats time in 12-hour format
string formatTime12 (unsigned int h, unsigned int m, unsigned int s) {
    string period; 
    unsigned int hour12;
    if (h == 0) {
        hour12 = 12;
        period = "A M";
    } else if (h < 12) {
        hour12 = h;
        period = "A M";
    } else if (h == 12) {
        hour12 = 12;
        period = "P M";
    } else {
        hour12 = h - 12;
        period = "P M";
    }

    return twodigitString(hour12) + ":" + twodigitString(m) + ":" + twodigitString(s) + " " + period;
}

// Displays Menu with proper formatting
void printMenu(char * strings[], unsigned int numStrings, unsigned char width) {
    std::cout << nCharString(width, '*') << std::endl;

    for (unsigned int i = 0; i < numStrings; ++i) {
        string itemText = strings[i];

        string left = "* " + std::to_string(i + 1) + " - " + itemText;
        size_t spacesNeeded = 0;

        if (width > left.length() + 1) {
            spacesNeeded = width - (left.length() + 1);
        }

        std::cout << left << nCharString(spacesNeeded, ' ') << "*" << std::endl;

        if (i + 1 < numStrings) {
            std::cout << std::endl;
        }
    }
    std::cout << nCharString(width, '*') << std::endl;
}

// Gets valid menu choice from user
unsigned int getMenuChoice(unsigned int maxChoice) {
    unsigned int choice;
    while (true) {
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
    }
        if (choice >= 1 && choice <= maxChoice) {
            return choice;
        }
    }
}

// Displays the clocks in both 12-hour and 24-hour formats
void displayClocks(unsigned int h, unsigned int m, unsigned int s) {
    std::cout << nCharString(27, '*') << nCharString(3, ' ') 
              << nCharString(27, '*') << std::endl;

    std::cout << "*" << nCharString(6, ' ') << "12-HOUR CLOCK" 
              << nCharString(6, ' ') << "*" << nCharString (3, ' ') 
              << "*" << nCharString(6, ' ') << "24-HOUR CLOCK" 
              << nCharString(6, ' ') << "*" << std::endl; 

    std::cout << std::endl;
    
    std::cout << "*" << nCharString(6, ' ') << formatTime12(h, m, s) 
              << nCharString(7, ' ') << "*" << nCharString(3, ' ') 
              << "*" << nCharString(8, ' ') << formatTime24(h, m, s) 
              << nCharString(9, ' ') << "*" << std::endl; 

    std::cout << nCharString(27, '*') << nCharString(3, ' ') 
              << nCharString(27, '*') << std::endl;
}

// Function to add Seconds
void addOneMinute();
void addOneSecond() {
    unsigned int seconds = getSecond();

    if (seconds < 59) {
        setSecond(seconds + 1);
    } else {
        setSecond(0);
        addOneMinute();
    }
}

// Function to add minutes
void addOneHour();
void addOneMinute() {
    unsigned int minutes = getMinute();
    
    if (minutes < 59) {
        setMinute(minutes + 1);
    } else {
        setMinute(0);
        addOneHour();
    }
}

// Function to add hours
void addOneHour() {
    unsigned int hour = getHour();
    if (hour < 23) {
        setHour(hour + 1);
    } else {
        setHour(0);
    }
}

// Main menu Loop
void mainMenu() {
    unsigned int choice = 0;

    while (choice != 4) {
        choice = getMenuChoice(4);

        if (choice == 1) {
            addOneHour();
        } else if (choice == 2) {
            addOneMinute();
        } else if (choice == 3) {
            addOneSecond();
        }
    }
}

// Main function
int main() {
    setHour(0);
    setMinute(0);
    setSecond(1);

    char opt1[] = "Add One Hour";
    char opt2[] = "Add One Minute";
    char opt3[] = "Add One Second";
    char opt4[] = "Exit Program";

    char * menu[] = {opt1, opt2, opt3, opt4};
    while(true) {
        displayClocks(getHour(), getMinute(), getSecond());
        printMenu(menu, 4, 26);
        
        unsigned int choice = getMenuChoice(4);
        if (choice == 1) addOneHour();
        else if (choice == 2) addOneMinute();
        else if (choice == 3) addOneSecond();
        else break;
        
        std::cout << std::endl;
    }
    return 0;
}