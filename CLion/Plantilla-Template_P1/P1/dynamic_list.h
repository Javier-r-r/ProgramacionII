/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 1
 * AUTHOR 1: Javier Rodriguez Rodriguez LOGIN 1: j.rrodriguez1@udc.es
 * AUTHOR 2: Ruben Seoane Iglesias LOGIN 2: r.seoane.iglesias@udc.es
 * GROUP: 3.4
 * DATE: 09 / 03 / 22
 */

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define LNULL NULL

typedef struct tNodo *tPosL;
struct tNodo{
    tItemL data;
    tPosL next;
};
typedef tPosL tList;

void createEmptyList (tList*);                  //Funcion para crear una lista vacia
bool createNode (tPosL*);                       //Funcion para crear un nodo en una posicion dada
bool isEmptyList(tList);                        //Funcion que devuelve true si la lista esta vacia y false en caso contrario
tPosL first(tList);                             //Funcion que devuelve la primera posicion de una lista dada
tPosL last(tList);                              //Funcion que devuelve la ultima posicion de una lista dada
tPosL next(tPosL, tList);                       //Funcion que devuelve la posicion posterior a una dada
tPosL previous(tPosL, tList);                   //Funcion que devuelve la posicion anterior a una dada
bool insertItem(tItemL, tPosL, tList*);         //Función para introducir un elemento de tipo tItemL en la lista, devuelve true si se pudo insertar, false en caso contrario
void deleteAtPosition(tPosL, tList*);           //Funcion que elimina el elemento que se encuentra en la posicion dada
tItemL getItem(tPosL, tList);                   //Funcion que devuelve el elemento que se encuentra en una posicion dada
void updateItem(tItemL d, tPosL p, tList*);     //Funcion que actualiza el dato que se encuentra en la posicion dada
tPosL findItem(tParticipantName d, tList);      //Función que devuelve la posicion de un elemento de tipo tParticipantName

#endif

