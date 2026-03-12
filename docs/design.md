# Design Document – Assignment 1: UNIX  
CSC 412: OS & Networks  

## Approach: Planning First

I am choosing the **planning-first approach**. I will outline which parts of the assignment I will attempt in order, highlight the areas that may be most challenging, describe what I need to research, and give a rough outline of functions, scripts, and data structures I will use.

---

## Plan of Attack (Order of Work)

1. **Set up build.sh**
   - Automate compilation of all C files in the `programs/` directory (and `fio/` as needed).
   - Ensure the script gracefully handles the “no C files” case by printing the required error with the full directory path.
   - Add `-Wall -Werror` flags.

2. **Reimplement Demo Programs in C**
   - **lowercase.c** → convert all input to lowercase.
   - **makewords.c** → break text into one word per line, no blank lines.
   - **mismatch.c** → compare stdin against `unix_dict.text` and output words not found.
   - **sentence.c** → read `unix_sentence.text`, print contents to stdout.
   - **sort.c** → implement sorting without using Linux `sort` or `qsort`.
   - **unique.c** → remove duplicate words.

3. **Reimplement Demo Programs in Bash**
   - Mirror the functionality of the six C programs using Bash and standard GNU utilities (except for the restriction on `sort.sh` which must be implemented without Linux `sort`).
   - Keep each script short and modular.

4. **fio Library Functions**
   - Extend `fio.c`/`fio.h` with:
     - `createFile()`
     - `writeToFile()`
   - Reuse existing `openFile()` as a guide.

5. **unix_demo.sh**
   - Automate the recreation of the 1982 demo:
     - Pipe six compiled C programs → output `unix_c_output.text`.
     - Pipe six Bash scripts → output `unix_bash_output.text`.
   - Verify outputs match.

6. **(Optional) Extra Credit**
   - Attempt `fsrecursive.c` for recursion practice.
   - Pipe results through earlier programs to produce unique, lowercase folder names.

---

## Anticipated Difficulties

1. **Sorting Without Standard Tools**
   - Implementing sorting in C without `qsort` and in Bash without `sort` will be time consuming.
   - I will likely need to implement a manual comparison-based sort (e.g., insertion or merge sort).

2. **Memory Management in C**
   - Reading variable-length input and handling buffers safely.
   - Avoiding memory leaks and ensuring `malloc`/`free` are used correctly.

---

## Research Needs

## Efficient Sorting in C
- Review merge sort and insertion sort; adapt for string arrays with custom comparators.  
- Compare with `qsort()` for efficiency; consider case-sensitivity and locale issues.  
- ⚠️ Debugging Tip: Watch for pointer mismanagement when swapping strings.  

## Bash Utilities for Text Processing
- Use `tr`, `uniq`, `grep`, and `awk` in pipelines for filtering, deduplication, and transformations.  
- Combine `sort` + `uniq` for reliable duplicate removal; test with edge cases.  
- ⚠️ Debugging Tip: Handle tabs, spaces, and special characters carefully.  

## Safe File I/O in C
- Use `fopen`, `fgets`, and `fclose` for safe buffered reads/writes; always validate file pointers.  
- Check for `EOF`/errors and prevent buffer overflows with `sizeof(buffer)`.  
- ⚠️ Debugging Tip: Always close files and test portability (line endings, binary vs text).  

---

## Rough Outline of Functions and Scripts

### C Functions

- `void sentence(void);`  
  Reads the file `unix_sentence.text` from disk and sends its contents to **stdout**.  
  This is the entry point of the pipeline (like `cat` in the demo).  

- `void makewords(void);`  
  Breaks the sentence into individual words, outputting one word per line.  
  Must avoid producing blank lines (handles multiple spaces correctly).  

- `void lowercase(void);`  
  Converts all input characters to lowercase to normalize words before sorting/comparison.  

- `void sort_words(void);`  
  Sorts the list of words alphabetically (cannot use `qsort` or Linux `sort`).  
  Must implement a sorting algorithm manually in C.  

- `void unique_words(void);`  
  Removes duplicate words from the sorted list, outputting only unique entries.  

- `void mismatch(void);`  
  Compares the processed words (from stdin) against the dictionary in `unix_dict.text`.  
  Outputs only the words from stdin that are **missing** in the dictionary.  

---

### FIO Functions (Library in `fio.c` / `fio.h`)

- `FILE* createFile(const char* filename);`  
  Creates (or overwrites) a new file on disk with the given filename.  
  Returns a valid file pointer for writing.  

- `void writeToFile(FILE* file, const char* data);`  
  Writes string data safely to an open file, handling buffers properly.  

These are part of your reusable C I/O library and extend the functionality provided by `openFile`.

---

### Bash Scripts

Each Bash script mirrors the functionality of its C program, using pipelines and core GNU tools.  

- `sentence.sh`  
  Outputs the contents of `unix_sentence.text` to **stdout**.  

- `makewords.sh`  
  Splits sentences into one word per line (e.g., using `tr` or `awk`).  

- `lowercase.sh`  
  Converts all characters to lowercase (e.g., `tr 'A-Z' 'a-z'`).  

- `sort.sh`  
  Sorts the words alphabetically (must implement without calling the system `sort` directly).  

- `unique.sh`  
  Removes duplicate words, leaving only unique ones (commonly `uniq`).  

- `mismatch.sh`  
  Compares stdin words against `unix_dict.text`, outputting words missing from the dictionary.  

- `unix_demo.sh`  
  Runs the **full demo pipeline**:  
  1. Compiles all C programs with `build.sh`.  
  2. Executes the six C programs piped together → writes `unix_c_output.text`.  
  3. Executes the six Bash scripts piped together → writes `unix_bash_output.text`.  
  4. Both outputs must match exactly.  

---

## Summary

My plan is to begin with **build.sh** since it is foundational. Then, I will implement the C programs in the order they appear in the pipeline, followed by the Bash versions. Next, I will extend the fio library and finally implement the demo driver script. The most difficult parts will be **sorting** and ensuring **safe file I/O** in C. To address this, I will research string sorting algorithms in C and safe memory/file handling techniques, as well as explore GNU utilities that simplify Bash solutions.
