/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 1
 * AUTHOR 1: Javier Rodriguez Rodriguez LOGIN 1: j.rrodriguez1@udc.es
 * AUTHOR 2: Ruben Seoane Iglesias LOGIN 2: r.seoane.iglesias@udc.es
 * GROUP: 3.4
 * DATE: 09 / 03 / 22
 */

#include "dynamic_list.h"

void createEmptyList(tList* L){
  *L = LNULL;
}

bool createNode(tPosL* p){
  *p = malloc(sizeof(struct tNodo));
  return *p != LNULL;
}

bool isEmptyList(tList L){
  return(L == LNULL);
}

tItemL getItem(tPosL p,tList L){
  return p -> data;
}

tPosL first(tList L){
  return L;
}

tPosL last(tList L){
  tPosL p;
  for(p=L;p->next!=LNULL;p=p->next);
  return p;
}

tPosL next( tPosL p, tList L){
  return p->next;
}

tPosL previous(tPosL p, tList L){
  tPosL q;
  if(p == first(L)){
    return LNULL;
  }else{
    for(q = first(L); q -> next != p; q = next(q,L));
    return q;
  }
}

tPosL findItem(tParticipantName d, tList L){
  tPosL p;
  if(isEmptyList(L)){
    return LNULL;
  }else{
    for(p = L;p != LNULL && (strcmp(p -> data.participantName, d) < 0); p = p -> next);
    if(p != LNULL && strcmp(p -> data.participantName, d) == 0)
      return p;
    else
      return LNULL;
  }
}

bool insertItem(tItemL d,tPosL p,tList* L){
  tPosL q,r;
  if(!createNode(&q))
    return false;
  else{
    q->data=d;
    q->next=LNULL;
    if (*L==LNULL) {                             //se comprueba si la lista está vacia
      *L = q;
    }
    else if(p==LNULL){                           //inserta en la última posicion
      for (r=*L; r->next!=LNULL;r=r->next);
      r->next=q;
    } else if(p==*L){                            //inserta en la primera posicion
      q->next=p;
      *L=q;
    }
    else{                                      //inserta el dato en una zona intermedia de la lista
      q->data=p->data;                         //mueve el dato de p a q
      p->data=d;                               //pone el dato nuevo en p
      q->next=p->next;
      p->next=q;
    }
    return true;
  }
}

void deleteAtPosition(tPosL p, tList *L){
  tPosL q;
  if(p == *L) {
    *L = (*L)->next;
  } else if (p -> next == LNULL){
    for(q = *L;q -> next != p; q = q -> next);
    q -> next = LNULL;
  } else {
    q = p -> next;
    p -> data = q -> data;
    p -> next = q -> next;
    p = q;
  }
  free(p);
}
void updateItem(tItemL d, tPosL p, tList* L){
  p -> data = d;
}