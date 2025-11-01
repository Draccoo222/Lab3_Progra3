#include <QCoreApplication>

#include "LinkedList.h"
#include "Operation.h"
#include "Stack.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;

void printMenu();
void insertWord(LinkedList<string>& list, Stack<Operation>& undoStack, Stack<Operation>& redoStack);
void removeWord(LinkedList<string>& list, Stack<Operation>& undoStack, Stack<Operation>& redoStack);
void replaceWord(LinkedList<string>& list, Stack<Operation>& undoStack, Stack<Operation>& redoStack);
void undo(LinkedList<string>& list, Stack<Operation>& undoStack, Stack<Operation>& redoStack);
void redo(LinkedList<string>& list, Stack<Operation>& undoStack, Stack<Operation>& redoStack);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LinkedList<string> list;
    Stack<Operation> undoStack;
    Stack<Operation> redoStack;

    int option = -1;

    while(option != 0) {
        printMenu();
        cout << "Selecciona opcion: ";
        cin >> option;

        switch(option) {
        case 1:
            insertWord(list, undoStack, redoStack);
            break;
        case 2:
            removeWord(list, undoStack, redoStack);
            break;
        case 3:
            replaceWord(list, undoStack, redoStack);
            break;
        case 4:
            list.print();
            break;
        case 5:
            undo(list, undoStack, redoStack);
            break;
        case 6:
            redo(list, undoStack, redoStack);
            break;
        case 0:
            cout << "Leaving..." << endl;
            break;
        default:
            cout << "Opcion invalida" << endl;
        }
        cout << endl;
    }

    list.clear();

    return a.exec();
}



void insertWord(LinkedList<string>& list, Stack<Operation>& undoStack, Stack<Operation>& redoStack) {
    int pos;
    string word;

    cout << "Position: ";
    cin >> pos;
    cout << "Word: ";
    cin >> word;

    if(pos < 0 || pos > list.size()) {
        cout << "Invalid Position" << endl;
        return;
    }

    list.pushBack(word);

    Operation op("", word, pos, OpType::REMOVE);
    undoStack.push(op);

    while(!redoStack.empty()) {
        redoStack.pop();
    }
}

void removeWord(LinkedList<string>& list, Stack<Operation>& undoStack, Stack<Operation>& redoStack) {
    int pos;

    cout << "Position: ";
    cin >> pos;

    if(pos < 0 || pos >= list.size()) {
        cout << "Invalid Position" << endl;
        return;
    }

    string oldValue = list.at(pos)->value;
    list.erase(pos);

    Operation op(oldValue, "", pos, OpType::INSERT);
    undoStack.push(op);

    while(!redoStack.empty()) {
        redoStack.pop();
    }
}

void replaceWord(LinkedList<string>& list, Stack<Operation>& undoStack, Stack<Operation>& redoStack) {
    int pos;
    string newWord;

    cout << "Position: ";
    cin >> pos;
    cout << "New Word: ";
    cin >> newWord;

    if(pos < 0 || pos >= list.size()) {
        cout << "Invalid Position"  << endl;
        return;
    }

    string oldValue = list.at(pos)->value;

    list.at(pos)->value = newWord;

    Operation op(newWord, oldValue, pos, OpType::REPLACE);
    undoStack.push(op);

    while(!redoStack.empty()) {
        redoStack.pop();
    }
}

void undo(LinkedList<string>& list, Stack<Operation>& undoStack, Stack<Operation>& redoStack) {
    if(undoStack.empty()) {
        cout << "No operations to undo" << endl;
        return;
    }

    Operation op = undoStack.pop();

    switch(op.type){
        case OpType::INSERT:{
                list.pushBack(op.oldValue);

                Operation redoOp("", op.oldValue, op.pos, OpType::REMOVE);
                redoStack.push(redoOp);
        }
        break;
        case OpType::REMOVE:{
            list.erase(op.pos);

            Operation redoOp(op.newValue, "", op.pos, OpType::INSERT);
            redoStack.push(redoOp);
        }
        break;
        case OpType::REPLACE:{
            list.at(op.pos)->value = op.newValue;

            Operation redoOp(op.newValue, op.oldValue, op.pos, OpType::REPLACE);
            redoStack.push(redoOp);

        }
        break;
    }

    cout << "Executing Undo" << endl;
}

void redo(LinkedList<string>& list, Stack<Operation>& undoStack, Stack<Operation>& redoStack) {
    if(redoStack.empty()) {
        cout << "No operations left to do" << endl;
        return;
    }

    Operation op = redoStack.pop();

    switch(op.type){
    case OpType::INSERT:{
        list.pushBack(op.oldValue);
        Operation undoOp("", op.oldValue, op.pos, OpType::REMOVE);
        undoStack.push(undoOp);
    }
    break;
    case OpType::REMOVE:{
        list.erase(op.pos);
        Operation undoOp(op.newValue, "", op.pos, OpType::INSERT);
        undoStack.push(undoOp);
    }
    break;
    case OpType::REPLACE:{
        list.at(op.pos)->value = op.newValue;
        Operation undoOp(op.newValue, op.oldValue, op.pos, OpType::REPLACE);
        undoStack.push(undoOp);
    }
    break;
    }
    cout << "Executing Redo" << endl;
}


void printMenu(){
    cout << "=== Mini Editor ===" << endl;
    cout << "1) Insert Word" << endl;
    cout << "2) Remove Word" << endl;
    cout << "3) Replace Word" << endl;
    cout << "4) Show document" << endl;
    cout << "5) Undo" << endl;
    cout << "6) Redo" << endl;
    cout << "0) Leave" << endl;

}
