/*
Name: Sanjay Dookhoo
ID: 814000842
*/

/*
Overview:
    -A set of Balanced BST is created for the set of synonyms.
    -Each BST is traversed inOrder, to identify a word, which is searched for in all other BST.
        If found: the Two BST are merged into another BST. And that tree begins the inOrder traversal to identify a word again
        If not found in the entirety of another BST: Move to the next tree and keep searching, until all trees are traversed

Reasoning:
    -A balanced BST allows for traversing in alphabetical order as well finding a word in O(log(n)).
    -Allows for finding a word in the most efficient time while accounting for an unlimited amount of words

Method:
    STORING
    -A sorted linked list of all related synonyms is created for each line of the input file
    -Each of those sorted linked list is used to created a Balanced BST
    -Each BST is traversed inOrder, to identify a word, which is searched for in all other BST.
        If found: the Two BST are merged into another BST. And that tree begins the inOrder traversal to identify a word again
        If not found in the entirety of another BST: Move to the next tree and keep searching, until all trees are traversed
    -Once all synonyms occurrences in different line has been removed, each node in all BST, then points to the root of its own BST. Allowing each node to access all its synonyms
    -All the remaining BST is then merged into one final BST

    OUTPUT REPEAT ALLOWED
    -perform inOrder traversal of the final tree
    -print the data in the node, and then perform an inOrder traversal of the BST root the node points to (to print its synonyms)
    -for the synonyms, do not print if it was already printed from the original BST that initiated the synonym traversal

    OUTPUT REPEAT NOT ALLOWED
    -initiate all nodes of the final BST printed state to 0
    -perform inOrder traversal of the final tree
    -if printed ==0
        -print the data in the node
        -and then perform an inOrder traversal of the BST root the node points to
        -for the data found in the second tree traversal, search the first tree (and get the state printed). if printed==0
            -for the synonyms, do not print if it was already printed from the original BST that initiated the synonym traversal
            -print
            -printed=1
    -printed=1

limitation:
    -words in the same line may be seperated by ' ' or '\t'
    -the end of a line is signaled by one or more new line chars
    -Due to the high storage capacity of computers
        -the original nodes of the BST (before it merges to one final BST) have extra unnecessary data to reduce code written (int and a Node ptr)
        -when a merge has been performed. the two trees that were used for the merge are not freed. (unnecesary time taken if it is not needed for the sake of this code)

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "generalConstant.h"
#include "linkedList.h"
#include "binaryTree.h"
#include "BSTLinkedList.h"
#include "mergeTwoBST.h"
#include "synMerging.h"

//print the first word as well as the necessary space for seperation
void fprintFirstWord(char *word,FILE *out){
    int i;
    fprintf(out,"%s",word);
    for(i=strlen(word);i<nextCol;i++) fprintf(out," ");
}

//traversal of synonyms
void inOrderRepeat(struct TNode* LNode,char *ignore,FILE *out)
{
    if (LNode == NULL)
        return;
    inOrderRepeat(LNode->left,ignore,out);

    if(strcmp (LNode->data,ignore)!=0)
        fprintf(out,"%s ", LNode->data);

    inOrderRepeat(LNode->right,ignore,out);
}

//printing all words
void printRepeat(struct TNode* LNode,FILE *out)
{
    if (LNode == NULL)
        return;
    printRepeat(LNode->left,out);

    //fprintf(out,"%s\t\t",LNode->data);
    fprintFirstWord(LNode->data,out);
    inOrderRepeat(LNode->synPointer,LNode->data,out);
    fprintf(out,"\n");

    printRepeat(LNode->right,out);
}

//traversal of synonyms
void inOrderNoRepeat(struct TNode* LNode,char *ignore,struct TNode* allWords,FILE *out)
{
    if (LNode == NULL)
        return;
    inOrderNoRepeat(LNode->left,ignore,allWords,out);

    if(strcmp(ignore,LNode->data)!=0){
        struct TNode* temp=searchBST(allWords,LNode->data);
        if(temp->printed==0){
            fprintf(out,"%s ", LNode->data);
            temp->printed=1;
        }
    }

    inOrderNoRepeat(LNode->right,ignore,allWords,out);
}

//printing all words
void printNoRepeat(struct TNode *LNode,struct TNode *allWords,FILE *out){
    if (LNode == NULL)
        return;
    printNoRepeat(LNode->left,allWords,out);

    if(LNode->printed==0){
        //fprintf(out,"%s\t\t",LNode->data);
        fprintFirstWord(LNode->data,out);
        inOrderNoRepeat(LNode->synPointer,LNode->data,allWords,out);
        fprintf(out,"\n");

        LNode->printed=1;
    }

    printNoRepeat(LNode->right,allWords,out);
}

/* Drier program to test above functions*/
int main()
{
    FILE *in = fopen("input.txt","r");
	FILE *out = fopen("output.txt","w");
	if(in == NULL)printf("Error reading input...\n");
    char buf[LINESIZE];
    char *token;

    /* Start with the empty list */
    struct LNode* head = NULL;
    struct LNode *new_node;

    /* Start with the empty list BST */
    struct LBSTNode* head_BST = NULL;

    struct TNode *root;

    //store synonym data
    while(fgets(buf, sizeof(buf), in)) //where sizeof(buf) is the length of line you anticipate reading in.
    {
        if(buf[strlen(buf)-1]=='\n')//if new line is at the end of the line
            buf[strlen(buf)-1]='\0';//remove new line character from the end

        token = strtok(buf, " \t");
        head = NULL;
        while (token && strcmp(token,"")!=0) {
            //insert into a linked list
            new_node = newNode(token);
            sortedInsert(&head, new_node);

            token = strtok(NULL, " \t");
        }
        //create balanced BST from that linked list
        root = sortedListToBST(head);

        //store root of balanced BST in a linked list
        appendBST(&head_BST, root);

        //free memory used to create original linked list
        //not done since its not necessary to increase performance
        //deleteEntireLinkedList(head);
    }

    synonymMerging(head_BST);

    assignSynonymPointerLBST(head_BST);

    root=finalTreeMerge(head_BST);

    fprintFirstWord("Words",out);
    fprintf(out,"Synonyms\n\n");
    printRepeat(root,out);

    fprintf(out,"\n\n");
    fprintFirstWord("Words",out);
    fprintf(out,"Synonyms\n\n");
    initPrinted(root);
    printNoRepeat(root,root,out);

    fclose(in);
	fclose(out);

    return 0;
}
