#include <stdio.h>
#include <stdlib.h>

struct RecordType {
    int id;
    char name;
    int order;
    struct RecordType* next;
};


struct HashType {
    int size;
    struct RecordType* table;
};

int hash(int x, int tableSize) {
    return x % tableSize;
}

int parseData(char* inputFileName, struct RecordType** ppData) {
    
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0, i, n;
    char c;
    struct RecordType* pRecord;
    *ppData = NULL;

    if (inFile) {
        
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        
        if (*ppData == NULL) {
            
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        
        for (i = 0; i < dataSz; ++i) {
            
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}


void printRecords(struct RecordType pData[], int dataSz) {
    printf("\nRecords:\n");
    
    for (int i = 0; i < dataSz; ++i) {
        
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    
    }
    printf("\n\n");
}

void displayRecordsInHash(struct HashType* pHashArray, int hashSz) {
    
    for (int i = 0;i < hashSz;i++) {
        
        printf("Index %d -> ", i);
        struct RecordType* temp = pHashArray[i].table;
        
        if (temp != NULL) {
            
            while (temp != NULL) {
                
                printf("%d, %c, %d ", temp->id, temp->name, temp->order);
                
                if (temp->next != NULL) {
                    printf("-> ");
                }
                
                temp = temp->next;
            }
            
            printf("\n\n");
        }
    }
}

void insertRecord(struct HashType* hashTable, struct RecordType* record, int tableSize) {

    int index = hash(record->id, tableSize);
    struct RecordType* temp = hashTable[index].table;
    if (temp == NULL) {
        hashTable[index].table = record;
    }else {
        
        while (temp->next != NULL) {
            temp = temp->next;
        }
        
        temp->next = record;
    }
}

int main(void) {
    
    struct RecordType* pRecords;
    int recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    int hashTableSz = 11;
   
    struct HashType* hashTable = (struct HashType*)malloc(sizeof(struct HashType) * hashTableSz);
    
    for (int i = 0; i < recordSz; i++) {
        hashTable[i].table = NULL;
    }
    
    for (int i = 0; i < recordSz; i++) {
        insertRecord(hashTable, &pRecords[i], hashTableSz);
    }
    
    printf("\n~~~~~Hash Table~~~~~\n");
    displayRecordsInHash(hashTable, hashTableSz);
    free(hashTable);
    free(pRecords);
    return 0;
}