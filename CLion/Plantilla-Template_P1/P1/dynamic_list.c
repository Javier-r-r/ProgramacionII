/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 1
 * AUTHOR 1: Javier Rodriguez Rodriguez LOGIN 1: j.rrodriguez1@udc.es
 * AUTHOR 2: Ruben Seoane Iglesias LOGIN 2: r.seoane.iglesias@udc.es
 * GROUP: 3.4
 * DATE: 09 / 03 / 23
 */

#include "dynamic_list.h"

void createEmptyList(tList* L){         //Objetivo: Crear una lista vacía
  *L = LNULL;                           //Entrada: Dirección de memoria en la que se va a crear la lista
}                                       //Salida: La lista creada
                                        //PostCD: La lista queda inicializada y no contiene elementos

bool createNode(tPosL* p){              //Objetivo: Crear un nodo
  *p = malloc(sizeof(struct tNodo));    //Entrada: Dirección de memoria en la que se va a crear el nodo
  return *p != LNULL;                   //Salida: True si se pudo crear el nodo, y False en caso contrario
}                                       //PreCD: Que la posición sea válida

bool isEmptyList(tList L){              //Objetivo: Determinar si la lista está vacía
  return(L == LNULL);                   //Entrada: La lista a comprobar
}                                       //Salida: True si la lista está vacía, false en caso contrario

tItemL getItem(tPosL p,tList L){        //Objetivo: Devolver el contenido del elemento de la lista que ocupa la posición indicada
  return p -> data;                     //Entrada: Posición de la lista, la lista
}                                       //Salida: El dato tItemL que está en la posición indicada
                                        //PreCD: La posición indicada es una posición válida en la lista

tPosL first(tList L){                   //Objetivo: Devolver la posición del primer elemento de la lista
  return L;                             //Entrada: Lista de la que se quiere conseguir la primera posición
}                                       //Salida: La primera posición de la lista
                                        //PreCD: La lista no está vacía

tPosL last(tList L){                    //Objetivo: Devolver la posición del último elemento de la lista
  tPosL p;                              //Entrada: La lista de la que se quiere conseguir la última posición
  for(p=L;p->next!=LNULL;p=p->next);    //Salida: La última posición de la lista
  return p;                             //PreCD: La lista no está vacía
}

tPosL next( tPosL p, tList L){          //Objetivo: Devolver la posición en la lista del elemento siguiente al de la posición indicada
    return p->next;                     //Entrada: Posición de la que se quiere saber la siguiente, Lista correspondiente
                                        //Salida: Posición siguiente (o LNULL si la posición no tiene siguiente)
                                        //PreCD: La posición indicada es una posición válida en la lista
}

tPosL previous(tPosL p, tList L){       //Objetivo: Devolver la posición en la lista del elemento anterior al de la posición indicada
  if(p == first(L)){                    //Entrada: Posición de la que se quiere saber la anterior, Lista correspondiente
    return LNULL;                       //Salida: Posición anterior (o LNULL si la posición no tiene anterior)
  }else{                                //PreCD: La posición indicada es una posición válida en la lista
    for(q = first(L); q -> next != p; q = next(q,L));
    return q;
  }
  tPosL q;
}

tPosL findItem(tParticipantName d, tList L){    //Objetivo: Devolver la posición del primer elemento de la lista cuyo nombre de
  tPosL p;                                      //participante se corresponda con el indicado
  if (isEmptyList(L)) {                         //Entrada: Nombre del participante a encontrar, Lista correspondiente
    return LNULL;                               //Salida: La posición que ocupa dicho participante en la lista (o LNULL si no existe tal participante)
  } else {
    for(p = L;p != LNULL && (strcmp(p -> data.participantName, d) < 0); p = p -> next);
    if(p != LNULL && strcmp(p -> data.participantName, d) == 0)
      return p;
    else
      return LNULL;
  }
}

bool insertItem(tItemL d,tPosL p,tList* L){     //Objetivo: Insertar un elemento en la lista antes de la posición indicada. Si la posición es LNULL, entonces se añade al final.
  if (!createNode(&q))                          //Entrada: El participante a insertar, Posición en la que se quiere insertar al participante, Lista en la que se va a insertar al participante
    return false;                               //Salida: La lista modificada, True si se pudo insertar el participante, False en caso contrario
  else {                                        //PreCD: La posición indicada es una posición válida en la lista o bien nula (LNULL)
    q->data=d;                                  //PostCD: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado
    q->next=LNULL;
    if (*L==LNULL) {                             //se comprueba si la lista está vacia
      *L = q;
    }
    else if (p == LNULL) {                           //inserta en la última posicion
      for (r = *L; r -> next != LNULL; r = r -> next);
      r -> next = q;
    } else if (p == *L) {                            //inserta en la primera posicion
      q -> next = p;
      *L = q;
    }
    else {                                      //inserta el dato en una zona intermedia de la lista
      q -> data = p -> data;                         //mueve el dato de p a q
      p -> data = d;                               //pone el dato nuevo en p
      q -> next = p -> next;
      p -> next = q;
    }
    return true;
  }
  tPosL q,r;
}

void deleteAtPosition(tPosL p, tList *L){       //Objetivo: Eliminar de la lista el elemento que ocupa la posición indicada
  tPosL q;                                      //Entrada: Posición donde está el participante a eliminar, Lista de donde se va a eliminar al participante
  if(p == *L) {                                 //Salida: Lista sin el participante
    *L = (*L)->next;                            //PreCD: La posición indicada es una posición válida en la lista
  } else if (p -> next == LNULL){               //PostCD: Las posiciones de los elementos de la lista posteriores a la de la
    for(q = *L;q -> next != p; q = q -> next);  //posición eliminada pueden haber variado
    q -> next = LNULL;
  } else {
    q = p -> next;
    p -> data = q -> data;
    p -> next = q -> next;
    p = q;
  }
  free(p);
}
void updateItem(tItemL d, tPosL p, tList* L){   //Objetivo: Modificar el contenido del elemento situado en la posición indicada
  p -> data = d;                                //Entrada: Dato tItemL que contiene la nueva información del participante, Posición donde se encuentra el participante, Lista donde se modifica la información
}                                               //Salida: Lista con la información modificada
                                                //PreCD: La posición indicada es una posición válida en la lista
                                                //PostCD: El orden de los elementos de la lista no se ve modificado