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

## Output example
```
(3/7 3/5 2/7 1/5 | 8)
(1 5/9 9/4 1 | 1)
(8/3 5/6 0 5/6 | 7/8)
(1 3/7 3/7 2/3 | 9/4)

... inverted
(-6525/13421 31680/93947 81642/93947 -19410/13421 | 0)
(30375/13421 -30852/93947 -30186/93947 2889/13421 | 0)
(-380/13421 66636/93947 23760/93947 -18408/13421 | 0)
(-9495/13421 -70524/93947 -118332/93947 59223/13421 | 0)

Answers:
(1 0 0 0 | -2271963/375788)
(0 1 0 0 | 1689237/93947)
(0 0 1 0 | -223780/93947)
(0 0 0 1 | 907911/375788)
--- #1 ---
x1 = -2271963/375788
x2 = 1689237/93947
x3 = -223780/93947
x4 = 907911/375788
Determinator: 13421/22680
(-2271963/375788 1689237/93947 -223780/93947 907911/375788)
1ms for 4x4
(1 0 0 0 | 0)
(0 1 0 0 | 0)
(0 0 1 0 | 0)
(0 0 0 1 | 0)
--- #1 ---
x1 = 0
x2 = 0
x3 = 0
x4 = 0
Determinator: 22680/13421
(0 0 0 0)
1ms for 4x4
```
