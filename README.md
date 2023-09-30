Integrantes: Monserrath Morales Alonso Maurel


* Breve explicación de lo que se solicita:

Se solicita crear un sistema que almacene puntos de interes y tambien datos relevantes de turistas. Dentro de cada puntos de interes, se solicita que se almacene el nombre del lugar, el tipo del lugar, la direccion, el horario y su descripcion. Es importante mencionar que el programa trabaja con una funcion para transformar datos ingresados a minusculas para evitar errores en los registros y busquedas, por lo que si se ingresan datos con mayúsculas no habrán problemas.

En cada elemento tipo turista se encontraran los siguientes elementos, pasaporte, nombre, pais, lista de lugares favoritos.

Con estos datos se nos solicita hacer una serie de funciones, las cuales se acceden mediante el menu de opciones ubicado en el main.


* Implementacion central :

Decidimos crear 4 hashmaps, uno para almacenar turistas, otro para los turistas por pais,otro para los puntos de interes, y uno para los punto de interes por tipo.

- Hashmap turista:
Dentro de el hasmap de turistas se almacenaran los siguientes datos

typedef struct Turista {
  char pasaporte[200];
  char nombre[200];
  char pais[200];
  List * favoritos;
} Turista;

Toda esta informacion será almacenada por un mapa como valor y su clave será el pasaporte (como para sea el caso de agregar un lugar favorito a la lista del turista o de mostrar los datos, entre otros.)

- Hashmap turista por país:
  
Conserva la misma estructura del hashmap anterior, sin embargo la diferencia está en que la clave ahora es el pais y no el pasaporte, el valor es una lista por cada pais registrado que almacenará todos los turistas provenientes a estos según les corresponda.

typedef struct Pais{
  Turista turista;
    ( pasaporte[200]
      nombre[200]
      pais[200] 
      List * favoritos;)
  List * list_turistas;
}Pais;

- Hasmap punto de interes:

El hashmap de puntos de intereses almacena los siguientes datos con la clave del nombre del lugar (como para sea el caso de mostrar los datos, entre otros.)

typedef struct PuntoInteres{
  char nombre[200];
  char tipo[200];
  char direccion[200];
  char horario[200];
  char descripcion[200];
} PuntoInteres;

- Hashmap punto de interes por tipo:

Al igual que se hizo una copia del hashmap de turista para poder ordenarse por país, se hace una estructura similar que el hashmap de puntos de intereses para poder mostrarlas posterioremente, ahora usando el tipo como clave de los mapas y su valor el punto de interes.

typedef struct Tipo{
  PuntoInteres puntoInteres;
    ( nombre[200];
      tipo[200];
      direccion[200];
      horario[200];
      descripcion[200]; )
  List * tipos;
}Tipo;


* Errores y dificultades del código:

1)
Lamentablemente existe un error al registrar y mostrar turistas por su país, al registrar un turista de un país determinado se almacena correctamente en la lista correspondiente y tambien se puede mostrar en el caso de que se active la opcion 6 la cual muestra todos los turistas de un país específico, sin embargo si registramos un nuevo turista con un país distinto al anterior, al querer mostrar nuevamente todos los turistas del país que fue utilizado en primer lugar, arrojará que no existen turistas en ese país. Es decir, que mostrará solo la lista del último elemento registrado.

Creemos que este problema ocurre en la funcion mostrar los mapas de punto por tipo y turista por pais, especificamente en las condiciones para mostrar un mapa si existe. Puesto que dentro de las pruebas, se demuestra que si se agregan de forma correcta los elementos en sus listas y se ordenan correctamente, por lo que no pueden ser esas funciones.

2)
Otro problema seria la importación y la exportación correcta de elementos,las funciones fueron creadas en base a la tarea anterior y adaptadas manualmente para esta, sin embargo no se lograron finalizar. Esto es debido a nuestra poca practica con la manipulacion de archivos.

No obstante, la funcion para importar sí funciona puesto que se muestra en la consola que almacena en los mapas la misma cantidad de elementos presentes en los archivos. Es decir, que se leen y almacenan los elementos de alguna forma que el programa los considera, pero no de la forma esperada.

Desconocemos el motivo de este error, existe una leve sospecha de que ocurre debido al mismo error anterior con las listas, pero es una hipotesis muy alejada de tener pruebas reales y justificadas.


* Participación de cada integrante:

Monserrath: 
- Función registrar_turista.
- Función eliminar_puntoInteres.
- Función agregar_lugarFav.
- Función mostrar_turista_por_pais.
- Función importarDatos.
- Función obtenerEntrada.
- Función comparar_turistas.

Alonso:
- Función registrar_puntoInteres.
- Función mostrar_uno.
- Función mostrar_puntoXTipo.
- Estructura de los hashmap y main.
- Función Exportar_datos_punto_interes.
- Función convertirMinusculas.

Se trabajó en conjunto para el diseño de la aplicación, organización del esquema principal y realización de este en cooperativo.
:D