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

int getSquare(char** map, int y, int x, char voidS);
void print(char** map, int y_max, int x_max);
int normArea(int square);
list_t* newNode(int y, int x, int area);
void addListTail(list_t* head, list_t* node);
void printList(list_t* head);   //doesn't matter
list_t* getList(char** map, int y_max, int x_max, char voidS);
list_t* areaMax(list_t* head);
int printArea(char** map, int size, int y, int x, char voidS, char printS);
void start(char** map, int y_max, int x_max, char voidS, char printS);

//--------------------------------------------------------

int main() {
    char** map = malloc(sizeof(char*) * 11);
    for (size_t i = 0; i < 11; i++) {
        map[i] = malloc(28);
    }
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 27; j++) {
            map[i][j] = '.';
        }
    }

    for (size_t i = 0; i < 27; i++) {
        map[9][i] = '\0';
    }
    
    for (size_t i = 0; i < 10; i++) {
        map[i][27] = '\0';
    }

//----------------------TEST-----------------------

map[0][0] = 'o';
map[1][1] = 'o';
map[2][2] = 'o';
map[3][3] = 'o';
map[4][4] = 'o';
map[5][5] = 'o';
map[6][6] = 'o';
map[7][7] = 'o';
map[8][8] = 'o';
map[9][9] = 'o';
map[8][18] = 'o';
map[7][17] = 'o';
map[6][16] = 'o';
map[5][15] = 'o';
map[4][14] = 'o';
map[3][13] = 'o';
map[2][12] = 'o';
map[1][11] = 'o';
map[0][10] = 'o';
map[9][19] = 'o';

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
map[9][8] = 'o';
map[9][9] = 'o';
map[9][10] = 'o';
map[7][2] = 'o';

map[1][4] = 'o';
map[2][8] = 'o';
map[4][4] = 'o';
map[5][15] = 'o';
map[7][6] = 'o';
map[7][21] = 'o';
map[8][2] = 'o';
map[8][10] = 'o';
map[3][23] = 'o';

//-------------------------------------------------

    start(map, 9, 27, '.', '#');
    return(0);

}

//---------------------LOGIC-----------------------

void start(char** map, int y_max, int x_max, char voidS, char printS) {
    print(map, y_max, x_max);

    list_t* head = getList(map, y_max, x_max, voidS);
    list_t* max = areaMax(head);
    printArea(map, 0, max->y, max->x, voidS, printS);

    print(map, y_max, x_max);
    printList(max);
}

int getSquare(char** map, int y, int x, char voidS) {

    int size = 0;
    int flag = -0;

    if (map[y][x] != voidS)
    return(-1);

    while (flag == -0) {
        for (int i = x; i < x + size + 2; i++) {
            if (map[y+size+1][i] != voidS || map[y+size+1][i] == '\0')
                flag++;
        }
        for (int i = y; i < y + size + 1; i++) {
            if (map[i][x+size+1] != voidS || map[i][x+size+1] == '\0')
                flag++;
        }
        size++;
    }

    return(size);
}

int normArea(int square) {
    return(square*square);
}

list_t* getList(char** map, int y_max, int x_max, char voidS) {
    list_t* head = newNode(0, 0, normArea(getSquare(map, 0, 0, voidS)));
    int i = 0, j = 1;

    while (i < y_max) {
        while (j < x_max) {
            addListTail(head, newNode(i, j, normArea(getSquare(map, i, j, voidS))));
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
