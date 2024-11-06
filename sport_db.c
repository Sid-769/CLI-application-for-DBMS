#include <stdio.h>
#include "sport_db.h"
#include "sport_db_event.h"
#include "sport_db_athlete.h"

void print_menu()
{

    printf("\nCommands:\n");
    printf("\nCommands:\n");
    printf("h - Print help\n");
    printf("q - Quit\n");
    printf("e - Control events\n");
    printf("a - Control athletes\n");

    printf("\nFor events ie. option 'e':\n");
    printf("  i - Insert a new event\n");
    printf("  s - Search for an event\n");
    printf("  u - Update an event\n");
    printf("  p - Print all events\n");
    printf("  e - Erase an event\n");

    printf("\nFor athletes ie. option 'a':\n");
    printf("  i - Insert a new athlete\n");
    printf("  s - Search for an athlete\n");
    printf("  u - Update an athlete\n");
    printf("  p - Print all athlete\n");
    printf("  e - Erase an athlete\n");
}

void print_help()
{
    print_menu();
}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    char command;
    char event_command;
    char athlete_command;
    int event_code, athlete_code;

    printf("*************************\n");
    printf("* 2211 Summer Olympics! *\n");
    printf("*************************\n");

    while (1)
    {
        printf("\nEnter operation code: ");
        scanf(" %c", &command);
        clear_input_buffer();

        switch (command)
        {
        case 'h':
            print_help();
            break;
        case 'q':
            return 0;
        case 'e':
            printf("\nEnter event operation code: ");
            scanf(" %c", &event_command);
            clear_input_buffer();
            switch (event_command)
            {
            case 'i':
                add_event();
                break;
            case 's':
                search_event();
                break;
            case 'u':
                update_event();
                break;
            case 'p':
                display_events();
                break;
            case 'e':
                delete_event();
                break;
            default:
                printf("Invalid event command. Try again.\n");
            }
            break;
        case 'a':
            printf("\nEnter athlete operation code: ");
            scanf(" %c", &athlete_command);
            clear_input_buffer();
            switch (athlete_command)
            {
            case 'i':
                printf("Enter event code to add athlete: ");
                scanf("%d", &event_code);
                clear_input_buffer();
                add_athlete(event_code);
                break;
            case 's':
                printf("Enter event code to search athlete: ");
                scanf("%d", &event_code);
                printf("Enter athlete code to search: ");
                scanf("%d", &athlete_code);
                clear_input_buffer();
                search_athlete(event_code, athlete_code);
                break;
            case 'u':
                printf("Enter event code to update athlete: ");
                scanf("%d", &event_code);
                printf("Enter athlete code to update: ");
                scanf("%d", &athlete_code);
                clear_input_buffer();
                update_athlete(event_code, athlete_code);
                break;
            case 'p':
                printf("Enter event code to list athletes: ");
                scanf("%d", &event_code);
                clear_input_buffer();
                display_athletes(event_code);
                break;
            case 'e':
                printf("Enter event code to delete athlete: ");
                scanf("%d", &event_code);
                printf("Enter athlete code to delete: ");
                scanf("%d", &athlete_code);
                clear_input_buffer();
                delete_athlete(event_code, athlete_code);
                break;
            default:
                printf("Invalid athlete command. Try again.\n");
            }
            break;
        default:
            printf("Invalid command. Try again.\n");
        }
    }
    return 0;
}