#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    int id;
    char *name;
    char *breed;
    int age;
    int wins;
} Horse;

typedef struct{
    Horse *horses;
    int size;
    int capacity;
} HorseList;

HorseList initHorseList();
void addHorse(HorseList *list, const char *name, const char *breed, int age);
void printHorseList(const HorseList list);
void freeHorseList(HorseList *list);
void loadHorsesFromFile(HorseList *list, const char *filename);
void saveHorsesToFile(const HorseList list, const char *filename);
int findHorseById(const HorseList list, int id);
void removeHorse(HorseList *list, int id);
void editHorse(HorseList *list, int id);
void findHorses(const HorseList list, const char *searchType, const char *searchValue);
void updateWins(HorseList *list, int id);
void freeHorse(Horse horse);

