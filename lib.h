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
        
    printf("%s", input_buffer);

    fclose(ptr_f); /* Close file */
    return input_buffer;
}
