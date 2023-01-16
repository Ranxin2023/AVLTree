#pragma once
#ifndef CLASS_H
#define CLASS_H
#include<iostream>
#include <queue>
using namespace std;
typedef class AVLTree* AVLTreeRef;
typedef class Nodes* NodesRef;

class AVLTree {
	private:
		NodesRef root;
		int height;
		
	public: 
		AVLTree();
		NodesRef getRoot();
		void addNodes(int pvalue);
		void middleTraverse();
		void layerTraverse();
		void setHeight(int height);
		int getHeight();
		void setRoot(NodesRef node);
		bool deleteNodes(int pvalue);
};

class Nodes {
	private:
		int value;
		AVLTreeRef tree;
		NodesRef left;
		NodesRef right;
		NodesRef parent;
		
	public:
		Nodes(int pvalue, AVLTreeRef ptree);
		int getValue();
		AVLTreeRef getTree();
		void addNodes(int pvalue);
		void setParent(NodesRef parent);
		int updateHeight();
		int getBalance();
		void AVLTreeRebalance();
		int getHeight();
		void setNodes(string direction, NodesRef child);
		//void replaceNodes(NodesRef newChild);
		void rightRotation();
		void leftRotation();
		void middleTraverse();
		void layerTraverse();
		NodesRef searchKey(int pvalue);
		NodesRef findLeftestRightTree();
		bool deleteNodes(int pvalue);
};

#endif