#include "hw0404.h"

uint16_t detect(uint16_t lower, uint16_t upper)
{
    int32_t temp = upper+1;
    printf("(%u ~ %u)：", lower, upper);
    while(temp < lower || temp > upper)
    {
        printf("-> ");
        scanf("%d", &temp);
        char c; scanf("%c", c);
    } 
    return (uint16_t)temp;
}

void time(info *i)
{
    //printf("Chage time (press Y if yes)?\n");
    
    printf("Year：%u-> ", i->year);
    i->year = detect(0, 9999);  
    
    printf("Month：%u-> ", i->month);
    i->month = detect(1, 12);
    printf("Weekday：%u-> ", i->weekday);
    i->weekday = detect(1, 7);
    
    printf("Date：%u-> ", i->date);
    i->date = detect(1, 31);
}

void att(attribute *i)
{
    printf("HP: %u-> ", i->hp);
    i->hp = detect(0, 999);

    printf("Power: %u-> ", i->power);
    i->power = detect(0, 999);
    
    printf("Intelligence: %u-> ", i->intelligence);
    i->intelligence = detect(0, 999);
    
    printf("Disposition: %u-> ", i->disposition);
    i->disposition = detect(0, 999);
    
    printf("Charisma: %u-> ", i->charisma);
    i->charisma = detect(0, 999);
    
    printf("Morality: %u-> ", i->morality);
    i->morality = detect(0, 999);
    
    printf("Believe: %u-> ", i->believe);
    i->believe = detect(0, 999);
    
    printf("Guilt: %u-> ", i->guilt);
    i->guilt = detect(0, 999);
    
    printf("Feel: %u-> ", i->feel);
    i->feel = detect(0, 999);
    
    printf("Tired: %u-> ", i->tired);
    i->tired = detect(0, 999);   
}

void jud(judge *i)
{    
    printf("Warrior: %u-> ", i->warrior_judge);
    i->warrior_judge = detect(0, 999);
    
    printf("Magic: %u-> ", i->magic_judge);
    i->magic_judge = detect(0, 999);
    
    printf("Social: %u-> ", i->social_judge);
    i->social_judge = detect(0, 999);
    
    printf("Housework: %u-> ", i->housework_judge);
    i->housework_judge = detect(0, 999);
}

void cap(capability *i)
{
    printf("Fight: %u-> ", i->fight_skill);
    i->fight_skill = detect(0, 999);
    
    printf("Attack: %u-> ", i->attack_ability);
    i->attack_ability = detect(0, 999);
    
    printf("Defense: %u-> ", i->defense_ability);
    i->defense_ability = detect(0, 999);
    
    printf("Magic skill: %u-> ", i->magic_skill);
    i->magic_skill = detect(0, 999);
    
    printf("Magic ability: %u-> ", i->magic_ability);
    i->magic_ability = detect(0, 999);
    
    printf("Anti_magic_ability: %u-> ", i->anti_magic);
    i->anti_magic = detect(0, 999);
}

void per(performance *i)
{
    printf("Etiquette: %u-> ", i->etiquette);
    i->etiquette = detect(0, 999);
    printf("Art: %u-> ", i->art);
    i->art = detect(0, 999);
    printf("Communication: %u-> ", i->communication);
    i->communication = detect(0, 999);
    printf("Cook: %u-> ", i->cook);
    i->cook = detect(0, 999);
    printf("Clean: %u-> ", i->clean);
    i->clean = detect(0, 999);
    printf("Treat: %u->", i->treat);
    i->treat = detect(0, 999);
}

void oth(other *i)
{
    printf("Money: %u-> ", i->money);
    i->money = detect(0, 0xFFFF);
    
    printf("Star: %u-> ", i->star);
    i->star = detect(0, 3);
    
    printf("Age: %u-> ", i->age);
    i->age = detect(0, 99);
}

void b(body *i, info *j)
{
    printf("Height <The Last two number is float(13789 -> 137.89)>: %u-> ", i->height);
    i->height = detect(10000, 20000);
    
    printf("Weight <The Last two number is float(13789 -> 137.89)>: %u-> ", i->weight);
    i->weight = detect(2000, 12000);
    
    printf("Chest <The Last two number is float(13789 -> 137.89)>: %u->", i->chest);
    i->chest = detect(3000, 12000);
    
    printf("Waist <The Last two number is float(13789 -> 137.89)>: %u->", i->waist);
    i->waist = detect(3000, 12000);
    
    printf("Hip <The Last two number is float(13789 -> 137.89)>: %u->", i->hip);
    i->hip = detect(3000, 12000);

    uint16_t year = j->year, month = j->month;
    uint16_t weekday = j->weekday, date = j->date;
    
    i->year = j->year;
    i->month = j->month;
    i->weekday = j->weekday;
    i->date = j->date;
}