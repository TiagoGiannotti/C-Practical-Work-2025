#ifndef VALIDATORS_H_INCLUDED
#define VALIDATORS_H_INCLUDED

#include "./main.h"

/* --------------------------------- Defines -------------------------------- */

#define MAXIMUM_DNI  100000000
#define MINIMUM_DNI 10000

/* -------------------------------- Functions ------------------------------- */
/**
 * @brief Valida todos los campos de un socio según reglas de negocio.
 * @param partner Puntero al socio a validar.
 * @param processDate Fecha de proceso para validaciones.
 * @return 1 si es válido, 0 si no.
 */
unsigned char isValidPartner(t_partner* partner, t_date* processDate);

#endif // VALIDATORS_H_INCLUDED
