#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

//-----------------------SRUCT---------------------------

typedef struct  list {
	int value_y;
    int value_x;
    int area;
	struct list *next;
} list_t;

//--------------------DECLARATIONS------------------------

int getSquare(char** map, int size, int y, int x);
void test(char** map);
void print(char** map);
void facets(char** map, int y, int x);
list_t *new_list_node(int y, int x, int area);
int		add_list_tail(list_t *head, list_t *new_node);
int normArea(int square);
list_t* getListHead(char** map, int y, int x);
void	print_list(list_t *head);
void getList(char** map, list_t *head, int i, int j, int y, int x);

//--------------------------------------------------------

int main() {
    char** map = malloc(sizeof(char*) * 6);
    for (size_t i = 0; i < 6; i++) {
        map[i] = malloc(11);
    }
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 10; j++) {
            map[i][j] = '.';
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
// int out = getSquare(map, 0, 1, 7);
// print(map);
// printf("%d", normArea(out));

//list_t *head = getListHead(map, 5, 10);
list_t *head1 = new_list_node(0, 0, normArea(getSquare(map, 0, 0, 0)));
print(map);
list_t *head = new_list_node(0, 6, normArea(getSquare(map, 0, 0, 6)));
print(map);
//list_t *head = new_list_node(4, 9, normArea(getSquare(map, 0, 4, 9)));
print(map);
//list_t *head = new_list_node(4, 5, normArea(getSquare(map, 0, 4, 5)));
print(map);

//print_list(head1);

//-------------------------------------------------

    return(0);
}

//---------------------LOGIC-----------------------

int getSquare(char** map, int size, int y, int x) {

    map[y][x] = 'x';

    for (int i = x; i < x + size + 2; i++) {
        if (map[y+size+1][i] != '.' || map[y+size+1][i] == '\0')
            return(size);
    }
    for (int i = y; i < y + size + 1; i++) {
        if (map[i][x+size+1] != '.' || map[i][x+size+1] == '\0')
            return(size);
    }
    for (int i = y; i < y + size + 1; i++) 
        map[i][x+size+1] = 'x';
    for (int i = x; i < x + size + 2; i++) 
        map[y+size+1][i] = 'x';

    size = getSquare(map, size+1, y, x);
    return(size);
}

list_t* getListHead(char** map, int y, int x) {
    list_t* head = new_list_node(-0, -0, -0);
    int i = 0, j = 0, key = 0;
    while (i < y - 1) {
        while (j < x - 1) {
            if (map[i][j] == '.') {
                head->value_y = i;
                head->value_x = j;
                head->area = normArea(getSquare(map, 0, i, j));
                key = -1;
                break;
            }
            j++;
        }
        if (key == -1)
            break;
        i++;
    }
    print_list(head);
    getList(map, head, i, j, y, x);
    return(head);
}

void getList(char** map, list_t *head, int i, int j, int y, int x) {
    while (i < y - 1) {
        while (j < x - 1) {
            if (map[i][j] == '+') {
                j++;
                continue;
            } else {
                add_list_tail(head, new_list_node(i, j, normArea(getSquare(map, 0, i, j))));
            }
            j++;
        }
        i++;
    }
}

int normArea(int square) {
    return((square+1)*(square+1));
}

//---------------------PRINT----------------------

void print(char** map) {

    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 10; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
}

//----------------------LIST----------------------

list_t	*new_list_node(int y, int x, int area)
{
	list_t	*node;

	node = NULL;
	node = (list_t*)malloc(sizeof(list_t*));
	if (node == NULL)
	{
		write(2, "Can't create list-node.", 23);
		return (node);
	}
	node->next = NULL;
    node->area = area;
    node->value_y = y;
    node->value_x = x;
	return (node);
}

int		add_list_tail(list_t *head, list_t *new_node)
{
	list_t	*copy;

	copy = head;
	while (copy->next != NULL)
		copy = copy->next;
	copy->next = new_node;
	return (0);
}

void	print_list(list_t *head)
{
	list_t	*copy;

	copy = head;
	while (copy != NULL)
	{
		printf("  y  -- %d\n", copy->value_y);
        printf("  x  -- %d\n", copy->value_x);
        printf("area -- %d\n\n", copy->area);
		copy = copy->next;
	}
}