#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int key;
  int data[3];
  int info[7];
} object;

typedef struct {
  object *objects;
  int capacity;
  int size;
} heap;

//creates heap of size 20 and links objects to heap
heap *buildHeap(int capacity) {
    heap *h = (heap*)malloc(sizeof(heap));
    h->objects = (object *)malloc(capacity * sizeof(object));
    h->capacity = capacity;
    h->size = 0;
    return h;
}

//checks if heap is full
int isFull(heap *h) { 
    return h->size == h->capacity; 
}

//insert to heap
void insert(heap *h, object obj) {
    if (isFull(h)){
        return;
    }

    h->objects[h->size] = obj;

    h->size++;
}

//downheap sort
void sort(heap *h) {
    int current2 = 15; // oragnise children left to right
    for(int i = 0; i < 5; i++){
        int current = current2;
        while (current != 0 && h->objects[current].key <= h->objects[(current - 1) / 2].key) {
            object temp = h->objects[(current - 1) / 2];
            h->objects[(current - 1) / 2] = h->objects[current];
            h->objects[current] = temp;

            current = (current - 1) / 2;
        }
        current2 = current2 + 1;
    }
    current2 = 10; // oragnise children left to right
    for(int i = 0; i < 5; i++){
        int current = current2;
        while (current != 0 && h->objects[current].key <= h->objects[(current - 1) / 2].key) {
            object temp = h->objects[(current - 1) / 2];
            h->objects[(current - 1) / 2] = h->objects[current];
            h->objects[current] = temp;

            current = (current - 1) / 2;
        }
        current2 = current2 + 1;
    }
    current2 = 10; //organise parents
    for(int i = 0; i < 10; i++){
        int current = current2;
        while (current != 0 && h->objects[current].key <= h->objects[(current - 1) / 2].key) {
            object temp = h->objects[(current - 1) / 2];
            h->objects[(current - 1) / 2] = h->objects[current];
            h->objects[current] = temp;

            current = (current - 1) / 2;
        }
        current2 = current2 - 1;
    }
}

//print heap
void printHeap(heap *h) {
    for (int i = 0; i < h->size; i++) {
        //printf("%-2d | ", i+1);
        //printf("%-3d | ", h->objects[i].key); //print key
    
        for (int j = 0; j < 3; j++){
            if(h->objects[i].data[j] < 10){
                printf("0%d ", h->objects[i].data[j]);
            }
            else{
                printf("%d ", h->objects[i].data[j]);
            }
        }

        for (int j = 0; j < 7; j++){
            if(h->objects[i].info[j] < 10){
                printf("0%d ", h->objects[i].info[j]);
            }
            else{
                printf("%d ", h->objects[i].info[j]);
            }
        }
        printf("\n");
    }
}

//main
int main() {
    int capacity = 20;
    heap *h = buildHeap(capacity);

    FILE *fp = fopen("f.dat", "r"); // read file

    for (int i = 0; i < 200; i++) { // read data
        object obj;
        int key = 0;
        for (int j = 0; j < 3; j++) {
            fscanf(fp, "%d", &obj.key);
            obj.data[j] = obj.key;
            key += obj.key;
        }
        obj.key = key; // add first 3 digets for key

        for (int j = 0; j < 7; j++){
            fscanf(fp, "%d", &obj.info[j]);
        }
        insert(h, obj); // insert data into heap
    }

    sort(h);
    
    printHeap(h);

    fclose(fp);

    return 0;
}