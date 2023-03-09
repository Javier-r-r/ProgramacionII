/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 1
 * AUTHOR 1: Javier Rodriguez Rodriguez LOGIN 1: j.rrodriguez1@udc.es
 * AUTHOR 2: Ruben Seoane Iglesias LOGIN 2: r.seoane.iglesias@udc.es
 * GROUP: 3.4
 * DATE: 03 / 03 / 23
 */


#include "static_list.h"


void createEmptyList(tList *L){
  L -> lastPos = LNULL;
}

bool isEmptyList(tList L){
  return L.lastPos == LNULL;
}

tPosL first(tList L){
  return 0;
}

tPosL last(tList L){
  return L.lastPos;
}

tPosL next(tPosL p, tList L){
  if(p == last(L)){
    return LNULL;
  } else return ++p;
}

tPosL previous(tPosL p, tList L){
  return --p;
}

bool insertItem(tItemL d,tPosL i,tList *L){
  if(L->lastPos==N-1){
    return false;
  } else{
    if(isEmptyList(*L) || strcmp(d.participantName,L->data[L->lastPos].participantName)>0){
      L->lastPos++;
      L->data[L->lastPos]=d;
    }
    else{
      L->lastPos++;
      for(i=L->lastPos; i>0 && strcmp(d.participantName,L->data[i-1].participantName)<0; i--)
        L->data[i]=L->data[i-1];
      L->data[i]=d;
    }
    return true;
  }
}

void deleteAtPosition(tPosL p, tList * L){
  tPosL i;
  L->lastPos--;
  for(i=p;i<=L->lastPos;i++){
    L->data[i]=L->data[i+1];
  }
}

tItemL getItem(tPosL p, tList L){
  return L.data[p];
}

void updateItem (tItemL d, tPosL p, tList * L){
  L -> data[p] = d;
}

tPosL findItem(tParticipantName d, tList L){
  tPosL p;
  if(L.lastPos==LNULL) {
    return LNULL;
  }
  else if ((strcmp(d,L.data[0].participantName)<0)||(strcmp(d,L.data[L.lastPos].participantName)>0)) {
    return LNULL;
  }
  else {
    for (p = 0; (p < L.lastPos) && (strcmp(L.data[p].participantName, d) < 0); p++);
    if (strcmp(L.data[p].participantName, d) == 0){
      return p;
    }else{
      return LNULL;
    }
  }
}
