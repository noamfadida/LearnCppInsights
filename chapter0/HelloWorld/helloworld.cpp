#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<string> msg{"Hello", "World", "with", "VSCode", "for", "C++"};
    for(const string& word : msg){
        cout << word << " ";
    }
    cout << endl;
}