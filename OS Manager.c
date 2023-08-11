
// by Nicholas Donofrio

// C Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>

// Global Constants
#define EXIT 0
#define INVALID -1
#define MEMORY 1
#define FILES 2
#define THREAD 3
#define FIRST 0
#define BEST 1
#define WORST 2
#define NEXT 3
#define PAGE 4
#define FIFO 0
#define LRU 1
#define FRAMES 3
#define SIZE 7 // Define constant SIZE


// DEFINE  - Uncomment if you need libraries
/*
#define S_IRGRP 0040 // Read permission for group
#define S_IWGRP 0020 // Write permission for group
#define S_IXGRP 0010 // Execute permission for group
#define S_IROTH 0004 // Read permission for others
#define S_IWOTH 0002 // Write permission for others
#define S_IXOTH 0001 // Execute permission for others
*/


// Preprocessor function prototypes
void clearScreen();
void memoryManagement();
void displayProcess();
void firstFit();
void worstFit();
void bestFit();
void nextFit();
void pageReplacement();
void lru();
//void findLRU(int time[]);
void fifo();
void displayPages();
void printAttributes();
void fileAttributes();
void multiThreads(void);
void *threadFunction(void *arg);

// Main
int main()
{
    // Stores the user's choice
    int choice = INVALID;

    while (choice != EXIT)
    {
        choice = displayMenu();

        switch (choice)
        {
            case MEMORY:
                memoryManagement();
                break;

            case FILES:
                fileAttributes();
                // do nothing for this assignment
                break;
            case THREAD:
                multiThreads();
                break;

            case PAGE:
                pageReplacement();
                break;

            case EXIT:
                printf("Exiting program...\n");
                break;
        }
        //clearScreen();
    }
    return 0;
}
// ClearScreen function
void clearScreen()
{
    // Prompts user to press enter
    printf("Press enter to continue...\n");

    // Char variable used for user input
    char c;
    scanf("%c", &c);

    // If user does not press enter
    if (c != '\n')
    {
      printf("Error! Reference source not found.");
      clearScreen();
      return;
    }

    // Other cases
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Display menu function
int displayMenu()
{
    // Stores the user's choice
    int choice = INVALID;

    while (choice == INVALID)
    {
        // Prints that display choices
        printf("********** Operating System Management Menu **********\n");
        printf("\nSelect the OS program to run, enter the number of your selection.\n");
        printf("1. Memory Management\n");
        printf("2. File Management\n");
        printf("3. Multi-Threads\n");
        printf("4. Page Replacement\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // If choice is invalid
        if (choice >= EXIT && choice > PAGE)
        {
            printf("Invalid choice. Please enter a value between 0 and 4.\n");
            choice = INVALID;
        }
    }

    return choice;
}

// MemoryManagement Function
void memoryManagement()
{

  // C. Call function clearScreen
   clearScreen();

  // Print
  printf("********** Memory Management **********\n\n");




    // Variable to store number of blocks
    int blocks = 5;

    // Variable to store number of processes
    int processes = 5;


  //  nextFit(blockSize, blocks, processSize, processes);



    // Decision making logic using switches
    for (int algorithm = FIRST; algorithm <= NEXT; algorithm++)
    {

       // One dimensional array for memory blocks
   int blockSize[] = {80, 10, 65, 35, 70};

    // One dimensional array for process size
    int processSize[] = {25, 70, 5, 45, 60};
        char* algorithmnName;
        // Calls each function respectively
        switch (algorithm)
        {
            case FIRST:
                //algorithmnName = "First Fit";
                firstFit(blockSize, blocks, processSize, processes);
                printf("\n\n");
                break;
            case BEST:
                //algorithmnName = "Best Fit";
                bestFit(blockSize, blocks, processSize, processes);
                printf("\n\n");
                break;
            case WORST:
               // algorithmnName = "Worst Fit";
                worstFit(blockSize, blocks, processSize, processes);
                printf("\n\n");
                break;
            case NEXT:
               // algorithmnName = "Next Fit";
                nextFit(blockSize, blocks, processSize, processes);
                printf("\n\n");
                break;
        }
       // printf("**********%s*******************************\n", algorithmnName);
       // printf("\n");
    }
}




// Function firstFit
void firstFit(int blockSize[], int blocks, int processSize[], int processes)
{

  printf("****** First Fit *********\n\n");
  // One dimensional array to store block id
  int allocation[processes];

  // Call function memset - Allocation, 1, sizeof(allocation)
  memset(allocation, INVALID, sizeof(allocation));

  // Loop to loop through amount of processes
  for (int i = 0; i < processes; i++)
  {
      for (int j = 0; j < blocks; j++)
      {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
      }
  }

    //clearScreen(); // ensures a clean output

    // Call function displayProcess
    displayProcess(allocation, processes, processSize);
}

// bestFit function
void bestFit(int blockSize[], int blocks, int processSize[], int processes)
{

    printf("***** Best Fit *********\n\n");
    // C. Array that stores block id
    int allocation[processes];

    // D. Call function memset
    memset(allocation, INVALID, sizeof(allocation));

    // Loop construct
    for (int i = 0; i < processes; i++)
    {
        // Find idex of the best fit block for current process
        int bestIdx = INVALID;
        for (int j = 0; j < blocks; j++)
        {
            // Check if the block is large enough to fit in current process
            if (blockSize[j] >= processSize[i])
            {
                // If this is the first block that fits set it as best fit
                if (bestIdx == INVALID)
                    bestIdx = j;
                // If this block is smaller update
                else if (blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }

      // If a block was found allocate the proces to it
        if (bestIdx != INVALID)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    // Call function displayProcess
    displayProcess(allocation, processes, processSize);
}

// worstFit function
void worstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    // Print header
    printf("***** Worst Fit *********\n\n");

    // Initialize array to store block ID
    int allocation[processes];

    // Set all values in allocation array to an invalid value
    memset(allocation, INVALID, sizeof(allocation));

    // Loop over each process
    for(int i = 0; i < processes; i++)
    {

        // Find the idnex of the best fit block for current process
        int wstIdx = INVALID;

        for(int j = 0; j < blocks; j++)
        {
            // Check if the block is large enough
            if(blockSize[j] >= processSize[i])
            {
                // If this is the firs tblock that fits set it
                if(wstIdx == INVALID)
                {
                    wstIdx = j;
                }

                // If this blockl is smaller than current best fit update it
                else if(blockSize[wstIdx] < blockSize[j])
                {
                    wstIdx = j;
                }
            }
        }

        // If a block was found allocate it
        if(wstIdx != -1) {
            allocation[i] = wstIdx;
            blockSize[wstIdx] -= processSize[i];
        }
    }


    displayProcess(allocation, processes, processSize);
}


// Function nextFit
void nextFit(int blockSize[], int blocks, int processSize[], int processes)
{

    printf("***** Next Fit *******************\n\n");
  // C. One-dimensional array to store block ID that is process allocated
  int allocation[processes];

  // D. Store block allocation for processes initialize to 0
  int id = 0;

  // E. Call function memset and pass
  // Array allocation, -1, sizeof(allocation)
  memset(allocation, INVALID, sizeof(allocation));

  // F. Using a looping construct loop while id is less than number of blocks
  for (int i = 0; i < processes; i++)
  {
        // 1. If current block size is greater than or equal to current processes size
        while (id < blocks)
        {
            if (blockSize[id] >= processSize[i])
            {
                // Update allocation array to set element at index to variable ID
                allocation[i] = id;

                // Reduce available memory of block size
                blockSize[id] -= processSize[i];

                // Break out of the inner loop
                break;
            }

            // Update the variable ID to set the next index
            id = (id + 1) % blocks;
        }
    }

  // G. Call function displayProcess passing arguments
  displayProcess(allocation, processes, processSize);
}

void displayProcess(int allocation[], int processes, int processSize[])
{

    // Print header
    printf("Process No.\tProcess Size\tBlock No.\n");

    // Loop over each process
    for (int i = 0; i < processes; i++)
    {
        // Print process number and size
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        // CHeck if process has been allocated to a block of memory
        if (allocation[i] == INVALID)
        {
            // If not print not allocated
            printf("Not Allocated\n");
        }
        else
        {
            //If so print block number
            printf("%d\n", allocation[i] + 1);
        }
    }
}


// pageReplacement Function
void pageReplacement()
{
    // Call clearScreen function
    clearScreen();

    // loop for each of the two page replacement algorithms
    for (int algorithm = FIFO; algorithm <= LRU; algorithm++)
    {
        // decision making logic based on the value of the looping variable (i.e., algorithm)
        switch (algorithm)
        {
            case FIFO:
                fifo();
                break;
            case LRU:
                lru();
                break;
        }
    }
}
void fifo(void)
{
    // Declare a one-dimensional array, data type integer, to store the page requests (i.e., pageRequests) initialized to data set 4 , 1, 2, 4, 2, 5, 1, 3, 6
    int pageRequests[] = {4, 1, 2, 4, 2, 5, 1, 3, 6};

    // Declare a variable, data type integer, to store the page faults, initialize to 0 (i.e., pageFaults)
    int pageFaults = 0;

    // Declare a one-dimensional array, data type integer, to store the memory frame a page is allocated to (i.e., allocation), size is parameter FRAMES
    int allocation[FRAMES];

    // Declare a variable, data type integer, to store page hits (i.e., present)
    int present = 0;

    // Declare a variable, data type integer, to store number of pages (i.e., pages) initialized to the number of page requests
    int pages = 9;

    memset(allocation, -1, sizeof(allocation));

    printf("********* Page Replacement *********\n\n");
    printf("********* First In First Out *********\n\n");
    printf("Page\tFrame 1\tFrame 2\tFrame 3\n");


     for (int i = 0; i < pages; i++)
     {
        present = 0;

        for (int j = 0; j < FRAMES; j++) {
            if (allocation[j] == pageRequests[i]) {
                present = 1;
                pageFaults--;
                break;
            }
        }

        pageFaults++;
        if (pageFaults <= FRAMES && present == 0)
        {
            allocation[pageFaults - 1] = pageRequests[i];
        }
        else if (present == 0)
        {
            allocation[(pageFaults - 1) % FRAMES] = pageRequests[i];
        }

        displayPages(pageRequests[i], allocation);
    }

    printf("\nTotal number of page faults: %d\n\n", pageFaults);
}

// Write function findLRU
int findLRU(int time[])
{
    int position = 0;
    int minimum = time[0];

    for (int i = 1; i < FRAMES; i++)
    {
        if (time[i] < minimum) {
            minimum = time[i];
            position = i;
        }
    }

    return position;
}

// Fifo Function
void lru()
{

    // Write a series of printf statements to display the algorithm name and the output header
    printf("********* Least Recently Used *********\n\n");
    printf(" Page   Frame 1   Frame 2   Frame 3\n");

    // Declare a one dimensional array pageRequests = 4,1,2,4,2,5,1,3,6
    int pageRequests[] = {4, 1, 2, 4, 2, 5, 1, 3, 6};

    // Declare a variable, data type integer to store page faults = 0
    int pageFaults = 0;

    // Declare a array to store memory frame a page is allocated
    int allocation[FRAMES];

    // Declare a variable initialized to number of page requests PAGES
    int pages = 9;

    // Declare a variable to store page hits ie. counter
    int counter = 0;

    // Declare a array ie time where size parameter is 10
    int time[10];

    // Flag variables
    int flag1, flag2;

    // Variable for position
    int position = 0;

    // Initialize the allocation array
    memset(allocation, INVALID, sizeof(allocation));
    //memset(time, INVALID, sizeof(time));



    for (int i = 0; i < pages; i++)
    {
        flag1 = flag2 = 0;
        for (int j = 0; j < FRAMES; j++)
        {
            if (allocation[j] == pageRequests[i]) {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0)
        {
            for (int j = 0; j < FRAMES; j++)
            {
                if (allocation[j] == INVALID)
                {
                    counter++;
                    pageFaults++;
                    allocation[j] = pageRequests[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }
        if (flag2 == 0) {
            position = findLRU(time);
            counter++;
            pageFaults++;
            allocation[position] = pageRequests[i];
            time[position] = counter;
        }
        displayPages(pageRequests[i], allocation);
    }

    printf("\nTotal page faults: %d\n", pageFaults);
}

void displayPages(int page, int allocation[]) {
    printf("%d\n", page);
   // printf("Memory Block Assigned: ");

    for (int i = 0; i <FRAMES; i++) {
        if (allocation[i] == -1) {
            printf("-\t ");
        } else {
            printf("%d\t ", allocation[i]);
        }
    }

    //printf("\n");
}
void printAttributes(char name[], struct stat statBuff) {
    time_t t;
    char timeStr[100];

    // Output file name
    printf("\n------------File Name: %s------------\n", name);

    // Output file device ID
    printf("Device ID: %ld\n", statBuff.st_dev);

    // Output file serial number
    printf("Serial Number: %ld\n", statBuff.st_ino);

    // Output file user ID
    printf("User ID: %d\n", statBuff.st_uid);

    // Output file group ID
    printf("Group ID: %d\n", statBuff.st_gid);

    // Output file mode
    printf("File Mode: %lo\n", (unsigned long)statBuff.st_mode);

    // Output file owner permissions
    printf("Owner Permissions: ");
    printf((statBuff.st_mode & S_IRUSR) ? "r" : "-");
    printf((statBuff.st_mode & S_IWUSR) ? "w" : "-");
    printf((statBuff.st_mode & S_IXUSR) ? "x" : "-");
    printf("\n");

    // Output file group permissions
    printf("Group Permissions: ");
    printf((statBuff.st_mode & S_IRGRP) ? "r" : "-");
    printf((statBuff.st_mode & S_IWGRP) ? "w" : "-");
    printf((statBuff.st_mode & S_IXGRP) ? "x" : "-");
    printf("\n");

    // Output file other permissions
    printf("Other Permissions: ");
    printf((statBuff.st_mode & S_IROTH) ? "r" : "-");
    printf((statBuff.st_mode & S_IWOTH) ? "w" : "-");
    printf((statBuff.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    // Output file creation date
    t = statBuff.st_ctime;
    struct tm *localTime = localtime(&t);
    if (localTime == NULL) {
        printf("Error: could not get local time\n");
    } else {
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
        printf("Created: %s\n", timeStr);
    }

    // Output file last modification date
    t = statBuff.st_mtime;
    localTime = localtime(&t);
    if (localTime == NULL) {
        printf("Error: could not get local time\n");
    } else {
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
        printf("Last Modified: %s\n", timeStr);
    }

    // Output file last accessed date
    t = statBuff.st_atime;
    localTime = localtime(&t);
    if (localTime == NULL) {
        printf("Error: could not get local time\n");
    } else {
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
        printf("Last Accessed: %s\n", timeStr);
    }

    // Output file size
    printf("Size: %ld bytes\n", statBuff.st_size);
}



// Function to get attributes of all files in current directory
void fileAttributes() {
    struct dirent *de;
    struct stat statBuff;
    int err;
    DIR *dr = opendir(".");

    if (dr == NULL) {
        printf("Could not open current directory");
        return;
    }

    while ((de = readdir(dr)) != NULL) {
        // Skip special directory entries
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
            continue;
        }

        err = stat(de->d_name, &statBuff);

        if (err == -1) {
            printf("Error in stat\nPress `Enter' to continue . . .");
            getchar();
        } else {
            printAttributes(de->d_name, statBuff);
        }
    }

    closedir(dr);
}

void multiThreads(void)
{
    int i, error;
    pthread_t tid[SIZE]; // Declare thread ID array

    for (i = 0; i < SIZE; i++) {
        // Create a thread for each element in tid
        error = pthread_create(&tid[i], NULL, threadFunction, (void *)&tid[i]);

        if (error != 0) { // Thread creation failed
            printf("\nThread can't be created: [%s]\n", strerror(error));
            exit(EXIT_FAILURE); // Terminate the program
        }
    }

    for (i = 0; i < SIZE; i++) {
        // Wait for each thread to complete before continuing
        error = pthread_join(tid[i], NULL);

        if (error != 0) { // Thread joining failed
            printf("\nThread can't be joined: [%s]\n", strerror(error));
            exit(EXIT_FAILURE); // Terminate the program
        }
    }
}


void* threadFunction(void* vargp)
{
    // Loops 3 times
    const int LOOP = 3;
    int i;
    int* myid = (int*)vargp;
  
    printf("\n----------------------------\nThread #%d has started\n----------------------------\n\n", *myid);
    for (i = 0; i < LOOP; i++) 
    {
        printf("Thread #%d printing iteration %d\n", *myid, i+1);
    }
    printf("\n----------------------------\nThread ID %d has finished\n----------------------------\n\n", *myid);
    return NULL;
}



