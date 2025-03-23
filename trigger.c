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

int main(int argc, char *argv[]){
    
    /* Check if first agument is NULL */

    if(argv[1] == NULL){
        printf("No argument provided, exiting...\n");
        return -1;
    }

    /* Get file pointer*/ */
    FILE *ptr_f = fopen(argv[1], "r");

    /* If file not exists return */
    if(ptr_f == NULL){
        printf("No file provided, exiting...\n");
        return -2;
    }

    /* Get size of file by going to the end and returning to its start */
    fseek(ptr_f, 0, SEEK_END); 
    int file_size = ftell(ptr_f);
    printf("Allocating %d bytes...\n", file_size);
    rewind(ptr_f);

    char *input_buffer = malloc(file_size); /* Alloc memory according to file size */
    fread(input_buffer, file_size, 1, ptr_f);
        
    printf("%s", input_buffer);

    fclose(ptr_f); /* Close file */

    
    printf("\n%c", input_buffer[0]);

    return 0;
}