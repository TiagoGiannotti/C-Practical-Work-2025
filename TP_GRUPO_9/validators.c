
#include "./main.h"
#include "./date.h"
#include "./validators.h"
#include <string.h>

unsigned char isValidPartner(t_partner* partner, t_date* processDate) {
    if (partner->dni < MINIMUM_DNI || partner->dni > MAXIMUM_DNI) return 0;

    if (
        !isValidDate(&(partner->date_birth)) ||
        cmpDate(&(partner->date_birth), processDate) >= 0
    ) return 0;

    if (partner->sex != 'M' && partner->sex != 'F') return 0;

    if (
        !isValidDate(&(partner->date_afiliation)) ||
        cmpDate(&(partner->date_afiliation), processDate) > 0 ||
        cmpDate(&(partner->date_afiliation), &(partner->date_birth)) <= 0
    ) return 0;

    if (
        strcmp(partner->category, "MENOR") != 0 &&
        strcmp(partner->category, "ADULTO") != 0 &&
        strcmp(partner->category, "VITALICIO") != 0 &&
        strcmp(partner->category, "HONORARIO") != 0
    ) return 0;

    if (
        cmpDate(&(partner->date_last_payment), &(partner->date_afiliation)) <= 0 &&
        cmpDate(&(partner->date_last_payment), processDate) > 0
    )
        return 0;

    if (partner->status != 'A' && partner->status != 'B') return 0;

    return 1;
}
