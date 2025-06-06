#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include "./Indice.h"
#include "./date.h"
#include <math.h>



/* --------------------------------- DEFINES -------------------------------- */

#define MAXLINE (int)(pow(2, sizeof(long int)) + 60 + 10 + 1 + 10 + 10 + 10 + 1 + 7 + 1)


/* --------------------------------- STRUCTS -------------------------------- */

typedef struct{
    char category[11];
    char fullName[60];
    char sex;
    char status;
    long int dni;
    t_date date_afiliation;
    t_date date_birth;
    t_date date_last_payment;
} t_partner;



/* -------------------------------- FUNCTIONS ------------------------------- */

unsigned int createFile(t_partner*);

unsigned int createTestFile(t_partner*);

unsigned int readFile(const char*,const char*,const char*,t_date*);

void printPartner(const t_partner* partner);

void normalizeFullName(char* fullName);

int sliceFile(t_partner*, char*);

int addMember(t_index*,const t_date*);

int removeMember(t_index*);

int updateMember(t_index*, const t_date*);

int showMember(const t_index*);

int listActiveMembersSorted(const t_index*);



#endif // MAIN_H_INCLUDED
