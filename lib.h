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

#include "string.h"

char *read_file(char argv[]){
    /* Get file pointer  */
    FILE *ptr_f = fopen(argv, "r");

    /* If file not exists return */
    if(ptr_f == NULL)
        return NULL;

    /* Get size of file by going to the end and returning to its start */
    fseek(ptr_f, 0, SEEK_END); 
    int file_size = ftell(ptr_f);
    printf("Allocating %d bytes...\n", file_size);
    rewind(ptr_f);

    char *input_buffer = malloc(file_size); /* Alloc memory according to file size */
    fread(input_buffer, file_size, 1, ptr_f);

    fclose(ptr_f); /* Close file */
    return input_buffer;
}

void cp_buffer_arr(char *buffer, int len_x, int len_y, double matrix[len_x][len_y]){
    /* Override all \n for whitespaces */
    char *char_ptr = strchr(buffer, '\n');
    for(int i = 0; char_ptr != NULL; i++){
        *char_ptr = ' ';
        char_ptr = strchr(char_ptr + 1, '\n');
    }

    int index_x = 0;
    int index_y = 0;
    char *str_ptr = strtok(buffer, " ");
    for(int i = 0; str_ptr != NULL; i++){
        matrix[index_x][index_y] = atof(str_ptr);
        index_y++;
        if(index_y == len_y){
            index_y = 0;
            index_x++;
        }
        str_ptr = strtok(NULL, " ");
    }
}