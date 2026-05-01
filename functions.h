#include "matrice.h"

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

matrix sum(matrix *A, matrix *B){  //trebuie o functie pentru fiecare caz de upper,lower,diagonal, unde contorii stiu sa sara direct peste valorile "0". 
                                                //speranta ar fii sa fie bine structurat codul ca genul asta de matrice sa nu trebuiasca sa aibe cu adevarat 0, sa ramana cu garbage data
                                                //dar codul sa nu incerce niciodata sa il acceseze
    if( rows((*A)) != rows((*B)) || columns((*A)) != columns((*B)))  {
        printf(error_msg[1]);
        //return 0 matrix
    }

    data_type type_of_sum = (A->type > B->type) ? A->type : B->type;

    matrix S = create_matrix(type_of_sum, rows((*A)), columns((*B)));

    if( A->flag & DIAGONAL ){

        if(B->flag & DIAGONAL)
            S.flag |= DIAGONAL;
        else if (B->flag & UPPER)
            S.flag |= UPPER;
        else if (B->flag & LOWER)
            S.flag |= LOWER;
    }

    else if (A->flag & UPPER){

        if(B->flag * DIAGONAL)
            S.flag |= UPPER;
        else if( B->flag |= UPPER)
            S.flag |= UPPER;
    }

    else if (A->flag & LOWER){

        if(B->flag * DIAGONAL)
            S.flag |= LOWER;
        else if( B->flag |= LOWER)
            S.flag |= LOWER;
    }

    S.flag |= TRASNPOSE;

    for(int i = 0; i < S.rows; i++){
        for(int j = 0; j < S.columns ; j++){

            void *pA = at(A,i,j);
            void *pB = at(B,i,j);
            void *pS = at(&S,i,j);

            switch ((S.type))
            {
            case INT:
                *(int*)pS = *(int*)pA + *(int*)pB;
                break;
            
            case FLOAT:
                *(float*)pS = *(float*)pA + *(float*)pB;
                break;
            }

        }
    }


                                      
}
