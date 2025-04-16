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
    enlarge_called = 1;

    long oldCapacity = map->capacity;
    Pair **oldBuckets = map->buckets;

    map->capacity *= 2;
    map->buckets = (Pair **)malloc(sizeof(Pair *) * map->capacity);
    
    if (map->buckets == NULL) return;

    for (long i = 0; i < map->capacity; i++) {
        map->buckets[i] = NULL;
    }

    map->size = 0;

    for (long i = 0; i < oldCapacity; i++) {
        if (oldBuckets[i] != NULL && oldBuckets[i]->key != NULL) {
            insertMap(map, oldBuckets[i]->key, oldBuckets[i]->value);
        }
    }

    free(oldBuckets);
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


void eraseMap(HashMap * map, char * key) {
    long index = hash(key, map->capacity);

    for (long i = 0; i < map->capacity; i++) {
        long pos = (index + i) % map->capacity;
        if (map->buckets[pos] == NULL) return;

        if (map->buckets[pos]->key != NULL && is_equal(map->buckets[pos]->key, key)) {
            map->buckets[pos]->key = NULL; // marcar como eliminado
            map->size--;
            return;
        }
    }
}

Pair * searchMap(HashMap * map, char * key) {
    long index = hash(key, map->capacity);

    for (long i = 0; i < map->capacity; i++) {
        long pos = (index + i) % map->capacity;
        if (map->buckets[pos] == NULL) return NULL;

        if (map->buckets[pos]->key != NULL && is_equal(map->buckets[pos]->key, key)) {
            map->current = pos;
            return map->buckets[pos];
        }
    }

    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
