#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef struct s_info
{
    uint16_t header[25];
    uint16_t year;
    uint16_t month;
    uint16_t weekday;
    uint16_t date;
    uint16_t unknow_0[2];
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
    uint16_t warrior_judge;
    uint16_t magic_judge;    
    uint16_t social_judge; 
    uint16_t housework_judge;
    uint16_t fight_skill;    
    uint16_t attack_ability;    
    uint16_t defense_ability;    
    uint16_t magic_skill;  
    uint16_t magic_ability;    
    uint16_t anti_magic;    
    uint16_t etiquette; 
    uint16_t art; 
    uint16_t communication; 
    uint16_t cook; 
    uint16_t clean; 
    uint16_t treat;
    uint16_t unknow_1[30];
    uint16_t money;
    uint16_t unknow_2[4];
    uint16_t age;
    uint16_t unknow_3[11];
    uint16_t height;
    uint16_t weight;
    uint16_t chest;
    uint16_t waist;
    uint16_t hip;
    uint16_t unknow_4[9];
    uint16_t relationship;//人際
}info;

info it;

void print_time()
{
    printf("Year: %u\n", it.year);
    printf("Month: %u\n", it.month);
    printf("Weekday: %u\n", it.weekday);   
    printf("Date: %u\n", it.date);
    printf("\n");
}

void print_age()
{
    printf("Age: %u\n", it.age);
    printf("\n");
}

void print_attribute()
{
    printf("HP: %u\n", it.hp);
    printf("Power: %u\n", it.power);
    printf("Intelligence: %u\n", it.intelligence);
    printf("Disposition: %u\n", it.disposition);
    printf("Charisma: %u\n", it.charisma);
    printf("Morality: %u\n", it.morality);
    printf("Believe: %u\n", it.believe);
    printf("Guilt: %u\n", it.guilt);
    printf("Feel: %u\n", it.feel);
    printf("Tired: %u\n", it.tired);
    printf("\n");
}

void print_judge()
{
    printf("Warrior: %u\n", it.warrior_judge);
    printf("Magic: %u\n", it.magic_judge);
    printf("Social: %u\n", it.social_judge);
    printf("Housework: %u\n", it.housework_judge);
    printf("\n");
}

void print_capability()
{
    printf("Fight: %u\n", it.fight_skill);
    printf("Attack: %u\n", it.attack_ability);
    printf("Defense: %u\n", it.defense_ability);
    printf("Magic skill: %u\n", it.magic_skill);
    printf("Magic ability: %u\n", it.magic_ability);
    printf("Anti_magic_ability: %u\n", it.anti_magic);
    printf("\n");
}

void print_performance()
{
    printf("Etiquette: %u\n", it.etiquette);
    printf("Art: %u\n", it.art);
    printf("Communication: %u\n", it.communication);
    printf("Cook: %u\n", it.cook);
    printf("Clean: %u\n", it.clean);
    printf("Treat: %u\n", it.treat);
    printf("\n");
}

void printf_body()
{
    printf("Height: %u\n", it.height/100);
    printf("Weight: %u\n", it.weight/100);
    printf("Chest circumference: %u\n", it.chest/100);
    printf("Waist circumference: %u\n", it.waist/100);
    printf("Hip circumference: %u\n", it.hip/100);
    printf("\n");
}

void menu()
{
    printf("-Time：\n\t。year\n \t。month\n\t。weekday\n\t。date\n");
    printf("-Attributes：\n\t。hp\n\t。power\n\t。intelligence\n\t。disposition\n\t。charisma\n\t。orality\n\t。believe\n\t。guilt\n\t。feel\n\t。tired\n");
    printf("-Judge：\n\t。warrior_judge\n\t。magic_judge\n\t。social_judge\n\t。housework_judge\n");
    printf("-Capability：\n\t。fight_skill\n\t。attack_ability\n\t。defense_judge\n\t。magic_skill\n\t。magic_ability\n\t。anti_magic\n");
    printf("-Performance：\n\t。etiquette\n\t。art\n\t。communication\n\t。cook\n\t。clean\n\t。treat\n");
    printf("-Finance：\n\t。money\n");
    printf("-Body：\n\t。height\n\t。weight\n\t。chaest\n\t。waist\n\t。hip\n");
    printf("-Age：\n\t。age\n");
}

int main()
{
    FILE *fp = NULL, *out = NULL;
    if((fp = fopen("F101.GNX", "r")) == NULL)
    {
        printf("File could not open.\n");
        return 0;
    }
    out = fopen("F105.GNX", "w");
    /*fread(&it, sizeof(info), 1, fp);
    fwrite(&it, sizeof(info), 1, out);*/
    
    int count = 0;
    uint32_t j = 0;
    
    while(!feof(fp))
    {
        fread(&j, 1, sizeof(uint32_t), fp);
        fwrite(&j, 1, sizeof(uint32_t), out);
        count++;
    }printf("%d\n", count);
    /*uint16_t *j = (uint16_t*)malloc(size);
    fread(j, 1, sizeof(j), fp);
    fwrite(j, 1, sizeof(j), out); */
    
}