
#ifndef __LIST_H__
#define __LIST_H__

typedef struct ElementStruct Element;

struct ElementStruct {
    void* content;
    Element* next;
};

typedef struct {
    Element *first;
    Element *current;
    int count;
} List;


#endif /* __LIST_H__ */
