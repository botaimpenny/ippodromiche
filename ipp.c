#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "/home/ubuntu/pjojectA/ipp.h"
//1
HorseList initHorseList(){
    HorseList list;
    list.horses = NULL;
    list.size = 0;
    list.capacity = 0;
    return list;
}

//2
void addHorse(HorseList *list, const char *name, const char *breed, int age){
    if (list->size == list->capacity){
        list->capacity = (list->capacity == 0) ? 1: list->capacity * 2;
        list->horses = (Horse *)realloc(list->horses, list->capacity * sizeof(Horse));
        if (list->horses == NULL){
            perror("Ошибка памяти, ячейка пуста. ");
            exit(EXIT_FAILURE);
        }
    }

    Horse newHorse;
    newHorse.id = list->size + 1; 

    newHorse.name = strdup(name);
    if (newHorse.name == NULL){
        perror("Ошибка выделения памяти");
        free(list->horses);
        exit(EXIT_FAILURE);
    }

    newHorse.breed = strdup(breed);
    if (newHorse.breed == NULL){
        perror("Ошибка выделения памяти");
        free(list->horses);
        exit(EXIT_FAILURE);
    }

    newHorse.age = age;
    newHorse.wins = 0;
    list->horses[list->size] = newHorse;
    list->size++;
}

//3
void printHorseList(const HorseList list){
    if (list.size == 0){
        printf("Нет данных\n");
        return;
    }
    printf("ID Имя Породв Возраст Кол-во побед\n");
    for (int i = 0; i < list.size; i++){
        printf("%d  %s  %s  %d  %d\n",list.horses[i].id, list.horses[i].name, list.horses[i].breed, list.horses[i].age, list.horses[i].wins);
    }
}

//4
void freeHorseList(HorseList *list){
    for (int i=0;i< list->size; i++){
        freeHorse(list->horses[i]);
    }
    free(list->horses);
    list->horses = NULL;
    list->size = 0;
    list->capacity = 0;
} 

//5
void freeHorse(Horse horse){
    free(horse.name);
    free(horse.breed);
}

//6
void loadHorsesFromFile(HorseList *list, const char *filename){
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL){
        return; 
    }

    int id, age, wins;
    char namebuf[256];
    char breedbuf[256];
    while (fread(&id, sizeof(int), 1, fp) == 1 && fread(namebuf, sizeof(char), 255, fp) == 255 && fread(breedbuf, sizeof(char), 255, fp) == 1 && fread(&age, sizeof(int), 1, fp) == 1 && fread(&wins,sizeof(int), 1, fp) == 1){
        namebuf[255] ='\0';
        breedbuf[255] = '\0';

        if (list->size == list->capacity){
            list->capacity = (list->capacity == 0) ? 1 : list->capacity * 2;
            list->horses = (Horse*)realloc(list->horses, list->capacity * sizeof(Horse));
            if (list->horses == NULL){
                perror("Ошибка памяти");
                fclose(fp);
                exit(EXIT_FAILURE);
            }
        }
        
        Horse newHorse;
        newHorse.id = id;
        newHorse.name = strdup(namebuf);
        newHorse.breed = strdup(breedbuf);
        newHorse.age = age;
        newHorse.wins = wins;

        list->horses[list->size] = newHorse;
        list->size++;
    }
    fclose(fp);
}

//7
void saveHorsesToFile(const HorseList list, const char *filename){
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL){
        perror("Файл пустой");
        return;
    }
    for (int i=0;i< list.size; i++){
        fwrite(&list.horses[i].id, sizeof(int), 1, fp);
        fwrite(list.horses[i].name, sizeof(char), strlen(list.horses[i].name), fp);
        fwrite("\0", sizeof(char), 1, fp);
        fwrite(list.horses[i].breed, sizeof(char), strlen(list.horses[i].breed), fp);
        fwrite("\0", sizeof(char), 1, fp);
        fwrite(&list.horses[i].age, sizeof(int), 1, fp);
        fwrite(&list.horses[i].wins, sizeof(int), 1, fp);
    }
    fclose(fp); 
}

//8
int findHorseById(const HorseList list, int id){
    for (int i=0;i < list.size; i++){
        if (list.horses[i].id == id){
            return i;
        }
    }
    return -1;
}

//9
void removeHorse(HorseList *list, int id){
    int index = findHorseById(*list, id);
    if (index == -1){
        printf("ID %d не найден\n", id);
        return;
    }
    freeHorse(list->horses[index]);

    for (int i=index;i < list->size-1; i++){
        list->horses[i] = list->horses[i + 1];
    }
    list->size--;
    printf("%d успешно удален\n", id);
}

//10
void editHorse(HorseList *list, int id){
    int index = findHorseById(*list, id);
    if (index == -1){
        printf("ID %d не найден\n", id);
        return;
    }
    Horse *horse = &list->horses[index];
    
    printf("Детали:\n");
    printf("Имя: %s\n", horse->name);
    printf("Порода: %s\n", horse->breed);
    printf("Возраст: %d\n", horse->age);
    printf("Кол-во побед: %d\n", horse->wins);

    char *newName = NULL;
    char *newBreed = NULL;
    int newAge;
    size_t newnamelen = 0;
    size_t newbreedlen = 0;

    printf("Введите новое имя: ");
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, stdin) > 0){
        if (line[0] != '\n'){
            line[strcspn(line,"\n")] = 0;
            newName = strdup(line);
            free(horse->name);
            horse->name = newName;
        }
        free(line);
    }

    printf("Введите новую породу: ");
    line = NULL;
    len = 0;
    if (getline(&line, &len, stdin) > 0){
        if (line[0] != '\n'){
            line[strcspn(line,"\n")] = 0;
            newBreed = strdup(line);
            free(horse->breed);
            horse->breed = newBreed;
        }
        free(line);
    }
    printf("Введите новый возраст: ");
    if (scanf("%d",&newAge) == 1){
        if (newAge != -1){
            horse->age = newAge;
        }
    }
    while(getchar() != '\n');
    printf("Лошадь №%d была изменена\n", id);
}

//11
void findHorses(const HorseList list, const char *searchType, const char *searchValue){
    int foundCount = 0;
    printf("Найдено: \n");
    printf("ID Имя Породв Возраст Кол-во побед\n");

    for (int i = 0; i < list.size; i++){
        if (strcmp(searchType, "name") == 0){
            if (strstr(list.horses[i].name, searchValue) != NULL){
                 printf("%d %s %s %d %d\n", list.horses[i].id, list.horses[i].name, list.horses[i].breed, list.horses[i].age, list.horses[i].wins);
                foundCount++;
            }
        } else if (strcmp(searchType, "breed") == 0){
             if (strstr(list.horses[i].breed, searchValue) != NULL){
                  printf("%d %s %s %d %d\n", list.horses[i].id, list.horses[i].name, list.horses[i].breed, list.horses[i].age, list.horses[i].wins);
                foundCount++;
            }
        }
    }

    if (foundCount == 0){
        printf("Ничего не найдено\n");
    } 
    else{
    printf("Найдено %d лоашдей\n", foundCount);
    }
}

//12
void updateWins(HorseList *list, int id){
    int index = findHorseById(*list, id);
    if(index == -1){
        printf("Ничего не найдено\n");
        return;
    }
    list->horses[index].wins++;
    printf("Победа для ID %d обновлены\n", id);
}
