//
//  KodPet.c
//  KodPetFlipper
//
//  Created by KodamaDeveloper
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "kodpet.h"

// Initialize a new Tamagotchi with default values
Tamagotchi* createTamagotchi() {
  Tamagotchi* t = malloc(sizeof(Tamagotchi));
  t->status = HUNGRY;
  t->hunger = 100;
  t->happiness = 100;
  t->cycle = 0;
  t->care = 10;
  t->evolution = EGG;
      if(savedataControl(t, "n"))
       return t;
  return t;
}

int parseInt(char* chars)
{
    int sum = 0;
    int len = strlen(chars);
    for (int x = 0; x < len; x++)
    {
        int n = chars[len - (x + 1)] - '0';
        sum = sum + powInt(n, x);
    }
    return sum;
}

int powInt(int x, int y)
{
    for (int i = 0; i < y; i++)
    {
        x *= 10;
    }
    return x;
}

int savedataControl(Tamagotchi* t, char* mode){
 char *fileName = "data.txt";
 char *normal = "n";
 char *save = "s";
     if(!access(fileName, F_OK) && mode == normal){
        dataopen();
        printf("The File %s\t was Found\n",fileName);
        FILE * file_pointer;
        char buffer[64], c;

        file_pointer = fopen(fileName, "r");
        printf("----read a line progress----\n");
        fgets(buffer, 50, file_pointer);
        printf("%s\n", buffer);

        printf("----read and parse data progress----\n");
        file_pointer = fopen(fileName, "r"); //reset the pointer
        char str1[10], str2[10], str3[10], str4[10], str5[10], str6[10];
        fscanf(file_pointer, "%s %s %s %s %s %s", str1, str2, str3, str4, str5, str6);
        printf("Read Data |%s|\n", str1);
        printf("Read Data |%s|\n", str2);
        printf("Read Data |%s|\n", str3);
        printf("Read Data |%s|\n", str4);
        printf("Read Data |%s|\n", str5);
        printf("Read Data |%s|\n", str6);

        printf("----read the entire file progress----\n");

        file_pointer = fopen(fileName, "r"); //reset the pointer
        while ((c = getc(file_pointer)) != EOF) printf("%c", c);

        t->status = parseInt(str1);
        t->hunger = parseInt(str2);
        t->happiness = parseInt(str3);
        t->cycle = parseInt(str4);
        t->care = parseInt(str5);
        t->evolution = parseInt(str6);



        fclose(file_pointer);
        dataclose();
        return 0;
    }else{
      if(mode != save){
        printf("The File %s\t not Found\n",fileName);
      }else
      {
        printf("Saved progress control");
      }

        int i;
        FILE * fptr;
        char fn[64];
        char str[64];
        snprintf(str, sizeof(str),"%i %i %i %i %i %i", t->status, t->hunger, t->happiness, t->cycle, t->care, t->evolution);
        fptr = fopen(fileName, "w"); // "w" defines "writing mode"
        for (i = 0; str[i]; i++) {
            /* write to file using fputc() function */
            fputc(str[i], fptr);
        }
        fclose(fptr);
        dataclose();
        return 0;
    }

    if(!access(fileName, R_OK )){
        printf("The File %s\t can be read\n",fileName);
    }else{
        printf("The File %s\t cannot be read\n",fileName);

    }

    if(!access( fileName, W_OK )){
        printf("The File %s\t it can be Edited\n",fileName);
        return 1;
    }else{
        printf("The File %s\t it cannot be Edited\n",fileName);
    }

    if(!access( fileName, X_OK )){
        printf("The File %s\t is an Executable\n",fileName);
    }else{
        printf("The File %s\t is not an Executable\n",fileName);
    }

}

// Perform an action on the Tamagotchi
void doAction(Tamagotchi* t, int action) {
printf("\n\n\n\n######## Cycle %i ###########\n", t->cycle);
printf("######## Evolution %i ###########\n", t->evolution);
  switch (action) {
    case FEED:
      t->hunger += 13;
      if (t->hunger > 100) {
        t->hunger = 100;
      }
      t->care--;
      printf("########  LAST ACTION: FEED\n");
      break;
    case MEDICINE:
      if (t->status == SICK) {
        t->status = HAPPY;
      }
      printf("########  LAST ACTION: MEDICINE\n");
      break;
    case PLAY:
      t->happiness += 12;
      if (t->happiness > 100) {
        t->happiness = 100;
        t->status = HAPPY;
      }
      t->care--;
      printf("########  LAST ACTION: PLAY\n");
      break;
    case CARE:
      t->care += 10;
      if (t->care > 30) {
        t->care = 30;
        t->happiness += HAPPY_FOR_CARE;
      }
      printf("########  LAST ACTION: CARE\n");
      break;
  }

  if(t->status == DIRTY){
    t->happiness--;
  }
  
}

// Update the Tamagotchi's status based on its current values
void updateStatus(Tamagotchi* t) {
  if (t->hunger <= DEAD_HUNGER || t->happiness <= DEAD_HAPPINESS) {
    t->status = DEAD;
    return;
  } else if (t->hunger < 20 || t->happiness < 20) {
    t->status = SICK;
  } else if(t->happiness >= 70){
    t->status = HAPPY;
  }
  else if(t->hunger < 50){
    t->status = HUNGRY;
  }else
  {
    t->status = NORMAL;
  }

  if(t->care <= 0){
    t->status = DIRTY;   
  }
  
  if(t->cycle >= CYCLE_EVOLUTION && t->evolution != QUANTUM){
    t->evolution++;
    t->cycle = 0;
  }

}

// Print the current status of the Tamagotchi
void printStatus(Tamagotchi* t) {
  int selectionoptionuser = 0;

  printf("########\n");
  printf("Hunger: %d\n", t->hunger);
  printf("Happiness: %d\n", t->happiness);
  switch (t->status) {
    case HUNGRY:
      printf("Status: Hungry\n");
      break;
    case SICK:
      printf("Status: Sick\n");
      break;
    case HAPPY:
      printf("Status: HAPPY\n");
      break;
    case POWERED:
      printf("Status: POWERED\n");
      break;
    case GOD:
      printf("Status: GOD\n");
      break;
    case NORMAL:
      printf("Status: NORMAL\n");
      break;
    case DIRTY:
      printf("Status: DIRTY\n");
      break;
    case DEAD:
      printf("Status: Dead\n");
      break;
  }

  printf("######## Select Option: \n 0. FEED. \n 1. MEDICINE \n 2. PLAY \n 4. CARE \n 9. Random Cycle Time \n");
  scanf("%d",&selectionoptionuser);

  if(selectionoptionuser == 9){
      int action = rand() % 3;
      doAction(t, action);
  }else{
  doAction(t, selectionoptionuser);
  }
  printf("########   Selected: %i\n", selectionoptionuser);
}

int main() {
  srand(time(NULL));

  Tamagotchi* t = createTamagotchi();

  // Main game loop
    while (t->status != DEAD) {
      // Randomly choose an action for the Tamagotchi to perform


      // Decrease hunger and happiness over time
      t->hunger -= CYCLE_HUNTER;
      t->happiness -= CYCLE_HAPPINESS;

      // Update the Tamagotchi's status based on its current values
      updateStatus(t);

      // Print the current status of the Tamagotchi
      printStatus(t);
        t->cycle++;

      if(savedataControl(t, "s") == 0)
       printf("Saved progress");
    }

    // Game over
    printf("Game over!\n");

    return 0;
  }

  void dataopen(){
    char ch, *fname;
	FILE *fpts, *fptt;
	
	printf("\n\n Decrypt a text file :\n");
	printf("--------------------------\n"); 	
	

  fname = "data.txt";
	
	fpts=fopen(fname, "w");
	if(fpts==NULL)
	{
		printf(" File does not exists or error in opening..!!");
		exit(7);
	}
	fptt=fopen("temp.txt", "r");
	if(fptt==NULL)
	{
		printf(" File does not exists or error in opening..!!");
		fclose(fpts);
		exit(9);
	}
	while(1)
	{
		ch=fgetc(fptt);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			ch=ch-100;
			fputc(ch, fpts);
		}
	}
	printf(" The file %s desprotected successfully..!!\n\n",fname);
	fclose(fpts);
	fclose(fptt);
  }
  void dataclose(){
    	char *fname, ch;
	FILE *fpts, *fptt;
	
	printf("\n\n Encrypt a text file :\n");
	printf("--------------------------\n"); 	
	

	//scanf("%s",fname);	
  fname = "data.txt";

	fpts=fopen(fname, "r");
	if(fpts==NULL)
	{
		printf(" File does not exists or error in opening..!!");
		exit(1);
	}
	fptt=fopen("temp.txt", "w");
	if(fptt==NULL)
	{
		printf(" Error in creation of file temp.txt ..!!");
		fclose(fpts);
		exit(2);
	}
	while(1)
	{
		ch=fgetc(fpts);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			ch=ch+100;
			fputc(ch, fptt);
		}
	}
	fclose(fpts);
	fclose(fptt);
	fpts=fopen(fname, "w");
	if(fpts==NULL)
	{
		printf(" File does not exists or error in opening..!!");
		exit(3);
	}
	fptt=fopen("temp.txt", "r");
	if(fptt==NULL)
	{
		printf(" File does not exists or error in opening..!!");
		fclose(fpts);
		exit(4);
	}
	while(1)
	{
		ch=fgetc(fptt);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			fputc(ch, fpts);
		}
	}
	printf(" File %s successfully protected ..!!\n\n", fname);
	fclose(fpts);
	fclose(fptt);
  }



