// If you are not compiling with the gcc option --std=gnu99, then
// uncomment the following line or you might get a compiler warning
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <z3.h>

#define ROW 3
#define COL 10
//creating first change for github, otherwise this is the working copy

//this is working now?

//creating a different branch that will be used to do things like write the program

/* struct for movie information */

struct movie {
//    so basically, the struct is why it's a pointer, that's what gets passed around, but stuff inside the struct
// doesn't need to be pointerized, can just be regular values.
    char *title;
    int year;
    char languages[3][11];
    double rating;
    struct movie *next;
};

void strCopy(struct movie *node_1, struct movie *node_2) {
    for (int i = 0; i <= 2; i++) {
        strcpy(node_1->languages[i], node_2->languages[i]);
    }
}

void my_swap(struct movie *node_1, struct movie *node_2) {
    struct movie *t_movie;
    t_movie = node_1;
    node_1 = node_2;
    node_2 = t_movie;
//    char *t_title = node_1->title;
//    int t_year = node_1->year;
//    char t_languages[3][11];
//
//    double t_rating = node_1->rating;
//    node_1->title = node_2->title;
//    node_1->year = node_2->year;
//    for (int i = 0; i <= 2; i++) {
//        strcpy(node_1->languages[i], node_2->languages[i]);
//    }
//    node_1->languages  =  node_2->languages;

//    node_1->rating = node_2->rating;
//    node_2->title = t_title;
//    node_2->year = t_year;
//    for (int i = 0; i < 2; i++) {
//        strcpy(node_2->languages[i], t_languages[i]);
//    }
//    node_2->rating = t_rating;
}


void bubble_sort(struct movie *list) {
    int swapped;
// so that just means you're declaring what will be a movie struct, pointer of memory.
    struct movie *lptr;
    struct movie *rpt = NULL;
    do {
        swapped = 0;
        lptr = list;
        while (lptr->next != rpt) {
            if (lptr->year < lptr->next->year) {
                my_swap(lptr, lptr->next);
                swapped = 1;
            }
            lptr = lptr->next;

        }
        rpt = lptr;
    } while (swapped);

}


/* Parse the current line which is space delimited and create a
*  movie struct with the data in this line
*/
struct movie *createmovie(char *currLine) {
    struct movie *pMovie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char *saveptr;

    // The first token is the Title
    char *token = strtok_r(currLine, ",", &saveptr); // make a char pointer, basically get the item that it's on
    pMovie->title = calloc(strlen(token) + 1,
                           sizeof(char)); // pmovie points to title, which is the length of token, get the string
    strcpy(pMovie->title, token); //
    // The next token is the year
    token = strtok_r(NULL, ",", &saveptr);
    int integer = atoi(token);
//    pMovie->year = calloc(integer, sizeof(int));
    pMovie->year = integer;

    // The next token is the languages
    token = strtok_r(NULL, ",", &saveptr);

    char *delim = ";";
    char *string = token;
    int i=0;
    int j=0;
    char temp[40];
    for(i=1;i<strlen(string)-1;i++){
        temp[j++]=string[i];
    }
    strcpy(string,temp);
    int count = 0;
    char *ptr = strtok(string, delim);
    while (ptr != NULL) {
        strcpy(pMovie->languages[count], ptr);
        count++;
        ptr = strtok(NULL, delim);
    }
//    pMovie->languages = calloc(strlen(token) + 1, sizeof(char));
//    strcpy(pMovie->languages, token);

    // The last token is the rating
    token = strtok_r(NULL, "\r\n", &saveptr);
    char *ptr2;
    double floatValue = strtod(token, &ptr2);
    pMovie->rating = floatValue;

    // Set the next node to NULL in the newly created movie entry
    pMovie->next = NULL;

    return pMovie;
}

/*
* Return a linked list of movies by parsing data from
* each line of the specified file.
*/
struct movie *processFile(char *filePath) {
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
    while ((nread = getline(&currLine, &len, movieFile)) != -1) {
        // Get a new movie node corresponding to the current line
        struct movie *newNode = createmovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL) {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        } else {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    free(currLine);
    fclose(movieFile);
    bubble_sort(head);
    return head;
}


/*
* Print data for the given movie
*/

void printmovie(struct movie *amovie) {
    while (amovie != NULL) {
        printf("%s, %s, %d, %f\n", amovie->title,
               amovie->languages,
               amovie->year,
               amovie->rating);
        amovie = amovie->next;
    }

}

/*
* Print the linked list of movies
*/

void choice_one(struct movie *list, int year) {
    while (list != NULL) {
        if (list->year == year) {
            do printf("%s", list->title);
            while (list->year == year);
            return;
        }
        list = list->next;
    }
}

void loopMovieList(struct movie *list, void (*f)(struct movie *list)) {
    while (list != NULL) {
        (*f)(list);
        list = list->next;
    }
}

void secondChoice(struct movie *list) {
    while (1) {
//        grab first items to compare against
        char *title = list->title;
        int year = list->year;
        double rating = list->rating;
//        go to next item

        list = list->next;
//        while in this year
        while (year == list->year) {
//            if greater than the current rating
            if (rating < list->rating) {
//                that becomes the new rating
                rating = list->rating;
                title = list->title;
            }
//            go to next item
            if (list->next == NULL) {
                return;
            }
            list = list->next;
        }
//        at the end, print top movie
        printf("%s, %u %f, \n", title,
               year,
               rating);
    }
}

int printQuestion(void) {

    printf("1. Show movies released in the specified year\n"
           "2. Show highest rated movie for each year\n"
           "3. Show the title and year of release of all movies in a specific language\n"
           "4. Exit from the program\n"
           "\n");
    int num;
    do {
        printf("Enter a choice from 1 to 4: ");
        scanf("%d", &num);
    } while ((1 > num) || (num > 4));

    return num;

}

/*
*   Process the file provided as an argument to the program to
*   create a linked list of movie structs and print out the list.
*   Compile the program as follows:
*       gcc --std=gnu99 -o movies main.c
*/

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movie_info1.txt\n");
        return EXIT_FAILURE;
    }
////    here it looks like you just need to put the file name and the other thing and it'll work
    struct movie *list = processFile(argv[1]);
    printmovie(list);

    while (true) {
        printf("1. Show movies released in the specified year\n"
               "2. Show highest rated movie for each year\n"
               "3. Show the title and year of release of all movies in a specific language\n"
               "4. Exit from the program\n"
               "\n");
        int num;
        printf("Enter a choice from 1 to 4: ");
        scanf("%d", &num);
        while ((1 > num) || (num > 4)) {
            printf("Please enter a valid number");
            scanf("%d", &num);
        }
        if (num == 1) {
            printf("Enter the year for which you want to see movies:");
            scanf("%d", &num);
            choice_one(list, num);
        }
        if (num == 4) {
            return EXIT_SUCCESS;
        }
        if (num == 2) {
            secondChoice(list);
        }
    }
    return EXIT_SUCCESS;
}

