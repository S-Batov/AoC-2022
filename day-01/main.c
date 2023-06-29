#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Elf{
    int foodCnt;
    int* food;
    int calories;
};

int str2int( const char* s){
    const char* p = s;
    for( ; *p >= '0' && *p <= '9'; p++);
    p--;

    int val = 0;
    int place = 1;

    for(; p>= s; p--){
        val += (*p - '0') * place;
        place *= 10;
    }

    return val;
}

int main(){
    struct Elf* elves;
    int elfCount = 0;
    int currElf = 0;
    char ch;
    char foodStr[6];
    int foodStrLen = 0;

    FILE* input = fopen("input.txt", "r");
    if(input == NULL){
        printf("File can't be opened");
    }

    do{
        ch = fgetc(input);
        if(feof(input)){
            foodStr[foodStrLen] = '\0';
            foodStrLen = 0;
            int foodVal = str2int(foodStr);
            strcpy(foodStr, "");

            //napravi novu hranu
            struct Elf* p_cur_elf = elves + elfCount - 1;
            if(p_cur_elf->foodCnt == 0){
                p_cur_elf->food = malloc(sizeof(int));
            }
            else{
                p_cur_elf->food = realloc(p_cur_elf->food, p_cur_elf->foodCnt * sizeof(int));
            }
            int* p_cur_elf_food = p_cur_elf->food + p_cur_elf->foodCnt;
            *p_cur_elf_food = foodVal;
            p_cur_elf->foodCnt++;
            

            break;
        }

        if(elfCount == 0){
            //u početku napravi novog elfa
            elves = malloc(sizeof(struct Elf));
            elves->foodCnt = 0;
            elfCount++;
        }

        if(ch == '\n'){
            //ako si dosa do kraja reda
            foodStr[foodStrLen] = '\0';
            foodStrLen = 0;
            int foodVal = str2int(foodStr);
            strcpy(foodStr, "");

            //napravi novu hranu
            struct Elf* p_cur_elf = elves + elfCount - 1;
            if(p_cur_elf->foodCnt == 0){
                p_cur_elf->food = malloc(sizeof(int));
            }
            else{
                p_cur_elf->food = realloc(p_cur_elf->food, (p_cur_elf->foodCnt + 1) * sizeof(int));
            }
            int* p_cur_elf_food = p_cur_elf->food + p_cur_elf->foodCnt;
            *p_cur_elf_food = foodVal;
            p_cur_elf->foodCnt++;

            ch = fgetc(input);
            if( ch == '\n' ){
                //ako si dosa do kraja reda i sljedeci znak je novi red
                //napravi novog elfa
                elfCount++;
                p_cur_elf++;
                elves = realloc(elves, elfCount * sizeof(struct Elf));
                currElf++;
                foodStrLen = 0;
                p_cur_elf = elves + elfCount - 1;
                p_cur_elf->foodCnt = 0;
                continue;
            }
            else{
                //pointer je inkrementiran pa triba pocet punit novu hranu
                foodStr[foodStrLen] = ch;
                foodStrLen++;
            }
        }
        else{
            //ako nije novi red onda je linija dio hrane
            foodStr[foodStrLen] = ch;
            foodStrLen++;
        }
    } while(1);
    

    for(int i = 0; i < elfCount; i++){
        int cal = 0;
        for(int j = 0; j < (elves + i)->foodCnt; j++){
            int* p_food = (elves + i)->food;
            int temp = *(p_food + j);
            cal += temp;
        }
        (elves + i)->calories = cal;
    }


    int maxCal1 = 0;
    int maxIndex1 = -1;
    int maxCal2 = 0;
    int maxIndex2 = -1;
    int maxCal3 = 0;
    int maxIndex3 = -1;

    for(int i = 0; i < elfCount; i++){
        if( (elves+i)->calories > maxCal1 ){
            maxCal1 = (elves + i)->calories;
            maxIndex1 = i;
        }
    }
    
    for(int i = 0; i < elfCount; i++){
        if(i == maxIndex1)
            continue;

        if( (elves+i)->calories > maxCal2 ){
            maxCal2 = (elves + i)->calories;
            maxIndex2 = i;
        }
    }
    
    for(int i = 0; i < elfCount; i++){
        if( i == maxIndex1 || i == maxIndex2)
            continue;

        if( (elves+i)->calories > maxCal3 ){
            maxCal3 = (elves + i)->calories;
            maxIndex3 = i;
        }
    }

    free(elves);
    printf("Top 3 cal: %d", maxCal1 + maxCal2 + maxCal3);
    while(!getch());
    return 0;
}