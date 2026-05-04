/*
- In this code we try to do the following:
    - create 

*/

#include <iostream>
#include <string>

using namespace std;

class Grandfather {
private:
    string legacy;
    int wealth;

public:
    Grandfather(string l, int w) : legacy(l), wealth(w) {}
    
    // Default constructor for when Father wants to be "Self-Made"
    Grandfather() : legacy("Standard Honesty"), wealth(1000) {}

    string getL() { return legacy; }
};

class Father : public Grandfather {
private:
    string business;
    int properties;

public:
    // OVERLOAD 1: Takes info for itself AND the Grandfather
    Father(string l, int w, string b, int p) 
        : Grandfather(l, w), business(b), properties(p) {
        cout << "Father: Using Grandfather's specific legacy." << endl;
    }

    // OVERLOAD 2: Only takes info for itself, lets Grandfather use Defaults
    Father(string b, int p) 
        : Grandfather(), business(b), properties(p) {
        cout << "Father: Starting fresh with a Default Grandfather legacy." << endl;
    }

    string getB() { return business; }
};

class Grandchild : public Father {
private:
    string hobby;
public:
    // This Grandchild call will trigger Father's Overload 2
    Grandchild(string b, int p, string h) 
        : Father(b, p), hobby(h) { 
        cout << "Grandchild created via 'Self-Made' Father." << endl;
    }
};

int main() {
    Grandchild g("Tech Startup", 2, "Gaming");
    cout << "Legacy inherited: " << g.getL() << endl;
    return 0;
}