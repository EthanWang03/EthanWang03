#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Available{
    int mileage;
    char licencePlate[8]; // max length of licence plate in ontario
    struct Available *next;
};
struct Rented{
    int mileage;
    int returnDate;
    char licencePlate[8]; // max length of licence plate in ontario
    struct Rented *next;
};
struct Repair{
    int mileage;
    char licencePlate[8]; // max length of licence plate in ontario
    struct Repair *next;
};

// adds new node onto the top of the linked list
void pushAvailable(struct Available ** head, int newMileage, char newLicencePlate[8]){
    //function 1
    struct Available* newNode = (struct Available*) malloc(sizeof(struct Available));
    newNode->mileage = newMileage; // set newNode to hold all new data
    strcpy(newNode->licencePlate, newLicencePlate);
    if (head == NULL){ //case if linked list is empty
        *head = newNode;
    }
    newNode->next = *head; //adds newNode to the head of the linked List
    *head = newNode;
}

// adds new node onto the top of the linked list
void pushRented(struct Rented ** head, int newMileage, char newLicencePlate[8], int returnDate){

    struct Rented* newNode = (struct Rented*) malloc(sizeof(struct Rented));
    newNode->mileage = newMileage; // set newNode to hold all new data
    strcpy(newNode->licencePlate, newLicencePlate);
    newNode->returnDate = returnDate;
    if (head == NULL){ //case if linked list is empty
        *head = newNode;
    }
    newNode->next = *head; //adds newNode to the head of the linked List
    *head = newNode;
}

// adds new node onto the top of the linked list
void pushRepair(struct Repair ** head, int newMileage, char newLicencePlate[8]){

    struct Repair* newNode = (struct Repair*) malloc(sizeof(struct Repair));
    newNode->mileage = newMileage; // set newNode to hold all new data
    strcpy(newNode->licencePlate, newLicencePlate);
    if (head == NULL){ //case if linked list is empty
        *head = newNode;
    }
    newNode->next = *head; //adds newNode to the head of the linked List
    *head = newNode;
}

// takes the node at the top of Available linked list and transfer data to Rented linked list
void rentAvailable(struct Available *availableHead, struct Rented **rentedHead, int returnDate){
    //function 5
    struct Rented* newNode = (struct Rented*) malloc(sizeof(struct Rented));

    newNode->mileage = availableHead->mileage;
    newNode->returnDate = returnDate; // stores data in newNode
    strcpy(newNode->licencePlate,availableHead->licencePlate);
    if(rentedHead == NULL){ // case for if rented is empty
        *rentedHead = newNode;
    }
    newNode->next = *rentedHead; //sets head to newNode
    *rentedHead = newNode;

}

// moves rented car from Rented linked list to the Repair linked list
double returnToRepair(struct Rented **rentedHead, struct Repair **repairHead, char search[8], int newMileage){
    //function 3
    struct Repair* newNode = (struct Repair*) malloc(sizeof(struct Repair));
    struct Rented *temp;
    struct Rented *prev;
    temp = *rentedHead;
    char copyPlate[8];
    int numMatch = 0;
    int diff = 0;
    int index = 0;
    double total;
    for(int i = 0; i < strlen(search); i++){ //seach in all uppercase
        search[i] = toupper(search[i]);
    }
    while(temp != NULL){ //while you are not at the end of the linked list
        strcpy(copyPlate,temp->licencePlate);
        if(strcmp(copyPlate,search) == 0){ //if licence plate is a match
            numMatch = numMatch + 1;
            diff = newMileage - temp->mileage;
            if(diff < 0){ // calculates profit
                printf("New Mileage is lower than previous mileage!\n");
                free(temp);
                return 0;
            }
            else{
                if(diff > 200){
                    diff = diff - 200;
                    total = 80 + (diff * 0.15);
                }
                else{
                    total = 80;
                }
            }
            newNode->mileage = newMileage;
            strcpy(newNode->licencePlate,temp->licencePlate);
            // saves new milage and information into newNode
            if(index == 0){
                // case for if the searched plate is at the top of the linked list
                *rentedHead = temp->next;
                newNode->next = *repairHead;
                *repairHead = newNode;
                free(temp);
                return total;
            }
            newNode->next = *repairHead;
            *repairHead = newNode;
            //sets the head of the available linked list to newNode

            prev->next = temp->next; //stores the seached node in temp
            free(temp); // deletes temp
            return total;
        }
        index = index + 1;
        prev = temp;
        temp = temp->next; // navigate through linked list
    }
    if(numMatch == 0){
        printf("Licence plate not found\n");
    }
    free(temp);
    return 0;
}

// moves rented car from Rented linked list to the Available linked list
double returnToAvailable(struct Rented **rentedHead, struct Available **availableHead, char search[8], int newMileage){
    //function 2
    struct Available* newNode = (struct Available*) malloc(sizeof(struct Available));
    struct Rented *temp;
    struct Rented *prev;
    temp = *rentedHead;
    char copyPlate[8];
    int numMatch = 0;
    int diff = 0;
    int index = 0;
    double total;
    for(int i = 0; i < strlen(search); i++){ //seach in all uppercase
        search[i] = toupper(search[i]);
    }
    while(temp != NULL){ //while you are not at the end of the linked list
        strcpy(copyPlate,temp->licencePlate);
        if(strcmp(copyPlate,search) == 0){ //if licence plate is a match
            numMatch = numMatch + 1;
            diff = newMileage - temp->mileage;
            if(diff < 0){ // calculates profit
                printf("New Mileage is lower than previous mileage!\n");
                free(temp);
                return 0;
            }
            else{
                if(diff > 200){
                    diff = diff - 200;
                    total = 80 + (diff * 0.15);
                }
                else{
                    total = 80;
                }
            }
            newNode->mileage = newMileage;
            strcpy(newNode->licencePlate,temp->licencePlate); 
            // saves newMileage and information from rented linked list into newNode
            if(index == 0){ 
                // case for if the searched plate is at the top of the linked list
                *rentedHead = temp->next;
                newNode->next = *availableHead;
                *availableHead = newNode;
                free(temp);
                return total;
            }
            newNode->next = *availableHead;
            *availableHead = newNode;
            //sets the head of the available linked list to newNode

            prev->next = temp->next; //stores the seached node in temp
            free(temp); // deletes temp
            return total;
        }
        index = index + 1;
        prev = temp;
        temp = temp->next; // navigate through linked list
    }
    if(numMatch == 0){
        printf("Licence plate not found\n");
    }
    free(temp);
    return 0;
}

// moves car being repaired from Repair linked list to the Available linked list
void repairToAvailable(struct Repair **repairHead, struct Available **availableHead, char search[8]){
    //function 4
    struct Available* newNode = (struct Available*) malloc(sizeof(struct Available));
    struct Repair *temp;
    struct Repair *prev;
    temp = *repairHead;
    char copyPlate[8];
    int numMatch = 0;
    int index = 0;
    for(int i = 0; i < strlen(search); i++){ //seach in all uppercase
        search[i] = toupper(search[i]);
    }
    while(temp != NULL){
        strcpy(copyPlate,temp->licencePlate);

        if(strcmp(copyPlate,search) == 0){ //if licence plate is a match
            numMatch = numMatch + 1;
            newNode->mileage = temp->mileage;
            strcpy(newNode->licencePlate,temp->licencePlate);
            // saves information from repair linked list into newNode
            if(index == 0){
                // case for if the searched plate is at the top of the linked list
                *repairHead = temp->next;
                newNode->next = *availableHead;
                *availableHead = newNode;
                free(temp);
                return;
            }
            newNode->next = *availableHead;
            *availableHead = newNode;
            //sets the head of the available linked list to newNode

            prev->next = temp->next; //stores the seached node in temp
            free(temp); //deletes temp
            return;
        }
        index = index + 1;
        prev = temp;
        temp = temp->next; // navigate through linked list
    }
    if(numMatch == 0){
        printf("Licence plate not found\n");
    }
    free(temp);
}

//deletes the head of the Available linked list
void deleteAvailable(struct Available **head){
    if(head == NULL){
        printf("No cars available \n");
        return;
    }
    struct Available* temp = (struct Available*) malloc(sizeof(struct Available));
    temp = *head;
    *head = (*head)->next; //set head to the next node
    free(temp);
}

//deletes the head of the Rented linked list  
void deleteRented(struct Rented **head){
    if(head == NULL){
        printf("No cars Rented \n");
        return;
    }
    struct Rented* temp = (struct Rented*) malloc(sizeof(struct Rented));
    temp = *head;
    *head = (*head)->next; //sets head to next node
    free(temp);
}

//prints Available linked list
void printListAvailable(struct Available *node)
{
    printf("\nCars available to rent: \n");
    printf("\nMiles  | Plate \n");
    printf("-------+---------\n");
    while (node != NULL){ //while you are not at the end of the linked list
        printf("%-6d | %-10s\n", node->mileage, node->licencePlate);
        node = node->next; //navigate through array
    }
}

//prints Rented linked list
void printListRented(struct Rented *node)
{
    printf("\nRented cars: \n");
    printf("\nReturn | Miles  | Plate\n");
    printf("-------+--------+---------\n");
    while (node != NULL){ //while you are not at the end of the linked list
        printf("%-6d | %-6d | %-10s\n", node->returnDate, node->mileage, node->licencePlate);
        node = node->next;
    } // navigates through array
}

//prints Repair linked list
void printListRepair(struct Repair *node)
{
    printf("\nCars in workshop: \n");
    printf("\nMiles  | Plate \n");
    printf("-------+---------\n");
    while (node != NULL){
        printf("%-6d | %-10s\n", node->mileage, node->licencePlate);
        node = node->next; // navigate through linked list
    }
}

//uses bubble sort to sort Available linked list by mileage
void sortAvailable(struct Available **head){
    struct Available *temp;
    struct Available *temp2 = NULL;
    int swappedMileage;
    char swappedLicence[8];
    if (head == NULL){ // checks if linked list is empty
        printf("Linked list is empty!\n");
        return;
    }
    temp = *head;
    while (temp->next != NULL){ // bubble sort
        temp2 = temp->next;
        while (temp2 != NULL){
            if (temp->mileage > temp2->mileage){
                swappedMileage = temp->mileage; // swaps mileage
                temp->mileage = temp2->mileage;
                temp2->mileage = swappedMileage;

                strcpy(swappedLicence,temp->licencePlate); // swaps licence plate
                strcpy(temp->licencePlate,temp2->licencePlate);
                strcpy(temp2->licencePlate,swappedLicence);
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
}

//uses bubble sort to sort Rented linked list by return date
void sortRented(struct Rented **head){
    struct Rented *temp;
    struct Rented *temp2 = NULL;
    int swappedReturn;
    int swappedMileage;
    char swappedLicence[8];
    if (head == NULL){ // checks if linked list is empty
        printf("Linked list is empty!\n");
        return;
    }
    temp = *head;
    while (temp->next != NULL){ // bubble sort
        temp2 = temp->next;
        while (temp2 != NULL){
            if (temp->returnDate > temp2->returnDate){
                swappedMileage = temp->mileage; // swaps mileage
                temp->mileage = temp2->mileage;
                temp2->mileage = swappedMileage;

                strcpy(swappedLicence,temp->licencePlate); // swaps licence plate
                strcpy(temp->licencePlate,temp2->licencePlate);
                strcpy(temp2->licencePlate,swappedLicence);

                swappedReturn = temp->returnDate; // swaps return date
                temp->returnDate = temp2->returnDate;
                temp2->returnDate = swappedReturn;
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
}

// returns 1 if Available linked list is empty
int checkNullAvailable(struct Available **availableHead){
    struct Available *temp;
    temp = *availableHead;
    if(temp == NULL){ // checks if linked list is empty
        printf("\nno cars available\n");
        return 1;
    }
    return 0;
}

//returns 1 if Rented linked list is empty
int checkNullRented(struct Rented **rentedHead){
    struct Rented *temp;
    temp = *rentedHead;
    if(temp == NULL){ // checks if linked list is empty
        printf("\nno cars rented\n");
        return 1;
    }
    return 0;
}

//returns 1 if Repair linked list is empty
int checkNullRepair(struct Repair **repairHead){
    struct Repair *temp;
    temp = *repairHead;
    if(temp == NULL){ // checks if linked list is empty
        printf("\nno cars in workshop\n");
        return 1;
    }
    return 0;
}

// checks if user inputted licence plate is already in use
// returns 1 if plate is already in use
int checkAvailable(struct Available **availableHead, char search[8]){
    struct Available *temp;
    temp = *availableHead;
    char copyPlate[8];
    while(temp != NULL){
        strcpy(copyPlate,temp->licencePlate);
        if(strcmp(copyPlate,search) == 0){ //if licence plate is a match
            printf("Licence plate is already registered\n");
            return 1;
        }
        temp = temp->next;
    }
    free(temp);
    return 0;
}

//loads Available linked list with data from file available.csv
void loadAvailableFromFile(struct Available **availableHead){
    FILE *file;
    char line[20];
    char *token;
    int miles;
    char licence[8];
    int size;

    file = fopen("available.csv", "r"); //open to read 
    if (NULL != file) {
        fseek (file, 0, SEEK_END);
        size = ftell(file); //travels to end of file and ftells the amount of chars

        if (0 == size) { // if no chars detected the file is empty
            printf("file is empty\n");
        }
        else{
            fseek(file, 0, SEEK_SET); //travel back to the start of the array
            while(feof(file) == 0){
                fgets(line,20,file); //scans file
                token = strtok(line,","); // token per ,
                strcpy(licence,token); // gets licence plate string
                //printf(token);
                token = strtok(NULL,"\0"); // token per end of string
                miles = atoi(token); // convert mileage string to int
                //printf(token);
                pushAvailable(availableHead, miles, licence); 
                // use pushAvailable to put node at the head of the linked list
            }
        }
    }
    fclose(file);
}

//loads Rented linked list with data from file rented.csv
void loadRentedFromFile(struct Rented **rentedHead){
    FILE *file;
    char line[20];
    char *token;
    int miles;
    char licence[8];
    int returnDate;

    file = fopen("rented.csv", "r");    
    if(file == NULL){
        printf("File is empty!\n");  
        return;        
    }
    while(feof(file) == 0){
        fgets(line,20,file);
        token = strtok(line,","); //parse per ,
        returnDate = atoi(token); 
        // gets return date and coverts to int
        token = strtok(NULL,",");
        strcpy(licence,token);
        token = strtok(NULL,"\0");
         // token per end of string
        miles = atoi(token);
        pushRented(rentedHead, miles, licence, returnDate);
        //uses pushRented to insert node to the top of the linked list
    }
    fclose(file);
}

//loads Repair linked list with data from file atWkShop.csv
void loadRepairFromFile(struct Repair **repairHead){
    FILE *file;
    char line[20];
    char *token;
    int miles;
    char licence[8];

    file = fopen("atWkShop.csv", "r");    
    if(file == NULL){
        printf("File is empty!\n");  
        return;        
    }
    while(feof(file) == 0){
        fgets(line,20,file);
        token = strtok(line,","); //parse per ,
        strcpy(licence,token);
        token = strtok(NULL,"\0"); //token till end of line
        miles = atoi(token);
        pushRepair(repairHead, miles, licence);
        //uses pushRepair to insert node at the top of the linked list
    }
    fclose(file);
}

//saves data from Available linked list to file available.csv
void saveAvailableToFile(struct Available *node){
    FILE *file;
    file = fopen("available.csv","wb");
    //wb clears the file before writing new data to it

    while(node != NULL){
        fprintf(file,"%s,%d",node->licencePlate,node->mileage);
        //uses fprintf to write into file
        node = node->next;
        if(node != NULL){ //enters new line
            fprintf(file,"\n");
        }//avoids adding \n to the end of the data
    }
    fclose(file);
}

//loads data from Rented linked list to file rented.csv
void saveRentedToFile(struct Rented *node){
    FILE *file;
    file = fopen("rented.csv","wb");
    //wb clears the file before writing new data to it

    while(node != NULL){
        fprintf(file,"%d,%s,%d",node->returnDate, node->licencePlate, node->mileage);
        //uses fprintf to write into file
        node = node->next;
        if(node != NULL){ //enters new line
            fprintf(file,"\n");
        }//avoids adding \n to the end of the data
    }
    fclose(file);
}

//loads data from Repair linked list to file atWkShop.csv
void saveRepairToFile(struct Repair *node){
    FILE *file;
    file = fopen("atWkShop.csv","wb");
    //wb clears the file before writing new data to it

    while(node != NULL){
        fprintf(file,"%s,%d",node->licencePlate,node->mileage);
        //uses fprintf to write into file
        node = node->next;
        if(node != NULL){ //enters new line
            fprintf(file,"\n");
        }//avoids adding \n to the end of the data
    }
    fclose(file);
}

//main
int main(){
    struct Available *availableHead = NULL; //creates linked lists
    struct Rented *rentedHead = NULL;
    struct Repair *repairHead = NULL;
    char licencePlate[8];
    int input;
    char a[10];
    double total = 0;
    loadAvailableFromFile(&availableHead); //loads data from file
    if(checkNullAvailable(&availableHead) == 0){ //only sort in order if linked list isnt empty
        sortAvailable(&availableHead);
    }
    loadRentedFromFile(&rentedHead);
    if(checkNullRented(&rentedHead) == 0){  //only sort in order if linked list isnt empty
        sortRented(&rentedHead);
    }
    loadRepairFromFile(&repairHead);
    while(1){
        printf("\n=============MENU=============\n");
        printf("1: Add new car to Available to rent list\n");
        printf("2: Return a rented car to Available to rent list\n");
        printf("3: Return a rented car to the Repair list\n");
        printf("4: Transfer a car from Repair list to Available list\n");
        printf("5: Rent the first available car\n");
        printf("6: Print all the lists\n");
        printf("7: Quit\n");
        printf("==============================\n");
        printf("\nChoose a menu option: ");
        scanf(" %d", &input);
        scanf("%c", a); // accounts for \n after input
        switch(input){//switch for all inputs
            case 1:
                //adds new car to the top of the Available linked list
                printf("Enter a licence plate: ");
                fgets(licencePlate,10,stdin);
                licencePlate[strlen(licencePlate)-1] = '\0'; // removes \n
                for(int i = 0; i < strlen(licencePlate); i++){//makes licence plate all caps
                    licencePlate[i] = toupper(licencePlate[i]);
                }
                if(checkAvailable(&availableHead,licencePlate) == 1){
                    //checks if licence plate is already in use or not
                    break;
                }
                printf("Enter a mileage: ");
                scanf(" %d", &input);
                scanf("%c", a); // accounts for \n after input
                pushAvailable(&availableHead, input,licencePlate);
                sortAvailable(&availableHead); // sort by mileage after user adds node
                break;
            case 2:
                //moves rented car from Rented linked list to the Available linked list
                if(checkNullRented(&rentedHead) == 1){ // break if rented linked list is empty
                    break;
                }
                printf("Enter a licence plate: ");
                fgets(licencePlate,10,stdin);
                licencePlate[strlen(licencePlate)-1] = '\0'; // removes \n
                printf("Enter a mileage: ");
                scanf(" %d", &input);
                scanf("%c", a); // accounts for \n after input
                total = total + returnToAvailable(&rentedHead,&availableHead,licencePlate,input);
                sortAvailable(&availableHead); // sort by mileage after user adds node
                break;
            case 3:
                //moves rented car from Rented linked list to the Repair linked list
                if(checkNullRented(&rentedHead) == 1){ // break if rented linked list is empty
                    break;
                }
                printf("Enter a licence plate: ");
                fgets(licencePlate,10,stdin);
                licencePlate[strlen(licencePlate)-1] = '\0'; // removes \n
                printf("Enter a mileage: ");
                scanf(" %d", &input);
                scanf("%c", a); // accounts for \n after input
                total = total + returnToRepair(&rentedHead,&repairHead,licencePlate,input);
                break;
            case 4:
                //moves car being repaired from Repair linked list to the Available linked list
                if(checkNullRepair(&repairHead) == 1){ // break if repair linked list is empty
                    break;
                }
                printf("Enter a licence plate: ");
                fgets(licencePlate,10,stdin);
                licencePlate[strlen(licencePlate)-1] = '\0'; // removes \n
                repairToAvailable(&repairHead,&availableHead,licencePlate);
                sortAvailable(&availableHead); // sort by mileage after user adds node
                break;
            case 5:
                //takes the node at the top of Available linked list and transfer data to Rented linked list
                if(checkNullAvailable(&availableHead) == 1){ // break if Available linked list is empty
                    break;
                }
                printf("Enter a return date YYMMDD\n");
                printf("if year input starts with a 0 just input last digit ");
                scanf(" %d", &input);
                scanf("%c", a); // accounts for \n after input
                rentAvailable(availableHead,&rentedHead,input);
                //already sorted by mileage therefore removing the top node does not change the order
                deleteAvailable(&availableHead); //deletes top node in Available linked list
                break;
            case 6:
                //prints linked lists
                //checks if they are empty before printing
                if(checkNullAvailable(&availableHead) == 0){
                    printListAvailable(availableHead);
                }
                if(checkNullRented(&rentedHead) == 0){
                    printListRented(rentedHead);
                }
                if(checkNullRepair(&repairHead) == 0){
                    printListRepair(repairHead);
                }
                break;
            case 7:
                //prints total
                printf("total is %.2f\n",total);
                saveAvailableToFile(availableHead);
                saveRentedToFile(rentedHead);
                saveRepairToFile(repairHead);
                return 0;
            default:
                //default for invalid inputs
                printf("invalid input");
        }
    }
}