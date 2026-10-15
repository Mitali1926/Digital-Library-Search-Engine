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
void swapDocuments(Document *a, Document *b)
{
    Document temp = *a;
    *a = *b;
    *b = temp;
}
int partition(Document books[], int low, int high)
{
    int pivot = books[high].id;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (books[j].id < pivot)
        {
            i++;
            swapDocuments(&books[i], &books[j]);
        }
    }

    swapDocuments(&books[i + 1], &books[high]);

    return i + 1;
}
void quickSort(Document books[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(books, low, high);

        quickSort(books, low, pivotIndex - 1);
        quickSort(books, pivotIndex + 1, high);
    }
}
int iterativeBinarySearch(Document books[], int n, int searchId)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (books[mid].id == searchId)
        {
            return mid;
        }
        else if (books[mid].id < searchId)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}
int recursiveBinarySearch(Document books[], int low, int high, int searchId)
{
    if (low > high)
    {
        return -1;
    }

    int mid = low + (high - low) / 2;

    if (books[mid].id == searchId)
    {
        return mid;
    }
    else if (books[mid].id < searchId)
    {
        return recursiveBinarySearch(books, mid + 1, high, searchId);
    }
    else
    {
        return recursiveBinarySearch(books, low, mid - 1, searchId);
    }
}
int naivePatternMatch(char text[], char pattern[])
{
    int i, j;

    for (i = 0; text[i] != '\0'; i++)
    {
        for (j = 0; pattern[j] != '\0'; j++)
        {
            if (text[i + j] != pattern[j])
            {
                break;
            }
        }

        if (pattern[j] == '\0')
        {
            return 1;
        }
    }

    return 0;
}
void searchByTitle(Document books[], int n, char pattern[])
{
    int found = 0;

    printf("\nSearch Results:\n");
    printf("-----------------------------\n");

    for (int i = 0; i < n; i++)
    {
        if (naivePatternMatch(books[i].title, pattern))
        {
            printf("\nID      : %d\n", books[i].id);
            printf("Title   : %s\n", books[i].title);
            printf("Author  : %s\n", books[i].author);
            printf("Subject : %s\n", books[i].subject);
            printf("Year    : %d\n", books[i].year);

            found = 1;
        }
    }

    if (found == 0)
    {
        printf("\nNo matching documents found.\n");
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
                int searchChoice;
                int searchId;
                int index;

                printf("\n------ SEARCH DOCUMENT BY ID ------\n");
                printf("1. Linear Search\n");
                printf("2. Iterative Binary Search\n");
                printf("3. Recursive Binary Search\n");
                printf("0. Back\n");

                printf("\nEnter search method: ");
                scanf("%d", &searchChoice);

                if (searchChoice == 0)
                {
                 break;
                }

                printf("Enter Document ID to search: ");
                scanf("%d", &searchId);

                if (searchChoice == 1)
                {
                 index = linearSearch(books, count, searchId);
                }
                else if (searchChoice == 2)
                {
                mergeSort(books, 0, count - 1);

                index = iterativeBinarySearch(books, count, searchId);
                }
                else if (searchChoice == 3)
                {
                mergeSort(books, 0, count - 1);

                index = recursiveBinarySearch(
                books, 0, count - 1, searchId
                );
                }
                else
                {
                  printf("\nInvalid search choice.\n");
                  break;
                }

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
                {
                 int sortChoice;

                 printf("\n------ SORT DOCUMENTS ------\n");
                 printf("1. Merge Sort\n");
                 printf("2. Quick Sort\n");
                 printf("0. Back\n");

                 printf("\nEnter sorting method: ");
                 scanf("%d", &sortChoice);

                 if (sortChoice == 1)
                 {
                   mergeSort(books, 0, count - 1);

                   printf("\nDocuments sorted using Merge Sort.\n");
                   displayDocuments(books, count);
                 }
                 else if (sortChoice == 2)
                 {
                   quickSort(books, 0, count - 1);

                   printf("\nDocuments sorted using Quick Sort.\n");
                   displayDocuments(books, count);
                 }
                 else if (sortChoice == 0)
                 {
                   printf("\nReturning to main menu.\n");
                 }
                 else
                 {
                   printf("\nInvalid sorting choice.\n");
                 }

                break;
                 }

            case 4:
            {
                char pattern[100];

                printf("\n------ SEARCH BY TITLE ------\n");

                printf("Enter word or phrase: ");
                scanf(" %99[^\n]", pattern);

                searchByTitle(books, count, pattern);

                break;
            }

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