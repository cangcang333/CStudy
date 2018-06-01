/*************************************************************************
	> File Name: chain_hash.c
	> Author: 
	> Mail: 
	> Created Time: 五  6/ 1 10:21:42 2018
 ************************************************************************/
/* Implement Chain Hashing (Separate Chaining With Linked List) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
    int key;
    int age;
    char name[100];
    struct node *next;
};
struct hash {
    struct node *head;
    int count;
};

struct hash *hashTable = NULL;
int elemCount = 0;

struct node *createNode(int key, char *name, int age)
{
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = key;
    newNode->age = age;
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

void insertToHash(int key, char *name, int age)
{
    int hashIndex = key % elemCount;
    struct node *newNode = createNode(key, name, age);

    /* head of list for the bucket with index "hashIndex" */
    if (hashTable[hashIndex].head == NULL)
    {
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count = 1;
        return ;
    }

    /* add new node to the list */
    newNode->next = (hashTable[hashIndex].head);

    /* update the head of the list and no of nodes in the current bucket */
    hashTable[hashIndex].head = newNode;
    hashTable[hashIndex].count++;
    return ;
}

void deleteFromHash(int key)
{
    /* find the bucket using hash index */
    int hashIndex = key % elemCount;
    int flag = 0;
    struct node *temp, *myNode;
    /* get the list head from current bucket */
    myNode = hashTable[hashIndex].head;
    if (myNode == NULL)
    {
        printf("Given data is not exist in hash table\n");
        return ;
    }
    temp = myNode;
    while (myNode != NULL)
    {
        /* delete the node with given key */
        if (myNode->key == key)
        {
            flag = 1;
            if (myNode == hashTable[hashIndex].head)
                hashTable[hashIndex].head = myNode->next;
            else
                /* ??? */
                temp->next = myNode->next;

            hashTable[hashIndex].count--;
            free(myNode);
            break;
        }
        temp = myNode;
        myNode = myNode->next;
    }

    if (flag)
        printf("Delete data successfully\n");
    else
        printf("Given data is not exist in hash table\n");

    return ;
}

void searchInHash(int key)
{
    int hashIndex = key % elemCount;
    int flag = 0;
    struct node *myNode;
    myNode = hashTable[hashIndex].head;
    if (myNode == NULL)
    {
        printf("Search element does not exist in hash table\n");
        return ;
    }
    while (myNode != NULL)
    {
        if (myNode->key == key)
        {
            printf("VoterID: %d\n", myNode->key);
            printf("Name   : %s\n", myNode->name);
            printf("Age:   : %d\n", myNode->age);
            flag = 1;
            break;
        }
        myNode = myNode->next;
    }

    if (flag == 0)
        printf("Search element does not exist in hash table\n");

    return ;
}

void display()
{
    struct node *myNode;
    int i;
    for (i = 0; i < elemCount; i++)
    {
        if (hashTable[i].count == 0)
            continue;
        myNode = hashTable[i].head;
        if (myNode == NULL)
            continue;
        printf("Data at index %d in Hash Table\n", i);
        printf("VoterID    Name    Age  \n");
        printf("------------------------\n");
        while (myNode != NULL)
        {
            printf("%-12d", myNode->key);
            printf("%-12s", myNode->name);
            printf("%d\n", myNode->age);
            myNode = myNode->next;
        }
    }
    return ;
}

int main(int argc, char *argv[])
{
    int n, ch, key, age;
    char name[100];
    printf("Enter the number os elements:");
    scanf("%d", &n);
    elemCount = n;
    /* create hash table with "n" number of buckets */
    hashTable = (struct hash *)calloc(n, sizeof(struct hash));

    insertToHash(34, "Ada", 35);
    insertToHash(22, "Bob", 23);
    insertToHash(11, "Cathy", 12);
    insertToHash(8, "Dan", 9);
    insertToHash(8, "Eric", 19);
    insertToHash(8, "Fred", 21);
    insertToHash(3, "God", 23);
    insertToHash(18, "Helix", 25);
    insertToHash(68, "Lily", 31);
    insertToHash(99, "Jack", 33);


    while (1)
    {
        printf("\n1. Insertion\t2. Deletion\n");
        printf("3. Searching\t4. Display\n5. Exit\n");
        printf("Enter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1:
                printf("Enter the key value: ");
                scanf("%d", &key);
                getchar();
                printf("Name:");
                fgets(name, 100, stdin);
                name[strlen(name) - 1] = '\0';
                printf("Age: ");
                scanf("%d", &age);
                /* inserting new node to hash table */
                insertToHash(key, name, age);
                break;

            case 2:
                printf("Enter the key to perform deletion:");
                scanf("%d", &key);
                deleteFromHash(key);
                break;

            case 3:
                printf("Enter the key to search:");
                scanf("%d", &key);
                searchInHash(key);
                break;

            case 4:
                display();
                break;
            
            case 5:
                exit(0);

            default:
                printf("You have entered the wrong option\n");
                break;
        }
    }

    return 0;
}
