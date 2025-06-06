#include "./main.h"
#include "./validators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

unsigned int readFile(const char* srcFile, const char* destFile, const char* errorFile, t_date* processDate) {
    FILE *psf, *pdf, *pef;

    t_partner partner;
    char line[MAXLINE];

    psf = fopen(srcFile, "rt");
    if(!psf) return 0;

    pef = fopen(errorFile, "wt");
    if (!pef) {
        fclose(psf);
        return 0;
    }

    pdf = fopen(destFile, "wb");
    if (!pdf){
        fclose(pdf);
        fclose(psf);
        return 0;
    }

    while(fgets(line, MAXLINE, psf) && sliceFile(&partner, line)) {


        if (isValidPartner(&partner, processDate)) {
            // TRANSFORMA
            normalizeFullName(partner.fullName);
             //printPartner(&partner);
            // GUARDAS EN ARCH DESTFILE
            fwrite(&partner,sizeof(t_partner),1,pdf);

 //         printf("VALIDO\n");
       } else {
  //         printf("INVALIDO\n");
        fprintf(pef,"%ld|%s|%02d-%02d-%04d|%c|%02d-%02d-%04d|%s|%02d-%02d-%04d|%c\n",
        partner.dni,
        partner.fullName,
        partner.date_birth.day, partner.date_birth.month, partner.date_birth.year,
        partner.sex,
        partner.date_afiliation.day, partner.date_afiliation.month, partner.date_afiliation.year,
        partner.category,
        partner.date_last_payment.day, partner.date_last_payment.month, partner.date_last_payment.year,
        partner.status);

        };
    }

    fclose(psf);
    fclose(pef);
    fclose(pdf);

    return 1;
}

int sliceFile(t_partner* partner,char* line) {

   char* dirField = line;

//obtenemos la posicion del primer pipe
    dirField = strrchr(line, '|');
    if (dirField == NULL) {
        return 0; // No pipe found, invalid format
    }

    // 12345678|Gomez Juan|1985-07-12|M|2010-03-15|ADULTO|2015-06-10\0A

//obtenemos el estado

    sscanf(dirField+1,"%c",&(partner->status));
    *dirField = '\0';

//obtenemos la fecha de la ultima cuota
    dirField = strrchr(line, '|');
    sscanf(dirField+1,"%02d-%02d-%04d", &(partner->date_last_payment.day), &(partner->date_last_payment.month), &(partner->date_last_payment.year)); // XX-XX-XXXX
    *dirField = '\0';

//obtenemos la categoria
    dirField = strrchr(line, '|');
    sscanf(dirField+1,"%s",(partner->category));
    *dirField = '\0';

//obtenemos la fecha de afiliacion
    dirField = strrchr(line, '|');
    sscanf(dirField+1,"%02d-%02d-%04d",&(partner->date_afiliation.day), &(partner->date_afiliation.month), &(partner->date_afiliation.year)); // XX-XX-XXXX
    *dirField = '\0';

//obtenemos el sexo
    dirField = strrchr(line, '|');
    sscanf(dirField+1,"%c",&(partner->sex));
    *dirField = '\0';

//obtenemos la fecha de nacimiento
    dirField = strrchr(line, '|');
    sscanf(dirField+1,"%02d-%02d-%04d", &(partner->date_birth.day), &(partner->date_birth.month), &(partner->date_birth.year)); // XX-XX-XXXX
    *dirField = '\0';

//obtenemos el nombre completo
    dirField = strrchr(line, '|');
    strcpy(partner->fullName, dirField+1);
    *dirField = '\0';

//obtenemos el dni
    sscanf(line,"%ld",&(partner->dni));

    return 1;
}
void printPartner(const t_partner* partner) {
    printf("%ld|%s|%02d-%02d-%04d|%c|%02d-%02d-%04d|%s|%02d-%02d-%04d|%c\n",
        partner->dni,
        partner->fullName,
        partner->date_birth.day, partner->date_birth.month, partner->date_birth.year,
        partner->sex,
        partner->date_afiliation.day, partner->date_afiliation.month, partner->date_afiliation.year,
        partner->category,
        partner->date_last_payment.day, partner->date_last_payment.month, partner->date_last_payment.year,
        partner->status
    );
}

// Normaliza el nombre completo: Apellido, Nombre(s)
void normalizeFullName(char* fullName) {
    char temp[60];
    char *src = fullName;
    char *dst = temp;
    // Saltar espacios iniciales
    while (*src == ' ') src++;
    // Procesar apellido (primera palabra)
    if (*src != '\0') {
        *dst++ = toupper((unsigned char)*src++);
        while (*src != ' ' && *src != '\0') {
            *dst++ = tolower((unsigned char)*src++);
        }
        *dst++ = ',';
        *dst++ = ' ';
    }
    // Saltar espacios entre apellido y nombres
    while (*src == ' ') src++;
    // Procesar nombres
    while (*src != '\0') {
        *dst++ = toupper((unsigned char)*src++);
        while (*src != ' ' && *src != '\0') {
            *dst++ = tolower((unsigned char)*src++);
        }
        while (*src == ' ') src++;
        if (*src != '\0') {
            *dst++ = ' ';
        }
    }
    *dst = '\0';
    strcpy(fullName, temp);
}

int addMember(t_index* idx, const t_date* process_date) {
    FILE* pf = fopen("socios.dat", "ab+");
    if (!pf) {
        printf("No se pudo abrir el archivo socios.dat\n");
        return 0;
    }

    t_partner new_partner;
    t_reg_index reg;

    // 1. Ingreso y verificación del DNI
    printf("Ingrese DNI: ");
    fflush(stdin); // Limpiar buffer
    scanf("%ld", &new_partner.dni);
    reg.dni = new_partner.dni;

    if (index_find(idx, &reg)) {
        printf("El DNI ya esta registrado.\n");
        fclose(pf);
        return 0;
    }

    // 2. Ingreso del resto de datos
    getchar(); // Limpiar \n pendiente

    printf("Ingrese Apellido y Nombre: ");
    fflush(stdin); // Limpiar buffer
    fgets(new_partner.fullName, sizeof(new_partner.fullName), stdin);
    new_partner.fullName[strcspn(new_partner.fullName, "\n")] = 0;

    printf("Sexo (M/F): ");
    fflush(stdin); // Limpiar buffer
    scanf(" %c", &new_partner.sex);
    

    printf("Fecha de nacimiento (dd/mm/aaaa): ");
    fflush(stdin); // Limpiar buffer
    scanf("%d/%d/%d", &new_partner.date_birth.day, &new_partner.date_birth.month, &new_partner.date_birth.year);

    printf("Fecha de afiliacion (dd/mm/aaaa): ");
    fflush(stdin); // Limpiar buffer
    scanf("%d/%d/%d", &new_partner.date_afiliation.day, &new_partner.date_afiliation.month, &new_partner.date_afiliation.year);

    printf("Categoria (ADULTO,MENOR,VITALICIO,HONORARIO): ");
    fflush(stdin); // Limpiar buffer
    scanf("%s", new_partner.category);

    printf("Fecha ultima cuota paga (dd/mm/aaaa): ");
    fflush(stdin); // Limpiar buffer
    scanf("%d/%d/%d", &new_partner.date_last_payment.day, &new_partner.date_last_payment.month, &new_partner.date_last_payment.year);

    new_partner.status = 'A'; // Estado por defecto al dar de alta

    // 3. Normalizar nombre y validar socio

    normalizeFullName(new_partner.fullName);

    if (!isValidPartner(&new_partner, (t_date*)process_date)) {
        printf("Datos invalidos. Alta cancelada.\n");
        fclose(pf);
        return 0;
    }

    // 4. Guardar al final del archivo
    fseek(pf, 0, SEEK_END);
    long reg_pos = ftell(pf) / sizeof(t_partner);

    if (fwrite(&new_partner, sizeof(t_partner), 1, pf) != 1) {
        printf("Error al escribir el nuevo socio.\n");
        fclose(pf);
        return 0;
    }

    fclose(pf);

    // 5. Insertar en el índice
    reg.num_reg = (unsigned) reg_pos;
    if (!index_insert(idx, &reg)) {
        printf("Error al insertar en el indice.\n");
        return 0;
    }

    printf("Alta realizada correctamente.\n");
    return 1;
}

int removeMember(t_index* idx) {
    long dni;
    printf("Ingrese DNI del socio a dar de baja: ");
    fflush(stdin); // Limpiar buffer
    scanf("%ld", &dni);

    t_reg_index reg = { dni, 0 };

    if (!index_find(idx, &reg)) {
        printf("El socio con DNI %ld no existe o ya fue dado de baja.\n", dni);
        return 0;
    }

    // Abrir archivo en modo lectura/escritura
    FILE* pf = fopen("socios.dat", "r+b");
    if (!pf) {
        printf("No se pudo abrir el archivo socios.dat\n");
        return 0;
    }

    // Posicionarse en el registro correspondiente
    fseek(pf, reg.num_reg * sizeof(t_partner), SEEK_SET);

    t_partner partner;
    if (fread(&partner, sizeof(t_partner), 1, pf) != 1) {
        printf("Error al leer el registro.\n");
        fclose(pf);
        return 0;
    }

    if (partner.status != 'A') {
        printf("El socio ya no esta activo.\n");
        fclose(pf);
        return 0;
    }

    // Marcar como dado de baja
    partner.status = 'B';

    // Sobrescribir el registro
    fseek(pf, -sizeof(t_partner), SEEK_CUR);
    if (fwrite(&partner, sizeof(t_partner), 1, pf) != 1) {
        printf("Error al escribir el registro actualizado.\n");
        fclose(pf);
        return 0;
    }

    fclose(pf);

    // Eliminar del índice
    index_delete(idx, &reg);

    printf("Socio con DNI %ld dado de baja exitosamente.\n", dni);
    return 1;
}

int updateMember(t_index* idx, const t_date* process_date) {
    long dni;
    printf("Ingrese DNI del socio a modificar: ");
    fflush(stdin); // Limpiar buffer
    scanf("%ld", &dni);

    t_reg_index reg = {dni, 0};
    if (!index_find(idx, &reg)) {
        printf("No se encontro ningun socio con ese DNI.\n");
        return 0;
    }

    FILE* pf = fopen("socios.dat", "r+b");
    if (!pf) {
        printf("No se pudo abrir socios.dat\n");
        return 0;
    }

    // Leer el socio actual
    fseek(pf, reg.num_reg * sizeof(t_partner), SEEK_SET);
    t_partner socio;
    if (fread(&socio, sizeof(t_partner), 1, pf) != 1) {
        printf("Error al leer el registro.\n");
        fclose(pf);
        return 0;
    }

    if (socio.status != 'A') {
        printf("El socio no esta activo. No se puede modificar.\n");
        fclose(pf);
        return 0;
    }

    // Mostrar datos actuales
    printf("\nDatos actuales:\n");
    printf("Nombre: %s\n", socio.fullName);
    printf("Sexo: %c\n", socio.sex);
    printf("Nacimiento: %02d/%02d/%04d\n", socio.date_birth.day, socio.date_birth.month, socio.date_birth.year);
    printf("Afiliacion: %02d/%02d/%04d\n", socio.date_afiliation.day, socio.date_afiliation.month, socio.date_afiliation.year);
    printf("Categoria: %s\n", socio.category);
    printf("Ultima cuota: %02d/%02d/%04d\n", socio.date_last_payment.day, socio.date_last_payment.month, socio.date_last_payment.year);

    // Modificación de campos (por simplicidad modificamos todos)
    getchar(); // limpiar \n
    printf("\nIngrese NUEVO Apellido y Nombre: ");
    fgets(socio.fullName, sizeof(socio.fullName), stdin);
    socio.fullName[strcspn(socio.fullName, "\n")] = 0;

    printf("Sexo (M/F): ");
    fflush(stdin); // Limpiar buffer
    scanf(" %c", &socio.sex);

    printf("Fecha de nacimiento (dd/mm/aaaa): ");
    fflush(stdin); // Limpiar buffer
    scanf("%d/%d/%d", &socio.date_birth.day, &socio.date_birth.month, &socio.date_birth.year);

    printf("Fecha de afiliacion (dd/mm/aaaa): ");
    fflush(stdin); // Limpiar buffer
    scanf("%d/%d/%d", &socio.date_afiliation.day, &socio.date_afiliation.month, &socio.date_afiliation.year);

    printf("Categoria: ");
    fflush(stdin); // Limpiar buffer
    scanf("%s", socio.category);

    printf("Fecha ultima cuota paga (dd/mm/aaaa): ");
    fflush(stdin); // Limpiar buffer
    scanf("%d/%d/%d", &socio.date_last_payment.day, &socio.date_last_payment.month, &socio.date_last_payment.year);

    // Normalización y validación
    normalizeFullName(socio.fullName);

    if (!isValidPartner(&socio, (t_date*)process_date)) {
        printf("Los datos ingresados no son validos. Modificacion cancelada.\n");
        fclose(pf);
        return 0;
    }

    // Sobrescribir el registro en la misma posición
    fseek(pf, reg.num_reg * sizeof(t_partner), SEEK_SET);
    if (fwrite(&socio, sizeof(t_partner), 1, pf) != 1) {
        printf("Error al guardar los cambios.\n");
        fclose(pf);
        return 0;
    }

    fclose(pf);
    printf("Socio modificado correctamente.\n");
    return 1;
}


int showMember(const t_index* idx) {
    long dni;
    printf("Ingrese DNI del socio a mostrar: ");
    fflush(stdin); // Limpiar buffer
    scanf("%ld", &dni);

    t_reg_index reg = {dni, 0};
    if (!index_find(idx, &reg)) {
        printf("El socio con DNI %ld no esta registrado o fue dado de baja.\n", dni);
        return 0;
    }

    FILE* pf = fopen("socios.dat", "rb");
    if (!pf) {
        printf("No se pudo abrir socios.dat\n");
        return 0;
    }

    // Leer socio desde su posición
    fseek(pf, reg.num_reg * sizeof(t_partner), SEEK_SET);
    t_partner partner;
    if (fread(&partner, sizeof(t_partner), 1, pf) != 1) {
        printf("Error al leer el registro.\n");
        fclose(pf);
        return 0;
    }

    fclose(pf);

    // Mostrar los datos del socio
    printf("\n--- Datos del Socio ---\n");
    printf("DNI: %ld\n", partner.dni);
    printf("Nombre completo: %s\n", partner.fullName);
    printf("Sexo: %c\n", partner.sex);
    printf("Fecha de nacimiento: %02d/%02d/%04d\n",
           partner.date_birth.day, partner.date_birth.month, partner.date_birth.year);
    printf("Fecha de afiliacion: %02d/%02d/%04d\n",
           partner.date_afiliation.day, partner.date_afiliation.month, partner.date_afiliation.year);
    printf("Categoria: %s\n", partner.category);
    printf("Ultima cuota paga: %02d/%02d/%04d\n",
           partner.date_last_payment.day, partner.date_last_payment.month, partner.date_last_payment.year);
    printf("Estado: %c\n", partner.status == 'A' ? 'A' : 'B');

    return 1;
}

int listActiveMembersSorted(const t_index* idx) {
    t_partner p;

    if (index_empty(idx)) {
        printf("No hay socios activos registrados.\n");
        return 0;
    }

    FILE* pf = fopen("socios.dat", "rb");
    if (!pf) {
        printf("No se pudo abrir el archivo socios.dat\n");
        return 0;
    }

    printf("\n--- Listado de socios activos (ordenado por DNI) ---\n");
    printf("%-15s|%-25s|%-8s|%-6s|%-8s|%-10s|%-8s|%-6s\n",
       "DNI",            // Para p.dni
       "Nombre",         // Para p.fullName
       "Nacimiento",     // Para p.date_birth
       "Sexo",           // Para p.sex
       "F.Afiliado",     // Para p.date_afiliation
       "Categoria",            // Para p.category
       "Ulti.Cuota",        // Para p.date_last_payment
       "Estado"          // Para p.status
        );

    for (const t_reg_index* it = idx->arr; it < idx->arr + idx->count; it++) {

        fseek(pf, it->num_reg * sizeof(t_partner), SEEK_SET);


        if (fread(&p, sizeof(t_partner), 1, pf) != 1) {

            printf("Error al leer socio en posicion %u.\n", it->num_reg);
            continue;
        }

        if (p.status == 'A') {

            printf("%-15ld|%-25s|%02d-%02d-%04d|%-6c|%02d-%02d-%04d|%-10s|%02d-%02d-%04d|%-6c\n",
                p.dni,
                p.fullName,
                p.date_birth.day, p.date_birth.month, p.date_birth.year,
                p.sex,
                p.date_afiliation.day, p.date_afiliation.month, p.date_afiliation.year,
                p.category,
                p.date_last_payment.day, p.date_last_payment.month, p.date_last_payment.year,
                p.status
            );
        }
    }
    fclose(pf);
    return 1;
}
