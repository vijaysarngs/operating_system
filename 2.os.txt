#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(1);
    }
    char *source_path = argv[1];
    char *dest_path = argv[2];
    FILE *source_file = fopen(source_path, "rb");
    if (source_file == NULL) {
        perror("Error opening source file");
        exit(1);
    }
    FILE *dest_file = fopen(dest_path, "wb");
    if (dest_file == NULL) {
        perror("Error opening destination file");
        fclose(source_file);
        exit(1);
    }
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }
    printf("Contents copied successfully from '%s' to '%s'.\n", source_path, dest_path);
    fclose(source_file);
    fclose(dest_file);
    return 0;
}
