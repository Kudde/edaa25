#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "error.h"
#include "poly.h"


typedef struct term_t {
        int ex;
        double co;
} term_t;

typedef struct poly_t {
        term_t* terms;
        int size;

} poly_t;

poly_t* new_poly_from_string(const char* source){

        const char* c = source;

        poly_t* poly = malloc(sizeof(poly_t));
        poly->terms = malloc(sizeof(term_t));
        poly->size = 0;

        double  coe = 1;
        int     exp = 1;
        char    op = '+';




        size_t i = -1;
        while (c[++i] != '\0') {


                if (isspace(c[i]))
                        continue;


                // OP
                if (c[i] == '+' || c[i] == '-')
                        op = c[i++];

                while (isspace(c[i]))
                        i++;

                // Coefficient
                if (isdigit(c[i])) {
                        sscanf(&c[i], "%lf", &coe);
                        if (op == '-') coe = -coe;
                        while (isdigit(c[i])) i++;
                }

                // Exponent
                if (c[i] == 'x') {
                        if (c[i+1] == '^') {
                                i += 2;
                                sscanf(&c[i], "%d", &exp);
                                while (isdigit(c[i])) i++;

                        } else {
                                i++;
                                exp = 1;
                        }

                } else
                        exp = 0;


                        // printf("coe = %f\n", coe);
                        // printf("exp = %d\n", exp);
                        // printf("i = %zu \n", i);
                // Add
                poly->size++;
                poly->terms = realloc(poly->terms, poly->size * sizeof(term_t));
                poly->terms[poly->size - 1].ex = exp;
                poly->terms[poly->size - 1].co = coe;



                if (c[i] == '\0')
                        break;


        }
        //printf("%s\n", "=========");

        return poly;
}

void free_poly(poly_t* poly) {
        free(poly->terms);
        free(poly);

}

poly_t* mul(poly_t* a, poly_t* b) {

        poly_t* c = malloc(sizeof(poly_t));
        c->terms = malloc(a->size * b->size * sizeof(term_t));

        int k = 0;
        for (int i = 0; i < a->size; i++) {
                for (int j = 0; j < b->size; j++, k++) {


                        //printf("%.0fx^%d * %.1fx^%d =  ",a->terms[i].co, a->terms[i].ex, b->terms[j].co , b->terms[j].ex);
                        if (c->terms[k-1].ex == a->terms[i].ex + b->terms[j].ex)
                                c->terms[k-1].co += a->terms[i].co * b->terms[j].co;
                        else {
                                c->terms[k].co = a->terms[i].co * b->terms[j].co;
                                c->terms[k].ex = a->terms[i].ex + b->terms[j].ex;
                        }

                        //printf("%.0fx^ %d\n", c->terms[a->terms[i].ex + b->terms[j].ex].co, c-> terms[a->terms[i].ex + b->terms[j].ex].ex);
                }
                c->size = k;

        }

	return c;


}

void print_poly(poly_t* poly) {
        for (size_t i = 0 ; i < poly->size ; i++) {
                int e = poly->terms[i].ex;
                double c = poly->terms[i].co;


                if (c == 0)
                        continue;

                if (c < 0) {
                        printf(" - ");
                        c = -c;

                } else if ( i != 0)
                        printf(" + ");

                if (e == 1) {
                        if (c == (int)c) printf("%dx", (int) c);
                        else printf("%fx", c);
                } else if (e != 0) {
                        if ((int) c != 1) {
                                if (c == (int)c) printf("%d", (int) c);
                                else printf("%f", c);
                        }


                        printf("x^%d", e);

                } else
                        printf("%.0f", c);



        }

        printf("\n");

}
