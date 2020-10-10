// If you are not compiling with the gcc option --std=gnu99, then
// uncomment the following line or you might get a compiler warning
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <z3.h>

#define ROW 3
#define COL 10
#define BUFFER 11
//creating first change for github, otherwise this is the working copy

//this is working now?

//creating a different branch that will be used to do things like write the program

/* struct for movie information */

struct movie {
//    so basically, the struct is why it's a pointer, that's what gets passed around, but stuff inside the struct
// doesn't need to be pointerized, can just be regular values.
    char *title;
    int year;
    char languages[4][12];
    double rating;
    struct movie *next;
};

void strCopy(struct movie *node_1, struct movie *node_2) {

    for (int i = 0; i <= 2; i++) {
        memset(node_1->languages[i], 0, BUFFER);
        strcpy(node_1->languages[i], node_2->languages[i]);
    }
}


void list_bubble_sort(struct movie **list) {
    int done = 0;         // True if no swaps were made in a pass

    // Don't try to sort empty or single-node lists
    if (*list == NULL || (*list)->next == NULL) return;

    while (!done) {
        struct movie **pv = list;            // "source" of the pointer to the
        // current node in the list struct
        struct movie *nd = *list;            // local iterator pointer
        struct movie *nx = (*list)->next;  // local next pointer

        done = 1;

        while (nx) {

            if (nd->year > nx->year) {
                nd->next = nx->next;
                nx->next = nd;
                *pv = nx;

                done = 0;
            }
            pv = &nd->next;
            nd = nx;
            nx = nx->next;
        }
    }
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
    int i = 0;
    char temp[40];
    int k = 0;
    while (string[k] != NULL) {
        if (string[k] != 93) {
            if (string[k] != 91) {
                // i only moves up for temp if there's something to write
                temp[i] = string[k];
                i++;
            }
        }

        k++;
    }
//    strcpy(string,temp);
    int count = 0;
    char *ptr = strtok(temp, delim);
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
    printf("Test\n");
    list_bubble_sort(&head);
    printf("Test\n");
    return head;
}


/*
* Print data for the given movie
*/

void printmovie(struct movie *amovie) {
    while (amovie != NULL) {
        printf("%s, %s, %s, %s, %d, %f\n", amovie->title,
               amovie->languages[0],
               amovie->languages[1],
               amovie->languages[2],
               amovie->year,
               amovie->rating);
        amovie = amovie->next;
    }

}

/*
* Print the linked list of movies
*/

void choice_one(struct movie *list, int year) {
    int found = 0;
    while (list != NULL) {
        if (list->year == year) {
            do {
                found = 1;
                printf("%s\n", list->title);
                list = list->next;
            } while (list->year == year);
            return;
        }
        list = list->next;
    }
    if (!found) {
        printf("No movies were made in this year\n");
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

void choiceThree(struct movie *list, char *lang) {
    int found = 0;
    while (list != NULL) {
        for (int i = 0; i < 4; i++) {
            if(strcmp(list->languages[i], lang) == 0) {
                found = 1;
                printf("%i %s\n", list->year, list->title);
            };
        }
        list = list->next;
    }
    if (!found) {
        printf("No movies were found with this language\n");
    }
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movie_info1.txt\n");
        return EXIT_FAILURE;
    }

    struct movie *list = processFile(argv[1]);

// I need to understand pointers, references, dereferences, and everything of that nature,
// Literally as soon as I can because that will save me a looooot of trouble.

// I currently don't understand how to use this language, and it is giving me trouble.
// I must learn about how to use pointers, if I am going to survive this class.
// I can't just put a pointer or dereference sign and think "maybe it will work this time",
// That is not going to be an option. I will learn what they all mean, and understand when
// and how to use them all. and that will make these next 3 months a whole lot easier on me.


    while (1) {
        printf("1. Show movies released in the specified year\n"
               "2. Show highest rated movie for each year\n"
               "3. Show the title and year of release of all movies in a specific language\n"
               "4. Exit from the program\n"
               "\n");
        int num;
        printf("Enter a choice from 1 to 4: \n");
        scanf("%d", &num);
        while ((1 > num) || (num > 4)) {
            printf("Please enter a valid number\n");
            scanf("%d", &num);
        }
        if (num == 1) {
            printf("Enter the year for which you want to see movies:\n");
            scanf("%d", &num);
            choice_one(list, num);
        }
        if (num == 4) {
            return EXIT_SUCCESS;
        }
        if (num == 2) {

            secondChoice(list);
        }
        if (num == 3) {
            char *lang;
            printf("Enter the language for the movies you want to see:\n");
            scanf("%s", lang);
            choiceThree(list, lang);
        }
    }
    return EXIT_SUCCESS;
}

