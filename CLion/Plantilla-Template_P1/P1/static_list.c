/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 1
 * AUTHOR 1: Javier Rodriguez Rodriguez LOGIN 1: j.rrodriguez1@udc.es
 * AUTHOR 2: Ruben Seoane Iglesias LOGIN 2: r.seoane.iglesias@udc.es
 * GROUP: 3.4
 * DATE: 03 / 03 / 23
 */


#include "static_list.h"


void createEmptyList(tList *L){         //Objetivo: Crear una lista vacía
  L -> lastPos = LNULL;                 //Entrada: Dirección de memoria en la que se va a crear la lista
}                                       //Salida: La lista creada
                                        //PostCD: La lista queda inicializada y no contiene elementos

bool isEmptyList(tList L){              //Objetivo: Determinar si la lista está vacía
  return L.lastPos == LNULL;            //Entrada: La lista a comprobar
}                                       //Salida: True si la lista está vacía, false en caso contrario


tPosL first(tList L){                   //Objetivo: Devolver la posición del primer elemento de la lista
  return 0;                             //Entrada: Lista de la que se quiere conseguir la primera posición
}                                       //Salida: La primera posición de la lista
                                        //PreCD: La lista no está vacía


tPosL last(tList L){                    //Objetivo: Devolver la posición del último elemento de la lista
  return L.lastPos;                     //Entrada: La lista de la que se quiere conseguir la última posición
}                                       //Salida: La última posición de la lista
                                        //PreCD: La lista no está vacía

tPosL next(tPosL p, tList L){           //Objetivo: Devolver la posición en la lista del elemento siguiente al de la posición indicada
  if(p == last(L)){                     //Entrada: Posición de la que se quiere saber la siguiente, Lista correspondiente
    return LNULL;                       //Salida: Posición siguiente (o LNULL si la posición no tiene siguiente)
  } else return ++p;                    //PreCD: La posición indicada es una posición válida en la lista
}

tPosL previous(tPosL p, tList L){       //Objetivo: Devolver la posición en la lista del elemento anterior al de la posición indicada
  return --p;                           //Entrada: Posición de la que se quiere saber la anterior, Lista correspondiente
}                                       //Salida: Posición anterior (o LNULL si la posición no tiene anterior)
                                        //PreCD: La posición indicada es una posición válida en la lista

bool insertItem(tItemL d,tPosL i,tList *L){    //Objetivo: Insertar un elemento en la lista antes de la posición indicada. Si la posición es LNULL, entonces se añade al final
  if(L->lastPos==N-1){                         //Devuelve un valor true si el elemento fue insertado; false en caso contrario
    return false;                              //Entrada: El participante a insertar, Posición en la que se quiere insertar al participante, Lista en la que se va a insertar al participante
  } else{                                      //Salida: La lista modificada, True si se pudo insertar el participante, False en caso contrario
    if(isEmptyList(*L) || strcmp(d.participantName,L->data[L->lastPos].participantName)>0){
      L->lastPos++;                            //PreCD: La posición indicada es una posición válida en la lista o bien nula (LNULL)
      L->data[L->lastPos]=d;                   //PostCD: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado
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

void deleteAtPosition(tPosL p, tList * L){      //Objetivo: Eliminar de la lista el elemento que ocupa la posición indicada
  tPosL i;                                      //Entrada: Posición donde está el participante a eliminar, Lista de donde se va a eliminar al participante
  L->lastPos--;                                 //Salida: Lista sin el participante
  for(i=p;i<=L->lastPos;i++){                   //PreCD: La posición indicada es una posición válida en la lista
    L->data[i]=L->data[i+1];                    //PostCD: Las posiciones de los elementos de la lista posteriores a la de la
  }                                             //posición eliminada pueden haber variado
}

tItemL getItem(tPosL p, tList L){       //Objetivo: Devolver el contenido del elemento de la lista que ocupa la posición indicada
  return L.data[p];                     //Entrada: Posición de la lista, la lista
}                                       //Salida: El dato tItemL que está en la posición indicada
                                        //PreCD: La posición indicada es una posición válida en la lista

void updateItem (tItemL d, tPosL p, tList * L){     //Objetivo: Modificar el contenido del elemento situado en la posición indicada
  L -> data[p] = d;                                 //Entrada: Dato tItemL que contiene la nueva información del participante, Posición donde se encuentra el participante, Lista donde se modifica la información
}                                                   //Salida: Lista con la información modificada
                                                    //PreCD: La posición indicada es una posición válida en la lista
                                                    //PostCD: El orden de los elementos de la lista no se ve modificado

tPosL findItem(tParticipantName d, tList L){        //Objetivo: Devolver la posición del primer elemento de la lista cuyo nombre de
  tPosL p;                                          //participante se corresponda con el indicado
  if(L.lastPos==LNULL) {                            //Entrada: Nombre del participante a encontrar, Lista correspondiente
    return LNULL;                                   //Salida: La posición que ocupa dicho participante en la lista (o LNULL si no existe tal participante)
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
