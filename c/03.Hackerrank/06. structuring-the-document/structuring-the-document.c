/*
 * HackerRank Challenge: Structuring the Document
 *
 * Author: [omaralisabbah]
 *
 * Description:
 * This program parses a text document into a hierarchical structure:
 *   Document -> Paragraphs -> Sentences -> Words
 *
 * It uses structs to represent each level of the hierarchy and provides
 * functions to query specific words, sentences, and paragraphs.
 *
 * Input format:
 *   - First line: number of paragraphs
 *   - Next lines: each paragraph (sentences separated by '.', words separated by spaces)
 *   - Then: number of queries
 *   - Each query specifies type (1=paragraph, 2=sentence, 3=word) and indices
 *
 * Output format:
 *   - Prints the requested paragraph, sentence, or word according to query.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_CHARACTERS 1005   // Maximum characters allowed in input text
#define MAX_PARAGRAPHS 5      // Maximum number of paragraphs

/* -------------------- STRUCT DEFINITIONS -------------------- */

// Word structure: represents a single word
struct word {
    char* data;   // pointer to string containing the word
};

// Sentence structure: represents a sequence of words
struct sentence {
    struct word* data;   // dynamic array of words
    int word_count;      // number of words in the sentence
};

// Paragraph structure: represents a sequence of sentences
struct paragraph {
    struct sentence* data;   // dynamic array of sentences
    int sentence_count;      // number of sentences in the paragraph
};

// Document structure: represents the entire document
struct document {
    struct paragraph* data;   // dynamic array of paragraphs
    int paragraph_count;      // number of paragraphs in the document
};

/* -------------------- HELPER FUNCTIONS -------------------- */

/*
 * Function: split
 * ---------------
 * Splits a string into tokens based on a delimiter.
 *
 * Parameters:
 *   text  - input string (modified in place by strtok)
 *   delim - delimiter string (e.g., " ", ".", "\n")
 *   count - output parameter: number of tokens found
 *
 * Returns:
 *   Dynamically allocated array of strings (tokens).
 */
char** split(char* text, const char* delim, int* count) {
    char* token = strtok(text, delim);
    char** result = NULL;
    *count = 0;
    
    while (token != NULL) {
        result = realloc(result, sizeof(char*) * (*count + 1));
        result[*count] = token;
        (*count)++;
        token = strtok(NULL, delim);
    }
    return result;
}

/* -------------------- DOCUMENT PARSING -------------------- */

/*
 * Function: get_document
 * ----------------------
 * Parses raw text into a document structure.
 *
 * Parameters:
 *   text - raw input string
 *
 * Returns:
 *   document struct with paragraphs, sentences, and words.
 */
struct document get_document(char* text) {
    struct document doc;
    int para_count;
    char** paragraphs = split(text, "\n", &para_count);
    doc.paragraph_count = para_count;
    doc.data = malloc(sizeof(struct paragraph) * para_count);
    
    for (int i = 0; i < para_count; i++) {
        int sent_count;
        char** sentences = split(paragraphs[i], ".", &sent_count);
        doc.data[i].sentence_count = sent_count;
        doc.data[i].data = malloc(sizeof(struct sentence) * sent_count);
        
        for (int j = 0; j < sent_count; j++) {
            int word_count;
            char** words = split(sentences[j], " ", &word_count);
            doc.data[i].data[j].word_count = word_count;
            doc.data[i].data[j].data = malloc(sizeof(struct word) * word_count);
            
            for (int k = 0; k < word_count; k++) {
                doc.data[i].data[j].data[k].data = words[k];
            }
        }
    }
    return doc;
}

/* -------------------- QUERY FUNCTIONS -------------------- */

/*
 * Function: kth_word_in_mth_sentence_of_nth_paragraph
 * ---------------------------------------------------
 * Returns the k-th word in the m-th sentence of the n-th paragraph.
 */
struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return Doc.data[n - 1].data[m - 1].data[k - 1];
}

/*
 * Function: kth_sentence_in_mth_paragraph
 * ---------------------------------------
 * Returns the k-th sentence in the m-th paragraph.
 */
struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return Doc.data[m - 1].data[k - 1];
}

/*
 * Function: kth_paragraph
 * -----------------------
 * Returns the k-th paragraph.
 */
struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k - 1];
}

/* -------------------- PRINT FUNCTIONS -------------------- */

/*
 * Function: print_word
 * --------------------
 * Prints a word.
 */
void print_word(struct word w) {
    printf("%s", w.data);
}

/*
 * Function: print_sentence
 * ------------------------
 * Prints a sentence (all words separated by spaces).
 */
void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

/*
 * Function: print_paragraph
 * -------------------------
 * Prints a paragraph (all sentences separated by '.').
 */
void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

/*
 * Function: print_document
 * ------------------------
 * Prints the entire document (paragraphs separated by newlines).
 */
void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

/* -------------------- INPUT HANDLING -------------------- */

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
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen(doc) + 1) * sizeof(char));
    strcpy(returnDoc, doc);
    return returnDoc;
}

/* -------------------- MAIN FUNCTION -------------------- */

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
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen = kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else { // type == 1
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}
