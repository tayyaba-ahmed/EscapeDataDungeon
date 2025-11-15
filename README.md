# Data Dungeon

Data Dungeon is an educational C++/Qt game that teaches and visualizes fundamental Data Structures (Stacks, Queues, Arrays, Heaps, Linked Lists, BSTs) through interactive puzzles. Players navigate through dungeon rooms, solve puzzles, and learn data structures while enjoying a gamified experience.

## Table of Contents
1) Features
2) Installation
3 )Gameplay
4) Data Structures Used and Justification
5) Project Structure in QT

## Features
- Interactive Puzzles: Each room presents a puzzle based on a specific data structure.
- DSA Visualization: Dynamic display of stacks, queues, arrays, heaps, BSTs, and linked lists.
- Health System: Players have 3 lives; wrong answers deduct health visually.
- Timed Challenges: Rooms have countdown timers to increase difficulty.
- Trap Room & Secret Code: Special room with a secret code puzzle.
- Story Dialog: Engaging story slides with fade-in/out animations.
- Custom Fonts & Styling: Enhanced user experience with custom fonts, animations, and graphics.

## Installation/Setup
Requirements:
- Qt 5.x or 6.x (Qt Creator recommended)
- C++17 compiler (GCC, Clang, or MSVC)
Steps:
1) Clone the repository:
  - git clone <repository_url>
2) Open the project in Qt Creator
   - Click on open project
   - Select CMakeLists.txt
   - Click on configure project
3) Build and run the project.

## Gameplay
1) Launch the game → story slides appear.
2) Press Start Game to begin the dungeon challenge.
3) Navigate through rooms:
   - Solve the puzzle shown in the room.
   - Type your answer in the input box and press Submit.
   - Watch the animated data structures (stack, queue, etc.) as hints.
4) Health:
   - Wrong answers deduct one heart from your health stack.
   - Collect the key in some rooms to gain an extra heart.
5) Timer: Each room has a countdown timer; failing to answer deducts health.
6) Complete all rooms to escape and reveal the secret code word.

## Data Structures Used and their justification for Use
Data Structure:
1) Stack:
   - Purpose: Represents player health visually; used in stack puzzles.
   - Justification: LIFO behavior naturally models “last life lost first” and stack puzzles rely on top-to-bottom order.
2) Queue:
   - Purpose: Used in queue-based puzzles and element animations.
   - FIFO behavior mirrors real queue operations, ideal for animating elements in order of arrival.
3) Vector:
   - Purpose: Stores puzzle data for arrays, stacks, queues, heaps, and linked lists.
   - Justification: Provides dynamic, contiguous storage with fast indexed access, making it suitable for generating puzzle elements.
4) Priority Queue (Min-Heap):
   - Purpose: Visualizes heap puzzles with proper ordering.
   - Justification: Min-heap ensures automatic ordering by priority, matching heap puzzle requirements and visualization of tree levels.
5) Linked List:
   - Purpose: Handles linked list puzzle logic and visualization.
   - Justification: Naturally models sequential nodes with pointers, perfect for linked list manipulation puzzles.
6) Binary Search Tree (BST):
	 - Purpose: Binary Search Tree puzzles with visualization of nodes per level.
   - Justification: BST structure allows ordered insertion and retrieval, making level-based visualization intuitive for players.
     
# Project Structure in QT
EscapeDataDungeon/
- CMakeLists.txt
- Forms/
  - mainWindow.ui 
- Header Files/
  - mainWindow.h   
  - gameengine.h
  - puzzlebase.h   
  - arraypuzzle.h 
  - stackpuzzle.h     
  - queuepuzzle.h 
  - heapuzzle.h      
  - linkedlistpuzzle.h
  - bstpuzzle.h      
  - storydialog.h 
  - trappuzzle.h 
├─ Resources/
│  ├─ resources.qrc 
│  ├─ ├─ images/ // Contains images 
│  ├─ ├─ fonts/ // Contains custom fonts 
├─ Source Files/
│  ├─ main.cpp 
│  ├─ mainWindow.cpp 
│  ├─ gameengine.cpp  
│  ├─ puzzlebase.cpp   
│  ├─ arraypuzzle.cpp    
│  ├─ stackpuzzle.cpp     
│  ├─ queuepuzzle.cpp   
│  ├─ heapuzzle.cpp      
│  ├─ linkedlistpuzzle.cpp
│  ├─ bstpuzzle.cpp    
│  ├─ bstpuzzle.cpp 
│  ├─ storydialog.cpp    
│  ├─ trappuzzle.cpp 
