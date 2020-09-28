// If you are not compiling with the gcc option --std=gnu99, then
// uncomment the following line or you might get a compiler warning
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//creating first change for github, otherwise this is the working copy

//this is working now?

//creating a different branch that will be used to do things like write the program

/* struct for movie information */

struct movie
{
    char *title;
    int *year;
    char *languages;
    int *rating;
    struct movie *next;
};

/* Parse the current line which is space delimited and create a
*  movie struct with the data in this line
*/
struct movie *createmovie(char *currLine)
{
    struct movie *pMovie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char *saveptr;

    // The first token is the ONID
    char *token = strtok_r(currLine, ",", &saveptr); // make a char pointer, basically get the item that it's on
    pMovie->title = calloc(strlen(token) + 1, sizeof(char)); // pmovie points to title, which is the length of token, get the string
    strcpy(pMovie->title, token); //

    // The next token is the year
    token = strtok_r(NULL, ",", &saveptr);
    pMovie->year = calloc(strlen(token) + 1, sizeof(char));
    strcpy(pMovie->year, token);

    // The next token is the firstName
    token = strtok_r(NULL, ",", &saveptr);
    pMovie->languages = calloc(strlen(token) + 1, sizeof(char));
    strcpy(pMovie->languages, token);

    // The last token is the rating
    token = strtok_r(NULL, "\r\n", &saveptr);
    pMovie->rating = calloc(strlen(token) + 1, sizeof(int));
    strcpy(pMovie->rating, token);

    // Set the next node to NULL in the newly created movie entry
    pMovie->next = NULL;

    return pMovie;
}

/*
* Return a linked list of movies by parsing data from
* each line of the specified file.
*/
struct movie *processFile(char *filePath)
{
    // Open the specified file for reading only
    FILE *movieFile = fopen(filePath, "r");

    char *currLine = NULL;
    size_t len = 0;
    ssize_t nread;
    char *token;

    // The head of the linked list
    struct movie *head = NULL;
    // The tail of the linked list
    struct movie *tail = NULL;

    nread = getline(&currLine, &len, movieFile);

    // Read the file line by line
    while ((nread = getline(&currLine, &len, movieFile)) != -1)
    {
        // Get a new movie node corresponding to the current line
        struct movie *newNode = createmovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    free(currLine);
    fclose(movieFile);
    return head;
}

/*
* Print data for the given movie
*/
void printmovie(struct movie* amovie){
    printf("%s, %s %s, %s\n", amovie->title,
           amovie->languages,
           amovie->year,
           amovie->rating);
}
/*
* Print the linked list of movies
*/
void printmovieList(struct movie *list)
{
    while (list != NULL)
    {
        printmovie(list);
        list = list->next;
    }
}

/*
*   Process the file provided as an argument to the program to
*   create a linked list of movie structs and print out the list.
*   Compile the program as follows:
*       gcc --std=gnu99 -o movies main.c
*/

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movie_info1.txt\n");
        return EXIT_FAILURE;
    }
////    here it looks like you just need to put the file name and the other thing and it'll work
    struct movie *list = processFile(argv[1]);
    printmovieList(list);
    return EXIT_SUCCESS;
}

