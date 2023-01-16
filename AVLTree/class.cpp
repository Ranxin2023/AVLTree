#include "class.h"
//-------------------------AVLTree Function--------------------------------------

AVLTree::AVLTree() {
	this->root = nullptr;
	this->height = -1;
}
void AVLTree::addNodes(int pvalue) {
	if (this->root == nullptr) {
		this->root = new Nodes(pvalue,this);
		this->height = 0;
	}
	else {
		this->root->addNodes(pvalue);
	}
}

void AVLTree::setHeight(int height) {
	this->height = height;
}

int AVLTree::getHeight() {
	return this->height;
}

void AVLTree::setRoot(NodesRef node) {
	this->root = node;
	this->root->setParent(nullptr);
}

NodesRef AVLTree::getRoot() {
	return this->root;
}

void AVLTree::middleTraverse() {
	this->root->middleTraverse();
}

void AVLTree::layerTraverse() {
	this->root->layerTraverse();
}

bool AVLTree::deleteNodes(int pvalue) {
	return this->root->deleteNodes(pvalue);
}
//-------------------------Nodes Function--------------------------------------
Nodes::Nodes(int pvalue, AVLTreeRef ptree):value(pvalue),tree(ptree) {
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}

void Nodes::addNodes(int pvalue) {
	int AVLTreeHeight;
	if (pvalue < this->value) {
		if (this->left == nullptr) {
			this->left = new Nodes(pvalue,this->tree);
			this->left->parent=this;
		}
		else {
			this->left->addNodes(pvalue);
		}
	}
	else {
		if (this->right == nullptr) {
			this->right = new Nodes(pvalue, this->tree);
			this->right->parent=this;
		}
		else {
			this->right->addNodes(pvalue);
		}
	}
	
	if (this->parent != nullptr) {
		this->parent->AVLTreeRebalance();
	}
	AVLTreeHeight = this->tree->getRoot()->updateHeight();
	this->tree->setHeight(AVLTreeHeight);
}

void Nodes::setParent(NodesRef parent) {
	this->parent = parent;
}

int Nodes::updateHeight() {
	int leftHeight=-1;
	int rightHeight=-1;
	int height=-1;
	if (this->left != nullptr) {
		leftHeight = this->left->updateHeight();
	}
	if (this->right != nullptr) {
		rightHeight = this->right->updateHeight();
	}
	leftHeight > rightHeight ? height = leftHeight:height=rightHeight;
	height++;
	return height;
}

int Nodes::getBalance() {
	int leftHeight = -1;
	int rightHeight = -1;
	
	if (this->left != nullptr) {
		leftHeight = this->left->updateHeight();
	}
	if (this->right != nullptr) {
		rightHeight = this->right->updateHeight();
	}
	
	return leftHeight-rightHeight;
}

void Nodes::AVLTreeRebalance() {
	if (this->getBalance() == -2) {
		//cout << "rebalance left start" << endl;
		if (this->right->getBalance() == 1) {//double rotation tree
			this->right->rightRotation();
		}
		this->leftRotation();
	}
	if (this->getBalance() == 2){
		//cout << "rebalance right start" << endl;
		if (this->left->getBalance() == -1) {//double rotation tree
			this->left->leftRotation();
		}
		this->rightRotation();
	}
	if (this->parent != nullptr) {
		this->parent->AVLTreeRebalance();
	}
}

void Nodes::setNodes(string direction, NodesRef child) {
	if (direction != "left" && direction != "right") {
		return;
	}
	if (child != nullptr) {
		child->parent = this;
	}
	if (direction == "left")	{
		this->left = child;
	}
	else {
		this->right = child;
	}	
}

void Nodes::rightRotation() {
	//cout << "right rotation with value"<<this->value << endl;
	NodesRef leftRightNode = this->left->right;
	if (this->parent != nullptr) {
		if(this==this->parent->left)
			this->parent->setNodes("left",this->left);
		if (this == this->parent->right)
			this->parent->setNodes("right", this->left);
	}
	else {
		this->tree->setRoot(this->left);
		//cout << "Now the value is" << this->value << endl;
	}
	this->left->setNodes( "right",this);
	this->setNodes("left",leftRightNode);
}

void Nodes::leftRotation() {
	//cout << "left rotation with value" << this->value << endl;
	NodesRef rightLeftNode = this->right->left;
	if (this->parent != nullptr) {
		if (this == this->parent->left)
			this->parent->setNodes("left", this->right);
		if (this == this->parent->right)
			this->parent->setNodes("right", this->right);
	}
	else {
		this->tree->setRoot(this->right);
	}
	this->right->setNodes("left", this);
	this->setNodes("right", rightLeftNode);
}

void Nodes::middleTraverse() {
	if (this->left != nullptr) {
		this->left->middleTraverse();
	}
	cout << this->value << "\t";
	if (this->right != nullptr) {
		this->right->middleTraverse();
	}
}

NodesRef Nodes::searchKey(int pvalue) {
	if (pvalue < this->value) {
		if (this->left == nullptr) {
			return nullptr;
		}
		else {
			return this->left->searchKey(pvalue);
		}
	}
	else if (pvalue == this->value) {
		return this;
	}
	else {
		if (this->right == nullptr) {
			return nullptr;
		}
		else {
			return this->right->searchKey(pvalue);
		}
	}
}

NodesRef Nodes::findLeftestRightTree() {
	if (this->left == nullptr) {
		return this;
	}
	else {
		return this->left->findLeftestRightTree();
	}
}

bool Nodes::deleteNodes(int pvalue) {
	NodesRef nodeDeleted;
	int newHeight;
	if (pvalue == this->value) {
		nodeDeleted = this;
	}
	else {
		nodeDeleted = this->searchKey(pvalue);
	}
	
	if (nodeDeleted == nullptr) {
		return false;
	}
	if (nodeDeleted->left == nullptr) {
		if (nodeDeleted->right == nullptr) {//remove the node with no child
			if (nodeDeleted->parent == nullptr) {
				this->tree->setRoot(nullptr);
				this->tree->setHeight(-1);
			}
			else {
				if (nodeDeleted->parent->left == nodeDeleted) {
					nodeDeleted->parent->left = nullptr;
				}
				if (nodeDeleted->parent->right == nodeDeleted) {
					nodeDeleted->parent->right = nullptr;
				}
			}
		}
		else {//remove the node with only right child
			if (nodeDeleted->parent == nullptr) {
				this->tree->setRoot(nodeDeleted->right);
			}
			else if (nodeDeleted->parent->left == nodeDeleted) {
				nodeDeleted->parent->setNodes("left",nodeDeleted->right);
			}
			else {
				nodeDeleted->parent->setNodes("right",nodeDeleted->right);
			}
		}
	}
	else {
		if (nodeDeleted->right == nullptr) {//remove the node with only the left child
			if (nodeDeleted->parent == nullptr) {
				this->tree->setRoot(nodeDeleted->left);
			}
			else if (nodeDeleted->parent->left == nodeDeleted) {
				nodeDeleted->parent->setNodes("left", nodeDeleted->left);
			}
			else {
				nodeDeleted->parent->setNodes("right",nodeDeleted->left);
			}
		}
		else {//remove node with two children
			NodesRef leftmostOfRightTree=nodeDeleted->right->findLeftestRightTree();
			nodeDeleted->value = leftmostOfRightTree->value;
			leftmostOfRightTree->deleteNodes(leftmostOfRightTree->value);
		}
	}
	if (this->parent != nullptr) {
		this->parent->AVLTreeRebalance();
	}
	newHeight = this->tree->getRoot()->updateHeight();
	this->tree->setHeight(newHeight);
	return true;
}


void Nodes::layerTraverse() {
	queue <NodesRef> q;
	q.push(this);
	//int i;
	while (q.size() != 0) {
			cout << q.front()->value << "\t";
		
		if (q.front()->left != nullptr) {
			q.push(q.front()->left);
		}
		if (q.front()->right != nullptr) {
			q.push(q.front()->right);
		}
		q.pop();
	}

}
