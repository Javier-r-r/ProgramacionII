/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 1
 * AUTHOR 1: Javier Rodriguez Rodriguez LOGIN 1: j.rrodriguez1@udc.es
 * AUTHOR 2: Ruben Iglesias Seoane LOGIN 2: r.seoane.iglesias@udc.es
 * GROUP: 3.4
 * DATE: 09 / 03 / 22
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif


void New (tParticipantName countryname, tEUParticipant euParticipant, tList *l) {
  tItemL participant;
  if (findItem(countryname, *l) != LNULL) {
    printf("+ Error: New not possible\n");
  } else {
    strcpy(participant.participantName, countryname);
    participant.EUParticipant = euParticipant;
    participant.numVotes = 0;
    if (insertItem(participant, LNULL, l)) {
      if (participant.EUParticipant) {
        printf("* New: participant %s location eu\n", participant.participantName);
      } else {
        printf("* New: participant %s location non-eu\n", participant.participantName);
      }
    }
  }
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, tList *l) {
  printf("********************\n");
  switch (command) {
    case 'N':                 //realiza new
      printf("%s %c %s %s\n", commandNumber, command, param1, param2);
      New(param1, param2, l);
      break;
    case 'V':                 //realiza vote
      break;
    case 'D':                 //realiza disqualify
      break;
    case 'S':
      break;
    default:
      break;
    }
}

void readTasks(char *filename, tList *l) {
  FILE *f = NULL;
  char *commandNumber, *command, *param1, *param2;
  const char delimiters[] = " \n\r";
  char buffer[MAX_BUFFER];

  f = fopen(filename, "r");

  if (f != NULL) {

    while (fgets(buffer, MAX_BUFFER, f)) {
      commandNumber = strtok(buffer, delimiters);
      command = strtok(NULL, delimiters);
      param1 = strtok(NULL, delimiters);
      param2 = strtok(NULL, delimiters);

      processCommand(commandNumber, command[0], param1, param2, l);
    }

    fclose(f);

  } else {
    printf("Cannot open file %s.\n", filename);
  }
}


int main(int nargs, char **args) {

  char *file_name = "new.txt";

  if (nargs > 1) {
    file_name = args[1];
  } else {
    #ifdef INPUT_FILE
    file_name = INPUT_FILE;
    #endif
  }

  tList list;
  createEmptyList(&list);

  readTasks(file_name, &list);

  return 0;
}






