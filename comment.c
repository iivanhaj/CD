#include <stdio.h>
#include <string.h>

int main() {
    char line[200];
    FILE *file = fopen("comment.txt", "r");
    int in_multiline_comment = 0;

    while (fgets(line, sizeof(line), file)) {
        if (in_multiline_comment) {
            printf("Comment: %s", line);
            if (strstr(line, "*/")) in_multiline_comment = 0;
        } else if (strncmp(line, "//", 2) == 0) {
            printf("Comment: %s", line);
        } else if (strstr(line, "/*")) {
            printf("Comment: %s", line);
            if (!strstr(line, "*/")) in_multiline_comment = 1;
        } else {
            char *inline_comment = strstr(line, "//");
            if (inline_comment) {
                printf("Not a comment: ");
                fwrite(line, 1, inline_comment - line, stdout); // Print code part
                printf("\nComment: %s", inline_comment); // Print comment part
            } else {
                printf("Not a comment: %s", line);
            }
        }
    }

    fclose(file);
    return 0;
}
