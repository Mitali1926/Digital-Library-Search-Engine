# Digital Library Search and Recommendation Engine

A menu-driven Digital Library application implemented in C.

The system loads document information from a CSV file and provides
document searching, title searching, recommendations and related-document
analysis using suitable data structures and algorithms.

## Features

- Load library documents from a CSV file
- Display all available documents
- Search documents using Document ID
- Search documents using title keywords
- Recommend documents according to subject
- Recommend documents according to available reading time
- Find relationships between documents
- Handle invalid user input

## Algorithms Used

### 1. Merge Sort

Used to sort documents according to Document ID.

Time Complexity: O(n log n)

### 2. Binary Search

Used to search for a document using its ID after the documents have
been sorted.

Time Complexity: O(log n)

### 3. KMP Pattern Matching

Used to search for words or phrases inside document titles.

Time Complexity: O(n + m)

### 4. 0/1 Knapsack

Used to recommend an optimal collection of documents when the user
has limited reading time.

Document reading time represents weight and recommendation score
represents value.

### 5. Dijkstra's Algorithm

Used to find minimum-distance relationships between connected
documents in the document graph.

## Technologies

- C Programming Language
- GCC Compiler
- Visual Studio Code
- CSV File Handling
- Git and GitHub

## Project Structure

DigitalLibrary/
- main.c
- documents.csv
- README.md
- .gitignore

## How to Compile

```bash
gcc main.c -o app.exe