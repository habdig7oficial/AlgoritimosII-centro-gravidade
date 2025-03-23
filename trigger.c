/* 
    Copyright © 2025 Mateus Felipe da Silveira Vieira, Thiago Brito Oliveira dos Santos	
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>5.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lib.h"

#include "stdbool.h"
#include "math.h"

double *sum_matrix(int len_x, int len_y, double matrix[len_x][len_y], bool is_row){
    double *res_sum = malloc(sizeof(double) * (is_row? len_x : len_y)); /* Alloc necessary memory checking if its row or column */

    /* 
        1 - Loop for row
        2 - Loop for column
    */
    if(is_row == true){
        for(int i = 0; i < len_x; i++){
            double internal_sum = 0;
            for(int j = 0; j < len_y; j++)
                internal_sum += matrix[i][j];
            res_sum[i] = internal_sum;
        }
    }
    else{
        for(int i = 0; i < len_y; i++){
            double internal_sum = 0;
            for(int j = 0; j < len_x; j++)
                internal_sum += matrix[j][i];
            res_sum[i] = internal_sum;
        }
    }

    return res_sum;
}

double sum_arr(double *arr, int len){
    double acc = 0;
    for(int i = 0; i < len; i++)
        acc += arr[i];
    return acc;
}

double *slice_arr(double *arr, int begin, int end){
    double *slice = malloc(sizeof(double) * (end - begin));
    for(int i = 0; i < (end - begin); i++){
        slice[i] = arr[i + begin];
    }
    /*
        printf("\n");
        for(int i = 0; i < (end - begin); i++)
            printf("%f\n", slice[i]);
    */

    return slice;
}

double *mass_arr(double arr[], int len){
    double *diff_arr = malloc(sizeof(double) * len);
    for(int i = 1; i <= len; i++){
        double before = sum_arr(slice_arr(arr, 0, i - 1), i);
        double after = sum_arr(slice_arr(arr, i, len), len - i);
        diff_arr[i - 1] = fabs(after - before);

        printf("|%f - %f| = %f\n\n", before, after, diff_arr[i - 1]);
    }
    return diff_arr;
}

struct Minimun{
    double value;
    int index;
};

struct Minimun min(double arr[], int len){
    struct Minimun res = {
        .value = arr[0],
        .index = 0
    };
    for(int i = 0; i < len ; i++)
        if(arr[i] < res.value){
            res.value = arr[i];
            res.index = i;
        }
        
    return res;
}

int main(int argc, char *argv[]){
    
    /* Check if first agument is NULL */
    if(argv[1] == NULL){
        printf("No argument provided, exiting...\n");
        return -1;
    }

    char *input_buffer = read_file(argv[1]);

    if(input_buffer == NULL){
        printf("No file provided, exiting...\n");
        return -1;
    }
    
    int len_x = atoi(&input_buffer[0]); /* Atoi casts char into int */
    int len_y = atoi(&input_buffer[2]); /* Atoi casts char into int */

    double matrix[len_x][len_y];

    input_buffer = &input_buffer[4]; /* Remove first line */

    cp_buffer_arr(input_buffer, len_x, len_y, matrix);

    double *sum_row = sum_matrix(len_x, len_y, matrix, true);
    double *sum_col = sum_matrix(len_x, len_y, matrix, false);

    printf("-- PROVIDED MATRIX --\n");
    print_matrix(len_x, len_y, matrix);

    printf("\n-- SUM --");
    printf("\nX: ");

    /* Print sum x */
    for(int i = 0; i < len_x; i++)
        printf("%f ", sum_row[i]);
    
    printf("\nY: ");

    /* Print sum y */
    for(int i = 0; i < len_y; i++)
        printf("%f ", sum_col[i]);

    printf("\n\n");

    printf("-- X DIFFERENCES --\n");
    /* Calc X mass center */
    double *mass_x = mass_arr(sum_row, len_x);
    struct Minimun center_x = min(mass_x, len_x);


    printf("\n-- Y DIFFERENCES --\n");
    /* Calc Y mass center */
    double *mass_y = mass_arr(sum_col, len_y);
    struct Minimun center_y = min(mass_y, len_y);

    for(int i = 0; i < len_y; i++)
        printf("%f ", mass_y[i]);


    printf("\nX[%d] mass center: %f\n", center_x.index, center_x.value);
    printf("Y[%d] mass center: %f", center_y.index, center_y.value);


    return 0;
}