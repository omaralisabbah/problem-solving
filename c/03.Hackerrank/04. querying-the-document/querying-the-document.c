/*
 * HackerRank Challenge: Querying the Document
 *
 * Author: [omaralisabbah]
 *
 * Description:
 * This program parses a text document into a hierarchical structure:
 *   Document -> Paragraphs -> Sentences -> Words
 *
 * It then allows queries to retrieve:
 *   - A specific paragraph
 *   - A specific sentence in a paragraph
 *   - A specific word in a sentence of a paragraph
 *
 * Input format (handled by HackerRank):
 *   - First line: number of paragraphs
 *   - Next lines: each paragraph text
 *   - Then: number of queries
 *   - Each query specifies type (1=paragraph, 2=sentence, 3=word) and indices
 *
 * Output:
 *   - Prints the requested paragraph, sentence, or word according to query.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_CHARACTERS 1005   // Maximum characters per paragraph
#define MAX_PARAGRAPHS 5      // Maximum number of paragraphs

/*
 * Helper function: split
 * ----------------------
 * Splits a string into tokens based on a delimiter.
 *
 * Parameters:
 *   text  - input string to split (modified in place by strtok)
 *   delim - delimiter string (e.g., " ", ".", "\n")
 *   size  - output parameter: number of tokens found
 *
 * Returns:
 *   Dynamically allocated array of strings (tokens).
 */
char** split(char* text, const char* delim, int* size) {
    char* token = strtok(text, delim);
    char** result = NULL;
    *size = 0;
    
    while (token != NULL) {
        result = realloc(result, sizeof(char*) * (*size + 1));
        result[*size] = token;
        (*size)++;
        token = strtok(NULL, delim);
    }
    return result;
}

/*
 * Query function: kth_word_in_mth_sentence_of_nth_paragraph
 * ---------------------------------------------------------
 * Retrieves the k-th word in the m-th sentence of the n-th paragraph.
 *
 * Parameters:
 *   document - 4D pointer structure
 *   k        - word index (1-based)
 *   m        - sentence index (1-based)
 *   n        - paragraph index (1-based)
 *
 * Returns:
 *   Pointer to the requested word string.
 */
char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return document[n - 1][m - 1][k - 1];
}

/*
 * Query function: kth_sentence_in_mth_paragraph
 * ---------------------------------------------
 * Retrieves the k-th sentence in the m-th paragraph.
 *
 * Parameters:
 *   document - 4D pointer structure
 *   k        - sentence index (1-based)
 *   m        - paragraph index (1-based)
 *
 * Returns:
 *   Array of words (char**) representing the sentence.
 */
char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    return document[m - 1][k - 1];
}

/*
 * Query function: kth_paragraph
 * -----------------------------
 * Retrieves the k-th paragraph.
 *
 * Parameters:
 *   document - 4D pointer structure
 *   k        - paragraph index (1-based)
 *
 * Returns:
 *   Array of sentences (char***) representing the paragraph.
 */
char*** kth_paragraph(char**** document, int k) {
    return document[k - 1];
}

/*
 * Function: get_document
 * ----------------------
 * Converts raw text into a hierarchical document structure:
 *   document[paragraph][sentence][word]
 *
 * Splits text by:
 *   - '\n' for paragraphs
 *   - '.'  for sentences
 *   - ' '  for words
 *
 * Parameters:
 *   text - raw input text
 *
 * Returns:
 *   4D pointer structure representing the document.
 */
char**** get_document(char* text) {
    int para_count;
    char** paragraphs = split(text, "\n", &para_count);
    
    char**** document = malloc(sizeof(char***) * para_count);
    
    for (int i = 0; i < para_count; i++) {
        int sent_count;
        char** sentences = split(paragraphs[i], ".", &sent_count);
        
        document[i] = malloc(sizeof(char**) * sent_count);
        
        for (int j = 0; j < sent_count; j++) {
            int word_count;
            char** words = split(sentences[j], " ", &word_count);
            
            document[i][j] = malloc(sizeof(char*) * word_count);
            for (int k = 0; k < word_count; k++) {
                document[i][j][k] = words[k];
            }
        }
    }
    return document;
}

/*
 * Function: get_input_text
 * ------------------------
 * Reads input paragraphs from stdin and concatenates them into a single string.
 *
 * Returns:
 *   Dynamically allocated string containing the full document text.
 */
char* get_input_text() {    
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar(); // consume newline after paragraph_count
    
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]); // read full line (paragraph)
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n"); // separate paragraphs with newline
    }

    char* returnDoc = (char*)malloc((strlen(doc) + 1) * sizeof(char));
    strcpy(returnDoc, doc);
    return returnDoc;
}

/*
 * Printing helpers:
 * -----------------
 * These functions format output according to HackerRank requirements.
 */

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count); // HackerRank provides word count
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count); // HackerRank provides sentence count
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

/*
 * Main function:
 * --------------
 * Reads input text, builds document structure, and processes queries.
 *
 * Query types:
 *   1 -> print paragraph
 *   2 -> print sentence
 *   3 -> print word
 */
int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{ // type == 1
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}
