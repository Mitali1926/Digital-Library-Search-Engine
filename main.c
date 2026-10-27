#include <stdio.h>
typedef struct
{
    int id;
    char title[100];
    char author[100];
    char subject[50];
    int year;
    int readingTime;
    int score;
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
    sscanf(line, "%d,%99[^,],%99[^,],%49[^,],%d,%d,%d",
       &books[count].id,
       books[count].title,
       books[count].author,
       books[count].subject,
       &books[count].year,
       &books[count].readingTime,
       &books[count].score);

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
int rabinKarp(char text[], char pattern[])
{
    int d = 256;
    int q = 101;

    int m = 0;
    int n = 0;

    int patternHash = 0;
    int textHash = 0;
    int h = 1;

    int i, j;

    while (pattern[m] != '\0')
        m++;

    while (text[n] != '\0')
        n++;

    if (m > n)
        return 0;

    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < m; i++)
    {
        patternHash = (d * patternHash + pattern[i]) % q;
        textHash = (d * textHash + text[i]) % q;
    }

    for (i = 0; i <= n - m; i++)
    {
        if (patternHash == textHash)
        {
            for (j = 0; j < m; j++)
            {
                if (text[i + j] != pattern[j])
                    break;
            }

            if (j == m)
                return 1;
        }

        if (i < n - m)
        {
            textHash =
                (d * (textHash - text[i] * h)
                + text[i + m]) % q;

            if (textHash < 0)
                textHash += q;
        }
    }

    return 0;
}
void searchByTitleRabinKarp(Document books[], int n, char pattern[])
{
    int found = 0;

    printf("\nSearch Results (Rabin-Karp):\n");
    printf("--------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        if (rabinKarp(books[i].title, pattern))
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
void computeLPS(char pattern[], int m, int lps[])
{
    int length = 0;
    int i = 1;

    lps[0] = 0;

    while (i < m)
    {
        if (pattern[i] == pattern[length])
        {
            length++;
            lps[i] = length;
            i++;
        }
        else
        {
            if (length != 0)
            {
                length = lps[length - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
int kmpSearch(char text[], char pattern[])
{
    int n = 0;
    int m = 0;

    while (text[n] != '\0')
        n++;

    while (pattern[m] != '\0')
        m++;

    if (m == 0)
        return 1;

    if (m > n)
        return 0;

    int lps[m];

    computeLPS(pattern, m, lps);

    int i = 0;
    int j = 0;

    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            return 1;
        }
        else if (i < n && text[i] != pattern[j])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    return 0;
}
void searchByTitleKMP(Document books[], int n, char pattern[])
{
    int found = 0;

    printf("\nSearch Results (KMP):\n");
    printf("-----------------------------\n");

    for (int i = 0; i < n; i++)
    {
        if (kmpSearch(books[i].title, pattern))
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
void recommendBySubject(Document books[], int n, char subject[])
{
    int found = 0;

    printf("\n------ RECOMMENDED DOCUMENTS ------\n");

    for (int i = 0; i < n; i++)
    {
        if (naivePatternMatch(books[i].subject, subject))
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
        printf("\nNo recommendations found for this subject.\n");
    }
}
void knapsackRecommendation(Document books[], int n, int maxTime)
{
    int dp[n + 1][maxTime + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= maxTime; w++)
        {
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            else if (books[i - 1].readingTime <= w)
            {
                int include =
                    books[i - 1].score +
                    dp[i - 1][w - books[i - 1].readingTime];

                int exclude = dp[i - 1][w];

                if (include > exclude)
                    dp[i][w] = include;
                else
                    dp[i][w] = exclude;
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    printf("\n------ OPTIMAL RECOMMENDATION ------\n");
    printf("Available Reading Time: %d hours\n", maxTime);
    printf("Maximum Recommendation Score: %d\n", dp[n][maxTime]);

    printf("\nSelected Documents:\n");

    int remainingTime = maxTime;

    for (int i = n; i > 0 && remainingTime > 0; i--)
    {
        if (dp[i][remainingTime] != dp[i - 1][remainingTime])
        {
            printf("\nID    : %d\n", books[i - 1].id);
            printf("Title : %s\n", books[i - 1].title);
            printf("Time  : %d hours\n", books[i - 1].readingTime);
            printf("Score : %d\n", books[i - 1].score);

            remainingTime -= books[i - 1].readingTime;
        }
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
        printf("5. Recommend Documents\n");
        printf("6. Algorithm Demonstrations\n");
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
                   int textSearchChoice;
                   char pattern[100];

                   printf("1. Naive Pattern Matching\n");
                   printf("2. Rabin-Karp\n");
                   printf("3. KMP\n");
                   printf("0. Back\n");

                   printf("\nEnter search method: ");
                   scanf("%d", &textSearchChoice);

                   if (textSearchChoice == 0)
                   {
                      break;
                   }

                  printf("Enter word or phrase: ");
                  scanf(" %99[^\n]", pattern);

                  if (textSearchChoice == 1)
                  {
                     searchByTitle(books, count, pattern);
                  }
                  else if (textSearchChoice == 2)
                  {
                     searchByTitleRabinKarp(books, count, pattern);
                  }
                  else if (textSearchChoice == 3)
                  {
                     searchByTitleKMP(books, count, pattern);
                  }
                  else
                  {
                     printf("\nInvalid search method.\n");
                   }
                  break;
                }

            case 5:
                {
                  int recommendationChoice;

                  printf("\n------ RECOMMEND DOCUMENTS ------\n");
                  printf("1. Recommend by Subject\n");
                  printf("2. Recommend within Reading Time (0/1 Knapsack)\n");
                  printf("0. Back\n");

                  printf("\nEnter choice: ");
                  scanf("%d", &recommendationChoice);

                  if (recommendationChoice == 1)
                  {
                    char subject[50];

                    printf("Enter preferred subject: ");
                    scanf(" %49[^\n]", subject);

                    recommendBySubject(books, count, subject);
                  }
                 else if (recommendationChoice == 2)
                  {
                    int availableTime;

                    printf("Enter available reading time in hours: ");
                    scanf("%d", &availableTime);

                 if (availableTime <= 0)
                  {
                    printf("\nReading time must be greater than 0.\n");
                  } 
                 else
                  {
                    knapsackRecommendation(
                    books,
                    count,
                    availableTime
                    );
                  }
                }
                else if (recommendationChoice == 0)
                {
                    printf("\nReturning to main menu.\n");
                }
                else
                {
                    printf("\nInvalid choice.\n");
                }

                   break;
                }
            case 6:
                {
                    printf("\n========== ALGORITHM MODULES ==========\n");
                    printf("1. Sorting Algorithms\n");
                    printf("   - Merge Sort\n");
                    printf("   - Quick Sort\n");

                    printf("\n2. Searching Algorithms\n");
                    printf("   - Linear Search\n");
                    printf("   - Iterative Binary Search\n");
                    printf("   - Recursive Binary Search\n");

                    printf("\n3. Pattern Matching Algorithms\n");
                    printf("   - Naive Pattern Matching\n");
                    printf("   - Rabin-Karp\n");
                    printf("   - KMP\n");

                    printf("\n4. Dynamic Programming\n");
                    printf("   - 0/1 Knapsack\n");

                    printf("\nTotal Documents Loaded: %d\n", count);

                    printf("\n=======================================\n");

                    break;
                } 
            case 0:
            printf("\nThank you for using Digital Library.\n");
            break;

        default:
            printf("\nInvalid choice. Please try again.\n");
        }


    } while (choice != 0);

    return 0;
}