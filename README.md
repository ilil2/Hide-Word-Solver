# Hide-Word-Solver

This project includes ANNA, a tool for processing images to detect hidden words, and a word solver that searches for specific words within a character grid. 

## ANNA Usage

To use ANNA, follow these steps:

### 1. Compile ANNA
- Navigate to the `HideWordSolver/` folder.
- Run `make` to compile the executable.
- Launch ANNA with `./ANNA-Solver-IA`.

### 2. Use ANNA
- **Main Page**
  - Select a PNG file to load.
  - Enable "Step by Step" mode.
  - Press "Start" to begin processing.
- **Step by Step**
  - Click "Next" to grayscale and binarize the image.
  - Specify the degree for image straightening, then press "Next" to apply.
  - Continue through the steps to detect letters.

## Proof of Concept (POC)

To test the Proof of Concept for ANNA, follow these steps:

### 1. Compile the POC
- Navigate to `HideWordSolver/ANNA/Poc/`.
- Run `make` to build the executable.
- Start the POC with `./poc`.

### 2. Use the POC
- Input `0` or `1` for letter `A`, add a space, then input `0` or `1` for letter `B` to perform an NXOR operation.

## Solver Usage

The solver searches for a specified word within a text grid. The solver takes two arguments:
- A text file containing a grid of uppercase letters. The grid must have at least five rows and five columns.
- The word to search for, which can be in uppercase or lowercase.

The program will output:
- "Not Found" if the word is not present in the grid.
- `(x0,y0)(x1,y1)` if the word is found, where:
  - `(x0,y0)` is the starting coordinate of the first letter in the grid.
  - `(x1,y1)` is the ending coordinate of the last letter.

Coordinates `(0,0)` correspond to the top-left corner of the grid.

### 1. Compile the Solver
- Navigate to `HideWordSolver/Solver/`.
- Run `make` to build the executable.
- Use the solver by running `./solver {grid_file} {word}`.

### 2. Use the Solver
- Provide the path to the grid file and the word to search as command-line arguments.
