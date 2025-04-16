#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap * map, char * key, void * value) {
    long index = hash(key, map->capacity);

    while (map->buckets[index] != NULL && map->buckets[index]->key != NULL) {
        if (is_equal(map->buckets[index]->key, key)) return; // ya existe
        index = (index + 1) % map->capacity;
    }

    Pair *newPair = createPair(key, value);
    map->buckets[index] = newPair;
    map->size++;
    map->current = index;

    if ((float)map->size / map->capacity > 0.7)
        enlarge(map);
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap *createMap(long capacity) { 
    // Reservamos memoria para el mapa
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    
    // Reservamos memoria para los buckets (arreglo de punteros a pares)
    map->buckets = (Pair **)malloc(sizeof(Pair *) * capacity); 
    
    // Inicializamos todos los buckets a NULL
    for (int i = 0; i < capacity; i++) {
        map->buckets[i] = NULL;
    }

    // Inicializamos los campos del HashMap
    map->size = 0;
    map->capacity = capacity;
    map->current = -1;

    // Devolvemos el mapa inicializado
    return map;
}


void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
