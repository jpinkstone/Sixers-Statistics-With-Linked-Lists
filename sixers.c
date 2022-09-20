#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CS265 Assignment 2 - Jack Pinkstone

// Player structure
struct player {
    char name[100];
    int salary;
    char season[100];
    struct player *next;
};

// Function to create and insert a player into a linked list
void insertPlayer(struct player ** list, char name[100], int salary, char season[100]){
    struct player *x;
    x = (struct player *) malloc(sizeof(struct player));    // Allocate memory for player
    if(!x){
        printf("Memory could not be allocated. Exiting...\n");
        exit(-1);
    }
    // Set name, salary, and season to struct
    strcpy(x->name, name);
    x->salary = salary;
    strcpy(x->season, season);
    // Set next node and beginning pointer
    x->next = *list;
    *list = x;
}

// Function to swap data of two players
void swap(struct player *a, struct player *b){
    char tempName[100];
    strcpy(tempName, a->name);
    int tempSalary = a->salary;
    char tempSeason[100];
    strcpy(tempSeason, a->season);
    // Set player a's data with player b's
    strcpy(a->name, b->name);
    a->salary = b->salary;
    strcpy(a->season, b->season);
    // Set player b's data with player a's
    strcpy(b->name, tempName);
    b->salary = tempSalary;
    strcpy(b->season, tempSeason);
}

// Bubble sort a linked list
void sortList(struct player *start){
    int swapped, i;
    struct player *ptr1;
    struct player *lptr = NULL;
    // Loop through the list swapping players until sorted
    // Uses the bubble sort algorithm
    do{
        swapped = 0;
        ptr1 = start;
  
        while (ptr1->next != lptr){
            if (strcmp(ptr1->name, ptr1->next->name) > 0){ 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }while (swapped);
}

int main(int argc, char *argv[]){

    // Variables to be used throughout the program
    char *sixers_file, *save_ptr1, *token;
    char sixers_line[256], name[100], season[100], mostName[100], tmpName[100];
    int salary = 0, mostNumber = 0, tmpNumber = 0;

    // Check the command line arguments and set filename
    if(argc == 2){
        sixers_file = argv[1];
    }else if(argc != 1){
        printf("The command line arguments are incorrect\n");
        exit(-1);
    }else{
        sixers_file = "sixers.csv";
    }

    // Open the file
    FILE *sixers_file_content = fopen(sixers_file, "r");
    
    // If the files cannot be opened, exit the program
    if(!sixers_file_content){
        printf("Cannot open the file\n");
        exit(-1);
    }

    // Create list that is null
    struct player *list;
    list = NULL;
    
    // Looping through each line of the file
    while(fgets(sixers_line, 256, sixers_file_content)){
        token = strtok_r(sixers_line, ",", &save_ptr1);
        // Looping through each token in the line
        for(int i = 0; token != NULL; i++){
            if(i == 0){
                strcpy(name, token);
            }else if(i == 1){
                salary = atoi(token);
            }else{
                strcpy(season, token);
            }
            // Get the next token in the line
            token = strtok_r(NULL, ",", &save_ptr1);
        }
        // Insert the player's data into the list as a player node
        insertPlayer(&list, name, salary, season);
    }

    // Sort list alphabetically by player name
    sortList(list);

    struct player *p = list;
    strcpy(tmpName, p->name);

    // Loop through nodes and find the player with most seasons
    for(p; p != NULL; p = p->next){
        if(strcmp(p->name, tmpName) == 0){
            tmpNumber ++;
        }else{
            if(tmpNumber > mostNumber){
                mostNumber = tmpNumber;
                strcpy(mostName, tmpName);
            }
            tmpNumber = 1;
            strcpy(tmpName, p->name);
        }
    }

    printf("The player that played the most seasons for the sixers is %s with %d seasons\n", mostName, mostNumber);

    p = list;
    strcpy(tmpName, p->name);
    tmpNumber = 0, mostNumber = 0;

    // Loop through nodes and find the player with most salary
    for(p; p != NULL; p = p->next){
        if(strcmp(p->name, tmpName) == 0){
            tmpNumber = tmpNumber + p->salary;
        }else{
            if(tmpNumber > mostNumber){
                mostNumber = tmpNumber;
                strcpy(mostName, tmpName);
            }
            tmpNumber = p->salary;
            strcpy(tmpName, p->name);
        }
    }

    printf("The player that earned the most money when they played for the sixers is %s with $%d \n", mostName, mostNumber);

    p = list;
    strcpy(mostName, p->name);
    mostNumber = p->salary;

    // Loop through nodes and find the player with most salary for one season
    for(p; p != NULL; p = p->next){
        if(p->salary > mostNumber){
            mostNumber = p->salary;
            strcpy(mostName, p->name);
        }
    }

    printf("The player that earned the most money in one season playing for the sixers is %s with $%d \n", mostName, mostNumber);
    
    // Close the file
    fclose(sixers_file_content);

}