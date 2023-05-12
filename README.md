## Augmented matrix class (+ fraction class)
Basic Augmented matrix operations

### Usage

*matrix.cpp and matrixops.cpp are excluded from VC solution*  
`T - template type (int/double/fractions/etc.)`  
There's `+, =, *, /, [], <<` operators  
`/` finds inverse matrix for second matrix and then multiplies first by second  

- Constructor:
```cpp
Matrix(size_t w, size_t h, size_t right_part = 0, bool one = 0);
```
>size_t w: width of Matrix (columns, including right part)  
>size_t h: height of Matrix (rows)  
>size_t right_part: right part of Matrix (<=> B in Ax=B)  
>if 0, auto-add (0, 0, 0,...) column at the right part  
>bool one: initialize Identity Matrix (E)
- Swap:
```cpp
bool swap(size_t l1, size_t l2);
```
Swaps two lines  
>size_t l1: line 1 index  
>size_t l2: line 2 index  
>**INDEXES START FROM 1**  
>Returns: 1 -> error  
- Add line:
```cpp
void addline(T *arr);
```
Add new row at the end of Matrix (if it's not full)  
>T *arr: array of elements with length of **width**  
- Show:
```cpp
void show(ostream& output = cout);
```
Prints matrix to your ostream (file/cout/etc.)  
Equivalent for `output << matrix;` 
>ostream& output: ostream  
- Start solving
```cpp
void startsolve(bool jord = 1, bool quiet = 0, ostream& output = cout);
```
>bool jord: Gaussian-Jordan method?  
>bool quiet: 1 -> don't show you possible solutions and result matrix  
>ostream& output: if not quiet, function prints here...  
- Is solved?
```cpp
bool is_solved();
```
Not solved if 0 = n row was detected after solving.  
- Check 0 = n rows
```cpp
bool checkzeroerror(size_t rpart);
```
`startsolve` does this automatically, but you still can use it  
>size_t rpart: index of right part column (**STARTS FROM 1, ENDS AT `right_part`**)  
>Returns: 1 -> 0 = n row detected  
- Add row multiplied by coef to another row
```cpp
bool summarize(size_t from, size_t to, T coef);
```
>**INDEXES START FROM 1**  
>Returns: 1 -> error  
- Divide (~Multiply) row by coef
```cpp
bool division(size_t to, T coef);
```
>**INDEXES START FROM 1**  
>Returns: 1 -> error  
- Transpose your matrix
```cpp
Matrix<T> transposed();
```
It will destroy right part columns  
>Returns: transposed matrix  
- Determinator
```cpp
T Determinator();
```
- Cancel determinator  
```cpp
void killholds();
```
## Fraction class
A lot of operators.
Overflows easily in big matrices (10x10 or bigger)  
