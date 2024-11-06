#ifndef SPORT_DB_ATHLETE_H
#define SPORT_DB_ATHLETE_H

#define MAX_NAME_LENGTH 50

struct Athlete
{
    int athlete_code;
    char athlete_name[MAX_NAME_LENGTH];
    int age;
    char nationality[4];
    struct Athlete *next;
};

// Function declarations
void add_athlete(int event_code);
void display_athletes(int event_code);
void search_athlete(int event_code, int athlete_code);
void update_athlete(int event_code, int athlete_code);
void delete_athlete(int event_code, int athlete_code);
int isValid_athlete_code(int athlete_code);
int isValid_athlete_name(const char *athlete_name);
int isValid_age(int age);
int isValid_nationality(const char *nationality);

#endif