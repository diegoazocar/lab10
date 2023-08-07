#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{

    int isWord;
    struct Trie *root;
    struct Trie *children[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *temp = pTrie->root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int id = (int)word[i] - 'a';
        if (temp->children[id] == NULL)
        {
            temp->children[id] = make_trienode(word[i]);
        }
        temp = temp->children[id];
    }
    temp->isWord = 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *temp = pTrie->root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int position = word[i] - 'a';
        if (temp->children[position] == NULL)
            return 0;
        temp = temp->children[position];
    }
    if (temp != NULL && temp->isWord == 1)
        return 1;
    return 0;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for (int i = 0; i < 26; i++)
    {
        if (pTrie->children[i] != NULL)
        {
            free_trienode(pTrie->children[i]);
        }
        else
        {
            continue;
        }
    }
    free(pTrie);
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pNode = (struct Trie *)malloc(sizeof(struct Trie));
    if (pNode)
    {
        pNode->isWord = 0;
        for (int i = 0; i < 26; i++)
        {
            pNode->children[i] = NULL;
        }
    }
    return pNode;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *inFile = fopen(filename, "r");
    if (!inFile)
    {
        printf("Cannot open dictionary file\n");
        exit(1);
    }

    int numWords = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), inFile))
    {
        buffer[strcspn(buffer, "\n")] = 0;
        pInWords[numWords] = strdup(buffer);
        numWords++;
    }

    fclose(inFile);
    return numWords;
}

int main(void)
{
    char *inWords[256];

    // read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}