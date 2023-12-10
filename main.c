#include "hashMap.h"
#include "stack.h"
#include "tree.h"
#include <time.h>


Map* pifPafPouf(Map* hmap) {
    for (int i = 0; i < 9; i++) {
        KdPlayer a;
        int nameLength = rand() % 9 + 1;
        for (int j = 0; j < nameLength; j++) {
            a.name[j] = 'a' + rand() % 26;
        }
        a.name[nameLength] = '\0';

        a.kills = rand() % 100;
        a.deaths = rand() % 50;
        a.hash = hash(a.name);

        if(addHM(hmap, a)!=1){
			exit(3);
		}
    }
    return hmap;
}



int main() {
    srand(time(NULL));

    Map* hmap = createHM();

    KdPlayer zak;
    strcpy(zak.name, "zak");
    zak.kills = 5;
    zak.deaths = 18;
    zak.hash = hash(zak.name);

    KdPlayer liam;
    strcpy(liam.name, "liam");
    liam.kills = 16;
    liam.deaths = 15;
    liam.hash = hash(liam.name);

    KdPlayer mario;
    strcpy(mario.name, "mario");
    mario.kills = 22;
    mario.deaths = 14;
    mario.hash = hash(mario.name);

    KdPlayer test;
    strcpy(test.name, "a");
    test.kills = 22;
    test.deaths = 14;
    test.hash = hash(test.name);


    addHM(hmap, zak);
    addHM(hmap, liam);
    addHM(hmap, mario);
    pifPafPouf(hmap);
    update(hmap,"zak",20,12);
    removeHM(hmap,"liam");
    display(hmap);
    KdPlayer* a = getHM(hmap,"zak");
    if (a != NULL) {
        printf("\n\n-KD Player has been found-\n\n	nom : %s\n	kills : %d\n	deaths : %d\n", a->name, a->kills, a->deaths);
    }
    printf("\n\n\n              -- size : %d --\n\n",hmap->size);

    freeMap(hmap);



    return 0;
}
