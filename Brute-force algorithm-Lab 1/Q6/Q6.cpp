#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Item{
    int weight, value;
};

void outputFile(const vector<int>& chosenItems, int value){
    ofstream outp("6_out.txt");
    if (!outp){
        cout << "Output fail!";
        return;
    }
    for (const int& i : chosenItems)
        outp << i << " ";
    outp << endl << value;

    outp.close();
}

int knapsack_BruteForce(const vector<Item>& items, vector<int>& chosenItems, int n, int capacity){
    if (n == 0 || capacity == 0)
        return 0;

    if (items[n - 1].weight > capacity)
        return knapsack_BruteForce(items, chosenItems, n - 1, capacity);

    vector<int> withLastItem = chosenItems;
    vector<int> withoutLastItem = chosenItems;

    int withLastItemValue = items[n - 1].value + knapsack_BruteForce(items, withLastItem, n - 1, capacity - items[n - 1].weight); 
    int withoutLastItemValue = knapsack_BruteForce(items, withoutLastItem, n - 1, capacity);

    if (withLastItemValue > withoutLastItemValue){
        chosenItems = withLastItem;
        chosenItems.push_back(n);
        return withLastItemValue;
    }
    else{
        chosenItems = withoutLastItem;
        return withoutLastItemValue;
    }
}

int main(){
    int capacity, n;
    vector<int> chosenItems;

    // Input file
    ifstream inp("6.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }

    inp >> capacity;
    inp >> n;
    vector<Item> items(n);
    for (int i = 0; i < n; ++i)
        inp >> items[i].weight >> items[i].value;

    inp.close();

    int maxValue = knapsack_BruteForce(items, chosenItems, n, capacity);
    for (const int& i : chosenItems)
        cout << i << " ";
    cout << "\nMaximum value: " << maxValue;
    outputFile(chosenItems, maxValue);
}