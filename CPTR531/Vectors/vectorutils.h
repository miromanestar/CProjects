#ifndef VECTORUTILS_H_INCLUDED_
#define VECTORUTILS_H_INCLUDED_

#include <vector>

//------------------------------------------------
//  Returns the maximum value in vector v.
//  The result is undefined if v is empty.
int maximum(const std::vector<int>& v);

//------------------------------------------------
//  Returns the position of the value seek
//  within vector v. 
//  Returns -1 (never a valid position in a
//  C++ vector) if seek is not an element of v.
int find(const std::vector<int>& v, int seek);

//------------------------------------------------
//  Returns the number of times the value seek
//  appears within vector v. 
//  Returns 0 if seek is not an element of v.
int count(const std::vector<int>& v, int seek);

//------------------------------------------------
//  Returns true if vectors v1 and v2 contain 
//  exactly the same elements, regardless of their
//  order; otherwise, the function returns false. 
bool equivalent(const std::vector<int>& v1, const std::vector<int>& v2);

//------------------------------------------------
//  Physically rearranges the elements of v
//  so they appear in order from lowest value
//  to highest value.
void sort(std::vector<int>& v);

//------------------------------------------------
//  Removes the first occurrence of element
//  del from vector v.  (The first occurrence
//  has the lowest index.)
//  The vector is unaffected if del is not an
//  element of v.
//  The function returns true if a element is
//  removed; otherwise, it returns false if
//  del does not appear in v.
bool remove_first(std::vector<int>& v, int del);

#endif