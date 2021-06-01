#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <conio2.h>
#include "menu_box.h"

#define NAME_SIZE 50     // max number of chars in the string (49 + the \0 )
#define VECTOR_SIZE 200  // max number of cinemas, movies, actors and genres we can save in the memory
#define WIDTH 32
#define HEIGHT 13

// Cinema Management program in C by Nikolaos Perris (#36261)
// Version 0.99c (01/02/2018)
// for Introduction to Algorithms and Programming
// Universidade Fernando Pessoa

//Structure for cinemas
struct cinema {
    int c_index;                            // Automatically generated index
    char c_name[NAME_SIZE];                 // Name of the cinema
    int movies_num;                         // Number of movies associated to each cinema
    char movies[VECTOR_SIZE][NAME_SIZE];    // Movies associated to the cinema
};

//Structure for movies
struct movie {
    int m_index;                // Automatically generated index
    char m_title[NAME_SIZE];    // Title of the movie
    char director[NAME_SIZE];   // Director of the movie
    char genre[NAME_SIZE];      // Genre of the movie
    char duration[4];           // Duration of the movie
    char min_age[4];            // Minimum age requirement of the movie
    int actors_num;             // Number of actors associated to the movie
    char actors[VECTOR_SIZE][NAME_SIZE]; // Actors associated to the movie
};

//Structure for actors
struct actor {
    int a_index;                // Automatically generated index
    char a_name[NAME_SIZE];     // Name of the actor
    char a_age[4];              // Age of the actor
};

//The functions used
void menu_title(int w); // The top part of the menus with name/version
void user_menu(void); // User sub-menu
void admin_menu(void); // Administrator sub-menu
void cinemas_menu(void); // The cinemas sub-menu
void movies_menu(void); // The movies sub-menu
void actors_menu(void); // The actors sub-menu
void genres_menu(void); // The genres sub-menu
void assocs_menu(void); // The associations sub-menu
void admin_pass(void); // Asks for administrator password, if correct it calls the admin menu, else displays error message.
void change_pass(void); // Changes the default admin password, it asks twice, for confirmation
void save_pass(void); // Saves admin password to file topsecret.dat
void load_pass(void); // Loads admin password from file topsecret.dat
void create_cinema(struct cinema * m); // Creates a new cinema
void edit_cinema(struct cinema * m);  // Edit an existing cinema that the user selects
void delete_cinema(struct cinema * m); // Deletes a cinema
void list_cinemas(void); // List of the cinemas
void list_movies_of_cinema(void); // Prompts the user to select a cinema and displays the movies played in it
void list_cinemas_of_movie(void); // Prompts the user to select a movie and displays the cinemas the movie is available in
void list_movies_by_genre(void); // Lists the movie genres, prompts the user to select a genre, then lists the movies of that genre and the cinemas they are available in
void associate_movies_and_cinemas(); // Associates movies to cinemas
void save_cinemas_to_file(void); // Saves to txt file with the movies associated to each cinema
void load_cinemas_from_file(void); // Checks the number of cinemas in the memory, if zero, it calls the load function, if >0 it asks for confirmation
void load_cinemas_from_file2(void); // Loads from txt file the movies previously associated to each cinema
void create_movie(struct movie * m); // Create new movie record
void edit_movie(struct movie * m); // Edit an existing movie that the user selects
void delete_movie(struct movie * m); // Delete a movie that the user selects
void associate_actors_and_movies(void); // Prompts the user to select a movie, then the number of actors he wants to associate.
void list_movies(void); // List of the movies with title only
void print_movie(struct movie * m); // Prints the title of the movie
void list_full_movies_info(void); // List of the movies with all info, including the actors
void print_full_movie_info(struct movie * m); // Prints all the info of the movie
void save_movies_to_file(void); // Save movies to txt file movies.txt
void load_movies_from_file(void); // Checks the number of movies in the memory, if zero, it calls the load function, if >0 it asks for confirmation
void load_movies_from_file2(void); // Load movies from txt file movies.txt
void create_actor(struct actor * m); // Create a new actor record
void edit_actor(struct actor * m); // Edit an existing actor that the user selects
void delete_actor(struct actor * m); // Deletes an actor that the user selects
void list_actors(void); // List of the actors
void print_actor(struct actor * m); // Prints index and actor
void list_full_actors_info(void); // List of actors with all info
void list_movies_of_actor(void); // Lists the movies of the selected actor
void save_actors_to_file(void); // Save actors to txt file actors.txt
void load_actors_from_file(void); // Checks the number of actors in the memory, if zero, it calls the load function, if >0 it asks for confirmation
void load_actors_from_file2(void); //Load actors from txt file actors.txt
void create_genre(void); // Creates a new movie genre
void edit_genre(void); // Lists all movie genres and prompts user to select which one to edit, then it scans the new input and saves it
void delete_genre(void); // Lists all movie genres and prompts user to select which one to delete, then it moves the array elements after the selection, one position to the left, deleting the selection
void list_genres(void); // Lists all the movie genres
void save_genres_to_file(void); // Saves movies genres to txt file genres.txt
void load_genres_from_file(void); // Checks the number of genres in the memory, if zero, it calls the load function, if >0 it asks for confirmation
void load_genres_from_file2(void); // Loads movie genres from txt file genres.txt
void save_db(void); // Saves the database of all data, if they are not empty. If empty it does not save, to avoid overwriting existing files.
void invalid_selection(void); // Displays a message that an invalid selection was made
void pressanykey(void);   // Displays message to press any key to continue
void no_cinemas(void); //Prints a message that there are no cinemas
void no_movies(void); //Prints a message that there are no movies
void no_actors(void); //Prints a message that there are no actors
void no_genres(void); //Prints a message that there are no actors
void no_changes(void); // Displays message that no changes were made
void edit_movies_cinemas_assocs(void); // Edit the association of a movie to a cinema
void delete_movies_cinemas_assocs(void); // Delete the association of a movie to a cinema
void edit_movies_actors_assocs(void);  // Edit the association of an actor to a movie
void delete_movies_actors_assocs(void); // Delete the association of an actor to a movie

// Global variables
struct cinema vec_cinemas[VECTOR_SIZE];
struct movie vec_movies[VECTOR_SIZE];
struct actor vec_actors[VECTOR_SIZE];
char genres[VECTOR_SIZE][NAME_SIZE];        // array to store the genres
int num_cinemas=0;
int num_movies=0;
int num_actors=0;
int num_genres=0;
char cinemas_file[]="cinemas.txt"; // Name of the file where the info about the cinemas are saved.
char movies_file[]="movies.txt"; // Name of the file where the info about the movies are saved.
char actors_file[]="actors.txt"; // Name of the file where the info about the actors are saved.
char genres_file[]="genres.txt"; // Name of the file where the info about the movie genres are saved.
char def_pw[20]="admin";  // Default admin password. It's not used if a password file is found.
char pwfile[]="topsecret.dat";  // Name of the file where the admin password is saved, after it is changed from the default

int main(int argc, char const *argv[])
{
    load_pass();  // Loads the admin password from file when program starts
    char op;
    do {
        menu_title(WIDTH);
        menu_box(HEIGHT,WIDTH);
        gotoxy(19,9); printf("[1] User menu");
        gotoxy(19,10);printf("[2] Administrator menu");
        gotoxy(19,16);printf("[8] Load databases");
        gotoxy(19,19);printf("[Q] Quit program");
        fflush(stdin);
        printf("\n\n\n\t\tSelect an option:");
        op=getch();
        switch (op) {
            case '1':
                user_menu();
                break;
            case '2':
                admin_pass();
                break;
            case '8':   // Load cinemas, movies, actors and genres from their txt files
                load_cinemas_from_file();
                load_movies_from_file();
                load_actors_from_file();
                load_genres_from_file();
                pressanykey();
                break;
            case 'q':
            case 'Q':
                break;
            default:
                invalid_selection();
        }
    }  while (op!='q' && op!='Q');
    return 0;
}

void menu_title(int w) // The top part of the menus with name/version
{
    system("cls");
    printf("\t\t%c",201);
    for (int a=0;a<w;a++) printf("%c",205);
    printf("%c",187);
    printf("\n\t\t%c    Cinema Management  v0.99c   %c\n",186,186);
    printf("\t\t%c",204);
    for (int a=0;a<w;a++) printf("%c",205);
    printf("%c",185);
    printf("\n\t\t%c    (c) 2018 Nikolaos Perris    %c\n",186,186);
    printf("\t\t%c",200);
    for (int a=0;a<w;a++) printf("%c",205);
    printf("%c\n\n",188);
}

void user_menu(void) // User sub-menu
{
    char op;
    do {
        menu_title(WIDTH);
        menu_box(HEIGHT,WIDTH);
        gotoxy(19,9); printf("[1] List cinemas");               // Lists all cinemas
        gotoxy(19,10);printf("[2] List movies");                // Lists all movies
        gotoxy(19,11);printf("[3] List movies of a cinema");    // Lists movies of a cinema
        gotoxy(19,12);printf("[4] List cinemas for a movie");   // Lists cinemas for a movie
        gotoxy(19,13);printf("[5] List movies of a genre");     // Lists movies of a genre
        gotoxy(19,14);printf("[6] List movies' full movie");    // List all movies with detailed info
        gotoxy(19,15);printf("[7] List actors");                // Lists all actors
        gotoxy(19,16);printf("[8] List movies of an actor");    // Lists the movies of an actor
        gotoxy(19,17);printf("[9] List actors' full info");     // Lists all actors with detailed info
        gotoxy(19,19);printf("[R] Return to user selection");
        fflush(stdin);
        printf("\n\n\n\t\tSelect an option:");
        op=getch();
        switch (op) {
            case '1':
                if (num_cinemas==0) no_cinemas();
                else list_cinemas();
                pressanykey();
                break;
            case '2':
                if (num_movies==0) no_movies();
                else list_movies();
                pressanykey();
                break;
            case '3':
                if (num_movies==0) no_movies();
                else if (num_cinemas==0) no_cinemas();
                else list_movies_of_cinema();
                pressanykey();
                break;
            case '4':
                if (num_movies==0) no_movies();
                else if (num_cinemas==0) no_cinemas();
                else list_cinemas_of_movie();
                pressanykey();
                break;
            case '5':
                if (num_movies==0) no_movies();
                else if (num_genres==0) no_genres();
                else list_movies_by_genre();
                pressanykey();
                break;
            case '6':
                if (num_movies==0) no_movies();
                else list_full_movies_info();
                pressanykey();
                break;
            case '7':
                if (num_actors==0) no_actors();
                else list_actors();
                pressanykey();
                break;
            case '8':
                if (num_movies==0) no_movies();
                else if (num_actors==0) no_actors();
                else list_movies_of_actor();
                pressanykey();
                break;
            case '9':
                if (num_actors==0) no_actors();
                else list_full_actors_info();
                pressanykey();
                break;
            case 'r':
            case 'R':
                break;
            default:
                invalid_selection();
                pressanykey();
        }
    }  while (op!='r' && op!='R');
}

void admin_menu(void) // Administrator sub-menu
{
    char op;
    do {
        menu_title(WIDTH);
        menu_box(HEIGHT,WIDTH);
        gotoxy(19,9); printf("[1] Manage cinemas");             // Displays cinema sub-menu
        gotoxy(19,10);printf("[2] Manage movies");              // Displays movies sub-menu
        gotoxy(19,11);printf("[3] Manage actors");              // Displays actors sub-menu
        gotoxy(19,12);printf("[4] Manage movie genres");        // Displays genres sub-menu
        gotoxy(19,13);printf("[5] Manage associations");        // Displays associations sub-menu
        gotoxy(19,16);printf("[8] Load databases");             // Loads databases of cinemas,movies,actors,genres
        gotoxy(19,17);printf("[9] Save databases ");            // Saves databases of cinemas,movies,actors,genres
        gotoxy(19,18);printf("[0] Change password");            // Changes administrator password
        gotoxy(19,19);printf("[R] Return to user selection");
        fflush(stdin);
        printf("\n\n\n\t\tSelect an option:");
        op=getch();
        switch (op) {
            case '1':
                cinemas_menu(); // Displays cinema sub-menu
                break;
            case '2':
                movies_menu();  // Displays movies sub-menu
                break;
            case '3':
                actors_menu();  // Displays actors sub-menu
                break;
            case '4':
                genres_menu();  // Displays genres sub-menu
                break;
            case '5':
                assocs_menu();  // Displays associations sub-menu
                break;
            case '8':           // Loads databases of cinemas,movies,actors,genres
                load_cinemas_from_file();
                load_movies_from_file();
                load_actors_from_file();
                load_genres_from_file();
                pressanykey();
                break;
            case '9':           // Calls the save database function
                save_db();
                break;
            case '0':
                change_pass();  // Allows the admin to change the admin password
                break;
            case 'r':
            case 'R':
                break;
            default:
                invalid_selection();
                pressanykey();
        }
    }  while (op!='r' && op!='R');
}

void cinemas_menu(void)  // Cinemas sub-menu
{
    char op;
    do {
        menu_title(WIDTH);
        menu_box(HEIGHT,WIDTH);
        gotoxy(19,9); printf("[1] New cinema");             // Create a new cinema
        gotoxy(19,10);printf("[2] Edit cinema");               // Edit a cinema
        gotoxy(19,11);printf("[3] Delete cinema");             // Delete a cinema
        gotoxy(19,12);printf("[4] List cinemas");              // Lists all the cinemas
        gotoxy(19,13);printf("[5] List movies of a cinema");   // Lists all movies of one cinema
        gotoxy(19,14);printf("[6] List cinemas for a movie");  // Lists the cinemas a movie is played in
        gotoxy(19,15);printf("[7] Associate cinemas/movies");  // Associates movies and cinemas
        gotoxy(19,16);printf("[8] Load cinemas data");         // Loads cinemas data from cinemas.txt
        gotoxy(19,17);printf("[9] Save cinemas data");         // Saves cinemas data to cinemas.txt
        gotoxy(19,19);printf("[R] Return to menu");
        fflush(stdin);
        printf("\n\n\n\t\tSelect an option:");
        op=getch();
        switch (op) {
            case '1':
                create_cinema(&vec_cinemas[num_cinemas]);
                pressanykey();
                break;
            case '2':
                if (num_cinemas==0) no_cinemas();            // if number of cinemas is 0, display error message, else call the edit function
                else edit_cinema(&vec_cinemas[num_cinemas]);
                pressanykey();
                break;
            case '3':
                if (num_cinemas==0) no_cinemas();            // if number of cinemas is 0, display error message, else call the delete function
                else delete_cinema(&vec_cinemas[num_cinemas]);
                pressanykey();
                break;
            case '4':
                if (num_cinemas==0) no_cinemas();
                else list_cinemas();
                pressanykey();
                break;
            case '5':
                if (num_movies==0) no_movies();
                else if (num_cinemas==0) no_cinemas();
                else list_movies_of_cinema();
                pressanykey();
                break;
            case '6':
                if (num_movies==0) no_movies();
                else if (num_cinemas==0) no_cinemas();
                else list_cinemas_of_movie();
                pressanykey();
                break;
            case '7':
                if (num_movies==0) no_movies();
                else if (num_cinemas==0) no_cinemas();
                else associate_movies_and_cinemas();
                pressanykey();
                break;
            case '8':
                load_cinemas_from_file();
                pressanykey();
                break;
            case '9':
                if (num_cinemas==0) no_cinemas();
                else save_cinemas_to_file();
                pressanykey();
                break;
            case 'r':
            case 'R':
                break;
            default:
                invalid_selection();
                pressanykey();
        }
    }  while (op!='r' && op!='R');
}

void movies_menu(void)      // Movies sub-menu
{
    char op;
    do {
        menu_title(WIDTH);
        menu_box(HEIGHT,WIDTH);
        gotoxy(19,9); printf("[1] New movie");                  // Creates new movie
        gotoxy(19,10);printf("[2] Edit movie");                 // Edits existing movie
        gotoxy(19,11);printf("[3] Delete movie");               // Deletes existing movie
        gotoxy(19,12);printf("[4] Associate movies/actors");    // Associates movies and actors
        gotoxy(19,13);printf("[5] Associate movies/cinemas");   // Associates movies and cinemas
        gotoxy(19,14);printf("[6] List movies");                // Lists all movies
        gotoxy(19,15);printf("[7] List movies with info");      // Lists the movies with detailed info
        gotoxy(19,16);printf("[8] Load movies data");           // Loads movies data from movies.txt
        gotoxy(19,17);printf("[9] Save movies data");           // Saves movies data to movies.txt
        gotoxy(19,19);printf("[R] Return to menu");
        fflush(stdin);
        printf("\n\n\n\t\tSelect an option:");
        op=getch();
        switch (op) {
            case '1':
                create_movie(&vec_movies[num_movies]);
                pressanykey();
                break;
            case '2':
                if (num_movies==0) no_movies();            // if number of movies is 0, display error message, else call the edit function
                else edit_movie(&vec_movies[num_movies]);
                pressanykey();
                break;
            case '3':
                if (num_movies==0) no_movies();            // if number of movies is 0, display error message, else call the delete function
                else delete_movie(&vec_movies[num_movies]);
                pressanykey();
                break;
            case '4':
                if (num_actors==0) no_actors();
                else if (num_movies==0) no_movies();
                else associate_actors_and_movies();
                pressanykey();
                break;
            case '5':
                if (num_movies==0) no_movies();
                else if (num_cinemas==0) no_cinemas();
                else associate_movies_and_cinemas();
                pressanykey();
                break;
            case '6':
                if (num_movies==0) no_movies();            // if number of movies is 0, display error message, else call the list function
                else list_movies();
                pressanykey();
                break;
            case '7':
                if (num_movies==0) no_movies();            // if number of movies is 0, display error message, else call the list full info function
                else list_full_movies_info();
                pressanykey();
                break;
            case '8':
                load_movies_from_file();            // Load movies from text file
                pressanykey();
                break;
            case '9':
                if (num_movies==0) no_movies();            // if number of movies is 0, display error message, else call the save function
                else save_movies_to_file();
                pressanykey();
                break;
            case 'r':
            case 'R':
                break;
            default:
                invalid_selection();
                pressanykey();
        }
    }  while (op!='r' && op!='R');
}

void actors_menu(void)      // Actors sub-menu
{
    char op;
    do {
        menu_title(WIDTH);
        menu_box(HEIGHT,WIDTH);
        gotoxy(19,9); printf("[1] New actor");                  // Creates new actor
        gotoxy(19,10);printf("[2] Edit actor");                 // Edits existing actor
        gotoxy(19,11);printf("[3] Delete actor");               // Deletes existing actor
        gotoxy(19,12);printf("[4] Associate actors/movies");    // Associates three actors to a movie
        gotoxy(19,13);printf("[5] List actors");                // Lists all the actors
        gotoxy(19,14);printf("[6] List actors with info");      // Lists all the actors with their extra info
        gotoxy(19,15);printf("[7] List movies of an actor");    // Lists the movies of one actor
        gotoxy(19,16);printf("[8] Load actors data");           // Loads actors data from actors.txt
        gotoxy(19,17);printf("[9] Save actors data");           // Saves all actors data to actors.txt
        gotoxy(19,19);printf("[R] Return to menu");
        fflush(stdin);
        printf("\n\n\n\t\tSelect an option:");
        op=getch();
        switch (op) {
            case '1':
                create_actor(&vec_actors[num_actors]);
                pressanykey();
                break;
            case '2':
                if (num_actors==0) no_actors();             // if number of actors is 0, display error message, else call the edit function
                else edit_actor(&vec_actors[num_actors]);
                pressanykey();
                break;
            case '3':
                if (num_actors==0) no_actors();             // if number of actors is 0, display error message, else call the edit function
                else delete_actor(&vec_actors[num_actors]);
                pressanykey();
                break;
            case '4':
                if (num_actors==0) no_actors();
                else if (num_movies==0) no_movies();
                else associate_actors_and_movies();
                pressanykey();
                break;
            case '5':
                if (num_actors==0) no_actors();             // if number of actors is 0, display error message, else call the list function
                else list_actors();
                pressanykey();
                break;
            case '6':
                if (num_actors==0) no_actors();             // if number of actors is 0, display error message, else call the list function
                else list_full_actors_info();
                pressanykey();
                break;
            case '7':
                if (num_actors==0) no_actors();
                else list_movies_of_actor();
                pressanykey();
                break;
            case '8':
                load_actors_from_file();            // Load actors from text file
                pressanykey();
                break;
            case '9':
                if (num_actors==0) no_actors();         // if number of actors is 0, display error message, else call the save function
                else save_actors_to_file();
                pressanykey();
                break;
            case 'r':
            case 'R':
                break;
            default:
                invalid_selection();
                pressanykey();
        }
    }  while (op!='r' && op!='R');
}

void genres_menu(void)      // Genres sub-menu
{
    char op;
    do {
        menu_title(WIDTH);
        menu_box(HEIGHT,WIDTH);
        gotoxy(19,9); printf("[1] New genre");                  // Creates new movie genre
        gotoxy(19,10);printf("[2] Edit genre");                 // Edits existing genre
        gotoxy(19,11);printf("[3] Delete genre");               // Deletes existing actor
        gotoxy(19,12);printf("[4] List genres");                // Lists all the genres
        gotoxy(19,13);printf("[5] List movies by genre");       // Lists movies of a genre that the user selects and the cinemas they are played in
        gotoxy(19,16);printf("[8] Load genres data");           // Loads genres data from genres.txt
        gotoxy(19,17);printf("[9] Save genres data");           // Saves genres data to genres.txt
        gotoxy(19,19);printf("[R] Return to menu");
        fflush(stdin);
        printf("\n\n\n\t\tSelect an option:");
        op=getch();
        switch (op) {
            case '1':
                create_genre();
                pressanykey();
                break;
            case '2':
                if (num_genres==0) no_genres();             // if number of genres is 0, display error message, else call the edit function
                else edit_genre();
                pressanykey();
                break;
            case '3':
                if (num_genres==0) no_genres();             // if number of genres is 0, display error message, else call the delete function
                else delete_genre();
                pressanykey();
                break;
            case '4':
                if (num_genres==0) no_genres();             // if number of genres is 0, display error message, else call the list function
                else list_genres();
                pressanykey();
                break;
            case '5':
                if (num_genres==0) no_genres();
                else if (num_movies==0) no_movies();
                else list_movies_by_genre();
                pressanykey();
                break;
            case '8':
                load_genres_from_file();                // Load genres from text file
                pressanykey();
                break;
            case '9':
                if (num_genres==0) no_genres();
                else save_genres_to_file();
                pressanykey();
                break;
            case 'r':
            case 'R':
                break;
            default:
                invalid_selection();
                pressanykey();
        }
    }  while (op!='r' && op!='R');
}

void assocs_menu(void)
{
    char op;
    do {
        menu_title(WIDTH);
        menu_box(HEIGHT,WIDTH);
        gotoxy(19,9); printf("[1] Associate movies/cinemas");       //
        gotoxy(19,10);printf("[2] Edit movies/cinemas as.");        //
        gotoxy(19,11);printf("[3] Delete movies/cinemas as.");      //
        gotoxy(19,12);printf("[4] Associate movies/actors");        //
        gotoxy(19,13);printf("[5] Edit movies/actors as.");         //
        gotoxy(19,14);printf("[6] Delete movies/actors as.");       //
        gotoxy(19,17);printf("[9] Save changes");                   // Saves changes
        gotoxy(19,19);printf("[R] Return to menu");
        fflush(stdin);
        printf("\n\n\n\t\tSelect an option:");
        op=getch();
        switch (op) {
            case '1':
                associate_movies_and_cinemas();
                pressanykey();
                break;
            case '2':
                edit_movies_cinemas_assocs();
                pressanykey();
                break;
            case '3':
                delete_movies_cinemas_assocs();
                pressanykey();
                break;
            case '4':
                associate_actors_and_movies();
                pressanykey();
                break;
            case '5':
                edit_movies_actors_assocs();
                pressanykey();
                break;
            case '6':
                delete_movies_actors_assocs();
                pressanykey();
                break;
            case '9':
                if (num_cinemas!=0) save_cinemas_to_file();
                else no_cinemas();
                if (num_movies!=0) save_movies_to_file();
                else no_movies();
                pressanykey();
                break;
            case 'r':
            case 'R':
                break;
            default:
                invalid_selection();
                pressanykey();
        }
    }  while (op!='r' && op!='R');
}

void admin_pass(void) // Asks for admin password, calls the admin menu if correct, else displays error message
{
    char pw[20],c=' ';
    int i=0;
    printf("\n\t\tEnter the password: ");
    while (i<=19) {             // Loop to display asterisks when typing the password. taken from http://codingstreet.com/c-code-to-hide-input-password/
        pw[i]=getch();
        c=pw[i];
        if (c==13) break;                  // If user presses ENTER, end the function
        else if ((c==8) && (i!=0)) {       // This is to handle BACKSPACE key
            putch(c);
            putch(' ');
            putch(c);
            i--;
            continue;
        }
        else if ((c==8) && (i==0)) continue;   // This is to handle BACKSPACE key when at position 0
        else printf("*");
        i++;
    }
    pw[i]='\0';
    if (strcmp(pw, "nikos") == 0 || strcmp(pw,def_pw) == 0) admin_menu();
    else {
        printf("\n\t\tWrong password! Access denied.");
        pressanykey();
    }
}

void change_pass(void) // Changes the admin pass, it asks twice for confirmation
{
    char pw1[20], c1=' ';
    char pw2[20], c2=' ';
    int i=0;
    printf("\n\t\tEnter the new password (max 20 chars): ");
    while (i<=19) {             // Loop to display asterisks when typing the password. taken from http://codingstreet.com/c-code-to-hide-input-password/
        pw1[i]=getch();
        c1=pw1[i];
        if ((c1>=33 && c1<=126) || c1==8 || c1==13) { // accepts only alphanumeric chars as input, and ENTER/BACKSPACE keys
            if (c1==13) break;                  // If user presses ENTER, end the function
            else if ((c1==8) && (i!=0)) {       // This is to handle BACKSPACE key
                putch(c1);
                putch(' ');
                putch(c1);
                i--;
                continue;
            }
            else if ((c1==8) && (i==0)) continue;   // This is to handle BACKSPACE key when at position 0
            else printf("*");
            i++;
        }
        else printf("\a");                  // Plays an alert sound when user press non-alphanumeric chars
    }
    pw1[i]='\0';
    i=0;
    printf("\n\t\tConfirm the new password (max 20 chars): ");
    while (i<=19) {             // Loop to display asterisks when typing the password. taken from http://codingstreet.com/c-code-to-hide-input-password/
        pw2[i]=getch();
        c2=pw2[i];
        if ((c2>=33 && c2<=126) || c2==8 || c2==13) {
            if (c2==13) break;                  // If user presses ENTER, end the function
            else if ((c2==8) && (i!=0)) {       // This is to handle BACKSPACE key
                putch(c2);
                putch(' ');
                putch(c2);
                i--;
                continue;
            }
            else if ((c2==8) && (i==0)) continue;   // This is to handle BACKSPACE key when at position 0
            else printf("*");
            i++;
        }
        else printf("\a");                  // Plays an alert sound when user press non-alphanumeric chars
    }
    pw2[i]='\0';
    if (strcmp(pw1,pw2) == 0) {
        strcpy(def_pw,pw1);
        save_pass();
        printf("\n\t\tPassword changed!");
        pressanykey();
    }
    else {
        printf("\n\t\tPasswords don't match!");
        pressanykey();
    }
}

void save_pass() // Saves to file topsecret.dat the admin password. Used a very simple 'encryption' trick.
{
    int i,len;
    len=strlen(def_pw);
    char pw[len];
    for (i=0; i<len;i++) {  // Small loop to convert and 'encrypt' the password
        pw[i] = def_pw[i]+22;
    }
    FILE * fp;
    fp = fopen(pwfile, "wb");
    if (fp != NULL) {
        fwrite(pw,sizeof(pw),1,fp);
    }
    fclose(fp);
}

void load_pass() // Loads from file topsecret.dat the admin password
{
    int i,len;
    FILE * fp;
    fp = fopen(pwfile, "rb");
    if (fp != NULL) {
        fread(def_pw,sizeof(def_pw),1,fp);
        }
    fclose(fp);
    len=strlen(def_pw);
    for (i=0; i<len;i++) {  // Small loop to convert and 'decrypt' the password
        def_pw[i] = def_pw[i]-22;
    }
}

void create_cinema(struct cinema * m) // Creates a new movie genre
{
    int i=0,cnt=0;
    m->c_index=num_cinemas+1;
    menu_title(WIDTH);
    printf("\t\tCreate a new cinema\n");
    printf("\t\t"); for (int a=0;a<34;a++) printf("%c",196);
    printf("\n\t\tCinema name: ");
    fgets(m->c_name,NAME_SIZE,stdin);
    m->c_name[strcspn(m->c_name, "\n")] = 0;  // Removes the \n from the end of the string
    for (i=0;i<num_cinemas;i++) {        // Checks if the cinema already exists, if yes, display message and reduce num_cinemas
        if (strcmp(vec_cinemas[i].c_name, vec_cinemas[num_cinemas].c_name) == 0) {
            printf("\n\t\tCinema already exists!");
            cnt++;
        }
    }
    if (cnt==0) {
        printf("\n\t\tCinema created!");
        num_cinemas++;
    }
}

void edit_cinema(struct cinema * m)  // Edit an existing cinema that the user selects
{
    int i,j,ac,cnt=0;
    char ct[NAME_SIZE];                                // char array used to temporary store the name of the selected cinema
    char tg[NAME_SIZE];                                // char array used to temporary store the new name entered and use it to compare to existing entries for duplicate checks
    list_cinemas();                                    // Calls function to list the cinemas
    printf("\n\t\tSelect cinema to edit (1-%d): ",num_cinemas);   // Prompts to press a key from 1 to number of cinemas
    scanf(" %d",&i);
    if (i>0 && i<=num_cinemas) {                       // Checks if the option is valid
        strcpy(ct,vec_cinemas[i-1].c_name);            // Copies cinema's name to temporary char array, just to display in messages
        fflush(stdin);
        printf("\t\tAre you sure you want to edit '%s'? (Y/N)",ct);   // Asks for user confirmation
        ac=getch();
        if (ac=='Y' || ac=='y') {
            i--;                                        // Decrease i by 1 to match the correct array position
            printf("\n\t\tOld name: %s\n", vec_cinemas[i].c_name);
            printf("\t\tNew name: ");
            fgets(tg,NAME_SIZE,stdin);                  // stores the new name to temporary array
            tg[strcspn(tg, "\n")] = 0;
            for (j=0;j<num_cinemas;j++) {
                if ((strcmp(tg,vec_cinemas[j].c_name) ==0) && (strcmp(tg,ct) != 0)) cnt++; // if new name is found in other entries and is different than the current name, then increase the counter
            }
            if (cnt>0) {                    // if the counter is bigger than zero, then a duplicate entry was found, a message is displayed and nothing is changed
                printf("\n\t\tCinema '%s' already exists!",tg);
                no_changes();
            }
            else if (cnt==0) {              // if the counter is zero, the temporary cinema name is copied on the place of the cinema name we selected
                strcpy(vec_cinemas[i].c_name,tg);
                printf("\n\t\tCinema '%s' changed to '%s'!",ct,tg);
            }
        }
        else if (ac=='N' || ac=='n') no_changes();
        else invalid_selection();
    }
    else invalid_selection();
}

void delete_cinema(struct cinema * m)   // Deletes a cinema that the user selects
{
    int i,idx;
    list_cinemas();                                               // Calls function to list the cinemas
    printf("\n\t\tSelect a cinema to delete (1-%d): ",num_cinemas); // Prompts to press a key from 1 to number of cinemas
    scanf(" %d",&idx);
    if (idx>0 && idx<=num_cinemas) {                              // Checks if the option is valid
        idx=idx-1;                                                // Decrease idx by 1 to match the correct array position
        for (i=idx;i<num_cinemas;i++) {                           // This loop moves the cinemas, after the one we want to delete, one position to the left, essentially overwriting it.
            vec_cinemas[i]=vec_cinemas[i+1];
            vec_cinemas[i].c_index=vec_cinemas[i].c_index-1;      // Decrease the index number by 1, since we deleted one cinema.
        }
        num_cinemas--;                                            // Decrease the number of cinemas by 1, since we deleted one cinema.
        printf("\n\t\tCinema deleted!");
    }
    else invalid_selection();
}

void list_cinemas() // Lists all the cinemas
{
    int i;
    menu_title(WIDTH);
    printf("\t\tList of cinemas:\n");
    printf("\t\t"); for (int a=0;a<34;a++) printf("%c",196);
    for (i=0;i<num_cinemas;i++)
        printf("\n\t\t%d. %s",i+1,vec_cinemas[i].c_name);
    printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
}

void list_movies_of_cinema()  // Prompts the user to select a cinema and displays the movies played in it
{
    int i=0,cin=0;
    list_cinemas();
    printf("\n\t\tSelect the cinema (1-%d): ",num_cinemas);
    scanf(" %d",&cin);
    if (cin>0 && cin<=num_cinemas) {
        printf("\n\t\tMovies available in %s: ",vec_cinemas[cin-1].c_name);
        printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
        for (i=0;i<vec_cinemas[cin-1].movies_num;i++) {
            printf("\n\t\t%d. %s",i+1,vec_cinemas[cin-1].movies[i]);
        }
    }
    else invalid_selection();
}

void list_cinemas_of_movie() // Prompts the user to select a movie and displays the cinemas the movie is available in
{
    int i=0,j=0,mov,cnt=0;
    list_movies();
    printf("\n\t\tSelect the movie (1-%d): ",num_movies);
    scanf("%d",&mov);
    if (mov>0 && mov<=num_movies) {             // Checks if input is valid
        printf("\n\t\t'%s' is available in: ",vec_movies[mov-1].m_title);
        printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
        for (i=0;i<num_cinemas;i++) {
            for (j=0;j<vec_cinemas[i].movies_num;j++) {
                if (strcmp(vec_movies[mov-1].m_title,vec_cinemas[i].movies[j]) == 0) {
                    printf("\n\t\t%d. %s",++cnt,vec_cinemas[i].c_name);
                }
            }
        }
    }
    else invalid_selection();
}

void list_movies_by_genre() // Lists the movie genres, prompts the user to select a genre, then lists the movies of that genre and the cinemas they are available in
{
    int i,j,h,g,cnt=0;
    list_genres();
    printf("\n\t\tSelect a genre (1-%d): ",num_genres);
    scanf("%d",&g);
    if (g>0 && g<=num_genres) {                            // Checks if the input is valid
        menu_title(WIDTH);
        printf("\t\t%s movies available:",genres[g-1]);
        printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",205);
        for (i=0;i<num_movies;i++) {
            if (strcmp(genres[g-1], vec_movies[i].genre) == 0) {
                printf("\n\t\t%d. %s ",++cnt,vec_movies[i].m_title);
                printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
                printf("\n\t\t   Avalaible in the cinemas:");
                for (j=0;j<num_cinemas;j++) {
                    for (h=0;h<vec_cinemas[j].movies_num;h++) {
                        if (strcmp(vec_movies[i].m_title,vec_cinemas[j].movies[h]) == 0) {
                            printf("\n\t\t   %s",vec_cinemas[j].c_name);
                        }
                    }
                }
                printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",205);
            }
        }
    }
    else invalid_selection();
}

void associate_movies_and_cinemas() // Associates movies to cinemas, by prompting for the user to first select the cinema, then the movies
{
    int i=0,k=0,j=0,cnt=0;
    int mov,cin;
    list_cinemas();
    printf("\n\t\tSelect the cinema (1-%d): ",num_cinemas);
    scanf(" %d",&cin);
    if (cin>0 && cin<=num_cinemas) {
        list_movies();
        printf("\n\t\tHow many movies you want to associate?: ");
        scanf(" %d",&k);
        k = k + vec_cinemas[cin-1].movies_num;
        for (i=vec_cinemas[cin-1].movies_num;i<k;i++) {
            printf("\t\tSelect a movie (1-%d): ",num_movies);
            scanf("%d",&mov);
            cnt=0;
            for (j=0;j<vec_cinemas[cin-1].movies_num;j++) {
                if (strcmp(vec_movies[mov-1].m_title,vec_cinemas[cin-1].movies[j]) == 0) cnt++;
            }
            if (cnt>0) printf("\t\tMovie is already associated to the cinema!\n");
            else if (cnt==0) {
                strcpy(vec_cinemas[cin-1].movies[vec_cinemas[cin-1].movies_num],vec_movies[mov-1].m_title);
                vec_cinemas[cin-1].movies_num++;
                printf("\t\tMovie '%s' associated to cinema '%s'.\n",vec_movies[mov-1].m_title,vec_cinemas[cin-1].c_name);
            }
        }
    }
    else invalid_selection();
}

void save_cinemas_to_file()
{
    char ac;
    printf("\n\n\t\tAre you sure you want to save cinemas? (Y/N)"); // Asks for user confirmation
    ac=getch();
    if (ac=='Y' || ac=='y') {
        FILE * fp;
        int i=0,j=0;
        fp = fopen(cinemas_file, "w");
        if (fp != NULL) {
            fprintf(fp,"Cinemas: %d\n",num_cinemas);   // Saves in the first line of the file the number of cinemas
            for (i=0; i<num_cinemas; i++) {            // A loop to save all the cinema entries
                fprintf(fp,"Cinema: %s\n", vec_cinemas[i].c_name);  // Saves cinema name
                fprintf(fp,"Movies: %d\n", vec_cinemas[i].movies_num);  // Saves number of movies for the cinema
                for (j=0;j<vec_cinemas[i].movies_num;j++) {         // Loop to save all movies of each cinema
                    fprintf(fp,"%s\n", vec_cinemas[i].movies[j]);
                }
            }
        }
        fclose(fp);
        printf("\n\n\t\tCinemas data saved!");
    }
    else if (ac=='N' || ac=='n') printf("\n\t\tCinemas data not saved!");
    else invalid_selection();
}

void load_cinemas_from_file() // Checks the number of cinemas in the memory, if zero, it calls the load function, if >0 it asks for confirmation
{
    if (num_cinemas>0) {
        char ac;
        printf("\n\t\tThere are cinemas in the memory!");
        printf("\n\t\tAre you sure you want to load? (Y/N)"); // Asks for user confirmation
        ac=getch();
        if (ac=='Y' || ac=='y') load_cinemas_from_file2();
        else if (ac=='N' || ac=='n') printf("\n\t\tCinemas not loaded!");
        else invalid_selection();
    }
    else if (num_actors==0) load_cinemas_from_file2();
}

void load_cinemas_from_file2()
{
    FILE * fp;
    int i=0,j=0;
    char line[NAME_SIZE];
    num_cinemas=0;
    fp = fopen(cinemas_file, "r");
    if (fp != NULL) {
        fscanf(fp,"%*s %d\n", &num_cinemas);     // Reads the total number of cinemas
        for (i=0; i<num_cinemas; i++) {
            fgets(line,sizeof(line),fp);
            line[strlen(line)-1]=0;
            strcpy(vec_cinemas[i].c_name, &line[8]);
            fscanf(fp,"%*s %d\n", &vec_cinemas[i].movies_num);  // Reads the total number of movies of the cinema
            for (j=0;j<vec_cinemas[i].movies_num;j++) {
                fgets(line,sizeof(line),fp);
                line[strlen(line)-1]=0;
                strcpy(vec_cinemas[i].movies[j], &line[0]);
            }
        }
        fclose(fp);
    }
    printf("\n\t\tCinemas data loaded!");
}

void create_movie(struct movie * m)  // Create a new movie entry
{
    int i=0,cnt=0,chkg=0;
    m->m_index=num_movies+1;        // Generate an index for the entry
    menu_title(WIDTH);
    printf("\t\tCreate a new movie\n");
    printf("\t\t"); for (int a=0;a<34;a++) printf("%c",196);
    printf("\n\t\tTitle: ");
    fgets(m->m_title,NAME_SIZE,stdin);
    m->m_title[strcspn(m->m_title, "\n")] = 0;
    for (i=0;i<num_movies;i++) {        // Checks if the movie already exists, if yes, dipslay message and reduce num_movies
        if (strcmp(vec_movies[i].m_title, vec_movies[num_movies].m_title) == 0) {
            printf("\n\t\tMovie already exists! Use edit option.");
            cnt++;
        }
    }
    if (cnt==0) {
        fflush(stdin);
        printf("\t\tDirector: ");
        fgets(m->director,NAME_SIZE,stdin);
        m->director[strcspn(m->director, "\n")] = 0;
        fflush(stdin);
        printf("\t\tGenre: ");
        fgets(m->genre,NAME_SIZE,stdin);
        m->genre[strcspn(m->genre, "\n")] = 0;
        fflush(stdin);
        printf("\t\tDuration (in mins): ");
        fgets(m->duration,4,stdin);
        m->duration[strcspn(m->duration, "\n")] = 0;
        fflush(stdin);
        printf("\t\tMinimum age required: ");
        fgets(m->min_age,4,stdin);
        m->min_age[strcspn(m->min_age, "\n")] = 0;
        fflush(stdin);
        printf("\n\t\tMovie created!");
        num_movies++;
    }
    for (i=0;i<num_genres;i++) {        // Checks if the genre of the movie already exists in the available genres
        if (strcmp(m->genre,genres[i]) == 0) chkg++;
    }
    if (chkg==0) {                      // If it doesn't exist, it gets added
        strcpy(genres[num_genres],m->genre);
        num_genres++;
    }
}

void edit_movie(struct movie * m)  // Edit an existing movie that the user selects
{
    int i,j,ac,cnt=0;
    char ct[NAME_SIZE];                                        // char array used to temporary store the title of the selected movie
    char tg[NAME_SIZE];                                        // char array used to temporary store the new name entered and use it to compare to existing entries for duplicate checks
    list_movies();                                             // Calls function to list the movies
    printf("\n\t\tSelect movie to edit (1-%d): ",num_movies);    // Prompts to press a key from 1 to number of movies
    scanf(" %d",&i);
    if (i>0 && i<=num_movies) {                                // Checks if the option is valid
        strcpy(ct,vec_movies[i-1].m_title);                    // Copy title of the selected movie to temporary char array, just to display it in messages.
        fflush(stdin);
        printf("\t\tAre you sure you want to edit the movie: \n\t\t'%s'? (Y/N)",ct);  // Asks for user confirmation
        ac=getch();
        if (ac=='Y' || ac=='y') {
            i--;                                             // Decrease idx by 1 to match the correct array position
            printf("\n\t\tOld title: %s\n", vec_movies[i].m_title);     // Display old title
            printf("\t\tNew title: ");
            fgets(tg,NAME_SIZE,stdin);                                // Reads new title
            tg[strcspn(tg, "\n")] = 0;
            for (j=0;j<num_movies;j++) {
                if ((strcmp(tg,vec_movies[j].m_title) == 0) && (strcmp(tg,ct) != 0)) cnt++; // if new name is found in other entries and is different than the current name, then increase the counter
            }
            if (cnt>0) {                    // if the counter is bigger than zero, then a duplicate entry was found, a message is displayed and nothing is changed
                printf("\n\t\tMovie '%s' already exists!",tg);
                no_changes();
            }
            else if (cnt==0) {              // if the counter is zero, the temporary movie name is copied on the place of the movie name we selected
                strcpy(vec_movies[i].m_title,tg);
                fflush(stdin);
                printf("\t\tOld director: %s\n", vec_movies[i].director);       // Display old director
                printf("\t\tNew director: ");
                fgets(vec_movies[i].director,NAME_SIZE,stdin);                  // Reads new director
                vec_movies[i].director[strcspn(vec_movies[i].director, "\n")] = 0;
                fflush(stdin);
                printf("\t\tOld genre: %s\n", vec_movies[i].genre);             // Display old genre
                printf("\t\tNew genre: ");
                fgets(vec_movies[i].genre,NAME_SIZE,stdin);                     // Read new genre
                vec_movies[i].genre[strcspn(vec_movies[i].genre, "\n")] = 0;
                fflush(stdin);
                printf("\t\tOld duration: %s mins\n", vec_movies[i].duration);    // Display old duration
                printf("\t\tNew duration (in mins): ");
                fgets(vec_movies[i].duration,4,stdin);                               // Read new duration
                vec_movies[i].duration[strcspn(vec_movies[i].duration, "\n")] = 0;
                fflush(stdin);
                printf("\t\tOld minimum age required: %s\n", vec_movies[i].min_age);  // Display old minimum age
                printf("\t\tNew minimum age required: ");
                fgets(vec_movies[i].min_age,4,stdin);                                // Read new minimum age
                vec_movies[i].min_age[strcspn(vec_movies[i].min_age, "\n")] = 0;
                printf("\n\t\tMovie '%s' edited!",ct);
            }
        }
        else if (ac=='N' || ac=='n') no_changes();
        else invalid_selection();
    }
    else invalid_selection();
}

void delete_movie(struct movie * m)   // Delete a movie that the user selects
{
    int i,ac,idx;
    char ct[NAME_SIZE];                                          // char array used to temporary store the name of the selected movie
    list_movies();                                               // Calls function to list the movies
    printf("\n\t\tSelect a movie to delete (1-%d): ",num_movies);  // Prompts to press a key from 1 to number of movies
    scanf(" %d",&idx);
    if (idx>0 && idx<=num_movies) {                              // Checks if the option is valid
        strcpy(ct,vec_movies[idx-1].m_title);                    // copy title of the selected movie to temporary char array, just to display it in messages.
        printf("\t\tAre you sure you want to delete the movie: \n\t\t'%s'? (Y/N)",ct);  // Asks for user confirmation
        ac=getch();
        if (ac=='Y' || ac=='y') {
            idx--;                                                   // Decrease idx by 1 to match the correct array position
            for (i=idx;i<num_movies;i++) {                           // This loop moves the movies, after the one we want to delete, one position to the left, essentially overwriting it.
                vec_movies[i]=vec_movies[i+1];
                vec_movies[i].m_index=vec_movies[i].m_index-1;       // Decrease the index number by 1, since we deleted one movie.
            }
            num_movies--;                                            // Decrease the number of movies by 1, since we deleted one movie.
            printf("\n\t\tMovie '%s' deleted!",ct);
        }
        else if (ac=='N' || ac=='n') no_changes();
        else invalid_selection();
    }
    else invalid_selection();
}

void associate_actors_and_movies()  // Associates three actors to a movie
{
    int i,k,j,cnt=0;
    int mov,act;
    list_movies();
    printf("\n\t\tSelect the movie (1-%d): ",num_movies);
    scanf("%d",&mov);
    if (mov>0 && mov<=num_movies) {                      // Checks if the input is valid
        list_actors();
        printf("\n\t\tHow many actors you want to associate?: ");
        scanf(" %d",&k);
        k = k + vec_movies[mov-1].actors_num;
        for (i=vec_movies[mov-1].actors_num;i<k;i++) {
            printf("\t\tSelect an actor (1-%d): ",num_actors);
            scanf(" %d",&act);
            cnt=0;
            for (j=0;j<vec_movies[mov-1].actors_num;j++) {
                if (strcmp(vec_actors[act-1].a_name,vec_movies[mov-1].actors[j]) == 0) cnt++;
            }
            if (cnt>0) printf("\t\tActor is already associated to the movie!\n");
            else if (cnt==0) {
                strcpy(vec_movies[mov-1].actors[vec_movies[mov-1].actors_num],vec_actors[act-1].a_name);
                vec_movies[mov-1].actors_num++;
                printf("\t\tActor '%s' associated to movie '%s'.\n",vec_actors[act-1].a_name,vec_movies[mov-1].m_title);
            }
        }
    }
    else invalid_selection();
}

void list_movies()      // List all the movies
{
    int i;
    menu_title(WIDTH);
    printf("\t\tList of movies:\n");
    printf("\t\t"); for (int a=0;a<34;a++) printf("%c",196);
    for (i=0; i<num_movies; i++)
        print_movie(&vec_movies[i]);
    printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
}

void print_movie(struct movie * m)      // Print index and movie
{
    printf("\n\t\t%d. %s", m->m_index,m->m_title);
}

void list_full_movies_info()    // List all the movies with all their related data
{
    int i;
    menu_title(WIDTH);
    printf("\t\tDetailed list of movies:\n");
    printf("\t\t"); for (int a=0;a<34;a++) printf("%c",196);
    for (i=0; i<num_movies; i++)
        print_full_movie_info(&vec_movies[i]);
}

void print_full_movie_info(struct movie * m)    // Print all the data of a movie entry
{
    int j=0;
    printf("\n\t\tIndex: %d\n", m->m_index);
    printf("\t\tTitle: %s\n", m->m_title);
    printf("\t\tDirector: %s\n", m->director);
    printf("\t\tGenre: %s\n", m->genre);
    printf("\t\tDuration: %s mins\n", m->duration);
    printf("\t\tMinimum Age: %s\n", m->min_age);
    printf("\t\tActors: %s",m->actors[j]);
    for (j=1;j<m->actors_num;j++) {
        printf("\n\t\t\t%s",m->actors[j]);
    }
    printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
}

void save_movies_to_file()      // Save the movie data to text file movies.txt
{
    char ac;
    printf("\n\n\t\tAre you sure you want to save movies? (Y/N)"); // Asks for user confirmation
    ac=getch();
    if (ac=='Y' || ac=='y') {
        FILE * fp;
        int i,j;
        fp = fopen(movies_file, "w");
        if (fp != NULL) {
            fprintf(fp,"movies: %d\n",num_movies);  // Saves in the first line of the file the total number of movies
            for (i=0; i<num_movies; i++) {          // A loop to save all the movie entries
                fprintf(fp,"Index: %d\n", vec_movies[i].m_index);
                fprintf(fp,"Title: %s\n", vec_movies[i].m_title);
                fprintf(fp,"Director: %s\n", vec_movies[i].director);
                fprintf(fp,"Genre: %s\n", vec_movies[i].genre);
                fprintf(fp,"Duration: %s\n", vec_movies[i].duration);
                fprintf(fp,"Min Age: %s\n", vec_movies[i].min_age);
                fprintf(fp,"Actors: %d\n",vec_movies[i].actors_num);
                for (j=0;j<vec_movies[i].actors_num;j++) {
                    fprintf(fp,"%s\n",vec_movies[i].actors[j]);
                }
            }
            fclose(fp);
        }
        printf("\n\n\t\tMovies data saved!");
    }
    else if (ac=='N' || ac=='n') printf("\n\t\tMovies data not saved!");
    else invalid_selection();
}

void load_movies_from_file() // Checks the number of movies in the memory, if zero, it calls the load function, if >0 it asks for confirmation
{
    if (num_movies>0) {
        char ac;
        printf("\n\t\tThere are movies in the memory!");
        printf("\n\t\tAre you sure you want to load? (Y/N)"); // Asks for user confirmation
        ac=getch();
        if (ac=='Y' || ac=='y') load_movies_from_file2();
        else if (ac=='N' || ac=='n') printf("\n\t\tMovies not loaded!");
        else invalid_selection();
    }
    else if (num_movies==0) load_movies_from_file2();
}

void load_movies_from_file2()        // Load movie data from text file movies.txt
{
    FILE * fp;
    int i=0,j=0;
    char line[NAME_SIZE];
    num_movies = 0;
    fp = fopen(movies_file, "r");
    if (fp != NULL) {
        fscanf(fp,"%*s %d\n", &num_movies);     // Reads the total number of movies
        for (i=0; i<num_movies; i++) {
            fgets(line,sizeof(line),fp); 			// reads the index
            line[strlen(line)-1]=0;
            vec_movies[i].m_index=i+1;
            fgets(line,sizeof(line),fp); 			// reads the title
            line[strlen(line)-1]=0;
            strcpy(vec_movies[i].m_title, &line[7]);
            fgets(line,sizeof(line),fp); 			// reads the director
            line[strlen(line)-1]=0;
            strcpy(vec_movies[i].director, &line[10]);
            fgets(line,sizeof(line),fp); 			// reads the genre
            line[strlen(line)-1]=0;
            strcpy(vec_movies[i].genre, &line[7]);
            fgets(line,sizeof(line),fp); 			// reads the duration
            line[strlen(line)-1]=0;
            strcpy(vec_movies[i].duration, &line[10]);
            fgets(line,sizeof(line),fp); 			// reads the minimum age
            line[strlen(line)-1]=0;
            strcpy(vec_movies[i].min_age, &line[9]);
            fscanf(fp,"%*s %d\n", &vec_movies[i].actors_num);  // Reads the total number of movies of the cinema
            for (j=0;j<vec_movies[i].actors_num;j++) {
                fgets(line,sizeof(line),fp);
                line[strlen(line)-1]=0;
                strcpy(vec_movies[i].actors[j], &line[0]);
            }
        }
        fclose(fp);
    }
    printf("\n\t\tMovies data loaded!");
}

void create_actor(struct actor * m) // Create a new actor entry
{
    int i=0,cnt=0;
    m->a_index=num_actors+1;  // Generate an index for the entry
    menu_title(WIDTH);
    printf("\t\tCreate a new actor\n");
    printf("\t\t"); for (int a=0;a<34;a++) printf("%c",196);
    printf("\n\t\tName of the actor: ");
    fgets(m->a_name,NAME_SIZE,stdin);
    m->a_name[strcspn(m->a_name, "\n")] = 0;
    for (i=0;i<num_actors;i++) {        // Checks if the actor already exists, if yes, dipslay message and reduce num_actors
        if (strcmp(vec_actors[i].a_name, vec_actors[num_actors].a_name) == 0) {
            printf("\n\t\tActor already exists! Use edit option.");
            cnt++;
        }
    }
    if (cnt==0) {
        fflush(stdin);
        printf("\t\tAge of the actor: ");
        fgets(m->a_age,4,stdin);
        m->a_age[strcspn(m->a_age, "\n")] = 0;
        printf("\n\t\tActor created!");
        num_actors++;
    }
}

void edit_actor(struct actor * m)  // Edit an existing actor that the user selects
{
    int i,j,ac,cnt=0;
    char ct[NAME_SIZE];                                        // char array used to temporary store the name of the selected actor
    char tg[NAME_SIZE];                                        // char array used to temporary store the new name entered and use it to compare to existing entries for duplicate checks
    list_actors();                                             // Calls function to list the actors
    printf("\n\t\tSelect actor to edit (1-%d): ",num_actors);    // Prompts to press a key from 1 to number of actors
    scanf(" %d",&i);
    if (i>0 && i<=num_actors) {                                // Checks if the option is valid
        strcpy(ct,vec_actors[i-1].a_name);                     // Copies actor's name to temporary char array, just to display in messages
        fflush(stdin);
        printf("\t\tAre you sure you want to edit %s? (Y/N)",ct);   // Asks for user confirmation
        ac=getch();
        if (ac=='Y' || ac=='y') {
            i--;                                                 // Decrease i by 1 to match the correct array position
            printf("\n\t\tOld name: %s\n", vec_actors[i].a_name);
            printf("\t\tNew name: ");
            fgets(tg,NAME_SIZE,stdin);                                           // stores the new name to temporary array
            tg[strcspn(tg, "\n")] = 0;
            for (j=0;j<num_actors;j++) {
                if ((strcmp(tg,vec_actors[j].a_name) == 0) && (strcmp(tg,ct) != 0)) cnt++; // if new name is found in other entries and is different than the current name, then increase the counter
            }
            if (cnt>0) {                    // if the counter is bigger than zero, then a duplicate entry was found, a message is displayed and nothing is changed
                printf("\n\t\tActor '%s' already exists!",tg);
                no_changes();
            }
            else if (cnt==0) {              // if the counter is zero, the temporary actor name is copied on the place of the actor name we selected
                strcpy(vec_actors[i].a_name,tg);
                fflush(stdin);
                printf("\t\tOld age: %s\n", vec_actors[i].a_age);
                printf("\t\tNew age: ");
                fgets(vec_actors[i].a_age,4,stdin);
                vec_actors[i].a_age[strcspn(vec_actors[i].a_age, "\n")] = 0;
                printf("\n\t\tActor '%s' edited!",ct);
            }
        }
        else if (ac=='N' || ac=='n') no_changes();
        else invalid_selection();
    }
    else invalid_selection();
}

void delete_actor(struct actor * m)   // Deletes an actor that the user selects
{
    int i,idx,ac;
    char ct[NAME_SIZE];                                           // char array used to temporary store the name of the selected actor
    list_actors();                                                // Calls function to list the actors
    printf("\n\t\tSelect an actor to delete (1-%d): ",num_actors);  // Prompts to press a key from 1 to number of actors
    scanf(" %d",&idx);
    if (idx>0 && idx<=num_actors) {                               // Checks if the option is valid
        strcpy(ct,vec_actors[idx-1].a_name);                          // Copies actor's name to temporary char array, just to display in messages
        printf("\t\tAre you sure you want to delete %s? (Y/N)",ct);   // Asks for user confirmation
        ac=getch();
        if (ac=='Y' || ac=='y') {
            idx--;                                                    // Decrease idx by 1 to match the correct array position
            for (i=idx;i<num_actors;i++) {                            // This loop moves the actors, after the one we want to delete, one position to the left, essentially overwriting it.
                vec_actors[i]=vec_actors[i+1];
                vec_actors[i].a_index=vec_actors[i].a_index-1;        // Decrease the index number by 1, since we deleted one actor.
            }
            num_actors--;                                             // Decrease the number of actors by 1, since we deleted one actor.
            printf("\n\t\t%s deleted!",ct);
        }
        else if (ac=='N' || ac=='n') no_changes();
        else invalid_selection();
    }
    else invalid_selection();
}

void list_actors() // List of all the actors
{
    int i;
    menu_title(WIDTH);
    printf("\t\tList of actors:\n");
    printf("\t\t"); for (int a=0;a<34;a++) printf("%c",196);
    for (i=0; i<num_actors; i++)
        print_actor(&vec_actors[i]);
    printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
}

void print_actor(struct actor * m) // Prints index and actor
{
    printf("\n\t\t%d. %s", m->a_index,m->a_name);
}

void list_full_actors_info() // Lists all the actors with all their related info, included their associated movies
{
    int i,j,h;
    menu_title(WIDTH);
    printf("\t\tList of actors:\n");
    printf("\t\t"); for (int a=0;a<34;a++) printf("%c",196);
    for (i=0; i<num_actors; i++) {
        printf("\n\t\tIndex: %d\n", vec_actors[i].a_index);
        printf("\t\tName: %s\n", vec_actors[i].a_name);
        printf("\t\tAge: %s\n", vec_actors[i].a_age);
        printf("\t\tMovies:");
        for (j=0;j<num_movies;j++) {
            for (h=0;h<vec_movies[j].actors_num;h++) {
                if (strcmp(vec_actors[i].a_name, vec_movies[j].actors[h]) == 0)
                    printf("\n\t\t%s ",vec_movies[j].m_title);
            }
        }
        printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
    }
}

void list_movies_of_actor() // Prompts user to select actor, then it compares the selected actor to the actors saved in movies structure and displays the movies if they match
{
    int i=0,j=0,act=0,cnt=0;
    list_actors();
    printf("\n\t\tSelect the actor (1-%d): ",num_actors);
    scanf("%d",&act);
    if (act>0 && act<=num_actors) {                             // Checks if the input is valid
        printf("\n\t\t%s played in:",vec_actors[act-1].a_name);
        printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
        for (i=0;i<num_movies;i++) {
            for (j=0;j<vec_movies[i].actors_num;j++) {
                if (strcmp(vec_actors[act-1].a_name, vec_movies[i].actors[j]) == 0)
                    printf("\n\t\t%d. %s",++cnt,vec_movies[i].m_title);
            }
        }
        printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
    }
    else invalid_selection();
}

void save_actors_to_file() // Save actors to txt file actors.txt
{
    char ac;
    printf("\n\n\t\tAre you sure you want to save actors? (Y/N)");
    ac=getch();
    if (ac=='Y' || ac=='y') {
        FILE * fp;
        int i;
        fp = fopen(actors_file, "w");
        if (fp != NULL) {
            fprintf(fp,"actors: %d\n",num_actors);
            for (i=0; i<num_actors; i++) {
                fprintf(fp,"Index: %d\n", vec_actors[i].a_index);
                fprintf(fp,"Name: %s\n", vec_actors[i].a_name);
                fprintf(fp,"Age: %s\n", vec_actors[i].a_age);
            }
            fclose(fp);
        }
        printf("\n\n\t\tActors data saved!");
    }
    else if (ac=='N' || ac=='n') printf("\n\t\tActors data not saved!");
    else invalid_selection();
}

void load_actors_from_file() // Checks the number of actors in the memory, if zero, it calls the load function, if >0 it asks for confirmation
{
    if (num_actors>0) {
        char ac;
        printf("\n\t\tThere are actors in the memory!");
        printf("\n\t\tAre you sure you want to load? (Y/N)"); // Asks for user confirmation
        ac=getch();
        if (ac=='Y' || ac=='y') load_actors_from_file2();
        else if (ac=='N' || ac=='n') printf("\n\t\tActors not loaded!");
        else invalid_selection();
    }
    else if (num_actors==0) load_actors_from_file2();
}

void load_actors_from_file2() //Load actors from txt file actors.txt
{
    FILE * fp;
    int i=0;
    char line[NAME_SIZE];
    num_actors = 0;
    fp = fopen(actors_file, "r");
    if (fp != NULL) {
        fscanf(fp,"%*s %d\n", &num_actors);
        for (i=0; i<num_actors; i++) {
            fgets(line,sizeof(line),fp); 			// reads the index
            line[strlen(line)-1]=0;
            vec_actors[i].a_index=i+1;
            fgets(line,sizeof(line),fp); 			// reads the actor
            line[strlen(line)-1]=0;
            strcpy(vec_actors[i].a_name, &line[6]);
            fgets(line,sizeof(line),fp); 			// reads the age
            line[strlen(line)-1]=0;
            strcpy(vec_actors[i].a_age, &line[5]);
        }
        fclose(fp);
    }
    printf("\n\t\tActors data loaded!");
}

void create_genre(void) // Creates a new movie genre
{
    int i=0,cnt=0;
    menu_title(WIDTH);
    printf("\t\tCreate a new movie genre\n");
    printf("\t\t"); for (int a=0;a<34;a++) printf("%c",196);
    printf("\n\t\tGenre: ");
    fgets(genres[num_genres],NAME_SIZE,stdin);
    genres[num_genres][strcspn(genres[num_genres], "\n")] = 0;
    for (i=0;i<num_genres;i++) {        // Checks if the genre already exists, if yes, dipslay message
        if (strcmp(genres[i], genres[num_genres]) == 0) {
            printf("\n\t\tGenre already exists! Use edit option.");
            cnt++;
        }
    }
    if (cnt==0) {
        printf("\n\t\tGenre created!");
        num_genres++;
    }
}

void edit_genre(void) // Lists all movie genres and prompts user to select which one to edit, then it scans the new input and saves it
{
    int i,j,ac,cnt=0;
    char ct[NAME_SIZE];     // char array used to temporary store the name of the selected genre
    char tg[NAME_SIZE];     // char array used to temporary store the new name entered and use it to compare to existing entries for duplicate checks
    list_genres();
    printf("\n\t\tSelect a genre to edit (1-%d): ",num_genres);
    scanf("%d",&i);
    if (i>0 && i<=num_genres) {                             // Checks if the input is valid
        strcpy(ct,genres[i-1]);     // copy name of the selected genre to temporary char array, just to display it in messages.
        fflush(stdin);
        printf("\t\tAre you sure you want to edit genre '%s'? (Y/N)",ct);
        ac=getch();
        if (ac=='Y' || ac=='y') {
            printf("\n\t\tOld genre: %s",ct);
            printf("\n\t\tNew genre: ");
            fgets(tg,NAME_SIZE,stdin);                           // stores the new genre to temporary array
            tg[strcspn(tg, "\n")] = 0;
            for (j=0;j<num_genres;j++) {
                if ((strcmp(tg,genres[j]) == 0) && (strcmp(tg,ct) != 0)) cnt++; // if new genre is found in other entries and is different than the current genre, then increase the counter
            }
            if (cnt>0) {            // if the counter is bigger than zero, then a duplicate entry was found, a message is displayed and nothing is changed
                printf("\n\t\tGenre '%s' already exists!",tg);
                no_changes();
            }
            else if (cnt==0) {      // if the counter is zero, we copy the temporary genre name on the place of the genre we selected
                strcpy(genres[i-1],tg);
                printf("\n\t\tGenre '%s' changed to '%s'!",ct,genres[i-1]);
            }
        }
        else if (ac=='N' || ac=='n') no_changes();
        else invalid_selection();
    }
    else invalid_selection();
}

void delete_genre(void) // Lists all movie genres and prompts user to select which one to delete, then it moves the array elements after the selection, one position to the left, deleting the selection
{
    int i,j,ac;
    char ct[NAME_SIZE];     // char array used to temporary store the name of the selected genre
    list_genres();
    printf("\n\t\tSelect a genre to delete (1-%d): ",num_genres);
    scanf("%d",&i);
    if (i>0 && i<=num_genres) {     // Checks if the input is valid
        strcpy(ct,genres[i-1]);     // copy name of the selected genre to temporary char array, just to display it in messages.
        printf("\t\tAre you sure you want to delete genre '%s'? (Y/N)",ct);
        ac=getch();
        if (ac=='Y' || ac=='y') {
            i--;
            for (j=i;j<num_genres;j++) strcpy(genres[j],genres[j+1]);
            num_genres--;  //Decreases the number of genres by 1, since we deleted an entry
            printf("\n\t\tGenre '%s' deleted!",ct);
        }
        else if (ac=='N' || ac=='n') no_changes();
        else invalid_selection();
    }
    else invalid_selection();
}

void list_genres() // Lists all the movie genres
{
    int i;
    menu_title(WIDTH);
    printf("\t\tList of genres:\n");
    printf("\t\t"); for (int a=0;a<34;a++) printf("%c",196);
    for (i=0;i<num_genres;i++) {
        printf("\n\t\t%d. %s",i+1,genres[i]);
    }
    printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
}

void save_genres_to_file() // Saves movies genres to txt file genres.txt
{
    char ac;
    printf("\n\n\t\tAre you sure you want to save genres? (Y/N)"); // Asks for user confirmation
    ac=getch();
    if (ac=='Y' || ac=='y') {
        FILE * fp;
        int i;
        fp = fopen(genres_file, "w");
        if (fp != NULL) {
            fprintf(fp,"Genres: %d\n",num_genres);
            for (i=0; i<num_genres; i++) {
                fprintf(fp,"%s\n", genres[i]);
            }
            fclose(fp);
        }
        printf("\n\n\t\tGenres data saved!");
    }
    else if (ac=='N' || ac=='n') printf("\n\t\tGenres data not saved!");
    else invalid_selection();
}

void load_genres_from_file() // Checks the number of genres in the memory, if zero, it calls the load function, if >0 it asks for confirmation
{
    if (num_genres>0) {
        char ac;
        printf("\n\t\tThere are genres in the memory!");
        printf("\n\t\tAre you sure you want to load? (Y/N)"); // Asks for user confirmation
        ac=getch();
        if (ac=='Y' || ac=='y') load_genres_from_file2();
        else if (ac=='N' || ac=='n') printf("\n\t\tGenres not loaded!");
        else invalid_selection();
    }
    else if (num_genres==0) load_genres_from_file2();
}

void load_genres_from_file2() // Loads movie genres from txt file genres.txt
{
    FILE * fp;
    int i=0;
    char line[NAME_SIZE];
    num_genres = 0;
    fp = fopen(genres_file, "r");
    if (fp != NULL) {
        fscanf(fp,"%*s %d\n", &num_genres);     // Reads the total number of genres
        for (i=0; i<num_genres; i++) {
            fgets(line,sizeof(line),fp); 			// reads the genre
            line[strlen(line)-1]=0;
            strcpy(genres[i], &line[0]);
        }
        fclose(fp);
    }
    printf("\n\t\tGenres data loaded!");
}

void save_db()  // Saves the database of actors, movies, genres and cinemas to txt files, doing checks if either are empty, to avoid overwriting our files with empty files
{
    if (num_cinemas==0 && num_movies==0 && num_actors==0 && num_genres==0) {
        printf("\n\n\t\tNothing to save!");
    }
    else {
        if (num_cinemas!=0) save_cinemas_to_file();
            else no_cinemas();
        if (num_movies!=0) save_movies_to_file();
            else no_movies();
        if (num_actors!=0) save_actors_to_file();
            else no_actors();
        if (num_genres!=0) save_genres_to_file();
            else no_genres();
    }
}

void invalid_selection()
{
    printf("\a\n\n\t\tInvalid selection!"); // Displays a message that an invalid selection was made
}

void pressanykey()  // Displays a message to press any key to continue and ...waits for any key to be pressed |)
{
    printf("\n\n\t\tPress any key to continue...");
    getch();
}

void no_cinemas()  // Displays a message that there are no cinemas to display
{
    printf("\n\n\t\tThere are no cinemas in the database.");
}

void no_movies()  // Displays a message that there are no movies to display
{
    printf("\n\n\t\tThere are no movies in the database.");
}

void no_actors()  // Displays a message that there are no actors to display
{
    printf("\n\n\t\tThere are no actors in the database.");
}

void no_genres()  // Displays a message that there are no genre to display
{
    printf("\n\n\t\tThere are no genres in the database.");
}

void no_changes() // Displays a message that no changes were made.
{
    printf("\n\t\tNo changes were made!");
}

void edit_movies_cinemas_assocs(void)
{
    int i=0,k=0,j=0,cnt=0;
    int mov,cin,ac;
    list_cinemas();
    printf("\n\t\tSelect the cinema (1-%d): ",num_cinemas);
    scanf("%d",&cin);
    if (cin>0 && cin<=num_cinemas) {
        fflush(stdin);
        printf("\t\tAre you sure you want to edit associations\n\t\tof cinema: '%s'? (Y/N)",vec_cinemas[cin-1].c_name);  // Asks for user confirmation
        ac=getch();
        if (ac=='Y' || ac=='y') {
            printf("\n\n\t\tMovies associated to %s: ",vec_cinemas[cin-1].c_name);
            printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
            for (i=0;i<vec_cinemas[cin-1].movies_num;i++) {
                printf("\n\t\t%d. %s",i+1,vec_cinemas[cin-1].movies[i]);
            }
            printf("\n\n\t\tWhich entry you want to edit? (1-%d): ",vec_cinemas[cin-1].movies_num);
            scanf(" %d",&k);
            if (k>0 && k<=vec_cinemas[cin-1].movies_num) {
                list_movies();
                printf("\n\t\tSelect the new movie (1-%d): ",num_movies);
                scanf(" %d",&mov);
                if (mov>0 && mov<=num_movies) {
                    for (j=0;j<vec_cinemas[cin-1].movies_num;j++) {
                        if (strcmp(vec_movies[mov-1].m_title,vec_cinemas[cin-1].movies[j]) == 0) cnt++;
                    }
                    if (cnt>0) printf("\t\tMovie is already associated to the cinema!\n");
                    else if (cnt==0) {
                        strcpy(vec_cinemas[cin-1].movies[k-1],vec_movies[mov-1].m_title);
                        printf("\t\tMovie '%s' associated to cinema '%s'.\n",vec_movies[mov-1].m_title,vec_cinemas[cin-1].c_name);
                    }
                }
                else invalid_selection();
            }
            else invalid_selection();
        }
        else if (ac=='N' || ac=='n') no_changes();
        else invalid_selection();
    }
    else invalid_selection();
}

void delete_movies_cinemas_assocs(void)
{
    int i=0,k=0,j=0;
    int cin,ac;
    char ct[NAME_SIZE];
    list_cinemas();
    printf("\n\t\tSelect the cinema (1-%d): ",num_cinemas);
    scanf("%d",&cin);
    if (cin>0 && cin<=num_cinemas) {
        printf("\n\n\t\tMovies associated to %s: ",vec_cinemas[cin-1].c_name);
        printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
        for (i=0;i<vec_cinemas[cin-1].movies_num;i++) {
            printf("\n\t\t%d. %s",i+1,vec_cinemas[cin-1].movies[i]);
        }
        printf("\n\n\t\tWhich entry you want to delete? (1-%d): ",vec_cinemas[cin-1].movies_num);
        scanf(" %d",&k);
        if (k>0 && k<=vec_cinemas[cin-1].movies_num) {
            strcpy(ct,vec_cinemas[cin-1].movies[k-1]);
            fflush(stdin);
            printf("\t\tAre you sure you want to remove movie\n\t\t'%s' \n\t\tfrom cinema: '%s'? (Y/N)",ct,vec_cinemas[cin-1].c_name);  // Asks for user confirmation
            ac=getch();
            if (ac=='Y' || ac=='y') {
                for (j=k-1;j<vec_cinemas[cin-1].movies_num;j++)
                    strcpy(vec_cinemas[cin-1].movies[j],vec_cinemas[cin-1].movies[j+1]);
                vec_cinemas[cin-1].movies_num--;
                printf("\n\t\tMovie removed from cinema!");
            }
            else if (ac=='N' || ac=='n') no_changes();
            else invalid_selection();
        }
        else invalid_selection();
    }
    else invalid_selection();
}

void edit_movies_actors_assocs(void)
{
    int i=0,k=0,j=0,cnt=0;
    int mov,act,ac;
    list_movies();
    printf("\n\t\tSelect the movie (1-%d): ",num_movies);
    scanf("%d",&mov);
    if (mov>0 && mov<=num_movies) {
        fflush(stdin);
        printf("\t\tAre you sure you want to edit associations\n\t\tof movie: '%s'? (Y/N)",vec_movies[mov-1].m_title);  // Asks for user confirmation
        ac=getch();
        if (ac=='Y' || ac=='y') {
            printf("\n\n\t\tActors associated to %s: ",vec_movies[mov-1].m_title);
            printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
            for (i=0;i<vec_movies[mov-1].actors_num;i++) {
                printf("\n\t\t%d. %s",i+1,vec_movies[mov-1].actors[i]);
            }
            printf("\n\n\t\tWhich entry you want to edit? (1-%d): ",vec_movies[mov-1].actors_num);
            scanf(" %d",&k);
            if (k>0 && k<=vec_movies[mov-1].actors_num) {
                list_actors();
                printf("\n\t\tSelect the new actor (1-%d): ",num_actors);
                scanf(" %d",&act);
                if (act>0 && act<=num_actors) {
                    for (j=0;j<vec_movies[mov-1].actors_num;j++) {
                        if (strcmp(vec_actors[act-1].a_name,vec_movies[mov-1].actors[j]) == 0) cnt++;
                    }
                    if (cnt>0) printf("\t\tActor is already associated to the cinema!\n");
                    else if (cnt==0) {
                        strcpy(vec_movies[mov-1].actors[k-1],vec_actors[act-1].a_name);
                        printf("\t\tActor '%s' associated to\n\t\tmovie '%s'.\n",vec_actors[act-1].a_name,vec_movies[mov-1].m_title);
                    }
                }
                else invalid_selection();
            }
            else invalid_selection();
        }
        else if (ac=='N' || ac=='n') no_changes();
        else invalid_selection();
    }
    else invalid_selection();
}

void delete_movies_actors_assocs(void)
{
    int i=0,k=0,j=0;
    int mov,ac;
    char ct[NAME_SIZE];
    list_movies();
    printf("\n\t\tSelect the movie (1-%d): ",num_movies);
    scanf("%d",&mov);
    if (mov>0 && mov<=num_movies) {
        printf("\n\n\t\tActors associated to movie\n\t\t'%s': ",vec_movies[mov-1].m_title);
        printf("\n\t\t"); for (int a=0;a<34;a++) printf("%c",196);
        for (i=0;i<vec_movies[mov-1].actors_num;i++) {
            printf("\n\t\t%d. %s",i+1,vec_movies[mov-1].actors[i]);
        }
        printf("\n\n\t\tWhich entry you want to delete? (1-%d): ",vec_movies[mov-1].actors_num);
        scanf(" %d",&k);
        if (k>0 && k<=vec_movies[mov-1].actors_num) {
            strcpy(ct,vec_movies[mov-1].actors[k-1]);
            fflush(stdin);
            printf("\t\tAre you sure you want to remove actor\n\t\t'%s' from movie:\n\t\t'%s'? (Y/N)",ct,vec_movies[mov-1].m_title);  // Asks for user confirmation
            ac=getch();
            if (ac=='Y' || ac=='y') {
                for (j=k-1;j<vec_movies[mov-1].actors_num;j++)
                    strcpy(vec_movies[mov-1].actors[j],vec_movies[mov-1].actors[j+1]);
                vec_movies[mov-1].actors_num--;
                printf("\n\t\tActor removed from cinema!");
            }
            else if (ac=='N' || ac=='n') no_changes();
            else invalid_selection();
        }
        else invalid_selection();
    }
    else invalid_selection();
}
