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

bool ask(char *s)
{
    char choice, c;
    printf("Chage %s (press Y if yes)?\n", s);
    scanf("%c", &choice);
    while ((c = getchar()) != '\n' && c != EOF){}
    return choice == 'Y';
}

void menu()
{
    char line[255];
    FILE *fp = fopen("menu.txt", "r");
    while(fgets(line, 255, fp))
        printf("%s", line);
    printf("\n");
}

void time(info *i)
{
    if(!ask("Time")) return;
    
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
    if(!ask("Attribute")) return;
    
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
    if(!ask("Judge")) return;
    
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
    if(!ask("Capability")) return;
    
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
    if(!ask("Performance")) return;
    
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
    if(!ask("Other")) return;
    
    printf("Money: %u-> ", i->money);
    i->money = detect(0, 0xFFFF);
    
    printf("Star: %u-> ", i->star);
    i->star = detect(0, 3);
    
    printf("Age: %u-> ", i->age);
    i->age = detect(0, 99);
}

void b(body *i, info *j)
{
    i->year = j->year;
    i->month = j->month;
    i->weekday = j->weekday;
    i->date = j->date;

    if(!ask("Body")) return;
    
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
}