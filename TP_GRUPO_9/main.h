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
/**
 * @brief Crea un archivo binario de socios a partir de un arreglo.
 * @param partners Puntero al arreglo de socios.
 * @return 1 si se creó correctamente, 0 si hubo error.
 */
unsigned int createFile(t_partner*);

/**
 * @brief Crea un archivo de prueba con socios de ejemplo.
 * @param partners Puntero al arreglo de socios.
 * @return 1 si se creó correctamente, 0 si hubo error.
 */
unsigned int createTestFile(t_partner*);

/**
 * @brief Lee socios desde un archivo de texto y los guarda en binario, validando y normalizando.
 * @param srcFile Archivo de texto fuente.
 * @param destFile Archivo binario destino.
 * @param errorFile Archivo de errores.
 * @param processDate Fecha de proceso para validaciones.
 * @return 1 si se procesó correctamente, 0 si hubo error.
 */
unsigned int readFile(const char* srcFile, const char* destFile, const char* errorFile, t_date* processDate);

/**
 * @brief Imprime los datos de un socio en formato de archivo.
 * @param partner Puntero al socio a imprimir.
 */
void printPartner(const t_partner* partner);

/**
 * @brief Normaliza el nombre completo: Apellido, Nombre(s), mayúsculas y minúsculas.
 * @param fullName Cadena a normalizar.
 */
void normalizeFullName(char* fullName);

/**
 * @brief Extrae los campos de una línea de texto y los carga en la estructura de socio.
 * @param partner Puntero al socio a cargar.
 * @param line Línea de texto a procesar.
 * @return 1 si se extrajo correctamente, 0 si hubo error de formato.
 */
int sliceFile(t_partner* partner, char* line);

/**
 * @brief Da de alta un nuevo socio, validando y guardando en archivo e índice.
 * @param idx Puntero al índice.
 * @param process_date Fecha de proceso para validaciones.
 * @return 1 si se dio de alta correctamente, 0 si hubo error.
 */
int addMember(t_index* idx, const t_date* process_date);

/**
 * @brief Da de baja lógica a un socio (cambia estado a 'B').
 * @param idx Puntero al índice.
 * @return 1 si se dio de baja correctamente, 0 si hubo error.
 */
int removeMember(t_index* idx);

/**
 * @brief Modifica los datos de un socio existente.
 * @param idx Puntero al índice.
 * @param process_date Fecha de proceso para validaciones.
 * @return 1 si se modificó correctamente, 0 si hubo error.
 */
int updateMember(t_index* idx, const t_date* process_date);

/**
 * @brief Muestra los datos de un socio buscado por DNI.
 * @param idx Puntero al índice.
 * @return 1 si se mostró correctamente, 0 si no se encontró.
 */
int showMember(const t_index* idx);

/**
 * @brief Lista todos los socios activos ordenados por DNI.
 * @param idx Puntero al índice.
 * @return 1 si se listó correctamente, 0 si no hay socios activos.
 */
int listActiveMembersSorted(const t_index* idx);


#endif // MAIN_H_INCLUDED
