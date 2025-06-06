#include "./main.h"
#include "./Indice.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* pf;
    int error;
    char option;
    t_date date;
    t_index index;

   // Ingreso y validación de fecha
    do {
        printf("Ingrese la fecha actual (DD/MM/YYYY): ");
        fflush(stdin); // Limpiar buffer
        scanf("%d/%d/%d", &date.day, &date.month, &date.year);
    } while (!isValidDate(&date));
    printf("\n");

    // Crear e inicializar índice
   index_create(&index);

  pf = fopen("socios.dat", "rb");
    if (!pf) {
    error = readFile("socios.txt", "socios.dat", "socios_error.txt", &date);
    if (!error)
        printf("Error leyendo archivo de texto.\n");
    else

        printf("Archivo socios.dat generado correctamente.\n");
    } else {
    fclose(pf);
    printf("Archivo socios.dat ya existente. No se regenera.\n");
    }

   if (!index_load(&index, "socios.dat")) {
    printf("Error cargando indice desde socios.dat\n");
    }
    system("pause"); 
    printf("\n");
    system("cls");

    do {
        printf("\n--- MENU ---\n");
        printf("a. Alta\nb. Baja\nc. Modificacion\nd. Mostrar socio\ne. Listado ordenado\nf. Salir\n");
        printf("Opcion: ");
        fflush(stdin); // Limpiar buffer
        scanf(" %c", &option);

        switch(option) {
          case 'a': addMember(&index,&date); break;
          case 'b': removeMember(&index); break;
          case 'c': updateMember(&index,&date); break;
          case 'd': showMember(&index); break;
          case 'e': listActiveMembersSorted(&index); break;
          case 'f': break;
        }
    } while (option != 'f');
    index_clear(&index);

    return 0;
}


