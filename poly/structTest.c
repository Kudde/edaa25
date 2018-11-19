#include <stdio.h>

struct point_t {
        double x;               // x and y are members of the struct
        double y;
}

typedef struct {
        double x;
        double y;
} point2_t;

int main(void) {

        struct point_t pt, *ptr;
        point2_t pt2, *ptr2;

        ptr2 = malloc(sizeof(point2_t)); // ptr2 is stored in the heap until it's freed while ptr is stored on the stack

        (*ptr).x = 2.2;
        (*ptr).y = 13.37;

        ptr2->x = 4.2;
        ptr2->y = 16.0;


        printf("ptr %f, %f\n",(*ptr).x, (*ptr).y);
        printf("ptr2 %f, %f\n",ptr->x, ptr->y;

        return 0;
}
