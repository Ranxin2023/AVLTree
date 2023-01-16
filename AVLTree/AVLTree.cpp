// AVLTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "class.h"

void test1(AVLTreeRef t);
void test2(AVLTreeRef t);
int main()
{
    //std::cout << "Hello World!\n";
    AVLTree * t = new AVLTree();
    //test1(t);
   test2(t);
    return 0;
}

void test1(AVLTreeRef t) {
    //add nodes 11
    t->addNodes(11);
    cout << t->getHeight() << endl;
    t->layerTraverse();
    cout << endl;
    //add nodes 6
    t->addNodes(6);
    cout << t->getHeight() << endl;
    t->layerTraverse();
    cout << endl;

    t->addNodes(4);
    cout << t->getHeight() << endl;
    t->layerTraverse();
    cout << endl;

    t->addNodes(15);
    cout << t->getHeight() << endl;
    t->layerTraverse();
    cout << endl;
    t->addNodes(8);
    cout << t->getHeight() << endl;
    t->layerTraverse();
    cout << endl;
    t->addNodes(9);
    cout << t->getHeight() << endl;
    t->layerTraverse();
    cout << endl;
    t->addNodes(7);
    cout << t->getHeight() << endl;
    t->layerTraverse();
    cout << endl;
    //delete nodes 6
    t->deleteNodes(6);
    cout << t->getHeight() << endl;
    t->layerTraverse();
    cout << endl;
    //add nodes 10
    t->addNodes(10);
    cout << t->getHeight() << endl;
    t->layerTraverse();
    cout << endl;
    //delete nodes 11
    t->deleteNodes(11);
    cout << t->getHeight() << endl;
    t->layerTraverse();
    cout << endl;
}

void test2(AVLTreeRef t) {
    t->addNodes(50);
    t->addNodes(25);
    t->addNodes(12);
    t->addNodes(8);
    t->addNodes(37);
    t->addNodes(100);
    t->addNodes(4);
    t->addNodes(2);
    t->addNodes(9);
    t->deleteNodes(12);
    t->addNodes(44);
    t->addNodes(200);
    t->addNodes(75);
    t->addNodes(20);
    t->deleteNodes(25);
    cout << "After layer traverse is:" << endl;
    t->layerTraverse();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
