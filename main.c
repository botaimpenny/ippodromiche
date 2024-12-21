#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "/home/ubuntu/pjojectA/ipp.h"

#define DATA_FILE "ippodrom.dat"
int main(){
    HorseList horses = initHorseList();
    loadHorsesFromFile(&horses, DATA_FILE);

    int choice;
    char *name = NULL;
    char *breed = NULL;
    int age;
    int id;
    char searchType[10];
    char searchValue[256];
    size_t name_len = 0;
    size_t breed_len = 0;

    while (1){
        printf("ипподром: \n");
        printf("1. Список всех лошадей\n");
        printf("2. Добавить новую лошадь\n");
        printf("3. Поиск\n");
        printf("4. Изменить кол-во побед\n");
        printf("5. Удалить лошадь\n");
        printf("6. Изменить конфигурацию лошади (тачка на прокачку йоу)\n");
        printf("0. выйти :<\n");
        printf(" ");

        if (scanf("%d", &choice) != 1){
            while(getchar() != '\n');
            printf("Ошибка ввода, попробуй снова\n");
            continue;
        }
        
        while(getchar() != '\n');
        switch (choice){
            case 1:
                printHorseList(horses);
                break;
            
            case 2:
                printf("Введите имя: ");
                if (getline(&name,&name_len, stdin) <= 0){
                    fprintf(stderr, "ошибка чтения\n");
                    free(name);
                    continue;
                }
                name[strcspn(name,"\n")] = 0;

                printf("Введите породу: ");
                if (getline(&breed,&breed_len, stdin) <= 0){
                    fprintf(stderr, "ошибка чтения\n");
                    free(breed);
                    continue;
                }
                breed[strcspn(breed,"\n")] = 0;

                printf("Введите возраст: ");
                if (scanf("%d", &age) != 1){
                    printf("Ошибка вывода возраста\n");
                    while(getchar() != '\n');
                    free(name);
                    free(breed);
                    continue;
                }
                while(getchar() != '\n');
                addHorse(&horses, name, breed, age);
                printf("Лошадь добавлена в список\n");
                free(name);
                free(breed);
                name = NULL;
                breed = NULL;
                break;
            
            case 3:
                printf("Поиск по имени и породе: ");
                if (scanf("%s", searchType) != 1){
                     printf("Ошибка ввода\n");
                     while(getchar() != '\n');
                     continue;
                }
                while(getchar() != '\n');

                printf("Введите известные данные: ");
                if (fgets(searchValue, sizeof(searchValue), stdin) == NULL){
                    fprintf(stderr, "Ошибка чтения\n");
                    continue;
                }
                searchValue[strcspn(searchValue, "\n")] = 0;
                findHorses(horses, searchType, searchValue);
                break;
            
            case 4:
                printf("Введите ID ");
                if (scanf("%d", &id) != 1){
                    printf("Ошибка ввода\n");
                    while(getchar() != '\n');
                    continue;
                }
                while(getchar() != '\n');
                updateWins(&horses, id);
                break;
            
            case 5:
                printf("Введите ID чтобы удалить лошадь: ");
                if (scanf("%d", &id) != 1){
                    printf("Ошибка ввода\n");
                    while(getchar() != '\n');
                    continue;
                }
                while(getchar() != '\n');
                removeHorse(&horses, id);
                break;

            case 6:
                printf("Введите ID чтобы внести изменения: ");
                if (scanf("%d", &id) != 1){
                    printf("Ошибка ввода\n");
                    while(getchar() != '\n');
                    continue;
                }
                while(getchar() != '\n');
                editHorse(&horses, id);
                break;
            
            case 0:
                saveHorsesToFile(horses, DATA_FILE);
                freeHorseList(&horses);
                printf("Выход...\n");
                return 0;
            
            default:
                printf("Ошибка ввода\n");
        }
    }
    return 0;
}
