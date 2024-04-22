#include <stdio.h>

int is_valid_hex_char(char c) {
    // 检查字符是否在0~9或a~f之间
    return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || c == 10);
}

int main() {
    FILE *file = fopen("hash", "r");
    if (file == NULL) {
        printf("Failed to open the file 'hash'\n");
        return 0;
    }

    int c;
    int found_invalid = 0;

    // 逐个读取文件中的字符
    while ((c = fgetc(file)) != EOF) {
        // 检查字符是否在0~9或a~f之间
        if (!is_valid_hex_char(c)) {
            // 输出不在范围内的字符
           if(c>'f' && c <= 'z'){
            printf("%c\n", c);
           }
            found_invalid = 1;
        }
    }

    // 如果未找到不在范围内的字符，输出"All characters are in the range"
    if (!found_invalid) {
        printf("All characters are in the range 0-9 or a-f\n");
    }

    fclose(file);
    return 0;
}
