# Self-Reflection Document

## What Changed Between the Design Document and the Final Implementation
Initially, my design document focused on implementing each program in a straightforward way, closely mirroring the classic UNIX utilities. However, during implementation, several changes had to be made:

- **Optimization trade-offs**: Some of my early designs used simple but slow approaches (e.g., copying entire buffers with `strdup`, or scanning large fixed-size buffers with `strncmp`). In the final code, I optimized these by reusing buffers and adjusting comparison logic to improve runtime.  
- **Helper functions**: In several programs I introduced helper functions to break down logic and make the code easier to read and maintain.  
- **Lowercase implementation**: My original design separated out the lowercase logic into a dedicated function. In the final implementation I simplified it and put the lowercase transformation directly into `main()`, which reduced unnecessary copying and made the program more efficient.  

## What Worked
- Using **helper functions** improved readability and made debugging easier because each piece of logic was more isolated.  
- The **line-based utilities** (`lowercase`, `makewords`, `unique`, `sort`) produced correct output after reducing redundant memory operations.  
- Simplifying the **lowercase program** to run directly in `main()` made the implementation more efficient without affecting correctness.  


## What Did Not Work  
- Some optimizations (e.g., always comparing up to 1024 chars with `strncmp`) made programs much slower and failed performance tests. I had to revise these comparators to behave more like `strcmp`.  

## Research Topics
During implementation, I had to research several C topics in more detail:

- **File system traversal** with `dirent.h` and `stat` for recursion.  
- **Efficient string comparison** in C, specifically the differences between `strcmp`, `strncmp`, and `strcasecmp`.  
- **UNIX pipelines and redirection** in Bash, to ensure my programs connected seamlessly with each other.  
- **Memory management best practices** (avoiding double frees and reducing unnecessary allocations).  

## Time Spent
Overall, this assignment took approximately **20 hours** to complete:

- 8 hours on initial implementation of all the programs.  
- 6 hours debugging and fixing runtime/memory issues.  
- 4 hours researching.  
- 2 hours writing scripts and testing pipeline integration.  

---

# UNIT Test

# UNIT Test: Large Input File (Harry Potter, Chapter 1)

### Purpose
To verify that the pipeline can handle long, realistic text files and still correctly:
- Split the text into words,
- Convert all words to lowercase,
- Sort alphabetically,
- Remove duplicates,
- Filter out dictionary words using `mismatch`.

This test also validates **performance and scalability** of the pipeline on a larger dataset (tens of thousands of characters).

### Input Data
The input file is the **first chapter of _Harry Potter and the Sorcerer’s Stone_** in plain text format.  
This chapter includes multiple paragraphs, sentences with punctuation, proper nouns, and repeated words.

Example excerpt from the input file:
CHAPTER ONE

THE BOY WHO LIVED

Mr and Mrs Dursley of number four Privet Drive were proud to say that they were perfectly normal thank you very much They were the last people you'd expect to be involved in anything strange or mysterious because they just didn't hold with such nonsense

Mr Dursley was the director of a firm called Grunnings which made drills He was a big beefy man with hardly any neck although he did have a very large mustache Mrs Dursley was thin and blonde and had nearly twice the usual amount of neck which came in very useful as she spent so much of her time craning over garden fences spying on the neighbors The Dursleys had a small son called Dudley and in their opinion there was no finer boy anywhere

### Expected Output Except
acting
admiring
albus
allowed
amuse
an
angrily
anxious
appeared
are
armchair
arms
arrived
asked
astonishing
astounding
astride
aunt
awake
backed
baker's
bakery
balls
beady
beard
beefy
been
behaving
bent

### Why this Shows the Functions Work
Using a long text file, such as the first chapter of *Harry Potter and the Sorcerer’s Stone*, validates the correctness of the pipeline in several ways.

Overall, the long text input confirms that **all stages of the pipeline interact correctly**, not just on small toy examples but also on realistic, complex input.