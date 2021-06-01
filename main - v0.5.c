#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define NAME_SIZE 50    // max number of chars in the string
#define VECTOR_SIZE 50  // max number of movies or actors we can save in the memory

// Cinema Management program in C by Nikolaos Perris (#36261)
// Version 0.5 (13/01/2018)
// for Introduction to Algorithms and Programming
// Universidade Fernando Pessoa

//Structure for movies
struct movie {
    int m_index;
    char title[NAME_SIZE];
    char director[NAME_SIZE];
    char genre[NAME_SIZE];
    char duration[4];
    char min_age[3];
};

//Structure for actors
struct actor {
    int a_index;
    char a_name[NAME_SIZE];
};

//The functions used
void cinemas_menu(void); // The cinemas sub-menu
void movies_menu(void); // The movies sub-menu
void actors_menu(void); // The actors sub-menu
void list_cinemas(char *v[],int n); // List of the cinemas
void list_cinemas2(char *v[],int n); // Used to display a list of cinemas for the associate function
void create_movie(struct movie * m); // Create new movie record
void list_movies(void); // List of the movies with title only
void list_full_movies_info(void); // List of the movies with all info
void print_movie(struct movie * m); // Prints the title of the movie
void print_full_movie_info(struct movie * m); // Prints all the info of the movie
void save_movies_to_file(void); // Save movies to txt file movies.txt
void load_movies_from_file(); // Load movies from txt file movies.txt
void create_actor(struct actor * m); // Create a new actor record
void list_actors(void); // List of the actors
void print_actor(struct actor * m); // Prints index and actor
void save_actors_to_file(void); // Save actors to txt file actors.txt
void load_actors_from_file(void); //Load actors from txt file actors.txt
void edit_movie(struct movie * m);  // Edit an existing movie that the user selects
void delete_movie(struct movie * m);   // Delete a movie that the user selects
void edit_actor(struct actor * m);  // Edit an existing actor that the user selects
void delete_actor(struct actor * m);   // Deletes an actor that the user selects
void no_movies(void);  //Prints a message that there are no movies to display
void no_actors(void);  //Prints a message that there are no actors to display
void save_db(void); // Saves the database of movies and actors, if they are not empty. If empty it does not save, to avoid overwriting existing files.
void associate_movie(void); // Not working
void not_implemented(void); // Displays a message that the selection is not yet implemented in the program.

// Global variables
char *cinemas[5]={"NOS Alameda","NOS Nascente","NOS MaiaShopping","NOS NorteShopping","NOS Mar Shopping"}; //The available cinemas
struct movie vec_movies[VECTOR_SIZE];
struct actor vec_actors[VECTOR_SIZE];
int num_movies=0;
int num_actors=0;
char movies_file[]="movies.txt"; // Name of the file where the info about the movies are saved.
char actors_file[]="actors.txt"; // Name of the file where the info about the actors are saved.

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
        printf("\t\t|| [1] Cinemas                  ||\n"); // Displays cinema sub-menu
        printf("\t\t|| [2] Manage movies            ||\n"); // Displays movies sub-menu
        printf("\t\t|| [3] Manage actors            ||\n"); // Displays actors sub-menu
        printf("\t\t|| [4] Load database            ||\n"); // Loads database
        printf("\t\t|| [5] Save database            ||\n"); // Saves database
        printf("\t\t||                              ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t||                              ||\n");
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
            case '4':   // Load both movies and actors from the txt files
                load_movies_from_file();
                load_actors_from_file();
                break;
            case '5':   // Calls the save database function
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
        printf("\t\t|| [2] List movies of a cinema  ||\n"); // Lists all movies of one cinema - NOT IMPLEMENTED YET
        printf("\t\t|| [3] List cinemas for a movie ||\n"); // Lists the cinemas a movie is played in - NOT IMPLEMENTED YET
        printf("\t\t|| [4] List movies by genre     ||\n"); // Lists movies by genre and the cinema they are played in - NOT IMPLEMENTED YET
        printf("\t\t||                              ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t|| [R] Return to main menu      ||\n");
        printf("\t\t||                              ||\n");
        printf("\t\t==================================\n");
        fflush(stdin);
        printf("\t\tSelect an option:");
        op=getch();         //scanf(" %c", &op);  <= instead of this, to not have to press enter
        switch (op) {
            case '1':
                list_cinemas(cinemas,5);
                break;
            case '2':
                not_implemented();
                break;
            case '3':
                not_implemented();
                break;
            case '4':
                not_implemented();
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
        printf("\t\t|| [4] Associate movie          ||\n"); // Associates a movie to a cinema - NOT IMPLEMENTED YET
        printf("\t\t|| [5] List movies              ||\n"); // Lists all movies
        printf("\t\t|| [6] List movies with info    ||\n"); // Lists the movies with detailed info
        printf("\t\t|| [7] Save movies              ||\n"); // Saves movies data to movies.txt
        printf("\t\t|| [8] Load movies              ||\n"); // Loads movies data from movies.txt
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
                not_implemented();
                break;
            case '5':
                if (num_movies==0) no_movies();             // if number of movies is 0, display error message, else call the list function
                else {
                    list_movies();
                    printf("\n\n\t\tPress any key to return to menu...");
                    getch();
                }
                break;
            case '6':
                if (num_movies==0) no_movies();             // if number of movies is 0, display error message, else call the list full info function
                else list_full_movies_info();
                break;
            case '7':
                if (num_movies==0)                          // if number of movies is 0, display error message, else call the save function
                {
                    printf("\n\n\t\tNothing to save!\n\t\tPress any key to return to menu...");
                    getch();
                }
                else save_movies_to_file();
                break;
            case '8':
                load_movies_from_file();            // Load movies from text file
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
        printf("\t\t|| [4] Associate actor          ||\n");  // Associates an actor to a movie - NOT IMPLEMENTED YET
        printf("\t\t|| [5] List actors              ||\n");  // Lists all the actors
        printf("\t\t|| [6] List actors and movies   ||\n");  // Lists all the actors and the movies they participated - NOT IMPLEMENTED YET
        printf("\t\t|| [7] List movies of an actor  ||\n");  // Lists the movies of one actor - NOT IMPLEMENTED YET
        printf("\t\t|| [8] Save actors              ||\n");  // Saves all actors data to actors.txt
        printf("\t\t|| [9] Load actors              ||\n");  // Loads actors data from actors.txt
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
                not_implemented();
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
                not_implemented();
                break;
            case '7':
                not_implemented();
                break;
            case '8':
                if (num_movies==0 && num_actors==0)          // if number of actors is 0, display error message, else call the save function
                {
                    printf("\n\n\t\tNothing to save!\n\t\tPress any key to return to menu...");
                    getch();
                }
                else save_actors_to_file();
                break;
            case '9':
                load_actors_from_file();
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



void list_cinemas(char *v[],int n)
{
    int i;
    system("cls");
    printf("\t\t==================================\n");
    printf("\t\t|| Cinema Management - Cinemas  ||\n");
    printf("\t\t==================================\n\n");
    printf("\t\tList of cinemas:\n");
    printf("\t\t==================================\n");
    for (i=0;i<n;i++)
        printf("\t\t%d. %s \n",i+1,v[i]);
    printf("\t\t==================================\n");
    printf("\n\n\t\tPress any key to return to menu...");
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
        printf("\n\n\t\tInvalid option!\n\t\tPress any key to return to menu...");
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
        printf("\n\n\t\tInvalid option!\n\t\tPress any key to return to menu...");
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
    }
    else {
        printf("\n\n\t\tInvalid option!\n\t\tPress any key to return to menu...");
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
        printf("\n\n\t\tInvalid option!\n\t\tPress any key to return to menu...");
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

void save_db()  // Saves the database of actors and movies to txt files, doing checks if either are empty, to avoid overwriting our files with empty files
{
    if (num_movies==0 && num_actors==0) {
        printf("\n\n\t\tNothing to save!");
        printf("\n\t\tPress any key to return to menu...");
        getch();
    }
    else {
        if (num_movies!=0) save_movies_to_file();
            else no_movies();
        if (num_actors!=0) save_actors_to_file();
            else no_actors();
    }
}

void associate_movie() // Not working at the moment, it just displays cinemas, movies and prompts the user to make selections that do nothing.
{
    int mov,cin;
    list_movies();
    printf("\t\tSelect the movie (1-%d): ",num_movies);
    scanf("%d",&mov);
    list_cinemas2(cinemas,5);
    printf("\t\tSelect the cinema (1-5): ");
    scanf("%d",&cin);
}

void list_cinemas2(char *v[],int n) // Used to display a list of cinemas for the associate function
{
    int i;
    printf("\t\tList of cinemas:\n");
    printf("\t\t==================================\n");
    for (i=0;i<n;i++)
    printf("\t\t%d. %s \n",i+1,v[i]);
    printf("\t\t==================================\n");
}

void not_implemented()
{
    printf("\n\n\t\tSelection is not yet implemented!\n\t\tPress any key to return to menu.");
    getch();
}
