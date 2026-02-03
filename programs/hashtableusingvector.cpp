#include <iostream>
#include <vector>
using namespace std;
class HashTable
{
    private:
        int size;
        vector<vector<int>>table;
        int hashFunction(int key)
        {
            return key % size;
        }
    public:
        HashTable(int tableSize)
        {
            size = tableSize;
            table.resize(size);
        }
        void insert(int key)
        {
            int index = hashFunction(key);
            table[index].push_back(key);
        }
        bool search(int key)
        {
            int index = hashFunction(key);
            for(int element : table[index])
            {
                if(element == key)
                return true;
            }
            return false;
        }
        void remov(int key)
        {
            int index = hashFunction(key);
            auto& chain = table[index];
            for(auto it = chain.begin(); it != chain.end(); ++it)
            {
                if(*it == key)
                {
                    chain.erase(it);
                    return;
                }
            }
        }
        void display()
        {
            for(int i = 0; i < size; i++)
            {
                cout << "Index " << i << ": ";
                for(int key : table[i])
                {
                    cout << key << "->";
                }
                cout << "NULL" << endl;
            }
        }
};

int main()
{
    HashTable ht(7);
    ht.insert(10);
    ht.insert(20);
    ht.insert(30);
    ht.insert(40);
    ht.insert(50);
    ht.insert(60);
    ht.insert(70);
    ht.insert(80);
    cout << "Hash Table after insertion:" << endl;
    ht.display();
    cout << endl << "Searching for 30:" << (ht.search(30) ? "Found" : "Not found") << endl;
    cout << endl << "Searching for 25:" << (ht.search(25) ? "Found" : "Not found") << endl;
    ht.remov(20);
    cout << endl << "Hash Table after deleting 20:" << endl;
    ht.display();
    return 0;
}