#include <stdio.h>
typedef struct
{
    int id;
    char title[100];
    char author[100];
    char subject[50];
    int year;
} Document;
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
int main()
{
    Document books[5] = {
    {101, "Introduction to Algorithms", "Cormen", "Algorithms", 2022},
    {102, "Operating System Concepts", "Silberschatz", "Operating Systems", 2021},
    {103, "Computer Networks", "Tanenbaum", "Networks", 2020},
    {104, "Database System Concepts", "Korth", "Database", 2021},
    {105, "Artificial Intelligence", "Russell", "AI", 2022}
};
    printf("========================================\n");
    printf("   DIGITAL LIBRARY SEARCH ENGINE\n");
    printf("========================================\n");

    displayDocuments(books, 5);

    return 0;
}