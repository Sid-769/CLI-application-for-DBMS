#ifndef SPORT_DB_EVENT_H
#define SPORT_DB_EVENT_H

#include "sport_db_athlete.h"

#define MAX_NAME_LENGTH 50

struct Event
{
    int event_code;
    char event_name[MAX_NAME_LENGTH];
    int competitor_count;
    char gender;
    struct Athlete *athletes;
    struct Event *next;
};

extern struct Event *event_head; // Declaring event_head with external linkage

void add_event();
void display_events();
void search_event();
void update_event();
void delete_event();
int isValid_event_code(int event_code);
int isValid_event_name(const char *event_name);
int isValid_competitor_count(int competitor_count);
int isValid_gender(char gender);

#endif