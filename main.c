#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "hashmap.h"
#include "list.h"

// definir estructuras
typedef struct Turista {
  char pasaporte[200];
  char nombre[200];
  char pais[200];
  List * favoritos;
} Turista;

typedef struct PuntoInteres{
  char nombre[200];
  char tipo[200];
  char direccion[200];
  char horario[200];
  char descripcion[200];
} PuntoInteres;

typedef struct Pais{
  Turista turista;
  List * list_turistas;
}Pais;

typedef struct Tipo{
  PuntoInteres puntoInteres;
  List * tipos;
}Tipo;

/* 1. **Registrar punto de interés** (char* nombre, char* tipo, char* dirección, char* horario, char* descripción): El usuario ingresa los datos del lugar y la aplicación los almacena. La validación de los datos debe asegurar que ningún campo char* tenga un largo mayor a 100 caracteres.
***** MAPA PUNTO INTERES *****
*/
void registrar_puntoInteres(HashMap *mapaPunto, HashMap *mapaTipo, char *nombre, char *tipo, char *direccion, char *horario, char *descripcion) {
  PuntoInteres * nuevoPunto = (PuntoInteres *) malloc(sizeof(PuntoInteres));
  strcpy(nuevoPunto->nombre, nombre);
  strcpy(nuevoPunto->tipo, tipo);
  strcpy(nuevoPunto->direccion, direccion);
  strcpy(nuevoPunto->horario, horario);
  strcpy(nuevoPunto->descripcion, descripcion);
  
  insertMap(mapaPunto, nombre, nuevoPunto); //clave: nombre, valor: nuevoPunto

  //----------------------------------------------------------
  Pair *tipo_existente = searchMap(mapaTipo, tipo);
  if (tipo_existente != NULL) {
      Tipo *tipo_actual = (Tipo *)tipo_existente->value;
      pushBack(tipo_actual->tipos, nuevoPunto); 
  } else {
      Tipo *nuevo_tipo = (Tipo *)malloc(sizeof(Tipo));
      nuevo_tipo->tipos = createList();
      pushBack(nuevo_tipo->tipos, nuevoPunto);
    
      insertMap(mapaTipo, tipo, nuevo_tipo); // clave: tipo, valor: nuevo_tipo
  }

  printf("\nPunto de interés registrado con éxito.\n");
  printf("\n----------------------------------------\n");
  return;
}

/* 2. **Mostrar datos de punto de interés** (char* nombre): El usuario ingresa el nombre del lugar y la aplicación muestra sus datos. Si no existe, se muestra un aviso.
***** MAPA PUNTO INTERES, CLAVE: NOMBRE, VALOR: DATOS *****
*/
void mostrar_uno(HashMap *mapa, char *nombre){
 Pair * nombre_buscado = searchMap(mapa,nombre);
 if (nombre_buscado!=NULL){
    PuntoInteres * punto = (PuntoInteres *) nombre_buscado->value;
    printf("\nNombre: %s\n", punto->nombre);
    printf("Tipo: %s\n", punto->tipo);
    printf("Dirección: %s\n", punto->direccion);
    printf("Horario: %s\n", punto->horario);
    printf("Descripción: %s\n", punto->descripcion);
  } else{
    printf("\nPunto de interés no encontrado.\n");
  }
  printf("\n----------------------------------------\n");
  return;
 }

/* 3. **Eliminar punto de interés** (char* nombre): El usuario ingresa el nombre del lugar y la aplicación lo elimina. Si no existe, se muestra un aviso.
***** MAPA PUNTO INTERES, CLAVE: NOMBRE *****
*/
void eliminar_puntoInteres(HashMap *mapa, char *nombre) {
  Pair * nombre_buscado = searchMap(mapa,nombre);
  if (nombre_buscado != NULL){
    eraseMap(mapa, nombre);
    printf("\nPunto de interés eliminado con éxito.\n");
  } else {
    printf("\nPunto de interés no encontrado.\n");
  }
  printf("\n----------------------------------------\n");
  return;
}

/* 4. **Registrar turista** (char* pasaporte, char* nombre, char* país): El usuario ingresa los datos del turista y la aplicación los almacena. 
***** MAPA TURISTA *****
*/

void registrar_turista(HashMap *mapaTurista, HashMap *mapaPais, char *pasaporte, char *nombre, char *pais) {
  Turista * nuevoTurista = (Turista *) malloc(sizeof(Turista));
  strcpy(nuevoTurista->pasaporte, pasaporte);
  strcpy(nuevoTurista->nombre, nombre);
  strcpy(nuevoTurista->pais, pais);
  nuevoTurista->favoritos = createList();

  insertMap(mapaTurista, pasaporte, nuevoTurista); // clave: pasaporte, valor: nuevoTurista
  
  //-------------------------------------------------
  Pair * pais_existente = searchMap(mapaPais, pais);
  if (pais_existente != NULL) {
      Pais * pais_actual = (Pais *) pais_existente->value;
      pushBack(pais_actual->list_turistas, nuevoTurista);
  } else {
      Pais * nuevo_pais = (Pais *) malloc(sizeof(Pais));
      nuevo_pais->turista = *nuevoTurista;
      nuevo_pais->list_turistas = createList();
      pushBack(nuevo_pais->list_turistas, nuevoTurista);
      
      insertMap(mapaPais, pais, nuevo_pais); // clave: pais, valor: nuevoPais
  }

  printf("\nTurista registrado con éxito.\n");
  printf("\n----------------------------------------\n");
  return;
}

/* 5. **Agregar lugar favorito a turista** (char* pasaporte, char* nombre_lugar): El usuario ingresa el pasaporte del turista y el nombre del lugar favorito, y la aplicación lo agrega a la lista de lugares favoritos del turista. 
***** MAPA TURISTA, CLAVE: PASAPORTE, VALOR: TURISTA *****
*/
void agregar_lugarFav(HashMap *mapa, char *pasaporte, char *nombre_lugar) {
    Pair * pasaporte_buscado = searchMap(mapa, pasaporte);
    if (pasaporte_buscado != NULL) {
        Turista * turista = (Turista *) pasaporte_buscado->value;
        pushBack(turista->favoritos, nombre_lugar);

        printf("\nLugar favorito agregado con éxito.\n");
    } else {
        printf("\nPasaporte no encontrado.\n");
    }
    printf("\n----------------------------------------\n");
    return;
}

/* 6. **Mostrar turistas por país** (char* país): La aplicación muestra todos los turistas de un país específico (ordenados por su número de pasaporte) y sus listas de lugares favoritos. 
***** MAPA PAIS, CLAVE: PAIS, VALOR: TURISTA *****
*/
int comparar_turistas(const void *a, const void *b) {
    Turista * turista1 = *(Turista **) a;
    Turista * turista2 = *(Turista **) b;
    return strcmp(turista1->pasaporte, turista2->pasaporte);
}

void mostrar_turistasXPais(HashMap *mapa_pais, char *pais) {
    Pair *pais_buscado = searchMap(mapa_pais, pais);
    if (pais_buscado != NULL) {
        printf("\n ---- Turistas en %s ----", pais);
        Pais *pais_actual = (Pais *)pais_buscado->value;

        // contar turistas en la lista
        int num_turistas = sizeList(pais_actual->list_turistas);

        // ordenar turistas por pasaporte
        Turista **turistas_array = (Turista **)malloc(num_turistas * sizeof(Turista *));
        Node *turista_node = pais_actual->list_turistas->head;
        int i = 0;
        while (turista_node != NULL) {
            Turista *turista = (Turista *)turista_node->data;
            turistas_array[i] = turista;
            turista_node = turista_node->next;
            i++;
        }
        qsort(turistas_array, num_turistas, sizeof(Turista *), comparar_turistas);

        // imprimir turista
        for (int j = 0; j < num_turistas; j++) {
            Turista * turista = turistas_array[j];
            printf("\nPasaporte: %s", turista->pasaporte);
            printf("\nNombre: %s", turista->nombre);
            printf("\nLugares Favoritos: ");

            // lugar favorito de turista
            Node *favorito_node = turista->favoritos->head;
            while (favorito_node != NULL) {
                char *lugarFavorito = (char *)favorito_node->data;
                printf("%s, ", lugarFavorito);
                favorito_node = favorito_node->next;
            }
            printf("\n");
        }
        free(turistas_array);
    } else {
        printf("\nPais no encontrado.\n");
    }
    printf("\n----------------------------------------\n");
    return;
}

/* 7. **Mostrar todos los puntos de interés de un tipo** (char* tipo): La aplicación muestra todos los lugares de un tipo específico (por ejemplo, todos los museos). 
***** MAPA PUNTO INTERES X TIPO *****
*/
void mostrar_puntoXTipo(HashMap *mapa_tipo, char *tipo) {
    Pair *tipo_buscado  = searchMap(mapa_tipo, tipo);
    if (tipo_buscado  != NULL) {
        printf("\n ---- Puntos de tipo %s ----", tipo);
        Tipo *tipo_actual  = (Tipo *) tipo_buscado->value;

        // contar puntos en la lista
        int num_puntos  = sizeList(tipo_actual->tipos);

        // ordenar puntos por tipo
        Tipo **puntos_array = (Tipo **) malloc(num_puntos * sizeof(Tipo *));
        Node *punto_node = tipo_actual->tipos->head;
        int i = 0;
        while (punto_node != NULL) {
            Tipo *punto = (Tipo *)punto_node->data;
            puntos_array[i] = punto;
            punto_node = punto_node->next;
            i++;
        }
        qsort(puntos_array, num_puntos , sizeof(Turista *), comparar_turistas);

        // imprimir punto
        for (int j = 0; j < num_puntos ; j++) {
            Tipo * punto = puntos_array[j];
            printf("\nNombre: %s", punto->puntoInteres.nombre);
            printf("\nTipo: %s", punto->puntoInteres.tipo);
            printf("\nDirección: %s", punto->puntoInteres.direccion);
            printf("\nHorario: %s", punto->puntoInteres.horario);
            printf("\nDescripción: %s", punto->puntoInteres.descripcion);
            printf("\n");
        }
        free(puntos_array);
    } else {
        printf("\nTipo de punto no encontrado.\n");
    }
    printf("\n----------------------------------------\n");
    return;
}

/* 8. **Importar puntos de interés y turistas desde archivos CSV** (char* nombre_archivo_puntos, char* nombre_archivo_turistas): El usuario ingresa los nombres de archivo y la aplicación carga todos los puntos de interés y turistas, incluyendo las listas de lugares favoritos. */
void convertirMinusculas(char *palabra) {
    int i = 0;
    while (palabra[i]) {
        palabra[i] = tolower((unsigned char) palabra[i]);
        i++;
    }
}

void importarDatos(char *puntos_interes, char *turistas, HashMap *mapaTurista, HashMap *mapaPunto, HashMap *mapaPais, HashMap *mapaTipo) {
  
    // Importar puntos de interés desde el archivo puntos_interes.csv
    FILE *fp_puntos = fopen(puntos_interes, "r");
    if (fp_puntos == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo de puntos de interés.\n");
        return;
    }
    char linea_puntos[1024];
    fgets(linea_puntos, 1023, fp_puntos); // Leer encabezado
    
    while (fgets(linea_puntos, 1023, fp_puntos) != NULL) {
        char nombre[30];
        char tipo[20];
        char direccion[50];
        char horario[15];
        char descripcion[1000];
        sscanf(linea_puntos, "%[^,],%[^,],%[^,],%[^,],%[^\n]", nombre, tipo, direccion, horario, descripcion);

        convertirMinusculas(nombre);
        convertirMinusculas(tipo);
        convertirMinusculas(direccion);
        convertirMinusculas(horario);
        convertirMinusculas(descripcion);
      
        registrar_puntoInteres(mapaPunto, mapaTipo, nombre,tipo,direccion,horario,descripcion);
    }
    
    fclose(fp_puntos);

    // Importar turistas desde el archivo turistas.csv
    FILE *fp_turistas = fopen(turistas, "r");
    if (fp_turistas == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo de turistas.\n");
        return;
    }
    char linea_turistas[1024];
    fgets(linea_turistas, 1023, fp_turistas); // Leer encabezado
    
    while (fgets(linea_turistas, 1023, fp_turistas) != NULL) {
        char pasaporte[10];
        char nombre[30];
        char pais[30];
        sscanf(linea_turistas, "%[^,],%[^,],%[^\n]", pasaporte, nombre, pais);
        convertirMinusculas(pasaporte);
        convertirMinusculas(nombre);
        convertirMinusculas(pais);
      
        registrar_turista(mapaTurista, mapaPais, pasaporte, nombre, pais);
    }

    fclose(fp_turistas);
}


/* 
9. **Exportar puntos de interés y turistas a archivos CSV** (char* nombre_archivo_puntos, char* nombre_archivo_turistas): La aplicación exporta todos los puntos de interés y turistas, sus datos y las listas de lugares favoritos a archivos CSV indicados por el usuario. 
*/
/*
void Exportar_datos_punto_interes(HashMap *mapa_puntoInteres) {
  char nombre_archivo[40];
  printf("----------------------------------------\n");
  printf("Ingrese el nombre del archivo que desea crear\n");
  scanf("%39s", nombre_archivo);

  FILE* archivo = fopen(nombre_archivo, "a");
  if (archivo == NULL) {
    printf("Error al abrir el archivo.\n");
    return;
  }
  
  fprintf(archivo,"Nombre_Punto_Interes,Tipo,Dirección,Horario,Descripción,\n");
  
  for (long i = 0; i < mapa_puntoInteres->capacity; i++) {
        Pair *pair = mapa_puntoInteres->buckets[i];
        while (pair != NULL) {
            PuntoInteres *punto = (PuntoInteres *)pair->value;
            fprintf(archivo, "%s,%s,%s,%s,%s\n", punto->nombre, punto->tipo, punto->direccion, punto->horario, punto->descripcion);
            pair = pair->next;
        }
    }

  
  fclose(archivo);
  printf("Se ha creado el archivo correctamente: %s\n", nombre_archivo);
  printf("----------------------------------------\n");
}
*/

// -------------- FUNCIONES PARA ENTRADAS DE CADENAS --------------
// funcion para obtener cadenas hasta ingresar un enter.
void obtenerEntrada(char *cadena, int tallaMax) {
  fgets(cadena, tallaMax, stdin);
  size_t largo = strlen(cadena);
  if (largo > 0 && cadena[largo - 1] == '\n') {
    cadena[largo - 1] = '\0';
  }
}
// funcion para validar que una cadena no exceda los 100 caracteres.
char * validarEntrada(char *cadena){
  while(1) {
    obtenerEntrada(cadena, 100);
    if(strlen(cadena)<100) {
      convertirMinusculas(cadena);
      return cadena;
    } else {
      printf("LIMITE DE CARACTERES EXCEDIDO, MAXIMO DE 100 CARACTERES. \nRepita el dato: ");
    }
  }
}

int main(){
  HashMap * mapa_puntoInteres = createMap(100);
  HashMap * mapa_turista = createMap(100);
  HashMap * mapa_paises = createMap(100);
  HashMap * mapa_tipos = createMap(100);

  int opcion;
  
  while (1) {
    printf("\n            MENU DE OPCIONES");
    printf("\n1. Registrar punto de interés");
    printf("\n2. Mostrar datos de punto de interés");
    printf("\n3. Eliminar punto de interés");
    printf("\n4. Registrar turista");
    printf("\n5. Agregar lugar favorito a turista");
    printf("\n6. Mostrar turistas por país");
    printf("\n7. Mostrar todos los puntos de interés de un tipo");
    printf("\n8. Importar puntos de interés y turistas desde archivos CSV");
    printf("\n9. Exportar puntos de interés y turistas a archivos CSV");
    printf("\n10. Salir del programa\n");
    scanf("%d", &opcion);
  
    if(opcion == 10) {
      return 0;
    }
    else if(opcion == 1) {
      getchar();
      char nombre[500], tipo[500], direccion[500], horario[500], descripcion[500];
      printf("----------------------------------------\n");
      printf("\n   Ingrese los datos del punto de interes");
      printf("\nNombre: ");
      validarEntrada(nombre);
      printf("Tipo: ");
      validarEntrada(tipo);
      printf("Direccion: ");
      validarEntrada(direccion);
      printf("Horario: ");
      validarEntrada(horario);
      printf("Descripción: ");
      validarEntrada(descripcion);
  
      registrar_puntoInteres(mapa_puntoInteres, mapa_tipos, nombre,tipo,direccion,horario,descripcion);
    }
      
    else if(opcion == 2) {
      getchar();
      char nombre[500];
      printf("----------------------------------------\n");
      printf("\n   Ingrese el nombre del punto de interes");
      printf("\nNombre: ");
      validarEntrada(nombre);
      
      mostrar_uno(mapa_puntoInteres, nombre);
    }
    else if(opcion == 3) {
      getchar();
      char nombre[500];
      printf("----------------------------------------\n");
      printf("\n   Ingrese el nombre del punto de interes a eliminar");
      printf("\nNombre: ");
      validarEntrada(nombre);
      
      eliminar_puntoInteres(mapa_puntoInteres, nombre);
    }
    else if(opcion == 4) {
      getchar();
      char pasaporte[500], nombre[500], pais[500];
      printf("----------------------------------------\n");
      printf("\n   Ingrese los datos del turista");
      printf("\nPasaporte: ");
      validarEntrada(pasaporte);
      printf("Nombre: ");
      validarEntrada(nombre);
      printf("Pais: ");
      validarEntrada(pais);
  
      registrar_turista(mapa_turista, mapa_paises, pasaporte, nombre, pais);
    }
    else if(opcion == 5) {
      getchar();
      char pasaporte[500], nombre_lugar[500];
      printf("----------------------------------------\n");
      printf("\n   Ingrese los datos del lugar favorito");
      printf("\nPasaporte: ");
      validarEntrada(pasaporte);
      printf("Nombre del lugar: ");
      validarEntrada(nombre_lugar);

      agregar_lugarFav(mapa_turista, pasaporte, nombre_lugar);
    }
    else if(opcion == 6) {
      getchar();
      char pais[500];
      printf("----------------------------------------\n");
      printf("\n   Ingrese los datos del pais");
      printf("\nPais: ");
      validarEntrada(pais);

      mostrar_turistasXPais(mapa_paises, pais);
    }
    
    else if(opcion == 7) {
      getchar();
      char tipo[500];
      printf("----------------------------------------\n");
      printf("\n   Ingrese el tipo del punto de interes");
      printf("\nTipo: ");
      validarEntrada(tipo);

      mostrar_puntoXTipo(mapa_tipos, tipo);
    }
    else if(opcion == 8) {
      char puntos_interes[] = "puntos_interes.csv";
      char turistas[] = "turistas.csv";
      importarDatos(puntos_interes, turistas, mapa_turista, mapa_puntoInteres, mapa_paises, mapa_tipos);
    }
    /*
    else if(opcion == 9) {
      Exportar_datos_punto_interes(mapa_puntoInteres);
    */
  }
}