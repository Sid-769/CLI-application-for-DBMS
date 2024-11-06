#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sport_db_event.h"
#include "sport_db.h"

struct Event *event_head = NULL;

void add_event()
{
    struct Event *new_event = (struct Event *)malloc(sizeof(struct Event));
    if (!new_event)
    {
        printf("Memory allocation error.\n");
        return;
    }

    printf("Enter event code: ");
    scanf("%d", &new_event->event_code);
    clear_input_buffer();
    if (!isValid_event_code(new_event->event_code))
    {
        printf("Invalid event code. Must be between 0 and 99.\n");
        free(new_event);
        return;
    }

    struct Event *current = event_head;
    while (current)
    {
        if (current->event_code == new_event->event_code)
        {
            printf("Event code already exists.\n");
            free(new_event);
            return;
        }
        current = current->next;
    }

    printf("Enter event name: ");
    fgets(new_event->event_name, MAX_NAME_LENGTH, stdin);
    size_t len = strlen(new_event->event_name);
    if (len > 0 && new_event->event_name[len - 1] == '\n')
    {
        new_event->event_name[len - 1] = '\0';
    }
    if (!isValid_event_name(new_event->event_name))
    {
        printf("Invalid event name. Must be less than %d characters.\n", MAX_NAME_LENGTH);
        free(new_event);
        return;
    }

    printf("Enter number of competitors: ");
    scanf("%d", &new_event->competitor_count);
    clear_input_buffer();
    if (!isValid_competitor_count(new_event->competitor_count))
    {
        printf("Invalid competitor count. Must be between 10 and 99.\n");
        free(new_event);
        return;
    }

    printf("Enter gender (M/W/X): ");
    scanf("%c", &new_event->gender);
    clear_input_buffer();
    if (!isValid_gender(new_event->gender))
    {
        printf("Invalid gender. Must be 'M', 'W', or 'X'.\n");
        free(new_event);
        return;
    }

    new_event->athletes = NULL;
    new_event->next = event_head;
    event_head = new_event;
    printf("Event added successfully.\n");
}

void display_events()
{
    struct Event *current = event_head;
    if (!current)
    {
        printf("No events to display.\n");
        return;
    }

    printf("Event Code\tEvent Name\t\tCompetitors\t\tGender\n");
    while (current)
    {
        printf("%7d\t%-20s\t%10d\t\t%c\n",
               current->event_code, current->event_name, current->competitor_count, current->gender);
        current = current->next;
    }
}

void search_event()
{
    int event_code;
    printf("Enter event code: ");
    scanf("%d", &event_code);
    clear_input_buffer();

    struct Event *current = event_head;
    while (current)
    {
        if (current->event_code == event_code)
        {
            printf("Event Code\tEvent Name\t\tCompetitors\t\tGender\n");
            printf("%7d\t%-20s\t%10d\t\t%c\n",
                   current->event_code, current->event_name, current->competitor_count, current->gender);
            return;
        }
        current = current->next;
    }
    printf("Event with code %d not found.\n", event_code);
}

void update_event()
{
    int event_code;
    printf("Enter event code: ");
    scanf("%d", &event_code);
    clear_input_buffer();

    struct Event *current = event_head;
    while (current)
    {
        if (current->event_code == event_code)
        {
            printf("Enter new event name: ");
            fgets(current->event_name, MAX_NAME_LENGTH, stdin);
            size_t len = strlen(current->event_name);
            if (len > 0 && current->event_name[len - 1] == '\n')
            {
                current->event_name[len - 1] = '\0';
            }
            if (!isValid_event_name(current->event_name))
            {
                printf("Invalid event name. Must be less than %d characters.\n", MAX_NAME_LENGTH);
                return;
            }

            printf("Enter new number of competitors: ");
            scanf("%d", &current->competitor_count);
            clear_input_buffer();
            if (!isValid_competitor_count(current->competitor_count))
            {
                printf("Invalid competitor count. Must be between 10 and 99.\n");
                return;
            }

            printf("Enter new gender (M/W/X): ");
            scanf("%c", &current->gender);
            clear_input_buffer();
            if (!isValid_gender(current->gender))
            {
                printf("Invalid gender. Must be 'M', 'W', or 'X'.\n");
                return;
            }

            printf("Event updated successfully.\n");
            return;
        }
        current = current->next;
    }
    printf("Event with code %d not found.\n", event_code);
}

void delete_event()
{
    int event_code;
    printf("Enter event code: ");
    scanf("%d", &event_code);
    clear_input_buffer();

    struct Event *current = event_head;
    struct Event *previous = NULL;

    while (current)
    {
        if (current->event_code == event_code)
        {
            if (previous)
            {
                previous->next = current->next;
            }
            else
            {
                event_head = current->next;
            }
            free(current);
            printf("Event deleted successfully.\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Event with code %d not found.\n", event_code);
}

int isValid_event_code(int event_code)
{
    return event_code >= 0 && event_code <= 99;
}

int isValid_event_name(const char *event_name)
{
    return strlen(event_name) < MAX_NAME_LENGTH;
}

int isValid_competitor_count(int competitor_count)
{
    return competitor_count >= 10 && competitor_count <= 99;
}

int isValid_gender(char gender)
{
    return gender == 'M' || gender == 'W' || gender == 'X';
}
