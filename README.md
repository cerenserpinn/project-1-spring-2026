Ceren Serpin 
Programming Assignment 1

Summary: I implemented a templated Points2D<Objects> class that stores a list of 2D points using dynamic memory. 
- Big five
- indexing
- addition of 2 sequences
- stream input/output.

**Big Five**
Implemented all 5 special member functions
1. Default constructor: Sets sequence_ = nullptr and size_= 0

2. Destructor: delete[] sequence_ to free heap memory.

3. Copy Constructor: Allocations a new heap array of the same size, and copies each point (deep copy).
-Also ensures the new object owns its own memory.

4. Copy Assignment:
- Handles self assignment
- Uses a copy and swap approach: makes a copy of rhs, swaps pointers and sizes

5. Move Constructor:
- Transfers the pointer and size from rhs to the new object
- Sets rhs.sequence_ = nullptr and rhs.size_ = 0 to prevent a double deletion

6. Move Assignment:
- Swaps sequence and size with the rhs object
- Transfers ownership

**Indexing**
Both of the following cuntions check bounds and abort if out of range.
-- const std::array<Object, 2> &operator[](size_t location) const
-- std::array<Object, 2> &operator[](size_t location)

**Addition**
- operator+ returns a new Points2D object: adds (x1 + x2, y1 + y2). if one is longer the remaining points are added (unchanged)
- Computing p_min(overlap) and p_max(result)

**Output**
operator<<
- for an empty object, prints ()
- otherwise prints each point (x,y) (x,y(
- ends outout with a new line

**Input**
- Reads input by first reading the number of points (n) then reads n pairs as object values
Process:
- Allocates a new array new_sequence of size n
- if reading fails while reading pairs, it deletes new_sequence and returns to avoid leaks
- Replaces old data by deleting some_points.sequence_ and assigning the new array 
