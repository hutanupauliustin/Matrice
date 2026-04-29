#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
//#include "complex.h"      //trebuie biblioteca basic pt asta

#define POZITIVE_DEFINED  0b10000000
#define NEGATIVE_DEFINED  0b01000000
#define SEMI_DEFINED      0b00100000
#define SPARSE            0b00010000
#define TRASNPOSE         0b00001000
#define UPPER             0b00000100
#define LOWER             0b00000010
#define ORTHOGONAL        0b00000001

#define DIAGONAL          0b00000011
#define LEFT              0b00000010
#define RIGHT             0b00000100

const int ZERO_INT = 0;
const float ZERO_FLOAT = 0.0f; 

const char* error_msg[] = {"accesing inexisting index","incompatible matrix sizes","inexisting determinant of matrix"};

typedef enum{
INT,
FLOAT,
//COMPLEX
} data_type;

typedef struct {

    uint16_t rows,columns;
    void *data;
    uint8_t flag;
    data_type type;

} matrix;

matrix create_matrix( data_type type , uint16_t rows, uint16_t columns){
    
    matrix A;
    A.rows = rows;
    A.columns = columns;
     A.type = type;
    switch(type){
        case INT :  
            A.data = malloc( sizeof(int) * rows *columns);
            break;
        case FLOAT :
            A.data = malloc( sizeof(float) * rows *columns);
            break;
        //case COMPLEX :
        //    A.data = malloc( sizeof(complex) * rows *columns);
        //    break;
    }
   
    return A;

}



matrix create_matrix_filled( size_t type_size , uint16_t rows, uint16_t columns){       //are nevoie de al treilea parametru dar depinde de tip, nu stiu cum sa fac
                                                                                        //poate mai bine merg mai multe fucntii pentru fiecare tip de date (momentan 3)    
    matrix A;
    A.rows = rows;
    A.columns = columns;
    A.data = malloc( sizeof(type_size) * rows *columns);

    //for(int i = 0;i < rows*columns;i++) A.data[i] = const;

    return A;

}

void *at(matrix *A, uint16_t r, uint16_t c){

    if( r >= A->rows || c >= A->columns){
        printf(error_msg[0]);
        return NULL;
    }

    if( A->flag & TRASNPOSE){
        uint16_t temp;
        temp = c;
        c = r;
        r = temp;
    }

    size_t element_size;

    switch(A->type){
        case INT: 
            if((A->flag & UPPER) && (r > c)) 
                return (void*)&ZERO_INT;
            if((A->flag & LOWER) && (r < c))
                return (void*)&ZERO_INT;

            element_size = sizeof(int);
            return (int*)(A->data + (r*A->columns + c )*element_size); 

            break;

        case FLOAT: 
            if((A->flag & UPPER) && (r > c)) 
                return (void*)&ZERO_FLOAT;
            if((A->flag & LOWER) && (r < c))
                return (void*)&ZERO_FLOAT;

            element_size = sizeof(float);
            return (int*)(A->data + (r*A->columns + c )*element_size); 

            break;

        //restul tipurilor
    }

    return NULL;

}


matrix sum(matrix *A, matrix *B, matrix *SUM){  //trebuie o functie pentru fiecare caz de upper,lower,diagonal, unde contorii stiu sa sara direct peste valorile "0". 
;                                               //speranta ar fii sa fie bine structurat codul ca genul asta de matrice sa nu trebuiasca sa aibe cu adevarat 0, sa ramana cu garbage data
}                                               //dar codul sa nu incerce niciodata sa il acceseze



