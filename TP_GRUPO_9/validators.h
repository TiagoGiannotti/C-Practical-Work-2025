#ifndef VALIDATORS_H_INCLUDED
#define VALIDATORS_H_INCLUDED

#include "./main.h"

/* --------------------------------- Defines -------------------------------- */

#define MAXIMUM_DNI  100000000
#define MINIMUM_DNI 10000

/* -------------------------------- Functions ------------------------------- */

unsigned char isValidPartner(t_partner* partner, t_date* processDate);

// char category[11];
//     char fullName[60];
//     char sex;
//     char status;	
//     long int dni;
//     t_date date_afiliation;
//     t_date date_birth;
//     t_date date_last_payment;

#endif // VALIDATORS_H_INCLUDED
