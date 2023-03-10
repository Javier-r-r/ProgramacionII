/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 1
 * AUTHOR 1: Javier Rodriguez Rodriguez LOGIN 1: j.rrodriguez1@udc.es
 * AUTHOR 2: Ruben Iglesias Seoane LOGIN 2: r.seoane.iglesias@udc.es
 * GROUP: 3.4
 * DATE: 16 / 03 / 23
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

char *BoolToChar (tEUParticipant eu) {        //El objetivo de esta funcion es pasar un dato de tipo tEUParticipant a un tipo char*
  if (eu) {
    return "eu";
  } else {
    return "non-eu";
  }
}

void New (tParticipantName countryname, char *euParticipant, tList *l) {  //El objetivo de esta funcion es modificar la lista
                                                                          //dada añadiendo un nuevo participante
  if (findItem(countryname, *l) != LNULL) {          //Comprueba que no esté el nombre del participante en la lista
    printf("+ Error: New not possible\n");    //Si esta da un error
  } else {                                           // Si no esta se añade
    tItemL participant;
    strcpy(participant.participantName, countryname);     //Se le asignan los parametros correspondientes
    participant.EUParticipant = !strcmp(euParticipant, "eu"); //Pasa de char a booleano
    participant.numVotes = 0;                             //Al crear un nuevo participante no tendra votos

    if (insertItem(participant, LNULL, l)) {              //Si da true al insertar el participante es que no hay errores
      printf("* New: participant %s location %s\n",
             participant.participantName, BoolToChar(participant.EUParticipant));    //Entonces lo inserta
    } else {                                              //Si insertItem da false
      printf("+ Error: New not possible\n");       //Da un error
    }
  }
}

void Vote (tParticipantName participantName, int *nullVotes, int *totalVotes, tList *l) {//Funcion que añade un voto al participante indicado

  tPosL pos;
  pos = findItem(participantName, *l);                      //Encontramos la posicion del participante en la lista

  if (isEmptyList(*l) || pos == LNULL) {//Si la lista esta vacia o no encuentra al participante
    printf("+ Error: Vote not possible. Participant %s not found. NULLVOTE\n", participantName);  //Da un error
    (*nullVotes)++;       //Añade uno al contador de votos nulos
    (*totalVotes)++;      //Y otro al contador de votos totales
  } else {                  //Si encontro el participante
    tItemL participant;
    participant = getItem(pos, *l);     //Recuperamos el participante
    participant.numVotes ++;            //Y le sumamos un voto
    printf("* Vote: participant %s location %s numvotes %d\n",
           participant.participantName, BoolToChar(participant.EUParticipant), participant.numVotes);
    (*totalVotes)++;          //Añade uno al contador de votos globales
    updateItem(participant, pos, l);      //Actualiza el valor en la lista
  }
}

void Disqualify (tParticipantName name, int *nullVotes, tList *l) {     //Funcion que descalifica al participante indicado

  tPosL pos = findItem(name, *l);

  if (isEmptyList(*l) || pos == LNULL) {      //Si la lista esta vacia o no encuentra el nombre del participante
    printf("+ Error: Disqualify not possible\n");     //Da un error
  } else {                                    //Si encontro al participante
    tItemL participant;
    participant = getItem(pos, *l);           //Recupera los datos del participante de la lista
    printf("* Disqualify: participant %s location %s\n",
           participant.participantName, BoolToChar(participant.EUParticipant));
    *nullVotes = *nullVotes + participant.numVotes;     //Aumenta el contador de votos nulos en funcion de todos los votos que tenga el participante
    deleteAtPosition(pos, l);     //Y elimina al participante
  }
}

void Stats (char *totalVoters, const tNumVotes *nullVotes, const tNumVotes *totalVotes, tList l) {    //Funcion que imprime por pantalla los stats de los participantes que estan en la lista

  if (isEmptyList(l)) {         //Si la lista esta vacia da un error
    printf("+ Error: Stats not possible\n");
  } else {
    float p_p, p_v;
    tPosL pos = first(l);
    tItemL item;
    tNumVotes Voters = strtol(totalVoters, NULL, 10);   //Pasa el dato de char* a int para enseñarlo por pantalla mas adelante

    while(pos != LNULL) {   //Va recorriendo toda la lista
      item = getItem (pos, l);      //Recupera los datos del participante
      if (item.numVotes == 0) {   //Si el participante no tiene votos
        p_p = 0;            //Devuelve que el porcentaje de votos es 0.0%
      } else {          //Si tiene votos
        p_p = (float) item.numVotes / (float) (*totalVotes - *nullVotes) * 100;   //Porcentaje de votos que tiene con respecto a los votos totales menos los votos nulos
      }
      printf("Participant %s location %s numvotes %d (%.2f%%)\n",
             item.participantName, BoolToChar(item.EUParticipant), item.numVotes, p_p);
      pos = next(pos, l);       //Avanza una posicion de la lista para continuar el bucle
    }

    printf("Null votes %d\n", *nullVotes);      //Imprime por pantalla la cantidad de votos nulos
    p_v = (float)*totalVotes/(float)Voters * 100;       //Calcula el porcentaje de participacion de los jueces
    printf("Participation: %d votes from %d voters (%.2f%%)\n", *totalVotes, Voters, p_v);    //Imprime por pantalla el porcentaje de participacion de los jueces
  }
}

void processCommand(char *commandNumber, char command, char *param1, char *param2,
                    tNumVotes *nullVotes, tNumVotes *totalVotes, tList *l) {   //Funcion que procesa que comando debe ejecutar el programa

  printf("********************\n");     //Imprime 20 asteriscos

  switch (command) {
    case 'N':                 //realiza new
      printf("%s %c: participant %s location %s\n", commandNumber, command, param1, param2);
      New(param1, param2, l);
      break;
    case 'V':                 //realiza vote
      printf("%s %c: participant %s\n", commandNumber, command, param1);
      Vote(param1, nullVotes, totalVotes, l);
      break;
    case 'D':                 //realiza disqualify
      printf("%s %c: participant %s\n", commandNumber, command, param1);
      Disqualify(param1, nullVotes, l);
      break;
    case 'S':                 //realiza stats
      printf("%s %c: totalvoters %s\n", commandNumber, command, param1);
      Stats(param1, nullVotes, totalVotes, *l);
      break;
    default:
      break;
    }
}

void readTasks(char *filename) {      //Lee el archivo para pasar los datos correspondientes a la funcion processCommand

  FILE *f = NULL;
  char *commandNumber, *command, *param1, *param2;
  const char delimiters[] = " \n\r";
  char buffer[MAX_BUFFER];
  tList list;
  createEmptyList(&list);

  tNumVotes *total_votes = malloc(sizeof(tNumVotes));     //Puntero del contador de votos totales
  tNumVotes *null_votes = malloc(sizeof(tNumVotes));      //Puntero del contador de los votos nulos
  *total_votes = 0;
  *null_votes = 0;

  f = fopen(filename, "r");   //Abre el archivo

  if (f != NULL) {

    while (fgets(buffer, MAX_BUFFER, f)) {        //Bucle que sirve para conseguir lps parametros de processCommand
      commandNumber = strtok(buffer, delimiters);
      command = strtok(NULL, delimiters);
      param1 = strtok(NULL, delimiters);
      param2 = strtok(NULL, delimiters);

      processCommand(commandNumber, command[0], param1, param2, null_votes, total_votes, &list);    //Llamada a la funcion processCommand
    }

    fclose(f);        //Cierra el archivo

  } else {
    printf("Cannot open file %s.\n", filename);
  }
}


int main(int nargs, char **args) {

  char *file_name = "disqualify2.txt";      //Archivo que abre por defecto

  if (nargs > 1) {
    file_name = args[1];
  } else {
    #ifdef INPUT_FILE
    file_name = INPUT_FILE;
    #endif
  }

  readTasks(file_name);   //Le pasa el archivo correspondiente a readTasks

  return 0;
}






