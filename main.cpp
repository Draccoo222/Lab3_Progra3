#include <QCoreApplication>

#include "LinkedList.h"
#include "Operation.h"
#include "Stack.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;






void clearCin();
void printMenu();

void insertWord(LinkedList<string> list, string word);
void removeWord(string word);




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LinkedList<string> list;
    Stack<Operation> undoStack;
    Stack<Operation> redoStack;

    return a.exec();
}



void insertWord(LinkedList<string> list, string word){




}

void printMenu(){
    cout << "1. Insert Word" << endl;
    cout << "2. Remove Word" << endl;
    cout << "3. Replace Word" << endl;
    cout << "4. Undo" << endl;
    cout << "5. Redo" << endl;
    cout << "6. Print" << endl;
}

void clearCin(){
    cin.clear();
}
