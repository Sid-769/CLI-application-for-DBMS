#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sport_db_event.h"
#include "sport_db_athlete.h"
#include "sport_db.h"

void add_athlete(int event_code)
{
    struct Event *current_event = event_head;
    while (current_event)
    {
        if (current_event->event_code == event_code)
        {
            struct Athlete *new_athlete = (struct Athlete *)malloc(sizeof(struct Athlete));
            if (!new_athlete)
            {
                printf("Memory allocation error.\n");
                return;
            }

            printf("Enter athlete code: ");
            scanf("%d", &new_athlete->athlete_code);
            clear_input_buffer();
            if (!isValid_athlete_code(new_athlete->athlete_code))
            {
                printf("Invalid athlete code.\n");
                free(new_athlete);
                return;
            }

            struct Athlete *current_athlete = current_event->athletes;
            while (current_athlete)
            {
                if (current_athlete->athlete_code == new_athlete->athlete_code)
                {
                    printf("Athlete code already exists.\n");
                    free(new_athlete);
                    return;
                }
                current_athlete = current_athlete->next;
            }

            printf("Enter athlete name: ");
            fgets(new_athlete->athlete_name, MAX_NAME_LENGTH, stdin);
            size_t len = strlen(new_athlete->athlete_name);
            if (len > 0 && new_athlete->athlete_name[len - 1] == '\n')
            {
                new_athlete->athlete_name[len - 1] = '\0';
            }
            if (!isValid_athlete_name(new_athlete->athlete_name))
            {
                printf("Invalid athlete name. Must be less than %d characters.\n", MAX_NAME_LENGTH);
                free(new_athlete);
                return;
            }

            printf("Enter athlete age: ");
            scanf("%d", &new_athlete->age);
            clear_input_buffer();
            if (!isValid_age(new_athlete->age))
            {
                printf("Invalid age. Must be between 14 and 120.\n");
                free(new_athlete);
                return;
            }

            printf("Enter athlete nationality: ");
            fgets(new_athlete->nationality, sizeof(new_athlete->nationality), stdin);
            len = strlen(new_athlete->nationality);
            if (len > 0 && new_athlete->nationality[len - 1] == '\n')
            {
                new_athlete->nationality[len - 1] = '\0';
            }
            if (!isValid_nationality(new_athlete->nationality))
            {
                printf("Invalid nationality. Must be a 3-letter code.\n");
                free(new_athlete);
                return;
            }

            new_athlete->next = current_event->athletes;
            current_event->athletes = new_athlete;
            printf("Athlete added successfully.\n");
            return;
        }
        current_event = current_event->next;
    }
    printf("Event with code %d not found.\n", event_code);
}

void display_athletes(int event_code)
{
    struct Event *current_event = event_head;
    while (current_event)
    {
        if (current_event->event_code == event_code)
        {
            struct Athlete *current_athlete = current_event->athletes;
            if (!current_athlete)
            {
                printf("No athletes to display for event code %d.\n", event_code);
                return;
            }

            printf("Athlete Code\tAthlete Name\t\tAge\t\tNationality\n");
            while (current_athlete)
            {
                printf("%11d\t%-20s\t%3d\t\t%s\n",
                       current_athlete->athlete_code, current_athlete->athlete_name, current_athlete->age, current_athlete->nationality);
                current_athlete = current_athlete->next;
            }
            return;
        }
        current_event = current_event->next;
    }
    printf("Event with code %d not found.\n", event_code);
}

void search_athlete(int event_code, int athlete_code)
{
    struct Event *current_event = event_head;
    while (current_event)
    {
        if (current_event->event_code == event_code)
        {
            struct Athlete *current_athlete = current_event->athletes;
            while (current_athlete)
            {
                if (current_athlete->athlete_code == athlete_code)
                {
                    printf("Athlete Code\tAthlete Name\t\tAge\t\tNationality\n");
                    printf("%11d\t%-20s\t%3d\t\t%s\n",
                           current_athlete->athlete_code, current_athlete->athlete_name, current_athlete->age, current_athlete->nationality);
                    return;
                }
                current_athlete = current_athlete->next;
            }
            printf("Athlete with code %d not found.\n", athlete_code);
            return;
        }
        current_event = current_event->next;
    }
    printf("Event with code %d not found.\n", event_code);
}

void update_athlete(int event_code, int athlete_code)
{
    struct Event *current_event = event_head;
    while (current_event)
    {
        if (current_event->event_code == event_code)
        {
            struct Athlete *current_athlete = current_event->athletes;
            while (current_athlete)
            {
                if (current_athlete->athlete_code == athlete_code)
                {
                    printf("Enter new athlete name: ");
                    fgets(current_athlete->athlete_name, MAX_NAME_LENGTH, stdin);
                    size_t len = strlen(current_athlete->athlete_name);
                    if (len > 0 && current_athlete->athlete_name[len - 1] == '\n')
                    {
                        current_athlete->athlete_name[len - 1] = '\0';
                    }
                    if (!isValid_athlete_name(current_athlete->athlete_name))
                    {
                        printf("Invalid athlete name. Must be less than %d characters.\n", MAX_NAME_LENGTH);
                        return;
                    }

                    printf("Enter new athlete age: ");
                    scanf("%d", &current_athlete->age);
                    clear_input_buffer();
                    if (!isValid_age(current_athlete->age))
                    {
                        printf("Invalid age. Must be between 14 and 120.\n");
                        return;
                    }

                    printf("Enter new athlete nationality: ");
                    fgets(current_athlete->nationality, sizeof(current_athlete->nationality), stdin);
                    len = strlen(current_athlete->nationality);
                    if (len > 0 && current_athlete->nationality[len - 1] == '\n')
                    {
                        current_athlete->nationality[len - 1] = '\0';
                    }
                    if (!isValid_nationality(current_athlete->nationality))
                    {
                        printf("Invalid nationality. Must be a 3-letter code.\n");
                        return;
                    }

                    printf("Athlete updated successfully.\n");
                    return;
                }
                current_athlete = current_athlete->next;
            }
            printf("Athlete with code %d not found.\n", athlete_code);
            return;
        }
        current_event = current_event->next;
    }
    printf("Event with code %d not found.\n", event_code);
}

void delete_athlete(int event_code, int athlete_code)
{
    struct Event *current_event = event_head;
    while (current_event)
    {
        if (current_event->event_code == event_code)
        {
            struct Athlete *current_athlete = current_event->athletes;
            struct Athlete *previous_athlete = NULL;
            while (current_athlete)
            {
                if (current_athlete->athlete_code == athlete_code)
                {
                    if (previous_athlete)
                    {
                        previous_athlete->next = current_athlete->next;
                    }
                    else
                    {
                        current_event->athletes = current_athlete->next;
                    }
                    free(current_athlete);
                    printf("Athlete deleted successfully.\n");
                    return;
                }
                previous_athlete = current_athlete;
                current_athlete = current_athlete->next;
            }
            printf("Athlete with code %d not found.\n", athlete_code);
            return;
        }
        current_event = current_event->next;
    }
    printf("Event with code %d not found.\n", event_code);
}

int isValid_athlete_code(int athlete_code)
{
    return athlete_code > 0;
}

int isValid_athlete_name(const char *athlete_name)
{
    return strlen(athlete_name) < MAX_NAME_LENGTH;
}

int isValid_age(int age)
{
    return age >= 14 && age <= 120;
}

int isValid_nationality(const char *nationality)
{
    return strlen(nationality) == 3;
}