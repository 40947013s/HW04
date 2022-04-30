#ifndef HW0404_H_INCLUDE
#define HW0404_H_INCLUDE

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_info
{
    uint16_t header[25];
    uint16_t year;
    uint16_t month;
    uint16_t weekday;
    uint16_t date;
}info; //29

typedef struct s_attribute
{
    uint16_t unchange[2];
    uint16_t hp;
    uint16_t power;
    uint16_t intelligence;
    uint16_t disposition;
    uint16_t charisma;
    uint16_t morality;
    uint16_t believe;
    uint16_t guilt;
    uint16_t feel;
    uint16_t tired;
    uint16_t unknowed;
}attribute; //12

typedef struct s_judge
{
    uint16_t warrior_judge;
    uint16_t magic_judge;    
    uint16_t social_judge; 
    uint16_t housework_judge;
}judge; //5

typedef struct s_capability
{
    uint16_t fight_skill;    
    uint16_t attack_ability;    
    uint16_t defense_ability;    
    uint16_t magic_skill;  
    uint16_t magic_ability;    
    uint16_t anti_magic;    
}capability; //6

typedef struct s_performance
{
    uint16_t etiquette; 
    uint16_t art; 
    uint16_t communication; 
    uint16_t cook; 
    uint16_t clean; 
    uint16_t treat;
}performance; //6

typedef struct s_other
{
    uint16_t unknow_1[30];
    uint16_t money;
    uint16_t unknow_2[2];
    uint16_t star;
    uint16_t unknow_3;
    uint16_t age;
    uint16_t unknow_4[11];
}other;

typedef struct s_body
{
    uint16_t height;
    uint16_t weight;
    uint16_t chest;
    uint16_t waist;
    uint16_t hip;
    uint16_t unknow_5[9];
    uint16_t relationship;//人際
    uint16_t unknow_6[338];
    uint16_t year;
    uint16_t month;
    uint16_t weekday;
    uint16_t date;
}body; //62

uint16_t detect(uint16_t lower, uint16_t upper);
void menu();
bool ask(char *s);
void time(info *i);
void att(attribute *i);
void jud(judge *i);
void cap(capability *i);
void per(performance *i);
void oth(other *i);
void b(body *i, info *j);

#endif