/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 1
 * AUTHOR 1: Javier Rodriguez Rodriguez LOGIN 1: j.rrodriguez1@udc.es
 * AUTHOR 2: Ruben Seoane Iglesias LOGIN 2: r.seoane.iglesias@udc.es
 * GROUP: 3.4
 * DATE: 03 / 03 / 22
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"

#include "string.h"
#define  N 25
#include "stdbool.h"
#define LNULL -1

typedef int tPosL;
typedef struct {
    tItemL data[N];
    tPosL lastPos;
} tList;

void createEmptyList (tList*);                //Funcion para crear una lista vacia
bool isEmptyList(tList);                      //Funcion que devuelve true si la lista esta vacia y false en caso contrario
tPosL first(tList);                           //Funcion que devuelve la primera posicion de una lista dada
tPosL last(tList);                            //Funcion que devuelve la ultima posicion de una lista dada
tPosL next(tPosL, tList);                     //Funcion que devuelve la posicion posterior a una dada
tPosL previous(tPosL, tList);                 //Funcion que devuelve la posicion anterior a una dada
bool insertItem(tItemL,tPosL , tList*);       //Función para introducir un elemento de tipo tItemL en la lista, devuelve true si se pudo insertar, false en caso contrario
void deleteAtPosition(tPosL, tList*);         //Funcion que elimina el elemento que se encuentra en la posicion dada
tItemL getItem(tPosL, tList);                 //Funcion que devuelve el elemento que se encuentra en una posicion dada
void updateItem(tItemL, tPosL, tList*);       //Funcion que actualiza el dato que se encuentra en la posicion dada
tPosL findItem(tParticipantName, tList);      //Función que devuelve la posicion de un elemento de tipo tParticipantName

#endif
