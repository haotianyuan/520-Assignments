#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, 0);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_copy(da);
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

  assert(da->buffer != NULL);
  assert(b >= a);

  DynamicArray * result = DynamicArray_new();

  for (int i=a; i<b; i++) {
      DynamicArray_push(result,DynamicArray_get(da, i));
  }

  return result;

}

double DynamicArray_min ( const DynamicArray * da ){
    assert(da->buffer != NULL);
    double res=DynamicArray_get(da,0);
    for(int i=1;i<DynamicArray_size(da);i++){
        if(DynamicArray_get(da,i)<res){
            res=DynamicArray_get(da,i);
        }
    }
    return res;
}

double DynamicArray_max ( const DynamicArray * da ){
    assert(da->buffer != NULL);
    double res=DynamicArray_get(da,0);
    for(int i=1;i<DynamicArray_size(da);i++){
        if(DynamicArray_get(da,i)>res){
            res=DynamicArray_get(da,i);
        }
    }
    return res;
}

double DynamicArray_mean ( const DynamicArray * da ){
    assert(da->buffer != NULL);
    double res=DynamicArray_get(da,0);
    for(int i=1;i<DynamicArray_size(da);i++){
        res+=DynamicArray_get(da,i);
    }
    return res/DynamicArray_size(da);
}

double DynamicArray_median (const DynamicArray * da ){
    assert(da->buffer != NULL);
    DynamicArray * temp = DynamicArray_new();
    for(int i=0;i<DynamicArray_size(da);i++){
        DynamicArray_push(temp,DynamicArray_get(da,i));
    }

    for(int i=0;i<DynamicArray_size(da)-1;i++){
        for(int j=0;j<DynamicArray_size(da)-1-i;j++){
            if(DynamicArray_get(temp,j)>DynamicArray_get(temp,j+1)){
                double temp_number=DynamicArray_get(temp,j);
                DynamicArray_set(temp,j,DynamicArray_get(temp,j+1));
                DynamicArray_set(temp,j+1,temp_number);
            }
        }
    }  
    double res=0;
    if(DynamicArray_size(da)%2==0){
        res=DynamicArray_get(temp,DynamicArray_size(da)/2);
        
        res+=DynamicArray_get(temp,DynamicArray_size(da)/2-1);
        res=res/2;
    }
    else{
        res=DynamicArray_get(temp,(DynamicArray_size(da)-1)/2);
    }
    DynamicArray_destroy(temp);
    return res;  
}

double DynamicArray_sum( const DynamicArray * da ){
    if(DynamicArray_size(da)==0){
        return 0;
    }

    double res=DynamicArray_get(da,0);
    for(int i=1;i<DynamicArray_size(da);i++){
        res+=DynamicArray_get(da,i);
    }
    return res;
}

double DynamicArray_first ( const DynamicArray * da ){
    assert(DynamicArray_size(da) > 0);
    return DynamicArray_get(da, 0);
}

double DynamicArray_last ( const DynamicArray * da ){
    assert(DynamicArray_size(da) > 0);
    return DynamicArray_get(da, DynamicArray_size(da)-1);
}

DynamicArray * DynamicArray_copy ( const DynamicArray * da ){
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_new();
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, DynamicArray_get(da, i));
    }
    return result;
}

DynamicArray * DynamicArray_range ( double a, double b, double step){
    
    if(step<0 && b>a){
        DynamicArray * da = DynamicArray_new();
        return da;
    }

    if(step==0){
        DynamicArray * da = DynamicArray_new();
        return da;
    }

    DynamicArray * da = DynamicArray_new();
    
    if(step>0){
        while(a<=b){
            //printf("%lf \n",a);
            DynamicArray_push(da,a);
            a=a+step;
        }
    }

    if(step<0){
        while(a>=b){
            DynamicArray_push(da,a);
            a=a+step;
        }
    }
    return da;
}

DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b ){
    assert(a->buffer != NULL);
    assert(b->buffer != NULL);

    DynamicArray * result = DynamicArray_new();
    for(int i=0;i<DynamicArray_size(a);i++){
        DynamicArray_push(result,DynamicArray_get(a,i));
    }

    for(int i=0;i<DynamicArray_size(b);i++){
        DynamicArray_push(result,DynamicArray_get(b,i));
    }
    return result;
}

DynamicArray * DynamicArray_take (const DynamicArray * a, int b){
    if(b>=0){
        DynamicArray * result = DynamicArray_new();
        if(b<DynamicArray_size(a)){
            for(int i=0;i<b;i++){
                DynamicArray_push(result,DynamicArray_get(a,i));
            }
        }
        else{
            for(int i=0;i<DynamicArray_size(a);i++){
                DynamicArray_push(result,DynamicArray_get(a,i));
            }
        }
        
        for(int i=DynamicArray_size(a);i<b;i++){
            
            DynamicArray_push(result,DynamicArray_get(a,0));
        }


        return result;
    }
    else{
        DynamicArray * result = DynamicArray_new();
        //int index=-b;
        int len=-b;
        int index=DynamicArray_size(a)-1;
        if(len<DynamicArray_size(a)){
            for(int i=0;i<len;i++){
                //result.push(DynamicArray_get(a,index));
                printf("%lf\n",DynamicArray_get(a,index));
                DynamicArray_push(result,DynamicArray_get(a,index));
                index--;
            }
        }
        else{
            for(int i=DynamicArray_size(a)-1;i>=0;i--){
                
                DynamicArray_push(result,DynamicArray_get(a,i));
            }

            for(int i=0;i<len-DynamicArray_size(a);i++){
                DynamicArray_push(result,0);
            }
        }

        return result;
    }
}





