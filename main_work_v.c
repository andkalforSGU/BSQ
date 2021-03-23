#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

//-----------------------SRUCT---------------------------

typedef struct list {
    int x;
    int y;
    int area;
    struct list* next;
} list_t;

//--------------------DECLARATIONS------------------------

int getSquare(char** map, int size, int y, int x, char wallS, char voidS);
void print(char** map, int y_max, int x_max);
int normArea(int square);
list_t* newNode(int y, int x, int area);
void addListTail(list_t* head, list_t* node);
void printList(list_t* head);   //doesn't matter
list_t* getList(char** map, int y_max, int x_max, char wallS, char voidS);
list_t* areaMax(list_t* head);
int printArea(char** map, int size, int y, int x, char voidS, char printS);
void start(char**, int y_max, int x_max, char wallS, char voidS, char printS);

//--------------------------------------------------------

int main() {
    char** map = malloc(sizeof(char*) * 11);
    for (size_t i = 0; i < 11; i++) {
        map[i] = malloc(21);
    }
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 20; j++) {
            map[i][j] = '.';
        }
    }

    for (size_t i = 0; i < 11; i++) {
        map[10][i] = '\0';
    }
    
    for (size_t i = 0; i < 11; i++) {
        map[i][20] = '\0';
    }

//----------------------TEST-----------------------

map[1][1] = 'o';
map[3][1] = 'o';
map[3][8] = 'o';
map[4][5] = 'o';
map[4][4] = 'o';
map[7][4] = 'o';
map[4][9] = 'o';
map[6][9] = 'o';
map[7][8] = 'o';
map[1][10] = 'o';
map[3][11] = 'o';
map[1][13] = 'o';
map[3][17] = 'o';
map[4][16] = 'o';
map[4][14] = 'o';
map[7][13] = 'o';
map[4][18] = 'o';
map[6][18] = 'o';
map[7][17] = 'o';
map[0][2] = 'o';
map[2][2] = 'o';
map[2][9] = 'o';
map[3][6] = 'o';
map[3][5] = 'o';
map[6][5] = 'o';
map[3][10] = 'o';
map[5][10] = 'o';
map[6][9] = 'o';
map[0][11] = 'o';
map[2][12] = 'o';
map[0][14] = 'o';
map[2][18] = 'o';
map[3][17] = 'o';
map[3][15] = 'o';
map[6][14] = 'o';
map[3][19] = 'o';
map[5][19] = 'o';
map[6][18] = 'o';
map[7][17] = 'o';
map[7][15] = 'o';
map[8][14] = 'o';
map[8][19] = 'o';
map[9][19] = 'o';
map[9][18] = 'o';

//-------------------------------------------------

    start(map, 10, 20, 'o', '.', 'X');

    return(0);
}

//---------------------LOGIC-----------------------

void start(char** map, int y_max, int x_max, char wallS, char voidS, char printS) {
    print(map, y_max, x_max);

    list_t* head = getList(map, y_max, x_max, wallS, voidS);
    list_t* max = areaMax(head);
    printArea(map, 0, max->y, max->x, voidS, printS);

    print(map, y_max, x_max);
    printList(max);
}

int getSquare(char** map, int size, int y, int x, char wallS, char voidS) {

    if (map[y][x] == wallS)
        return(-1);
    for (int i = x; i < x + size + 2; i++) {
        if (map[y+size+1][i] != voidS || map[y+size+1][i] == '\0')
            return(size);
    }
    for (int i = y; i < y + size + 1; i++) {
        if (map[i][x+size+1] != voidS || map[i][x+size+1] == '\0')
            return(size);
    }
    size = getSquare(map, size+1, y, x, wallS, voidS);
    return(size);
}

int normArea(int square) {
    return((square+1)*(square+1));
}

list_t* getList(char** map, int y_max, int x_max, char wallS, char voidS) {
    list_t* head = newNode(0, 0, normArea(getSquare(map, 0, 0, 0, wallS, voidS)));
    int i = 0, j = 1;

    while (i < y_max) {
        while (j < x_max) {
            addListTail(head, newNode(i, j, normArea(getSquare(map, 0, i, j, wallS, voidS))));
            j++;
        }
        j = 0;
        i++;
    }
    
    return(head);
}

int printArea(char** map, int size, int y, int x, char voidS, char printS) {
    map[y][x] = printS;

    for (int i = x; i < x + size + 2; i++) {
        if (map[y+size+1][i] != voidS || map[y+size+1][i] == '\0')
            return(0);
    }
    for (int i = y; i < y + size + 1; i++) {
        if (map[i][x+size+1] != voidS || map[i][x+size+1] == '\0')
            return(0);
    }
    for (int i = y; i < y + size + 1; i++)                  //P
        map[i][x+size+1] = printS;                          //R
    for (int i = x; i < x + size + 2; i++)                  //I
        map[y+size+1][i] = printS;                          //N
    printArea(map, size+1, y, x, voidS, printS);            //T
    return(0);
}

//---------------------PRINT----------------------

void print(char** map, int y_max, int x_max) {

    for (size_t i = 0; i < y_max; i++) {
        for (size_t j = 0; j < x_max; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
}

//----------------------LIST----------------------

list_t* newNode(int y, int x, int area) {
    list_t* node = (list_t*)malloc(sizeof(list_t));
    node->next = NULL;
    node->y = y;
    node->x = x;
    node->area = area;

    return(node);
}

void addListTail(list_t* head, list_t* node) {
    list_t* copy = head;
    while (copy->next != NULL) {
        copy = copy->next;
    }
    copy->next = node;
}

void printList(list_t* head) {
    list_t* copy = head;
    while (copy != NULL) {
        printf("  x  -- %d\n", copy->x);
        printf("  y  -- %d\n", copy->y);
        printf("area -- %d\n\n", copy->area);
        copy = copy->next;
    }
}

list_t* areaMax(list_t* head) {
    list_t* copy = head;
    int max = copy->area;
    int x = copy->x;
    int y = copy->y;

    while (copy != NULL) {
        if (copy->area > max) {
            max = copy->area;
            x = copy->x;
            y = copy->y;
        }
        copy = copy->next;
    }
    list_t* node = newNode(y, x, max);
    return(node);
}
