# Custom Adaptive C++ Array

## Author

Abdul-Aziz Nassor HybridTable.cpp, HybridTable.h <br>
Dr. Stanley Fung - HybridTableTester.cpp, HybridTableTester.h, HybridTableTesterMain.cpp, main.cpp, makefile <br>

## Description 

This is a C++ program that creates a custom adaptive array. In other words, this is an array that is originally a fixed size as provided however, upon adding indices that are outside it's bounds, a linked list is created and linked to the array. This makes it "adaptive" and can be resized any time.

A screenshot of how it would look is shown below. 

"Here is a picture showing (conceptually) how the (index, value) pairs (1,-1), (2, 123), (-1, 2046), (7, 97), (99, -2) are stored in a HybridTable where the array part has size 4 (i.e., it handles the index range 0 to 3). In primitive array syntax this is like a[1] = -1, a[2] = 123, a[7] = 97, etc." (Dr. Stanley Fung).

![A screenshot showing the adaptive array](https://github.com/aanassor1/Custom-Adaptive-Array/blob/main/Example_Screenshot.png)

## What I learnt
* Array Manipulation
* Linked List Manipulation
* Data structures
  
## Installation

Go onto Github, find the project and clone the repository.
Afterwards, open bash, locate the destinated file with 'cd', and use git clone on the cloned repository.

```bash
git clone https://github.com/aanassor1/Custom-Adaptive-Array.git
```

Then, use the makefile to compile the C++ files and then run the .exe  that is created.
