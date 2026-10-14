#include <stdio.h>
#include <stdlib.h>

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

int main(void) {
    Person* me = create_person("Basy", 19);
    if (me == NULL) {
        return 1;
    }

    printf("Name: %s\n", me->name);
    printf("Age: %d\n", me->age);
    free(me);

    return 0;
}
