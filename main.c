#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 1000
#define GRAPH_SIZE 5
#define INF 99999

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
        int fieldsRead;

        fieldsRead = sscanf(
            line,
            "%d,%99[^,],%99[^,],%49[^,],%d,%d,%d",
            &books[count].id,
            books[count].title,
            books[count].author,
            books[count].subject,
            &books[count].year,
            &books[count].readingTime,
            &books[count].score
        );

        if (fieldsRead == 7)
        {
            count++;
        }
    }

    fclose(file);

    return count;
}

void displayDocuments(Document books[], int n)
{
    printf("\n%-5s %-30s %-20s %-22s %-6s\n",
           "ID", "TITLE", "AUTHOR", "SUBJECT", "YEAR");

    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%-5d %-30s %-20s %-22s %-6d\n",
               books[i].id,
               books[i].title,
               books[i].author,
               books[i].subject,
               books[i].year);
    }
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

int binarySearch(Document books[], int n, int searchId)
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
    int n = strlen(text);
    int m = strlen(pattern);

    if (m == 0)
    {
        return 1;
    }

    if (m > n)
    {
        return 0;
    }

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


void searchByTitle(Document books[], int n, char pattern[])
{
    int found = 0;

    printf("\n------ SEARCH RESULTS ------\n");

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

    if (!found)
    {
        printf("\nNo matching document found.\n");
    }
}




void recommendBySubject(Document books[], int n, char subject[])
{
    int found = 0;

    printf("\n------ RECOMMENDED DOCUMENTS ------\n");

    for (int i = 0; i < n; i++)
    {
        if (strcmp(books[i].subject, subject) == 0)
        {
            printf("\nID      : %d\n", books[i].id);
            printf("Title   : %s\n", books[i].title);
            printf("Author  : %s\n", books[i].author);
            printf("Subject : %s\n", books[i].subject);

            found = 1;
        }
    }

    if (!found)
    {
        printf("\nNo documents found for this subject.\n");
    }
}

void knapsackRecommendation(Document books[], int n, int maxTime)
{
    int dp[n + 1][maxTime + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int time = 0; time <= maxTime; time++)
        {
            if (i == 0 || time == 0)
            {
                dp[i][time] = 0;
            }
            else if (books[i - 1].readingTime <= time)
            {
                int include =
                    books[i - 1].score +
                    dp[i - 1][time - books[i - 1].readingTime];

                int exclude = dp[i - 1][time];

                if (include > exclude)
                {
                    dp[i][time] = include;
                }
                else
                {
                    dp[i][time] = exclude;
                }
            }
            else
            {
                dp[i][time] = dp[i - 1][time];
            }
        }
    }

    printf("\n------ OPTIMAL RECOMMENDATION ------\n");
    printf("Available Time: %d hours\n", maxTime);
    printf("Maximum Recommendation Score: %d\n",
           dp[n][maxTime]);

    printf("\nSelected Documents:\n");

    int remainingTime = maxTime;

    for (int i = n; i > 0 && remainingTime > 0; i--)
    {
        if (dp[i][remainingTime] !=
            dp[i - 1][remainingTime])
        {
            printf("\nID    : %d\n", books[i - 1].id);
            printf("Title : %s\n", books[i - 1].title);
            printf("Time  : %d hours\n",
                   books[i - 1].readingTime);
            printf("Score : %d\n",
                   books[i - 1].score);

            remainingTime -= books[i - 1].readingTime;
        }
    }
}

void dijkstra(int graph[GRAPH_SIZE][GRAPH_SIZE], int source)
{
    int distance[GRAPH_SIZE];
    int visited[GRAPH_SIZE];

    for (int i = 0; i < GRAPH_SIZE; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
    }

    distance[source] = 0;

    for (int count = 0;
         count < GRAPH_SIZE - 1;
         count++)
    {
        int minimum = INF;
        int u = -1;

        for (int i = 0; i < GRAPH_SIZE; i++)
        {
            if (!visited[i] &&
                distance[i] < minimum)
            {
                minimum = distance[i];
                u = i;
            }
        }

        if (u == -1)
        {
            break;
        }

        visited[u] = 1;

        for (int v = 0; v < GRAPH_SIZE; v++)
        {
            if (!visited[v] &&
                graph[u][v] != 0 &&
                distance[u] != INF &&
                distance[u] + graph[u][v] < distance[v])
            {
                distance[v] =
                    distance[u] + graph[u][v];
            }
        }
    }

    printf("\n------ RELATED DOCUMENT DISTANCES ------\n");

    for (int i = 0; i < GRAPH_SIZE; i++)
    {
        printf("Document %d -> Distance = %d\n",
               i + 101,
               distance[i]);
    }
}

int main()
{
    Document books[MAX_BOOKS];

    int count;
    int choice;

    count = loadDocuments(
        "documents.csv",
        books,
        MAX_BOOKS
    );

    if (count == 0)
    {
        printf("No documents loaded.\n");
        return 1;
    }
    mergeSort(books, 0, count - 1);

    do
    {
        printf("\n============================================\n");
        printf("      DIGITAL LIBRARY SEARCH ENGINE\n");
        printf("============================================\n");

        printf("1. Display All Documents\n");
        printf("2. Search Document by ID\n");
        printf("3. Search Document by Title\n");
        printf("4. Recommend Documents\n");
        printf("5. Find Related Documents\n");
        printf("6. About Algorithms\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                displayDocuments(books, count);
                break;
            }

            case 2:
            {
                int searchId;

                printf("\nEnter Document ID: ");
                scanf("%d", &searchId);

                int index =
                    binarySearch(
                        books,
                        count,
                        searchId
                    );

                if (index != -1)
                {
                    printf("\nDocument Found!\n");
                    printf("-----------------------------\n");

                    printf("ID      : %d\n",
                           books[index].id);

                    printf("Title   : %s\n",
                           books[index].title);

                    printf("Author  : %s\n",
                           books[index].author);

                    printf("Subject : %s\n",
                           books[index].subject);

                    printf("Year    : %d\n",
                           books[index].year);
                }
                else
                {
                    printf("\nDocument not found.\n");
                }

                break;
            }

            case 3:
            {
                char pattern[100];

                printf("\nEnter title word or phrase: ");

                scanf(" %99[^\n]", pattern);

                searchByTitle(
                    books,
                    count,
                    pattern
                );

                break;
            }

            case 4:
            {
                int recommendationChoice;

                printf("\n------ RECOMMENDATION ENGINE ------\n");
                printf("1. Recommend by Subject\n");
                printf("2. Recommend by Available Reading Time\n");
                printf("0. Back\n");

                printf("\nEnter choice: ");
                scanf("%d", &recommendationChoice);

                if (recommendationChoice == 1)
                {
                    char subject[50];

                    printf("Enter subject: ");
                    scanf(" %49[^\n]", subject);

                    recommendBySubject(
                        books,
                        count,
                        subject
                    );
                }
                else if (recommendationChoice == 2)
                {
                    int availableTime;

                    printf("Enter available reading time: ");
                    scanf("%d", &availableTime);

                    if (availableTime > 0)
                    {
                        knapsackRecommendation(
                            books,
                            count,
                            availableTime
                        );
                    }
                    else
                    {
                        printf("\nInvalid reading time.\n");
                    }
                }

                break;
            }

            case 5:
            {
                int graph[GRAPH_SIZE][GRAPH_SIZE] =
                {
                    {0, 4, 2, 0, 0},
                    {4, 0, 1, 5, 0},
                    {2, 1, 0, 8, 10},
                    {0, 5, 8, 0, 2},
                    {0, 0, 10, 2, 0}
                };

                printf("\nFinding related-document distances");
                printf(" from Document 101...\n");

                dijkstra(graph, 0);

                break;
            }

            case 6:
            {
                printf("\n========== ALGORITHMS USED ==========\n");

                printf("\n1. Merge Sort\n");
                printf("   Purpose: Sort documents by ID\n");
                printf("   Complexity: O(n log n)\n");

                printf("\n2. Binary Search\n");
                printf("   Purpose: Search document by ID\n");
                printf("   Complexity: O(log n)\n");

                printf("\n3. KMP\n");
                printf("   Purpose: Search document titles\n");
                printf("   Complexity: O(n + m)\n");

                printf("\n4. 0/1 Knapsack\n");
                printf("   Purpose: Recommendation under");
                printf(" limited reading time\n");

                printf("\n5. Dijkstra\n");
                printf("   Purpose: Find shortest relationship");
                printf(" between documents\n");

                printf("\n=====================================\n");

                break;
            }

            case 0:
            {
                printf("\nThank you for using Digital Library.\n");
                break;
            }

            default:
            {
                printf("\nInvalid choice. Please try again.\n");
            }
        }

    } while (choice != 0);

    return 0;
}