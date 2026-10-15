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
int linearSearch(Document books[], int n, int searchId)
{
    for (int i = 0; i < n; i++)
    {
        if (books[i].id == searchId)
        {
            return i;
        }
    }

    return -1;
}
void merge(Document books[], int left, int mid, int right)
{
    int i, j, k;

    int n1 = mid - left + 1;
    int n2 = right - mid;

    Document leftArray[n1];
    Document rightArray[n2];

    for (i = 0; i < n1; i++)
    {
        leftArray[i] = books[left + i];
    }

    for (j = 0; j < n2; j++)
    {
        rightArray[j] = books[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (leftArray[i].id <= rightArray[j].id)
        {
            books[k] = leftArray[i];
            i++;
        }
        else
        {
            books[k] = rightArray[j];
            j++;
        }

        k++;
    }

    while (i < n1)
    {
        books[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        books[k] = rightArray[j];
        j++;
        k++;
    }
}
void mergeSort(Document books[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(books, left, mid);
        mergeSort(books, mid + 1, right);

        merge(books, left, mid, right);
    }
}
int main()
{
    Document books[1000];
    int count;
    int choice;

    count = loadDocuments("documents.csv", books, 1000);

    if (count == 0)
    {
        printf("No documents loaded.\n");
        return 1;
    }

    do
    {
        printf("\n========================================\n");
        printf("     DIGITAL LIBRARY SEARCH ENGINE\n");
        printf("========================================\n");

        printf("1. Display All Documents\n");
        printf("2. Search Document by ID\n");
        printf("3. Sort Documents\n");
        printf("4. Search Text\n");
        printf("5. Algorithm Demonstrations\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                displayDocuments(books, count);
                break;

            case 2:
            {
                int searchId;
                int index;

                printf("\nEnter Document ID to search: ");
                scanf("%d", &searchId);

                index = linearSearch(books, count, searchId);

                if (index != -1)
                {
                   printf("\nDocument Found!\n");
                   printf("-----------------------------\n");
                   printf("ID      : %d\n", books[index].id);
                   printf("Title   : %s\n", books[index].title);
                   printf("Author  : %s\n", books[index].author);
                   printf("Subject : %s\n", books[index].subject);
                   printf("Year    : %d\n", books[index].year);
                }
                else
                {  
                   printf("\nDocument not found.\n");
                }

                 break;
                }

            case 3:
                mergeSort(books, 0, count - 1);

                printf("\nDocuments sorted successfully using Merge Sort.\n");

                displayDocuments(books, count);

                break;

            case 4:
                printf("\nText searching will be added later.\n");
                break;

            case 5:
                printf("\nAlgorithm demonstrations will be added later.\n");
                break;

            case 0:
                printf("\nThank you for using Digital Library.\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}