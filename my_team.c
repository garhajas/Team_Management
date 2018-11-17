// Program for maintaining a personal team.
//
//
// Uses a linked list to hold the team players.
//
// Author: <Jaskaran Garha>


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

//**********************************************************************
// Linked List Definitions
//  Define your linked list node and pointer types
//  here for use throughout the file.
//
//
//   ADD STATEMENT(S) HERE
typedef struct node
{
    char *familyName;
    char *firstName;
    char position;
    int value;
    struct node *next;
} Player;

//**********************************************************************
// Linked List Function Declarations
//
// Functions that modify the linked list.
//   Declare your linked list functions here.
//
//   ADD STATEMENT(S) HERE
struct node *first = NULL;

//**********************************************************************
// Support Function Declarations
//

void safegets(char s[], int arraySize);      // gets without buffer overflow
void familyNameDuplicate(char familyName[]); // marker/tester friendly
void familyNameFound(char familyName[]);     //   functions to print
void familyNameNotFound(char familyName[]);  //     messages to user
void familyNameDeleted(char familyName[]);
void printPlayer(Player *toBePrinted);
void printTeamEmpty(void);
void printTeamTitle(void);
void printNoPlayersWithLowerValue(int value);

/* My support functions */
Player *getInput();
Player *createNode(char *playerName, char *familyName, char position, int value);
Player *insertPlayer(Player *list, Player *toBeAdded);
void printList(Player *list);

/* insertion helper function */
int positionCount(Player *list, char position);
int isDuplicate(Player *list, Player *toBeAdded);
Player *addToFront(Player *list, Player *toBeInserted);
Player *addToBack(Player *list, Player *toBeInserted);
int totalPlayers(Player *list);

/* add players based on their positions */
Player *addGoalKeeper(Player *list, Player *goalKeeper);
Player *addDefender(Player *list, Player *defender);
Player *addMidFielder(Player *list, Player *midFielder);
Player *addStriker(Player *list, Player *striker);

/* node deletion helper functions */
Player *findNode(Player *list, char *toBeDeleted);
Player *deleteNode(Player *list, Player *toBeDeleted);
void freeNode(Player *toBeFreed);

void clearList(Player *list);

/* printing the special values */
void customPrint(Player *list, int value);

//**********************************************************************
// Program-wide Constants
//

const int MAX_LENGTH = 1023;
const char NULL_CHAR = '\0';
const char NEWLINE = '\n';
const char GOALKEEPER = 'G';
const char DEFENDER = 'D';
const char MIDFIELDER = 'M';
const char STRIKER = 'S';

//**********************************************************************
// Main Program
//

int main(void)
{
    const char bannerString[] = "Personal Team Maintenance Program.\n\n";
    const char commandList[] = "Commands are I (insert), D (delete), S (search by name),\n"
                               "  V (search by value), P (print), Q (quit).\n";

    // Declare linked list head.
    //   ADD STATEMENT(S) HERE TO DECLARE LINKED LIST HEAD.

    // announce start of program
    printf("%s", bannerString);
    printf("%s", commandList);

    /* list that contains player information */
    Player *list = NULL;

    char response;
    char input[MAX_LENGTH + 1];
    do
    {
        printf("\nCommand?: ");
        safegets(input, MAX_LENGTH + 1);
        // Response is first char entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I')
        {
            // Insert a player entry into the linked list.
            // Maintain the list in correct order (G, D, M, S).
            //   ADD STATEMENT(S) HERE

            // USE THE FOLLOWING PRINTF STATEMENTS WHEN PROMPTING FOR DATA:
            // printf("  family name: ");
            // printf("  first name: ");
            // printf("  position: ");
            // printf("  value: ");

            printf("Insert player information below:\n");
            Player *toBeInserted = getInput();

            /* check for duplicate family names here */
            int returnedResult = isDuplicate(list, toBeInserted);

            if (returnedResult == 0)
            {
                list = insertPlayer(list, toBeInserted);
            }
            else
            {
                familyNameFound(toBeInserted->familyName);
            }
            //response = getchar();
        }
        else if (response == 'D')
        {
            // Delete a player from the list.

            printf("\nEnter family name for entry to delete: ");
            char familyName[1023] = {0};
            fgets(familyName, 1023, stdin);

            /* removes new line */
            familyName[strlen(familyName) - 1] = '\0';

            Player *toBeDeleted = findNode(list, familyName);

            if (toBeDeleted != NULL)
            {
                familyNameDeleted(familyName);
                list = deleteNode(list, toBeDeleted);
            }
            else
            {
                familyNameNotFound(familyName);
            }
        }
        else if (response == 'S')
        {
            // Search for a player by family name.

            printf("\nEnter family name to search for: ");
            char familyName[1023] = {0};
            fgets(familyName, 1023, stdin);

            /* removes new line */
            familyName[strlen(familyName) - 1] = '\0';

            Player *playerFound = findNode(list, familyName);

            if (playerFound == NULL)
            {
                familyNameNotFound(familyName);
            }
            else
            {
                familyNameFound(playerFound->familyName); // PP
                printf("\n");
                printPlayer(playerFound);
            }
        }
        else if (response == 'V')
        {
            // Search for players that are worth less than or equal a value.

            printf("\nEnter value: ");
            int value = 0;
            scanf("%d", &value);
            customPrint(list, value);

            //   ADD STATEMENT(S) HERE
        }
        else if (response == 'P')
        {
            printList(list);
        }
        else if (response == 'Q')
        {
            ; // do nothing, we'll catch this case below
        }
        else
        {
            // do this if no command matched ...
            printf("\nInvalid command.\n%s\n", commandList);
        }
    } while (response != 'Q');

    // Delete the whole linked list that hold the team.
    //   ADD STATEMENT(S) HERE

    clearList(list);
    printTeamEmpty();

    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE

    return 0;
}

//**********************************************************************
// Support Function Definitions

// Function to get a line of input without overflowing target char array.
void safegets(char s[], int arraySize)
{
    int i = 0, maxIndex = arraySize - 1;
    char c;
    while (i < maxIndex && (c = getchar()) != NEWLINE)
    {
        s[i] = c;
        i = i + 1;
    }
    s[i] = NULL_CHAR;
}

// Function to call when user is trying to insert a family name
// that is already in the book.
void familyNameDuplicate(char familyName[])
{
    printf("\nAn entry for <%s> is already in the team!\n"
           "New entry not entered.\n",
           familyName);
}

// Function to call when a player with this family name was found in the team.
void familyNameFound(char familyName[])
{
    printf("\nThe player with family name <%s> was found in the team.\n",
           familyName);
}

// Function to call when a player with this family name was not found in the team.
void familyNameNotFound(char familyName[])
{
    printf("\nThe player with family name <%s> is not in the team.\n",
           familyName);
}

// Function to call when a family name that is to be deleted
// was found in the team.
void familyNameDeleted(char familyName[])
{
    printf("\nDeleting player with family name <%s> from the team.\n",
           familyName);
}

// Function to call when printing an empty team.
void printTeamEmpty(void)
{
    printf("\nThe team is empty.\n");
}

// Function to call to print title when whole team being printed.
void printTeamTitle(void)
{
    printf("\nMy Team: \n");
    printf("\n");
}

// Function to call when no player in the team has lower or equal value to the given value
void printNoPlayersWithLowerValue(int value)
{
    printf("\nNo player(s) in the team is worth less than or equal to <%d>.\n", value);
}

//**********************************************************************
// Add your functions below this line.

/*
* This function gets the user input and calls a node creation function
* returns the malloced node
*/
Player *getInput()
{
    char playerName[1023] = {0};
    char familyName[1023] = {0};
    char position;
    int value;

    /*get family name*/
    printf("family name: ");
    fgets(familyName, 1023, stdin);

    /*get first name*/
    printf("first name: ");
    fgets(playerName, 1023, stdin);

    /*get player position */

    int loop = 1;

    while (loop == 1)
    {
        printf("Player position: ");
        //printf("\n");
        scanf("%c", &position);
        position = toupper(position);

        if (position == 'G' || position == 'D' || position == 'M' || position == 'S')
        {
            break;
        }
        else
        {
            printf("Incorrect option entered\n");
        }
    }

    /* get player value */
    printf("Enter player position (Enter numerical values only): ");
    scanf("%d", &value);
    /* removes new line */
    playerName[strlen(playerName) - 1] = '\0';
    familyName[strlen(familyName) - 1] = '\0';

    /* create a node now */
    Player *playerCreated = createNode(playerName, familyName, position, value);
    return playerCreated;
}

/* creates a node to be inserted into the linked list */
Player *createNode(char *playerName, char *familyName, char position, int value)
{
    Player *newPlayer = malloc(sizeof(Player));
    newPlayer->firstName = malloc(sizeof(char) * strlen(playerName) + 1);
    newPlayer->familyName = malloc(sizeof(char) * strlen(familyName) + 1);

    strcpy(newPlayer->firstName, playerName);
    strcpy(newPlayer->familyName, familyName);
    newPlayer->position = position;
    newPlayer->value = value;
    newPlayer->next = NULL;
    return newPlayer;
}

/* Check for duplicate before insertion
    - returns 1 if duplicate is found
    - returns 0 if no duplicate is found
*/
int isDuplicate(Player *list, Player *toBeAdded)
{
    if (list == NULL)
    {
        return 0;
    }

    Player *temp = list;
    while (temp != NULL)
    {
        if (strcmp(temp->familyName, toBeAdded->familyName) == 0)
        {
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

/* insert the value into a linked list of players */
Player *insertPlayer(Player *list, Player *toBeAdded)
{
    /* when list is empty*/
    if (list == NULL)
    {
        list = toBeAdded;
        toBeAdded->next = NULL;
        return list;
    }

    else
    {
        /* when list is not empty */
        Player *tempIterator = list;

        /* check the position of player */
        switch (toBeAdded->position)
        {
        case 'G':
            list = addGoalKeeper(list, toBeAdded);
            break;

        case 'S':
            list = addStriker(list, toBeAdded);
            break;

        case 'D':
            list = addDefender(list, toBeAdded);
            break;

        case 'M':
            list = addMidFielder(list, toBeAdded);
            break;
        }
    }

    return list;
}

void printPlayer(Player *toBePrinted)
{
    if (toBePrinted == NULL)
    {
        printf("Player does not exist! \n");
    }

    else
    {
        printf("%s\n", toBePrinted->familyName);
        printf("%s\n", toBePrinted->firstName);
        printf("%c\n", toBePrinted->position);
        printf("%d\n\n", toBePrinted->value);
    }

    return;
}

/* Print the list node by node */
void printList(Player *list)
{
    Player *temp = list;
    printTeamTitle();

    while (temp != NULL)
    {
        printf("%s\n", temp->familyName);
        printf("%s\n", temp->firstName);
        printf("%c\n", temp->position);
        printf("%d\n\n", temp->value);
        temp = temp->next;
    }
}

Player *addGoalKeeper(Player *list, Player *goalKeeper)
{
    /* check the number of goal keepers in the team */
    int count = positionCount(list, goalKeeper->position);

    if (count == 0)
    {
        list = addToFront(list, goalKeeper);
        return list;
    }
    else
    {
        /* Now loop through the list and see where the last goal keeper is and first Defender, midfielder, striker, or null*/
        Player *temp = list;
        while (temp != NULL)
        {
            if (temp->position == 'G' && (temp->next == NULL || temp->next->position == 'S' || temp->next->position == 'M' || temp->next->position == 'D'))
            {
                // printf("Adding another goal keeper here!\n");
                goalKeeper->next = temp->next;
                temp->next = goalKeeper;
                return list;
            }

            temp = temp->next;
        }
    }
}

/* Add striker to the list -- always gets added to the back */
Player *addStriker(Player *list, Player *striker)
{
    Player *temp = list;
    list = addToBack(list, striker);
    return list;
}

/* Add defender to the list */
Player *addDefender(Player *list, Player *defender)
{
    /* check the number of defenders in the team */
    int defenderCount = positionCount(list, defender->position);
    int goalCount = positionCount(list, 'G');

    if (defenderCount == 0)
    {
        if (goalCount == 0)
        {
            //add to front
            list = addToFront(list, defender);
        }
        else
        {
            //add after goal keepers -- in between null, midfielders, strikers
            Player *temp = list;

            while (temp != NULL)
            {
                if (temp->next == NULL)
                {
                    list = addToBack(list, defender);
                    return list;
                }
                else if (temp->next->position == 'M' || temp->next->position == 'S')
                {
                    defender->next = temp->next;
                    temp->next = defender;
                    return list;
                }

                temp = temp->next;
            }
        }
    }
    else
    {
        // at the end of defenders there is null
        Player *temp = list;

        while (temp != NULL)
        {
            if (temp->next == NULL)
            {
                list = addToBack(list, defender);
                return list;
            }
            else
            {
                //at the end of defenders there is not null or something else shows up
                if (temp->next->position == 'M' || temp->next->position == 'S')
                {
                    defender->next = temp->next;
                    temp->next = defender;
                    return list;
                }
            }

            temp = temp->next;
        }
    }

    return list;
}

Player *addMidFielder(Player *list, Player *midFielder)
{

    /**
     *  G, D, M, S
     *
     *
     *  case 1: when there are no midfielders and strikers only -- add to front
     *  case 2: when there are are no strikers but midfielders
     * */

    int strikerCount = positionCount(list, 'S');
    int midCount = positionCount(list, midFielder->position);
    if (midCount == 0)
    {
        if (strikerCount == 0)
        {
            list = addToBack(list, midFielder);
            return list;
        }
        else
        {

            /**
             * when the list only has one striker and one player then add the midfielder to the front.
             * */
            Player *temp = list;
            int playerCount = totalPlayers(list);

            if (playerCount == 1 && strikerCount == 1)
            {
                list = addToFront(list, midFielder);
                return list;
            }

            while (temp != NULL)
            {
                /* when I find the first striker */
                if (temp->next->position == 'S')
                {
                    //  printf("found a striker\n");
                    //  printf("current position: %c\n", temp->position);
                    midFielder->next = temp->next;
                    temp->next = midFielder;
                    return list;
                }
                temp = temp->next;
            }
        }
    }
    else
    {
        // at the end of defenders there is null
        Player *temp = list;

        while (temp != NULL)
        {
            if (temp->next == NULL)
            {
                list = addToBack(list, midFielder);
                return list;
            }
            else
            {
                //at the end of defenders there is not null or something else shows up
                if (temp->next->position == 'S')
                {
                    midFielder->next = temp->next;
                    temp->next = midFielder;
                    return list;
                }
            }

            temp = temp->next;
        }
    }

    return list;
}

/* checks how many players are present in the team based on certain position */
int positionCount(Player *list, char position)
{
    int count = 0;
    Player *temp = list;

    while (temp != NULL)
    {
        if (position == temp->position)
        {
            count++;
        }

        temp = temp->next;
    }

    return count;
}

Player *addToFront(Player *list, Player *toBeInserted)
{
    if (list != NULL)
    {
        toBeInserted->next = list;
        list = toBeInserted;
        return list;
    }

    /* when the list is empty */
    list = toBeInserted;
    toBeInserted->next = NULL;
    return list;
}

Player *addToBack(Player *list, Player *toBeInserted)
{
    if (list != NULL)
    {
        Player *temp = list;

        while (temp != NULL)
        {
            if (temp->next == NULL)
            {
                temp->next = toBeInserted;
                toBeInserted->next = NULL;
                return list;
            }

            temp = temp->next;
        }
    }

    /* when the list is empty */
    list = toBeInserted;
    toBeInserted->next = NULL;
    return list;
}

/*
    this function returns a pointer to the node that is to be deleted
    if there is no node found then it returns NULL
    toBeDeleted == family name input by the user
*/
Player *findNode(Player *list, char *toBeDeleted)
{
    if (list == NULL)
    {
        return NULL;
    }

    Player *temp = list;
    Player *nodeFound = NULL;

    while (temp != NULL)
    {
        if (strcmp(temp->familyName, toBeDeleted) == 0)
        {
            nodeFound = temp;
            return nodeFound;
        }

        temp = temp->next;
    }

    return NULL;
}

/* this function receives the given family name and deletes that node from the list*/
Player *deleteNode(Player *list, Player *toBeDeleted)
{
    if (list == NULL)
    {
        return list;
    }

    /* if the node is in the beginning */
    if (strcmp(list->familyName, toBeDeleted->familyName) == 0)
    {
        Player *temp = list->next;
        toBeDeleted->next = NULL;
        freeNode(toBeDeleted);
        list = temp;
        return list;
    }

    /* if the node found is in the middle/ end of the list */

    Player *midNode = list;

    while (midNode != NULL)
    {
        if (strcmp(midNode->next->familyName, toBeDeleted->familyName) == 0)
        {
            Player *temp = midNode->next;
            midNode->next = temp->next;
            temp->next = NULL;

            freeNode(temp);
            break;
        }

        midNode = midNode->next;
    }

    //printList(list);
    return list;
}

/* frees the node completely*/
void freeNode(Player *toBeFreed)
{
    //printf("free node is entered!\n");
    if (toBeFreed == NULL)
    {
        //printf("the node is null!\n");
        return;
    }

    free(toBeFreed->familyName);
    free(toBeFreed->firstName);
    free(toBeFreed);
    return;
}

/* print the players that are below or less that a certain value*/
void customPrint(Player *list, int value)
{
    if (list == NULL)
    {
        printNoPlayersWithLowerValue(value);
        return;
    }

    int foundPlayers = 0;

    Player *temp = list;
    while (temp != NULL)
    {
        if (temp->value <= value)
        {
            foundPlayers = 1;
            printf("\n");
            printf("%s\n", temp->familyName);
            printf("%s\n", temp->firstName);
            printf("%c\n", temp->position);
            printf("%d\n\n", temp->value);
        }
        temp = temp->next;
    }

    if (foundPlayers == 0)
    {
        printNoPlayersWithLowerValue(value);
    }

    return;
}

void clearList(Player *list)
{
    if (list == NULL)
    {
        return;
    }

    Player *current = list;
    Player *next;

    while (current != NULL)
    {
        next = current->next;
        freeNode(current);
        current = next;
    }

    list = NULL;
    return;
}

int totalPlayers(Player *list)
{
    Player *temp = list;
    int playerCount = 0;

    while (temp != NULL)
    {
        playerCount++;
        temp = temp->next;
    }

    return playerCount;
}
