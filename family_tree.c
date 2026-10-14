#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char name[50];
    int age;
    struct Person* father;
    struct Person* mother;
} Person;

Person* create_person(const char* name, int age) {
    Person* new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    snprintf(new_person->name, sizeof(new_person->name), "%s", name);
    new_person->age = age;
    new_person->father = NULL;
    new_person->mother = NULL;

    return new_person;
}

void read_person_info(const char *role, char *name_out, int *age_out) {

    char age_text[20];

    printf("Enter name for %s: ", role);
    if (fgets(name_out, 50, stdin) == NULL) {
        name_out[0] = '\0';
        *age_out = 0;
        return;
    }

    name_out[strcspn(name_out, "\n")] = '\0';

    printf("Enter age for %s: ", role);
    if (fgets(age_text, sizeof(age_text), stdin) == NULL ||
        sscanf(age_text, "%d", age_out) != 1) {
        *age_out = 0;
    }
}



int main(void) {

    const char *roles[7] = {
        "Paternal Grandfather",
        "Paternal Grandmother",
        "Maternal Grandfather",
        "Maternal Grandmother",
        "Father",
        "Mother",
        "Yourself"
    };

    Person *people[7];
    char name[50];
    int age;

    for (int i = 0; i < 7; i++) {

        read_person_info(roles[i], name, &age);

        people[i] = create_person(name, age);

        if (people[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(people[j]);
            }
            return 1;
        }
    }

    printf("\n=== FAMILY MEMBERS ===\n");

    for (int i = 0; i < 7; i++) {
        printf("%s: %s | Age: %d\n",
               roles[i], people[i]->name, people[i]->age);
    }

    for (int i = 0; i < 7; i++) {
        free(people[i]);
    }

    return 0;
}
