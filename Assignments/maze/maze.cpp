#include <memory>
#include <vector>
#include <GL/sgl.hpp>

class DisjointSet {
    std::vector<int> set;
public:
    DisjointSet(int numElements): set(numElements) { 
        for (int i = 0; i < (int) set.size(); i++) {
            set[i] = i;
        }
    }

    //Returns the "parent" element of an equivalence class
    int Find(int i) {
        if (set[i] != i)
            set[i] = Find(set[i]);
        return set[i];
    }

    //Combines two equivalence classes, smaller class is pointed to the larger class
    void Union(int a, int b) {
        int set1 = Find(a);
        int set2 = Find(b);
        if (Cardinality(set1) >= Cardinality(set2))
            set[set2] = set1;
        else
            set[set1] = set2;
    }

    //Takes a set and puts each element from it inside its own equivalence class
    void Split(int a) {
        std::vector<int> temp;
        for (int i = 0; i < (int) set.size(); i++) {
            if (Find(set[i]) == a) {
                temp.push_back(i);
            }
        }

        for (int item : temp) {
            set[item] = item;
        }
    }

    //Returns the number of items in a set
    int Cardinality(int a) {
        int count = 0;
        for (int i = 0; i < (int) set.size(); i++) {
            if (Find(set[i]) == a)
                count++;
        }

        return count;
    }
};

class MazeCell {
    double x, y;
    int cellIndex;
public:
    MazeCell(double x, double y, int cell) : x(x), y(y), cellIndex(cell) { }
    MazeCell() : x(0), y(0), cellIndex(0) { }
    double get_x() { return x; }
    double get_y() { return y; }
    int get_index() { return cellIndex; }
};

class Maze: public sgl::Window {
    std::vector<std::vector<MazeCell>> maze;
    double cellWidth, cellHeight;
    int cellCount;
public:
    Maze(int cellsX, int cellsY) : maze(cellsY, std::vector<MazeCell>(cellsX)),
        sgl::Window("Maze Generator - Miro Manestar", 0, 600, 0, 400) { 
            cellWidth = get_max_x()/(cellsX + 2);
            cellHeight = get_max_y()/(cellsY + 2);
            make_maze();
        }

    void paint() override {
        sgl::set_color(sgl::BLACK);
        
    }

    void make_maze() {
        for (int y = 0; y < (int) maze.size(); y++) {
            for (int x = 0; x < (int) maze[y].size(); x++) {
                maze[y][x] = MazeCell((x + 1) * cellWidth, (y + 1) * cellHeight, y * (maze.size() - 1) + x);
            }
        }
    }
};

int main() {
    Maze maze(40, 25);
}