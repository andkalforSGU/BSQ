#include <stdlib.h>
#include <stdio.h>

int getSquare(char** map, int size, int y, int x);
void test(char** map);
void print(char** map);
void facets(char** map, int y, int x);

int main() {
    char** map = malloc(sizeof(char*) * 6);
    for (size_t i = 0; i < 6; i++) {
        map[i] = malloc(11);
    }
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 10; j++) {
            map[i][j] = 'k';
        }
    }

    for (size_t i = 0; i < 11; i++) {
        map[5][i] = '\0';
    }
    
    for (size_t i = 0; i < 6; i++) {
        map[i][10] = '\0';
    }
//----------------------TEST-----------------------

map[2][5] = '+';
map[4][8] = '+';
print(map);
// test(map);
// printf("%d\n", out);
facets(map, 5, 10);
print(map);
int out = getSquare(map, 0, 0, 0);
print(map);

//-------------------------------------------------
    return(0);
}

int getSquare(char** map, int size, int y, int x) {
    
    map[y][x] = 'O';


    if (map[y+1][x+1] != '\0' && map[y+1][x+1] == 'k')            //right-down
        size += getSquare(map, size+1, y+1, x+1); 
    if (map[y][x+1] != '\0' && map[y][x+1] == 'k')                //right
        size += getSquare(map, size+1, y, x+1);
    if (map[y+1][x] != '\0' && map[y+1][x] == 'k')                //down
        size += getSquare(map, size+1, y+1, x); 

    return(size);
}

void test(char** map) {
//     printf("%c\n", *(*(map)+1));   //right
//     printf("%c\n", *(*(map+1)+1)); //down-rigth
//     printf("%c\n", *(*(map+1)));   //down

    // for (size_t i = 0; i < 4; i++) {
    //     printf("%c", **(map+i));
    // }
    // map[0][0] = 'X';
}

void print(char** map) {

    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 10; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
}

void facets(char** map, int y, int x) {
    for (size_t i = 0; i < y; i++) {
        for (size_t j = 0; j < x; j++) {
            if (map[i][j] == '+') {
                for (int k = 0; k < x; k++) {
                    if (map[i][k] != '+' && map[i][k] != '-' && map[i][k] != '|')
                        map[i][k] = '-';
                    else if (map[i][k] == '|')
                        map[i][k] = '+';
                }
                    
                for (int k = 0; k < y; k++) {
                    if (map[k][j] != '+' && map[y][j] != '-' && map[y][j] != '|')
                        map[k][j] = '|';
                    else if (map[k][j] == '-')
                        map[k][j] = '+';
                }
            }
        }
    }
}















