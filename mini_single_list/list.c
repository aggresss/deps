#include <stdio.h>
#include <stdlib.h>

typedef struct ListElementStruct {
    void* content;
    struct ListElementStruct* next;
} ListElement;

typedef struct {
    ListElement *first;
    int count;
} List;

#define ListInitializer {NULL, 0};

ListElement* ListNext(List* aList, ListElement** pos)
{
    return *pos = (*pos == NULL) ? aList->first : (*pos)->next;
}

void ListAppend(List* aList, void* content)
{
    ListElement * prev = NULL, *current = NULL;
    ListElement* newel = malloc(sizeof(ListElement));
    newel->content = content;
    newel->next = NULL;
    if (aList->first) {
        while (ListNext(aList, &current) != NULL) {
            prev = current;
        }
        prev->next = newel;
    } else {
        aList->first = newel;
    }
    ++(aList->count);
}

int ListRemove(List* aList, void* content)
{
    int rc = -1;
    ListElement *prev = NULL, *current = NULL;
    while (ListNext(aList, &current) != NULL) {
        if (current->content == content) {
            if (prev) {
                prev->next = current->next;
            } else {
                aList->first = current->next;
            }
            free(current);
            rc = 0; --(aList->count); break;
        }
        prev = current;
    }
    return rc;
}

ListElement* ListFind(List* aList, void* content)
{
    ListElement *rc = NULL, *current = NULL;
    while (ListNext(aList, &current) != NULL) {
        if (current->content == content) {
            rc = current;
            break;
        }
    }
    return rc;
}

int main(int argc, char* argv[])
{
    ListElement *current;

    char seq_num[] = "0123456789";
    List l = ListInitializer;

    /* Test ListAppend */
    ListAppend(&l, &seq_num[0]);
    ListAppend(&l, &seq_num[2]);
    ListAppend(&l, &seq_num[3]);
    ListAppend(&l, &seq_num[8]);

    current = NULL;
    while (ListNext(&l, &current) != NULL) {
        printf("%c\n", *(char *)(current->content));
    }
    printf("list count: %d\n", l.count);

    /* Test ListRemove */
    ListRemove(&l, &seq_num[0]);
    ListRemove(&l, &seq_num[8]);

    current = NULL;
    while (ListNext(&l, &current) != NULL) {
        printf("%c\n", *(char *)(current->content));
    }
    printf("list count: %d\n", l.count);

    /* Test ListFind */
    current = ListFind(&l, &seq_num[3]);
    if (current) {
        printf("list find: %c\n", *(char *)(current->content));
    }

    return 0;
}
