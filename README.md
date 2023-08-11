# OS-Manager
 This program serves as an educational tool to showcase and simulate various operating system concepts, such as memory allocation algorithms, page replacement strategies, file attributes retrieval, and multi-threading using POSIX threads. It's designed to help learners understand how these concepts work 

# Usability
Main Function (main):

The main function is the entry point of the program.
It displays a menu to the user with different options: Memory Management, File Management, Multi-Threads, Page Replacement, and Exit.
The user can choose an option, and based on their choice, different functions are called.
Memory Management (memoryManagement):

This section demonstrates different memory allocation algorithms: First Fit, Best Fit, Worst Fit, and Next Fit.
Each algorithm is implemented as a separate function (firstFit, bestFit, worstFit, nextFit).
For each algorithm, the program simulates memory allocation for a set of processes using a set of memory blocks.
The allocation results (which process is assigned to which block) are displayed.
Page Replacement (pageReplacement):

This section demonstrates two page replacement algorithms: First-In-First-Out (FIFO) and Least Recently Used (LRU).
Each algorithm is implemented as a separate function (fifo, lru).
The program simulates page replacement for a sequence of page requests, showing how pages are allocated in memory frames and how page faults occur.
File Attributes (fileAttributes):

This section displays attributes of files in the current directory.
It uses the readdir function to iterate through files and the stat function to obtain file attributes (e.g., owner, permissions, size, timestamps).
The attributes are printed for each file.
Multi-Threads (multiThreads):

This section demonstrates multi-threading using POSIX threads (pthread library).
It creates a specified number of threads, each running the threadFunction.
The threads execute concurrently, and the output demonstrates their execution order.
Thread Function (threadFunction):

This function is used as the entry point for each thread created in the multiThreads section.
It prints a series of messages to simulate thread execution.
Helper Functions (clearScreen, displayMenu, displayProcess, displayPages, printAttributes, findLRU):

These functions provide various utilities for clearing the screen, displaying menus, printing information, and aiding the main functionalities of the program.
