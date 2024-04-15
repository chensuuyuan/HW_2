#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 8  // 每个字符串的长度为7个字符 + 1个空字符
#define HASH_TABLE_SIZE 1000  // 哈希表大小

// 哈希表节点结构体
typedef struct Node {
    char str[MAX_STRING_SIZE];
    struct Node *next;
} Node;

// 哈希表结构体
typedef struct {
    Node *buckets[HASH_TABLE_SIZE];
} HashTable;

// 哈希函数
unsigned int hash(const char *str) {
    unsigned int hash_value = 0;
    while (*str) {
        hash_value = (hash_value * 31) + *str;
        str++;
    }
    return hash_value % HASH_TABLE_SIZE;
}

// 初始化哈希表
void init_hash_table(HashTable *table) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
}

// 插入字符串到哈希表中
void insert(HashTable *table, const char *str) {
    unsigned int index = hash(str);
    Node *new_node = (Node *)malloc(sizeof(Node));
    strcpy(new_node->str, str);
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

// 检查字符串是否在哈希表中存在
int exists(HashTable *table, const char *str) {
    unsigned int index = hash(str);
    Node *current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->str, str) == 0) {
            return 1;  // 字符串存在
        }
        current = current->next;
    }
    return 0;  // 字符串不存在
}

// 释放哈希表中的内存
void free_hash_table(HashTable *table) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Node *current = table->buckets[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
        table->buckets[i] = NULL;
    }
}

int main() {
    FILE *file = fopen("hash", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    HashTable table;
    init_hash_table(&table);

    char buffer[MAX_STRING_SIZE];
    int found_duplicate = 0;

    while (fread(buffer, sizeof(char), 7, file) == 7) {
        buffer[7] = '\0';  // 在末尾添加空字符

        // 检查是否存在重复字符串
        if (exists(&table, buffer)) {
            printf("发现重复的字符串: %s\n", buffer);
            found_duplicate = 1;
            break;
        }

        // 将字符串插入哈希表中
        insert(&table, buffer);
    }

    if (!found_duplicate) {
        printf("没有发现重复的字符串\n");
    }

    // 关闭文件并释放哈希表
    fclose(file);
    free_hash_table(&table);

    return 0;
}
