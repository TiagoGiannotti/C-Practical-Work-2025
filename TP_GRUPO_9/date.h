#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

typedef struct {
    int day;
    int month;
    int year;
} t_date;

int cmpDate(t_date* a, t_date* b);

unsigned char isValidDate(t_date* date);

#endif // DATE_H_INCLUDED
