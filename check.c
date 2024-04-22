#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 7  // The size of each group to check

int check_characters(char c) {
    // Check if the character is in the range 0-9 or a-f
    return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || c== 10);
}

int main() {
    FILE *file = fopen("hash", "r");
    if (file == NULL) {
        printf("Failed to open the file 'hash'\n");
        return 0;
    }

    // Define a buffer to read in chunks of 7 characters
    char buffer[CHUNK_SIZE + 1];
    buffer[CHUNK_SIZE] = '\0';  // Null terminate the buffer

    // Use a dynamic array to keep track of previous chunks
    char **chunks = NULL;
    size_t chunk_count = 0;

    // Read the file character by character and form chunks of 7 characters
    int c;
    while ((c = fgetc(file)) != EOF) {
        // Shift buffer to the left and add new character at the end
        memmove(buffer, buffer + 1, CHUNK_SIZE - 1);
        buffer[CHUNK_SIZE - 1] = (char)c;

        // Check if buffer is full
        if (buffer[CHUNK_SIZE - 1] != '\0') {
            // Check if all characters in the buffer are in the range 1-9 or a-f
            int valid = 1;
            for (int i = 0; i < CHUNK_SIZE; i++) {
                if (!check_characters(buffer[i])) {
//                    printf("%c",buffer[i]);
                    valid = 0;
                    break;
                }
            }

            // If all characters are valid, check for duplicates
            if (valid) {
                // Check if the buffer matches any previous chunks
                int duplicate = 0;
                for (size_t i = 0; i < chunk_count; i++) {
                    if (strcmp(buffer, chunks[i]) == 0) {
                        duplicate = 1;
                        break;
                    }
                }

                // Output if a duplicate is found
                if (duplicate) {
                    printf("Duplicate found: %s\n", buffer);
                } else {
                    // Add the current chunk to the list of chunks
                    chunk_count++;
                    chunks = realloc(chunks, chunk_count * sizeof(char *));
                    chunks[chunk_count - 1] = strdup(buffer);
                }
            }
        }
    }

    // Clean up
    for (size_t i = 0; i < chunk_count; i++) {
        free(chunks[i]);
    }
    free(chunks);
    fclose(file);
system("./char");
    return 0;
}
