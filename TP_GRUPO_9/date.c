
#include "./date.h"

int cmpDate(t_date* a, t_date* b) {
    int yearDiff;
    int monthDiff;


    yearDiff = a->year - b->year;
    if (yearDiff != 0) return yearDiff; //2002-2025

    monthDiff = a->month - b->month;
    if (monthDiff != 0) return monthDiff;

    return a->day - b->day;
}

unsigned char isValidDate(t_date* date) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay;

    if (!date) return 0;
    if (date->year < 1) return 0;
    if (date->month < 1 || date->month > 12) return 0;

    maxDay = daysInMonth[date->month - 1];

    if (date->month == 2 &&
        ((date->year % 4 == 0 && date->year % 100 != 0) || (date->year % 400 == 0))) {
        maxDay = 29;
    }

    if (date->day < 1 || date->day > maxDay) return 0;

    return 1;
}
