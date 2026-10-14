#include <stdio.h>
typedef struct
{
    int id;
    char title[100];
    char author[100];
    char subject[50];
    int year;
} Document;
int loadDocuments(const char *filename, Document books[], int maxBooks)
{
    FILE *file;
    char line[500];
    int count = 0;

    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: Could not open %s\n", filename);
        return 0;
    }


    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) != NULL && count < maxBooks)
    {
        sscanf(line, "%d,%99[^,],%99[^,],%49[^,],%d",
               &books[count].id,
               books[count].title,
               books[count].author,
               books[count].subject,
               &books[count].year);

        count++;
    }

    fclose(file);

    return count;
}
void displayDocuments(Document books[], int n)
{
    printf("\n%-5s %-30s %-20s %-20s %-6s\n",
           "ID", "TITLE", "AUTHOR", "SUBJECT", "YEAR");

    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%-5d %-30s %-20s %-20s %-6d\n",
               books[i].id,
               books[i].title,
               books[i].author,
               books[i].subject,
               books[i].year);
    }
}
int main() {

    Document books[1000];
    int count;
    

    printf("========================================\n");
    printf("   DIGITAL LIBRARY SEARCH ENGINE\n");
    printf("========================================\n");

    count = loadDocuments("documents.csv", books, 1000);
    printf("\n%d documents loaded successfully.\n", count);

    displayDocuments(books, count);

    return 0;
}