#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

typedef struct {
    int day;
    int month;
    int year;
} t_date;

/**
 * @brief Compara dos fechas.
 * @param a Puntero a la primera fecha.
 * @param b Puntero a la segunda fecha.
 * @return <0 si a<b, 0 si a==b, >0 si a>b.
 */
int cmpDate(t_date* a, t_date* b);

/**
 * @brief Valida si una fecha es válida (día, mes, año).
 * @param date Puntero a la fecha.
 * @return 1 si es válida, 0 si no.
 */
unsigned char isValidDate(t_date* date);

#endif // DATE_H_INCLUDED
