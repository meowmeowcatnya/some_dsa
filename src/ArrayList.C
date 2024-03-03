#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct ArrayList {
    std::size_t capacity;
    std::size_t size;
    int* arr;
    int (*get) (ArrayList* list, size_t index);
    void (*set) (ArrayList* list, size_t index, int element);
    int (*length) (ArrayList* list);
    void (*push) (ArrayList* list, int element);
    int (*pop) (ArrayList* list);
};

int get(ArrayList* list, size_t index){
    if (index >= list->size) {
        printf("Index out of bounds. Exiting");
        exit(1);
    } else {
        return list->arr[index];
    }
}

void set(ArrayList* list, size_t index, int element) {
    if (index >= list->size) {
        printf("Index out of bounds. Exiting");
        exit(1);
    } else {
        list->arr[index] = element;
    }
}

int length(ArrayList* list) {
    return list->size;
}

void push(ArrayList* list, int element) {
    if (list->size < list->capacity) {
        list->arr[list->size] = element;
        list->size += 1;
    } else {
        void* ptr = malloc(2 * list->capacity * sizeof(int));
        if(ptr == NULL) {
            printf("Couldn't push since list is full and couldn't grow.");
            return;
        }
        int* newArr = (int*) ptr;
        for(size_t i = 0; i<list->size; i++) {
            newArr[i] = list->arr[i];
        }
        free(list->arr);
        newArr[list->size] = element;
        list->capacity = 2*list->capacity;
        list->size += 1;
        list->arr = newArr;
    }
}

int pop(ArrayList* list){
    if(list->size == 0) {
        printf("List is empty. Exiting");
        exit(1);
    }
    int element = list->arr[list->size-1];
    list->size -= 1;
    if(list->size < list->capacity / 4) {
        void* ptr = malloc(list->capacity/2 * sizeof(int));
        if(ptr == NULL){
            printf("Couldn't shrink list. Exiting");
            exit(1);
        }
        int* newArr = (int*) ptr;
        for(size_t i=0; i<list->size; i++){
            newArr[i]=list->arr[i];
        }
        free(list->arr);
        list->arr=newArr;
    }
    return element;
}

ArrayList arraylist_factory() {
    void* ptr = malloc(10*sizeof(int));
    if (ptr == NULL) {
        printf("initializing arraylist failed. Exiting");
        exit(1);
    } else {
        ArrayList arrayList = {.capacity = 10, .size = 0, .arr = (int*) ptr};
        arrayList.get = get;
        arrayList.length = length;
        arrayList.pop = pop;
        arrayList.push = push;
        arrayList.set = set;
        return arrayList;
    }
}

void destructor(ArrayList* list){
    free(list->arr);
}

int main(){
    ArrayList test = arraylist_factory();
    ArrayList* ptr = &test;
    for(size_t i=0; i<15; i++){
        test.push(ptr, i);
    }
    printf("length is %d\n", test.length(ptr));
    
    destructor(ptr);
}
