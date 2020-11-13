#include <iostream> 
#include <queue> 
using namespace std; 
#define ROW 5 
#define COL 2 
  
struct Person { 
  
    int age; 
  
    float height; 
  
    // this will used to initialize the variables 
    // of the structure 
    Person(int age, float height) 
        : age(age), height(height) 
    { 
    } 
}; 
  
// this is an strucure which implements the 
// operator overlading 
struct CompareHeight { 
    bool operator()(Person const& p1, Person const& p2) 
    { 
        // return "true" if "p1" is ordered  
        // before "p2", for example: 
        return p1.height < p2.height; 
    } 
}; 
  
int main() 
{ 
    priority_queue<Person, vector<Person>, CompareHeight> Q; 
  
    // When we use priority_queue with  structure 
    // then we need this kind of syntax where 
    // CompareAge is the functor or comparison function 
    float arr[ROW][COL] = { { 30, 5.5 }, { 25, 5 },  
                    { 20, 6 }, { 33, 6.1 }, { 23, 5.6 } }; 
  
    for (int i = 0; i < ROW; ++i) { 
  
        Q.push(Person(arr[i][0], arr[i][1])); 
  
        // insert an object in priority_queue by using 
        // the Person strucure constructor 
    } 
  
    while (!Q.empty()) { 
        Person p = Q.top(); 
        Q.pop(); 
        cout << p.age << " " << p.height << "\n"; 
    } 
    return 0; 
} 