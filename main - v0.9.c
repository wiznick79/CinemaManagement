#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define NAME_SIZE 50    // max number of chars in the string
#define VECTOR_SIZE 100  // max number of movies or actors we can save in the memory

// Cinema Management program in C by Nikolaos Perris (#36261)
// Version 0.9 (14/01/2018)
// for Introduction to Algorithms and Programming
// Universidade Fernando Pessoa

//Structure for cinemas
struct cinema {
    char cin_names[NAME_SIZE];
    char movie1[NAME_SIZE];
    char movie2[NAME_SIZE];
    char movie3[NAME_SIZE];
    char movie4[NAME_SIZE];
};

//Structure for movies
struct movie {
    int m_index;
    char title[NAME_SIZE];
    char director[NAME_SIZE];
    char genre[NAME_SIZE];
    char duration[4];
    char min_age[3];
    char actor1[NAME_SIZE];
    char actor2[NAME_SIZE];
    char actor3[NAME_SIZE];
};

//Structure for actors
struct actor {
    int a_index;
    char a_name[NAME_SIZE];
    char a_age[3];
};

//The functions used
void cinemas_menu(void); // The cinemas sub-menu
void movies_menu(void); // The movies sub-menu
void actors_menu(void); // The actors sub-menu
void list_cinemas(); // List of the cinemas
void save_cinemas_to_file(void); // Saves to txt file with the movies associated to each cinema
void load_cinemas_from_file(void); // Loads from txt file the movies previously associated to each cinema
void create_movie(struct movie * m); // Create new movie record
void list_movies(void); // List of the movies with title only
void list_full_movies_info(void); // List of the movies with all info, including the actors
void print_movie(struct movie * m); // Prints the title of the movie
void print_full_movie_info(struct movie * m); // Prints all the info of the movie
void save_movies_to_file(void); // Save movies to txt file movies.txt
void load_movies_from_file(); // Load movies from txt file movies.txt
void create_actor(struct actor * m); // Create a new actor record
void list_actors(void); // List of the actors
void list_full_actors_info(); // List of actors with all info
void print_actor(struct actor * m); // Prints index and actor
void save_actors_to_file(void); // Save actors to txt file actors.txt
void load_actors_from_file(void); //Load actors from txt file actors.txt
void edit_movie(struct movie * m); // Edit an existing movie that the user selects
void delete_movie(struct movie * m); // Delete a movie that the user selects
void edit_actor(struct actor * m); // Edit an existing actor that the user selects
void delete_actor(struct actor * m); // Deletes an actor that the user selects
void no_movies(void); //Prints a message that there are no movies
void no_actors(void); //Prints a message that there are no actors
void no_genres(void); //Prints a message that there are no actors
void save_db(void); // Saves the database of all data, if they are not empty. If empty it does not save, to avoid overwriting existing files.
void associate_actors_and_movies(struct actor * m); // Prompts the user to select a movie, then the 3 actors they played in it. It stores those 3 actors as actor1, actor2, actor3 in the movie structure
void list_movies_of_actor(void); // Lists the movies of the selected actor - NOT WORKING CORRECTLY
void associate_movies_and_cinemas(void); // Not working
void list_movies_of_cinema(void); // Prompts the user to select a cinema and displays the movies played in it
void list_cinemas_of_movie(void); // Prompts the user to select a movie and displays the cinemas the movie is available in
void genres_menu(void); // Genres sub-menu
void create_genre(void); // Creates a new movie genre
void list_genres(void); // Lists all the movie genres
void edit_genre(void); // Lists all movie genres and prompts user to select which one to edit, then it scans the new input and saves it
void delete_genre(void); // Lists all movie genres and prompts user to select which one to delete, then it moves the array elements after the selection, one position to the left, deleting the selection
void list_movies_by_genre(void); // Lists the movie genres, prompts the user to select a genre, then lists the movies of that genre and the cinemas they are available in
void save_genres_to_file(void); // Saves movies genres to txt file genres.txt
void load_genres_from_file(void); // Loads movie genres from txt file genres.txt
void not_implemented(void); // Displays a message that the selection is not yet implemented in the program.

// Global variables
struct cinema *cin_names[6] = {"NOS Alameda","NOS Nascente","NOS MaiaShopping","NOS NorteShopping","NOS Mar Shopping"}; // Predefined names of cinemas
struct cinema vec_cinemas[VECTOR_SIZE];
struct movie vec_movies[VECTOR_SIZE];
struct actor vec_actors[VECTOR_SIZE];
char genres[NAME_SIZE][VECTOR_SIZE];
int num_cins=5;
int num_movies=0;
int num_actors=0;
int num_genres=0;
char cinemas_file[]="cinemas.txt"; // Name of the file where the info about the cinemas are saved.
char movies_file[]="movies.txt"; // Name of the file where the info about the movies are saved.
char actors_file[]="actors.txt"; // Name of the file where the info about the actors are saved.
char genres_file[]="genres.txt"; // Name of the file where the info about the movie genres are saved.

int main(int argc, char const *argv[])
{
    char op;
    do {
        system("cls");
        printf("\t\t==================================\n");
        printf("\t\t|| Cinema Management - Main     ||\n");
        printf("\t\t==================================\n\n");
        printf("\t\t==================================\n");
        printf("\t\t||                              ||\n");
        printf("\t\t|| [1] Manage cinemas           ||\n"); // Displays cinema sub-menu
        printf("\t\t|| [2] Manage movies            ||\n"); // Displays movies sub-menu
        printf("\t\t|| [3] Manage actors            ||\n"); // Displays actors sub-menu
        printf("\t\t|| [4] Manage movie genres      ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t|| [8] Load database            ||\n"); // Loads database
        printf("\t\t|| [9] Save database            ||\n"); // Saves database
        printf("\t\t||                              ||\n");
        printf("\t\t|| [Q] Quit program             ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t==================================\n");
        fflush(stdin);
        printf("\t\tSelect an option:");
        op=getch();         //scanf(" %c", &op);  <= instead of this, to not have to press enter
        switch (op) {
            case '1':
                cinemas_menu();
                break;
            case '2':
                movies_menu();
                break;
            case '3':
                actors_menu();
                break;
            case '4':
                genres_menu();
                break;
            case '8':   // Load both movies and actors from the txt files
                load_cinemas_from_file();
                load_movies_from_file();
                load_actors_from_file();
                load_genres_from_file();
                break;
            case '9':   // Calls the save database function
                save_db();
                break;
            case 'q':
            case 'Q':
                break;
            default:
                printf("\a\n\n\t\tInvalid option!\n\t\tPress any key to return to menu...");  //Plays an alert sound and displays error message when user selects invalid option
                getch();
        }
    }  while (op!='q' && op!='Q');
    return 0;
}

void cinemas_menu()
{
    char op;
    do {
        system("cls");
        printf("\t\t==================================\n");
        printf("\t\t|| Cinema Management - Cinemas  ||\n");
        printf("\t\t==================================\n\n");
        printf("\t\t==================================\n");
        printf("\t\t||                              ||\n");
        printf("\t\t|| [1] List cinemas             ||\n"); // Lists all the cinemas
        printf("\t\t|| [2] List movies of a cinema  ||\n"); // Lists all movies of one cinema
        printf("\t\t|| [3] List cinemas for a movie ||\n"); // Lists the cinemas a movie is played in - NOT IMPLEMENTED YET
        printf("\t\t|| [4] List movies by genre     ||\n"); // Lists movies by genre and the cinema they are played in - NOT IMPLEMENTED YET
        printf("\t\t|| [5] Associate cinemas/movies ||\n"); // Associates movies and cinemas
        printf("\t\t||                              ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t|| [8] Load cinemas data        ||\n"); // Loads cinemas data from cinemas.txt
        printf("\t\t|| [9] Save cinemas data        ||\n"); // Saves cinemas data to cinemas.txt
        printf("\t\t||                              ||\n");
        printf("\t\t|| [R] Return to main menu      ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t==================================\n");
        fflush(stdin);
        printf("\t\tSelect an option:");
        op=getch();         //scanf(" %c", &op);  <= instead of this, to not have to press enter
        switch (op) {
            case '1':
                list_cinemas();
                printf("\n\n\t\tPress any key to return to menu...");
                getch();
                break;
            case '2':
                if (num_movies==0) no_movies();
                else list_movies_of_cinema();
                break;
            case '3':
                if (num_movies==0) no_movies();
                else list_cinemas_of_movie();
                break;
            case '4':
                if (num_movies==0) no_movies();
                else list_movies_by_genre();
                break;
            case '5':
                if (num_movies==0) no_movies();
                else associate_movies_and_cinemas();
                break;
            case '8':
                load_cinemas_from_file();
                break;
            case '9':
                save_cinemas_to_file();
                break;
            case 'r':
            case 'R':
                break;
            default:
                printf("\a\n\n\t\tInvalid option!\n\t\tPress any key to return to menu...");  //Plays an alert sound and displays error message when user selects invalid option
                getch();
        }
    }  while (op!='r' && op!='R');
}

void movies_menu()
{
    char op;
    do {
        system("cls");
        printf("\t\t==================================\n");
        printf("\t\t|| Cinema Management - Movies   ||\n");
        printf("\t\t==================================\n\n");
        printf("\t\t==================================\n");
        printf("\t\t||                              ||\n");
        printf("\t\t|| [1] New movie                ||\n"); // Creates new movie
        printf("\t\t|| [2] Edit movie               ||\n"); // Edits existing movie
        printf("\t\t|| [3] Delete movie             ||\n"); // Deletes existing movie
        printf("\t\t|| [4] Associate movies/actors  ||\n"); // Associates movies and actors
        printf("\t\t|| [5] Associate movies/cinemas ||\n"); // Associates movies and actors
        printf("\t\t|| [6] List movies              ||\n"); // Lists all movies
        printf("\t\t|| [7] List movies with info    ||\n"); // Lists the movies with detailed info
        printf("\t\t|| [8] Load movies data         ||\n"); // Loads movies data from movies.txt
        printf("\t\t|| [9] Save movies data         ||\n"); // Saves movies data to movies.txt
        printf("\t\t||                              ||\n");
        printf("\t\t|| [R] Return to main menu      ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t==================================\n");
        fflush(stdin);
        printf("\t\tSelect an option:");
        op=getch();         //scanf(" %c", &op);  <= instead of this, to not have to press enter
        switch (op) {
            case '1':
                create_movie(&vec_movies[num_movies]);
                num_movies++;
                break;
            case '2':
                if (num_movies==0) no_movies();             // if number of movies is 0, display error message, else call the edit function
                else edit_movie(&vec_movies[num_movies]);
                break;
            case '3':
                if (num_movies==0) no_movies();             // if number of movies is 0, display error message, else call the delete function
                else delete_movie(&vec_movies[num_movies]);
                break;
            case '4':
                if (num_actors==0) no_actors();
                else if (num_movies==0) no_movies();
                    else associate_actors_and_movies(&vec_actors[num_actors]);
                break;
            case '5':
                if (num_movies==0) no_movies();
                else associate_movies_and_cinemas();
                break;
            case '6':
                if (num_movies==0) no_movies();             // if number of movies is 0, display error message, else call the list function
                else {
                    list_movies();
                    printf("\n\n\t\tPress any key to return to menu...");
                    getch();
                }
                break;
            case '7':
                if (num_movies==0) no_movies();             // if number of movies is 0, display error message, else call the list full info function
                else list_full_movies_info();
                break;
            case '8':
                load_movies_from_file();            // Load movies from text file
                break;
            case '9':
                if (num_movies==0) no_movies();                         // if number of movies is 0, display error message, else call the save function
                else save_movies_to_file();
                break;
            case 'r':
            case 'R':
                break;
            default:
                printf("\a\n\n\t\tInvalid option!\n\t\tPress any key to return to menu...");  //Plays an alert sound and displays error message when user selects invalid option
                getch();
        }
    }  while (op!='r' && op!='R');
}

void actors_menu()
{
    char op;
    do {
        system("cls");
        printf("\t\t==================================\n");
        printf("\t\t|| Cinema Management - Actors   ||\n");
        printf("\t\t==================================\n\n");
        printf("\t\t==================================\n");
        printf("\t\t||                              ||\n");
        printf("\t\t|| [1] New actor                ||\n");  // Creates new actor
        printf("\t\t|| [2] Edit actor               ||\n");  // Edits existing actor
        printf("\t\t|| [3] Delete actor             ||\n");  // Deletes existing actor
        printf("\t\t|| [4] Associate actors/movies  ||\n");  // Associates three actors to a movie
        printf("\t\t|| [5] List actors              ||\n");  // Lists all the actors
        printf("\t\t|| [6] List actors with info    ||\n");  // Lists all the actors with their extra info
        printf("\t\t|| [7] List movies of an actor  ||\n");  // Lists the movies of one actor
        printf("\t\t|| [8] Load actors data         ||\n");  // Loads actors data from actors.txt
        printf("\t\t|| [9] Save actors data         ||\n");  // Saves all actors data to actors.txt
        printf("\t\t||                              ||\n");
        printf("\t\t|| [R] Return to main menu      ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t==================================\n");
        fflush(stdin);
        printf("\t\tSelect an option:");
        op=getch();         //scanf(" %c", &op);  <= instead of this, to not have to press enter
        switch (op) {
            case '1':
                create_actor(&vec_actors[num_actors]);
                num_actors++;
                break;
            case '2':
                if (num_actors==0) no_actors();             // if number of actors is 0, display error message, else call the edit function
                else edit_actor(&vec_actors[num_actors]);
                break;
            case '3':
                if (num_actors==0) no_actors();             // if number of actors is 0, display error message, else call the edit function
                else delete_actor(&vec_actors[num_actors]);
                break;
            case '4':
                if (num_actors==0) no_actors();
                else if (num_movies==0) no_movies();
                    else associate_actors_and_movies(&vec_actors[num_actors]);
                break;
            case '5':
                if (num_actors==0) no_actors();             // if number of actors is 0, display error message, else call the list function
                else {
                    list_actors();
                    printf("\n\n\t\tPress any key to return to menu...");
                    getch();
                }
                break;
            case '6':
                if (num_actors==0) no_actors();             // if number of actors is 0, display error message, else call the list function
                else list_full_actors_info();
                break;
            case '7':
                if (num_actors==0) no_actors();
                else list_movies_of_actor();
                break;
            case '8':
                load_actors_from_file();
                break;
            case '9':
                if (num_actors==0) no_actors();         // if number of actors is 0, display error message, else call the save function
                else save_actors_to_file();
                break;
            case 'r':
            case 'R':
                break;
            default:
                printf("\a\n\n\t\tInvalid option!\n\t\tPress any key to return to menu...");  //Plays an alert sound and displays error message when user selects invalid option
                getch();
        }
    }  while (op!='r' && op!='R');
}

void genres_menu()
{
    char op;
    do {
        system("cls");
        printf("\t\t==================================\n");
        printf("\t\t|| Cinema Management - Genres   ||\n");
        printf("\t\t==================================\n\n");
        printf("\t\t==================================\n");
        printf("\t\t||                              ||\n");
        printf("\t\t|| [1] New genre                ||\n");  // Creates new movie genre
        printf("\t\t|| [2] Edit genre               ||\n");  // Edits existing genre
        printf("\t\t|| [3] Delete genre             ||\n");  // Deletes existing actor
        printf("\t\t|| [4] List genres              ||\n");  // Lists all the genres
        printf("\t\t|| [5] List movies by genre     ||\n");  //
        printf("\t\t||                              ||\n");  //
        printf("\t\t||                              ||\n");  //
        printf("\t\t|| [8] Load genres data         ||\n");  // Loads genres data from genres.txt
        printf("\t\t|| [9] Save genres data         ||\n");  // Saves genres data to genres.txt
        printf("\t\t||                              ||\n");
        printf("\t\t|| [R] Return to main menu      ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t==================================\n");
        fflush(stdin);
        printf("\t\tSelect an option:");
        op=getch();         //scanf(" %c", &op);  <= instead of this, to not have to press enter
        switch (op) {
            case '1':
                create_genre();
                num_genres++;
                break;
            case '2':
                if (num_genres==0) no_genres();             // if number of genres is 0, display error message, else call the edit function
                else edit_genre();
                break;
            case '3':
                if (num_genres==0) no_genres();             // if number of genres is 0, display error message, else call the delete function
                else delete_genre();
                break;
            case '4':
                if (num_genres==0) no_genres();             // if number of genres is 0, display error message, else call the list function
                else {
                    list_genres();
                    printf("\n\n\t\tPress any key to return to menu...");
                    getch();
                }
                break;
            case '5':
                if (num_genres==0) no_genres();
                else list_movies_by_genre();
                break;
            case '8':
                load_genres_from_file();
                break;
            case '9':
                if (num_genres==0) no_genres();
                else save_genres_to_file();
                break;
            case 'r':
            case 'R':
                break;
            default:
                printf("\a\n\n\t\tInvalid option!\n\t\tPress any key to return to menu...");  //Plays an alert sound and displays error message when user selects invalid option
                getch();
        }
    }  while (op!='r' && op!='R');
}

void list_cinemas() // Lists all the cinemas
{
    int i;
    system("cls");
    printf("\t\t==================================\n");
    printf("\t\t|| Cinema Management - Cinemas  ||\n");
    printf("\t\t==================================\n\n");
    printf("\t\tList of cinemas:\n");
    printf("\t\t==================================\n");
    for (i=0;i<5;i++)
        printf("\t\t%d. %s \n",i+1,cin_names[i]);
    printf("\t\t==================================\n");
}

void list_movies_of_cinema()  // Prompts the user to select a cinema and displays the movies played in it
{
    int cin;
    list_cinemas();
    printf("\t\tSelect the cinema (1-5): ");
    scanf("%d",&cin);
    if (cin>0 && cin<=5) {
        printf("\n\t\tMovies available in %s: ",cin_names[cin-1]);
        printf("\n\t\t==================================\n");
        printf("\n\t\t%s",vec_cinemas[cin-1].movie1);
        printf("\n\t\t%s",vec_cinemas[cin-1].movie2);
        printf("\n\t\t%s",vec_cinemas[cin-1].movie3);
        printf("\n\t\t%s",vec_cinemas[cin-1].movie4);
        printf("\n\n\t\tPress any key to return to menu...");
        getch();
    }
    else {
        printf("\n\n\t\tInvalid selection!\n\t\tPress any key to return to menu...");
        getch();
    }
}

void list_cinemas_of_movie() // Prompts the user to select a movie and displays the cinemas the movie is available in
{
    int i,mov;
    list_movies();
    printf("\t\tSelect the movie (1-%d): ",num_movies);
    scanf("%d",&mov);
    if (mov>0 && mov<=num_movies) {
        printf("\n\t\t%s is available in: ",vec_movies[mov-1].title);
        for (i=0;i<5;i++) {
            if (*vec_movies[mov-1].title==*vec_cinemas[i].movie1) printf("\n\t\t%s",cin_names[i]);
            if (*vec_movies[mov-1].title==*vec_cinemas[i].movie2) printf("\n\t\t%s",cin_names[i]);
            if (*vec_movies[mov-1].title==*vec_cinemas[i].movie3) printf("\n\t\t%s",cin_names[i]);
            if (*vec_movies[mov-1].title==*vec_cinemas[i].movie4) printf("\n\t\t%s",cin_names[i]);
        }
        printf("\n\n\t\tPress any key to return to menu...");
        getch();
    }
    else {
        printf("\n\n\t\tInvalid selection!\n\t\tPress any key to return to menu...");
        getch();
    }
}

void save_cinemas_to_file()
{
    FILE * fp;
    int i;
    fp = fopen(cinemas_file, "w");
    if (fp != NULL)
    {
        fprintf(fp,"cinemas: %d\n",num_cins);  // Saves in the first line of the file the number of cinemas
        for (i=0; i<num_cins; i++)             // A loop to save all the cinema entries
        {
            fprintf(fp,"Movie 1: %s\n", vec_cinemas[i].movie1);
            fprintf(fp,"Movie 2: %s\n", vec_cinemas[i].movie2);
            fprintf(fp,"Movie 3: %s\n", vec_cinemas[i].movie3);
            fprintf(fp,"Movie 4: %s\n", vec_cinemas[i].movie4);
        }
        fclose(fp);
    }
    printf("\n\n\t\tCinemas data saved!\n\t\tPress any key to continue...");
    getch();
}

void load_cinemas_from_file()
{
    FILE * fp;
    int i=0;
    char line[NAME_SIZE];
    num_cins = 0;
    fp = fopen(cinemas_file, "r");
    if (fp != NULL) {
        fscanf(fp,"%*s %d\n", &num_cins);     // Reads the total number of cinemas
        for (i=0; i<num_cins; i++)
        {
            fgets(line,sizeof(line),fp); 			// reads the first movie
            line[strlen(line)-1]=0;
            strcpy(vec_cinemas[i].movie1, &line[9]);
            fgets(line,sizeof(line),fp); 			// reads the second movie
            line[strlen(line)-1]=0;
            strcpy(vec_cinemas[i].movie2, &line[9]);
            fgets(line,sizeof(line),fp); 			// reads the third movie
            line[strlen(line)-1]=0;
            strcpy(vec_cinemas[i].movie3, &line[9]);
            fgets(line,sizeof(line),fp); 			// reads the fourth movie
            line[strlen(line)-1]=0;
            strcpy(vec_cinemas[i].movie4, &line[9]);
        }
        fclose(fp);
    }
    printf("\n\n\t\tCinemas data loaded!\n\t\tPress any key to continue...");
    getch();
}

void create_movie(struct movie * m)  // Create a new movie entry
{
    m->m_index=num_movies+1;        // Generate an index for the entry
    system("cls");
    printf("\t\t==================================\n");
    printf("\t\t|| Cinema Management - New movie||\n");
    printf("\t\t==================================\n\n");
    printf("\t\tCreate a new movie\n");
    printf("\t\t==================================\n");
    printf("\t\tTitle: ");
    gets(m->title);
    printf("\t\tDirector: ");
    gets(m->director);
    printf("\t\tGenre: ");
    gets(m->genre);
    printf("\t\tDuration (in mins): ");
    gets(m->duration);
    printf("\t\tMinimum age required: ");
    gets(m->min_age);
}

void list_movies()      // List all the movies
{
    int i;
    system("cls");
    printf("\t\t==================================\n");
    printf("\t\t|| Cinema Management - Movies   ||\n");
    printf("\t\t==================================\n\n");
    printf("\t\tList of movies:\n");
    printf("\t\t==================================\n");
    for (i=0; i<num_movies; i++)
        print_movie(&vec_movies[i]);
    printf("\t\t==================================\n");
}

void print_movie(struct movie * m)      // Print index and movie
{
    printf("\t\t%d. %s\n", m->m_index,m->title);
}

void list_full_movies_info()    // List all the movies with all their related data
{
    int i;
    system("cls");
    printf("\t\t==================================\n");
    printf("\t\t|| Cinema Management - Movies   ||\n");
    printf("\t\t==================================\n\n");
    printf("\t\tList of movies:\n");
    printf("\t\t==================================\n");
    for (i=0; i<num_movies; i++)
        print_full_movie_info(&vec_movies[i]);
    printf("\n\n\t\tPress any key to return to menu...");
    getch();
}

void print_full_movie_info(struct movie * m)    // Print all the data of a movie entry
{
    printf("\t\tIndex: %d\n", m->m_index);
    printf("\t\tTitle: %s\n", m->title);
    printf("\t\tDirector: %s\n", m->director);
    printf("\t\tGenre: %s\n", m->genre);
    printf("\t\tDuration: %s mins\n", m->duration);
    printf("\t\tMinimum Age: %s\n", m->min_age);
    printf("\t\tActors: %s\n \t\t\t%s\n \t\t\t%s\n",m->actor1,m->actor2,m->actor3);
    printf("\t\t==================================\n");
}

void save_movies_to_file()      // Save the movie data to text file movies.txt
{
    FILE * fp;
    int i;
    fp = fopen(movies_file, "w");
    if (fp != NULL)
    {
        fprintf(fp,"movies: %d\n",num_movies);  // Saves in the first line of the file the total number of movies
        for (i=0; i<num_movies; i++)            // A loop to save all the movie entries
        {
            fprintf(fp,"Index: %d\n", vec_movies[i].m_index);
            fprintf(fp,"Title: %s\n", vec_movies[i].title);
            fprintf(fp,"Director: %s\n", vec_movies[i].director);
            fprintf(fp,"Genre: %s\n", vec_movies[i].genre);
            fprintf(fp,"Duration: %s\n", vec_movies[i].duration);
            fprintf(fp,"Min Age: %s\n", vec_movies[i].min_age);
            fprintf(fp,"Actor 1: %s\n", vec_movies[i].actor1);
            fprintf(fp,"Actor 2: %s\n", vec_movies[i].actor2);
            fprintf(fp,"Actor 3: %s\n", vec_movies[i].actor3);
        }
        fclose(fp);
    }
    printf("\n\n\t\tMovies data saved!\n\t\tPress any key to continue...");
    getch();
}

void load_movies_from_file()        // Load movie data from text file movies.txt
{
    FILE * fp;
    int i=0;
    char line[NAME_SIZE];
    num_movies = 0;
    fp = fopen(movies_file, "r");
    if (fp != NULL) {
        fscanf(fp,"%*s %d\n", &num_movies);     // Reads the total number of movies
        for (i=0; i<num_movies; i++)
        {
            fgets(line,sizeof(line),fp); 			// reads the index
            line[strlen(line)-1]=0;
            vec_movies[i].m_index=i+1;
            fgets(line,sizeof(line),fp); 			// reads the title
            line[strlen(line)-1]=0;
            strcpy(vec_movies[i].title, &line[7]);
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
            fgets(line,sizeof(line),fp); 			// reads the first actor
            line[strlen(line)-1]=0;
            strcpy(vec_movies[i].actor1, &line[9]);
            fgets(line,sizeof(line),fp); 			// reads the second actor
            line[strlen(line)-1]=0;
            strcpy(vec_movies[i].actor2, &line[9]);
            fgets(line,sizeof(line),fp); 			// reads the third actor
            line[strlen(line)-1]=0;
            strcpy(vec_movies[i].actor3, &line[9]);
        }
        fclose(fp);
    }
    printf("\n\n\t\tMovies data loaded!\n\t\tPress any key to continue...");
    getch();
}

void create_actor(struct actor * m) // Create a new actor entry
{
    m->a_index=num_actors+1;  // Generate an index for the entry
    system("cls");
    printf("\t\t==================================\n");
    printf("\t\t|| Cinema Management - New actor||\n");
    printf("\t\t==================================\n\n");
    printf("\t\tCreate a new actor\n");
    printf("\t\t==================================\n");
    printf("\t\tName of the actor: ");
    gets(m->a_name);
    printf("\t\tAge of the actor: ");
    gets(m->a_age);
}

void list_actors() // List of all the actors
{
    int i;
    system("cls");
    printf("\t\t==================================\n");
    printf("\t\t|| Cinema Management - Actors   ||\n");
    printf("\t\t==================================\n\n");
    printf("\t\tList of actors:\n");
    printf("\t\t==================================\n");
    for (i=0; i<num_actors; i++)
        print_actor(&vec_actors[i]);
    printf("\t\t==================================\n");
}

void print_actor(struct actor * m) // Prints index and actor
{
    printf("\t\t%d. %s\n", m->a_index,m->a_name);
}

void list_full_actors_info() // Lists all the actors with all their related info, included their associated movies
{
    int i,j;
    system("cls");
    printf("\t\t==================================\n");
    printf("\t\t|| Cinema Management - Actors   ||\n");
    printf("\t\t==================================\n\n");
    printf("\t\tList of actors:\n");
    printf("\t\t==================================\n");
    for (i=0; i<num_actors; i++) {
        printf("\t\tIndex: %d\n", vec_actors[i].a_index);
        printf("\t\tName: %s\n", vec_actors[i].a_name);
        printf("\t\tAge: %s\n", vec_actors[i].a_age);
        printf("\t\tMovies:");
        for (j=0;j<num_movies;j++) {
            if (strncmp(vec_actors[i].a_name, vec_movies[j].actor1, NAME_SIZE) == 0) printf("\n\t\t%s ",vec_movies[j].title);
            if (strncmp(vec_actors[i].a_name, vec_movies[j].actor2, NAME_SIZE) == 0) printf("\n\t\t%s ",vec_movies[j].title);
            if (strncmp(vec_actors[i].a_name, vec_movies[j].actor3, NAME_SIZE) == 0) printf("\n\t\t%s ",vec_movies[j].title);
        }
        printf("\n\t\t==================================\n");
    }
    printf("\n\n\t\tPress any key to return to menu...");
    getch();
}

void save_actors_to_file() // Save actors to txt file actors.txt
{
    FILE * fp;
    int i;
    fp = fopen(actors_file, "w");
    if (fp != NULL)
    {
        fprintf(fp,"actors: %d\n",num_actors);
        for (i=0; i<num_actors; i++)
        {
            fprintf(fp,"Index: %d\n", vec_actors[i].a_index);
            fprintf(fp,"Name: %s\n", vec_actors[i].a_name);
            fprintf(fp,"Age: %s\n", vec_actors[i].a_age);
        }
        fclose(fp);
    }
    printf("\n\n\t\tActors data saved!\n\t\tPress any key to continue...");
    getch();
}

void load_actors_from_file() //Load actors from txt file actors.txt
{
    FILE * fp;
    int i=0;
    char line[NAME_SIZE];
    num_actors = 0;
    fp = fopen(actors_file, "r");
    if (fp != NULL)
    {
        fscanf(fp,"%*s %d\n", &num_actors);
        for (i=0; i<num_actors; i++)
        {
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
    printf("\n\n\t\tActors data loaded!\n\t\tPress any key to continue...");
    getch();
}

void edit_movie(struct movie * m)  // Edit an existing movie that the user selects
{
    int idx;
    list_movies();                                                  // Calls function to list the movies
    printf("\t\tSelect movie to edit (1-%d): ",num_movies);         // Prompts to press a key from 1 to number of movies
    scanf("%d",&idx);
    if (idx>0 && idx<=num_movies)                                   // Checks if the option is valid
    {
        idx=idx-1;                                                  // Decrease idx by 1 to match the correct array position
        printf("\t\tOld title: %s\n", vec_movies[idx].title);       // Display old title
        printf("\t\tNew title: ");
        scanf(" %[^\n]%*c",&vec_movies[idx].title);                 // Reads new title
        printf("\t\tOld director: %s\n", vec_movies[idx].director); // Display old director
        printf("\t\tNew director: ");
        scanf(" %[^\n]%*c",&vec_movies[idx].director);              // Reads new director
        printf("\t\tOld genre: %s\n", vec_movies[idx].genre);       // Display old genre
        printf("\t\tNew genre: ");
        scanf(" %[^\n]%*c",&vec_movies[idx].genre);                 // Read new genre
        printf("\t\tOld duration: %s mins\n", vec_movies[idx].duration);    // Display old duration
        printf("\t\tNew duration (in mins): ");
        scanf("%s",&vec_movies[idx].duration);                      // Read new duration
        printf("\t\tOld minimum age required: %s\n", vec_movies[idx].min_age);  // Display old minimum age
        printf("\t\tNew minimum age required: ");
        scanf("%s",&vec_movies[idx].min_age);                       // Read new minimum age
    }
    else {
        printf("\n\n\t\tInvalid selection!\n\t\tPress any key to return to menu...");
        getch();
    }
}

void delete_movie(struct movie * m)   // Delete a movie that the user selects
{
    int i,idx;
    list_movies();                                               // Calls function to list the movies
    printf("\t\tSelect a movie to delete (1-%d): ",num_movies);  // Prompts to press a key from 1 to number of movies
    scanf("%d",&idx);
    if (idx>0 && idx<=num_movies)                                // Checks if the option is valid
    {
        idx=idx-1;                                               // Decrease idx by 1 to match the correct array position
        for (i=idx;i<num_movies;i++)                             // This loop moves the movies, after the one we want to delete, one position to the left, essentially overwriting it.
        {
            vec_movies[i]=vec_movies[i+1];
            vec_movies[i].m_index=vec_movies[i].m_index-1;       // Decrease the index number by 1, since we deleted one movie.
        }
        num_movies--;                                            // Decrease the number of movies by 1, since we deleted one movie.
    }
    else {
        printf("\n\n\t\tInvalid selection!\n\t\tPress any key to return to menu...");
        getch();
    }
}

void edit_actor(struct actor * m)  // Edit an existing actor that the user selects
{
    int idx;
    list_actors();                                             // Calls function to list the actors
    printf("\t\tSelect actor to edit (1-%d): ",num_actors);    // Prompts to press a key from 1 to number of actors
    scanf("%d",&idx);
    if (idx>0 && idx<=num_actors)                              // Checks if the option is valid
    {
        idx=idx-1;                                             // Decrease idx by 1 to match the correct array position
        printf("\t\tOld name: %s\n", vec_actors[idx].a_name);
        printf("\t\tNew name: ");
        scanf(" %[^\n]%*c",&vec_actors[idx].a_name);
        printf("\t\tOld age: %s\n", vec_actors[idx].a_age);
        printf("\t\tNew age: ");
        scanf(" %[^\n]%*c",&vec_actors[idx].a_age);
    }
    else {
        printf("\n\n\t\tInvalid selection!\n\t\tPress any key to return to menu...");
        getch();
    }
}

void delete_actor(struct actor * m)   // Deletes an actor that the user selects
{
    int i,idx;
    list_actors();                                                // Calls function to list the actors
    printf("\t\tSelect an actor to delete (1-%d): ",num_actors);  // Prompts to press a key from 1 to number of actors
    scanf("%d",&idx);
    if (idx>0 && idx<=num_actors)                                 // Checks if the option is valid
    {
        idx=idx-1;                                                // Decrease idx by 1 to match the correct array position
        for (i=idx;i<num_actors;i++)                              // This loop moves the actors, after the one we want to delete, one position to the left, essentially overwriting it.
        {
            vec_actors[i]=vec_actors[i+1];
            vec_actors[i].a_index=vec_actors[i].a_index-1;        // Decrease the index number by 1, since we deleted one actor.
        }
        num_actors--;                                             // Decrease the number of actors by 1, since we deleted one actor.
    }
    else {
        printf("\n\n\t\tInvalid selection!\n\t\tPress any key to return to menu...");
        getch();
    }
}

void no_movies()  // Prints a message that there are no movies to display
{
    printf("\n\n\t\tThere are no movies in the database.");
    printf("\n\t\tPress any key to return to menu...");
    getch();
}

void no_actors()  // Prints a message that there are no actors to display
{
    printf("\n\n\t\tThere are no actors in the database.");
    printf("\n\t\tPress any key to return to menu...");
    getch();
}

void no_genres()  // Prints a message that there are no genre to display
{
    printf("\n\n\t\tThere are no genres in the database.");
    printf("\n\t\tPress any key to return to menu...");
    getch();
}

void save_db()  // Saves the database of actors and movies to txt files, doing checks if either are empty, to avoid overwriting our files with empty files
{
    if (num_movies==0 && num_actors==0 && num_genres==0) {
        printf("\n\n\t\tNothing to save!");
        printf("\n\t\tPress any key to return to menu...");
        getch();
    }
    else {
        if (num_movies!=0) save_movies_to_file();
            else no_movies();
        if (num_actors!=0) save_actors_to_file();
            else no_actors();
        if (num_genres|=0) save_genres_to_file();
            else no_genres();
    }
}

void associate_actors_and_movies(struct actor * m)  // Associates three actors to a movie
{
    int mov,act;
    list_movies();
    printf("\t\tSelect the movie (1-%d): ",num_movies);
    scanf("%d",&mov);
    if (mov>0 && mov<=num_movies) {                               // Checks if the input is valid
        list_actors();
        printf("\t\tSelect the first actor (1-%d): ",num_actors);
        scanf("%d",&act);
        strcpy(vec_movies[mov-1].actor1,vec_actors[act-1].a_name);
        printf("\t\tSelect the second actor (1-%d): ",num_actors);
        scanf("%d",&act);
        strcpy(vec_movies[mov-1].actor2,vec_actors[act-1].a_name);
        printf("\t\tSelect the third actor (1-%d): ",num_actors);
        scanf("%d",&act);
        strcpy(vec_movies[mov-1].actor3,vec_actors[act-1].a_name);
    }
    else {
        printf("\n\n\t\tInvalid selection!\n\t\tPress any key to return to menu...");
        getch();
    }
}

void list_movies_of_actor() // Prompts user to select actor, then it compares the selected actor to the actors saved in movies structure and displays the movies if they match
{
    int i,act;
    list_actors();
    printf("\t\tSelect the actor (1-%d): ",num_actors);
    scanf("%d",&act);
    if (act>0 && act<=num_actors) {                             // Checks if the input is valid
        printf("\n\t\t%s played in:",vec_actors[act-1].a_name);
        printf("\n\t\t==================================");
        for (i=0;i<num_movies;i++) {
            if (strncmp(vec_actors[act-1].a_name, vec_movies[i].actor1, NAME_SIZE) == 0) printf("\n\t\t%s ",vec_movies[i].title);
            if (strncmp(vec_actors[act-1].a_name, vec_movies[i].actor2, NAME_SIZE) == 0) printf("\n\t\t%s ",vec_movies[i].title);
            if (strncmp(vec_actors[act-1].a_name, vec_movies[i].actor3, NAME_SIZE) == 0) printf("\n\t\t%s ",vec_movies[i].title);
        }
        printf("\n\t\t==================================");
        printf("\n\n\t\tPress any key to return to menu...");
        getch();
    }
    else {
        printf("\n\n\t\tInvalid selection!\n\t\tPress any key to return to menu...");
        getch();
    }
}

void associate_movies_and_cinemas() // Associates movies to cinemas, by prompting for the user to first select the cinema, then the movies
{
    int mov,cin;
    list_cinemas();
    printf("\t\tSelect the cinema (1-5): ");
    scanf("%d",&cin);
    if (cin>0 && cin<=5) {
        list_movies();
        printf("\t\tSelect the first movie (1-%d): ",num_movies);
        scanf("%d",&mov);
        strcpy(vec_cinemas[cin-1].movie1,vec_movies[mov-1].title);
        printf("\t\tSelect the second movie (1-%d): ",num_movies);
        scanf("%d",&mov);
        strcpy(vec_cinemas[cin-1].movie2,vec_movies[mov-1].title);
        printf("\t\tSelect the third movie (1-%d): ",num_movies);
        scanf("%d",&mov);
        strcpy(vec_cinemas[cin-1].movie3,vec_movies[mov-1].title);
        printf("\t\tSelect the fourth movie (1-%d): ",num_movies);
        scanf("%d",&mov);
        strcpy(vec_cinemas[cin-1].movie4,vec_movies[mov-1].title);
    }
    else {
        printf("\n\n\t\tInvalid selection!\n\t\tPress any key to return to menu...");
        getch();
    }
}

void create_genre() // Creates a new movie genre
{
    system("cls");
    printf("\t\t==================================\n");
    printf("\t\t|| Cinema Management - New genre||\n");
    printf("\t\t==================================\n\n");
    printf("\t\tCreate a new movie genre\n");
    printf("\t\t==================================\n");
    printf("\t\tGenre: ");
    gets(genres[num_genres]);
}

void list_genres() // Lists all the movie genres
{
    int i;
    system("cls");
    printf("\t\t==================================\n");
    printf("\t\t|| Cinema Management - Genres   ||\n");
    printf("\t\t==================================\n\n");
    printf("\n\t\tList of genres:\n");
    printf("\t\t==================================\n");
    for (i=0;i<num_genres;i++) {
        printf("\t\t%d. %s\n",i+1,genres[i]);
    }
    printf("\t\t==================================\n");
}

void edit_genre() // Lists all movie genres and prompts user to select which one to edit, then it scans the new input and saves it
{
    int i;
    list_genres();
    printf("\t\tSelect a genre to edit (1-%d): ",num_genres);
    scanf("%d",&i);
    printf("\t\tType the new name: ");
    scanf(" %[^\n]%*c",genres[i-1]);
    printf("\n\t\tGenre changed!\n\t\tPress any key to return to menu...");
    getch();
}

void delete_genre() // Lists all movie genres and prompts user to select which one to delete, then it moves the array elements after the selection, one position to the left, deleting the selection
{
    int i,j;
    list_genres();
    printf("\t\tSelect a genre to delete (1-%d): ",num_genres);
    scanf("%d",&j);
    j=j-1;
    for (i=j;i<num_genres;i++) {
        strcpy(genres[i],genres[i+1]);
    }
    num_genres--;  //Decreases the number of genres by 1, since we deleted an entry
}

void list_movies_by_genre() // Lists the movie genres, prompts the user to select a genre, then lists the movies of that genre and the cinemas they are available in
{
    int i,j,g;
    list_genres();
    printf("\t\tSelect a genre (1-%d): ",num_genres);
    scanf("%d",&g);
    system("cls");
    if (g>0 && g<=num_genres) {                             // Checks if the input is valid
        printf("\n\t\t%s movies available:",genres[g-1]);
        printf("\n\t\t==================================");
        for (i=0;i<num_movies;i++) {
            if (strncmp(genres[g-1], vec_movies[i].genre, NAME_SIZE) == 0) {
                printf("\n\t\t%s ",vec_movies[i].title);
                printf("\n\t\t----------------------------------");
                printf("\n\t\tAvalaible in the cinemas:");
                for (j=0;j<5;j++) {
                    if (*vec_movies[i].title==*vec_cinemas[j].movie1) printf("\n\t\t%s",cin_names[j]);
                    if (*vec_movies[i].title==*vec_cinemas[j].movie2) printf("\n\t\t%s",cin_names[j]);
                    if (*vec_movies[i].title==*vec_cinemas[j].movie3) printf("\n\t\t%s",cin_names[j]);
                    if (*vec_movies[i].title==*vec_cinemas[j].movie4) printf("\n\t\t%s",cin_names[j]);
                }
            printf("\n\t\t==================================");
            }
        }
        printf("\n\n\t\tPress any key to return to menu...");
        getch();
    }
    else {
        printf("\n\n\t\tInvalid selection!\n\t\tPress any key to return to menu...");
        getch();
    }
}

void save_genres_to_file() // Saves movies genres to txt file genres.txt
{
    FILE * fp;
    int i;
    fp = fopen(genres_file, "w");
    if (fp != NULL)
    {
        fprintf(fp,"Genres: %d\n",num_genres);
        for (i=0; i<num_genres; i++)
        {
            fprintf(fp,"%s\n", genres[i]);
        }
        fclose(fp);
    }
    printf("\n\n\t\tGenres data saved!\n\t\tPress any key to continue...");
    getch();
}

void load_genres_from_file() // Loads movie genres from txt file genres.txt
{
    FILE * fp;
    int i=0;
    char line[NAME_SIZE];
    num_genres = 0;
    fp = fopen(genres_file, "r");
    if (fp != NULL) {
        fscanf(fp,"%*s %d\n", &num_genres);     // Reads the total number of genres
        for (i=0; i<num_genres; i++)
        {
            fgets(line,sizeof(line),fp); 			// reads the genre
            line[strlen(line)-1]=0;
            strcpy(genres[i], &line[0]);
        }
        fclose(fp);
    }
    printf("\n\n\t\tGenres data loaded!\n\t\tPress any key to continue...");
    getch();
}

void not_implemented()
{
    printf("\n\n\t\tSelection is not yet implemented!\n\t\tPress any key to return to menu.");
    getch();
}
