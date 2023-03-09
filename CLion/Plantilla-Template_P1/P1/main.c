/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 1
 * AUTHOR 1: Javier Rodriguez Rodriguez LOGIN 1: j.rrodriguez1@udc.es
 * AUTHOR 2: Ruben Iglesias Seoane LOGIN 2: r.seoane.iglesias@udc.es
 * GROUP: 3.4
 * DATE: 09 / 03 / 23
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

char *BoolToChar (tEUParticipant eu) {
  if(eu) {
    return "eu";
  } else {
    return "non-eu";
  }
}

void New (tParticipantName countryname, char *euParticipant, tList *l) {
  tItemL participant;
  if (findItem(countryname, *l) != LNULL) {
    printf("+ Error: New not possible\n");
  } else {
    strcpy(participant.participantName, countryname);
    participant.EUParticipant = !strcmp(euParticipant, "eu"); //Pasa de char a booleano
    participant.numVotes = 0;
    if (insertItem(participant, LNULL, l)) {
      printf("* New: participant %s location %s\n", participant.participantName, BoolToChar(participant.EUParticipant));
    } else {
      printf("+ Error: New not possible\n");
    }
  }
}

void Vote (tParticipantName participantName, int *nullVotes, int *totalVotes, tList *l) {
  tItemL participant;
  tPosL pos;
  pos = findItem(participantName, *l);
  if (isEmptyList(*l) || findItem(participantName, *l) == LNULL) {
    printf("+ Error: Vote not possible. Participant %s not found. NULLVOTE\n", participantName);
    (*nullVotes)++;
    (*totalVotes)++;
  } else {
    participant = getItem(pos, *l);
    participant.numVotes ++;
    printf("* Vote: participant %s location %s numvotes %d\n", participant.participantName, BoolToChar(participant.EUParticipant), participant.numVotes);
    (*totalVotes)++;
    updateItem(participant, pos, l);
  }
}

void Disqualify (tParticipantName name, int *nullVotes, tList *l) {
  tPosL pos = findItem(name, *l);
  tItemL participant;
  if (isEmptyList(*l) || pos == LNULL) {
    printf("+ Error: Disqualify not possible\n");
  } else {
    participant = getItem(pos, *l);
    printf("* Disqualify: participant %s location %s\n", participant.participantName, BoolToChar(participant.EUParticipant));
    for (int i = 0; i < participant.numVotes; i++) {
      (*nullVotes)++;
    }
    deleteAtPosition(pos, l);
  }
}

void Stats (char *totalVoters, tNumVotes *nullVotes, tNumVotes *totalVotes, tList l) {
  float v_n;
  tPosL pos;
  tItemL item;
  int Voters = strtol(totalVoters, NULL, 10);

  if (isEmptyList(l)) {
    printf("+ Error: Stats not possible\n");
  } else {
    pos = first(l);
    while(pos != LNULL) {
      item = getItem (pos, l);
      if (item.numVotes == 0) {
        v_n = 0;
      } else {
        v_n = (float) item.numVotes / (float) (*totalVotes - *nullVotes) * 100;
      }
      printf("Participant %s location %s numvotes %d (%.2f%%)\n", item.participantName, BoolToChar(item.EUParticipant), item.numVotes, v_n);
      pos = next(pos, l);
    }
    printf("Null votes %d\n", *nullVotes);
    float p = (float)*totalVotes/(float)Voters * 100;
    printf("Participation: %d votes from %d voters (%.2f%%)\n", *totalVotes, Voters, p);
  }

}

void processCommand(char *commandNumber, char command, char *param1, char *param2, int *nullVotes, int *totalVotes, tList *l) {
  printf("********************\n");
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

void readTasks(char *filename) {
  FILE *f = NULL;
  char *commandNumber, *command, *param1, *param2;
  const char delimiters[] = " \n\r";
  char buffer[MAX_BUFFER];
  tNumVotes *valid_votes = malloc(sizeof(tNumVotes));
  tNumVotes *null_votes = malloc(sizeof(tNumVotes));
  *valid_votes = 0;
  *null_votes = 0;
  tList list;
  createEmptyList(&list);


  f = fopen(filename, "r");

  if (f != NULL) {

    while (fgets(buffer, MAX_BUFFER, f)) {
      commandNumber = strtok(buffer, delimiters);
      command = strtok(NULL, delimiters);
      param1 = strtok(NULL, delimiters);
      param2 = strtok(NULL, delimiters);

      processCommand(commandNumber, command[0], param1, param2, null_votes, valid_votes, &list);
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

  readTasks(file_name);

  return 0;
}






