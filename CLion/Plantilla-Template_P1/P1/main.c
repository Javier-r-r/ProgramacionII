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
    } else {
      printf("+ Error: New not possible\n");
    }
  }
}

void Vote (tParticipantName participantName, tNumVotes *nullCounter, tList *l) {
  tItemL participant;
  tPosL pos;
  pos = findItem(participantName, *l);
  participant = getItem(pos, *l);
  if (findItem(participantName, *l) == LNULL || isEmptyList(*l)) {
    printf("+ Error: Vote not possible. Participant %s not found. NULLVOTE\n", participant.participantName);
    nullCounter ++;
  } else {
    if (participant.EUParticipant) {
      participant.numVotes ++;
      printf("* Vote: participant %s location eu numvotes %d\n", participant.participantName, participant.numVotes);
    } else {
      participant.numVotes ++;
      printf("* Vote: participant %s location non-eu numvotes %d\n", participant.participantName, participant.numVotes);
    }
  }
}

/*void Disqualify (tParticipantName participant, tList *l) {

}*/

void Stats (tNumVotes totalVoters, tNumVotes *nullCounter, tList l) {
  float v_n = 0,v_e;
  tPosL pos;
  tItemL item;
  tNumVotes votes = 0;

  if(isEmptyList(l)) {
    printf("+ Error: Stats not possible\n");
  } else {
    pos = first(l);
    while(pos != LNULL) {
      item = getItem (pos, l);
      if (item.EUParticipant) {
        votes = votes + item.numVotes;
        v_n = (float) item.numVotes/(float)votes;
        printf("Participant %s location eu numvotes %d (%.2f%%)\n", item.participantName, item.numVotes, v_n);
      } else {
        votes = votes + item.numVotes;
        v_n = (float) item.numVotes/(float)votes;
        printf("Participant %s location non-eu numvotes %d (%.2f%%)\n", item.participantName, item.numVotes, v_n);
      }
      pos = next(pos, l);
    }
    printf("Null votes %d\n", nullCounter);
    printf("Participation: %d votes from %s voters (%.2f%%)\n", votes, totalVoters, (float)votes/(float)totalVoters);
  }

}

void processCommand(char *commandNumber, char command, char *param1, char *param2, tList *l) {
  printf("********************\n");
  tNumVotes *nullCounter = 0;
  switch (command) {
    case 'N':                 //realiza new
      printf("%s %c: participant %s location %s\n", commandNumber, command, param1, param2);
      New(param1, param2, l);
      break;
    case 'V':                 //realiza vote
      printf("%s %c: participant %s\n", commandNumber, command, param1);
      Vote(param1, nullCounter, l);
      break;
    case 'D':                 //realiza disqualify
      printf("%s %c: participant %s\n", commandNumber, command, param1);
      /*Disqualify(param1, l);*/
      break;
    case 'S':
      printf("%s %c: totalvoters %s\n", commandNumber, command, param1);
      Stats(param1, nullCounter, *l);
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






