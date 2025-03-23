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
#include "lib.h"

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

    printf("\n%d\n%d", len_x, len_y);

    return 0;
}