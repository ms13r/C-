#include <string>
#include <sstream>
#include <stack>
#include "bet.h"
using namespace std;

bool hasPrecedence(const string & c, const string & s);
bool hasPrecedence2(const string & c, const string & s);
bool isOperator(const string & s);

BET::BET(){
    root = new BinaryNode();
}

BET::BET(const string postfix){
    root = new BinaryNode();
    buildFromPostfix(postfix);	// Call helper function to build the string
}

BET::BET(const BET& x){
    root = clone(x.root);
}

BET::~BET(){
    makeEmpty(root);
}

bool BET::buildFromPostfix(const std::string postfix){
    stack <BinaryNode *> myStack;
    string contents, temporaryOperator;
    stringstream sStream(postfix);	// Build a string stream to use as a buffer for the full contents of the string
					// The string stream will be used to delimit by spaces, as opposed to what was
					// done in assignment 3. This way, a simply loop will take care of multi-char #s

    while(sStream >> temporaryOperator){
	// Use notes from the slide for pseudo code to implement here
	if(temporaryOperator != "+" && temporaryOperator != "-" && temporaryOperator != "/" && temporaryOperator != "*"){
	    // Token is operand
	    myStack.push(new BinaryNode(temporaryOperator));
	}
	else{
	    BET::BinaryNode* newNode  = new BET::BinaryNode(temporaryOperator);	// Place the operator as the data
	    newNode->right = myStack.top();		// Right contents are first (top of stack)
	    myStack.pop();
	    newNode->left = myStack.top();		// Push the left contents
	    myStack.pop();
	    myStack.push(newNode);
	}
    }

    if(myStack.size() == 1){
	root = myStack.top();
	myStack.pop();
	return true;
    }
    return false;
}

const BET & BET::operator=(const BET & x){
    this->root = clone(x.root);
    return *this;
}

void BET::printInfixExpression(){
    printInfixExpression(root);
    cout << '\n';
}

void BET::printPostfixExpression(){
    printPostfixExpression(root);
    cout << '\n';
}

size_t BET::size(){
    return size(root);
}

size_t BET::leaf_nodes(){
    return leaf_nodes(root);
}

bool BET::empty(){
    if(root == nullptr)
	return true;
    else
	return false;
}

void BET::printInfixExpression(BinaryNode *n){
    if(n != nullptr){
	if(leaf_nodes(n) == 1){
	    // Found a leaf node, print out the data
	    cout << n->data << " ";
	    return;
	}
	else{
	    if((isOperator(n->data) && isOperator(n->left->data)) && hasPrecedence(n->data, n->left->data)){
		// If both the left child and the current node are operators
		cout << "( ";
		printInfixExpression(n->left);
		cout << ")";
	    }
	    else
	        printInfixExpression(n->left);
	    cout << n->data << " ";
	    if((isOperator(n->data) && isOperator(n->right->data)) && hasPrecedence2(n->data, n->right->data)){
		// If both the right child and the current node are operators
		cout << "( ";
		printInfixExpression(n->right);
		cout << ")";
	        return;
	    }
	    else
	        printInfixExpression(n->right);
	}
    }
}

void BET::makeEmpty(BinaryNode* &t){
    if(t != nullptr){
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
    }

    t = nullptr;
}

BET::BinaryNode * BET::clone(BinaryNode *t) const{
    if(t == nullptr)
	return nullptr;
    else
	return (new BinaryNode{t->data, clone(t->left), clone(t->right)});
}

void BET::printPostfixExpression(BinaryNode *n){
    if(n != nullptr){
	if(leaf_nodes(n) == 1){
	    // Found a leaf node, print out the data
	    cout << n->data << " ";
	    return;
	}
	else{
	    printInfixExpression(n->left);	
	    printInfixExpression(n->right);
	    cout << n->data << '\n';
	}
    }
    else
	return;
}

size_t BET::size(BinaryNode *t){
    if(t == nullptr)
	return 0;		// If the current node is not present, there is nothing there, return 1 (base case)
    else
	return (1 + size(t->left) + size(t->right));	// Else, return 1 + size of both the left and right children (for recursion)
}

size_t BET::leaf_nodes(BinaryNode *t){
    if(t == nullptr)
	return 0; 		// Empty node
    else if(t->left == nullptr && t->right == nullptr)	// Else the node has no more children, so we have found a leaf
	return 1;
    else
	return (leaf_nodes(t->left) + leaf_nodes(t->right));	// Return all the children of the left and right nodes if it is a tree with depth > 1
}

bool isOperator(const string & s){
    if(s == "/" || s == "+" || s == "-" || s == "*")
	return true;
    return false;
}

bool hasPrecedence(const string & c, const string & s){
    if(c == "*" && s == "*")
        return false;
    if(c == "*" && s == "/")
        return false;
    if(c == "*" && s == "+")
        return true;
    if(c == "*" && s == "-")
        return true;
    if(c == "/" && s == "*")
        return false;
    if(c == "/" && s == "/")
        return false;
    if(c == "/" && s == "+")
        return true;
    if(c == "/" && s == "-")
        return true;
    if(c == "+" && s == "*")
        return false;
    if(c == "+" && s == "/")
        return false;
    if(c == "+" && s == "+")
        return false;
    if(c == "+" && s == "-")
        return false;
    if(c == "-" && s == "*")
        return false;
    if(c == "-" && s == "/")
        return false;
    if(c == "-" && s == "+")
        return false;
    if(c == "-" && s == "-")
        return false;
}

bool hasPrecedence2(const string & c, const string & s){
    if(c == "*" && s == "*")
        return false;
    if(c == "*" && s == "/")
        return false;
    if(c == "*" && s == "+")
        return true;
    if(c == "*" && s == "-")
        return true;
    if(c == "/" && s == "*")
        return false;
    if(c == "/" && s == "/")
        return false;
    if(c == "/" && s == "+")
        return true;
    if(c == "/" && s == "-")
        return true;
    if(c == "+" && s == "*")
        return false;
    if(c == "+" && s == "/")
        return false;
    if(c == "+" && s == "+")
        return true;
    if(c == "+" && s == "-")
        return true;
    if(c == "-" && s == "*")
        return false;
    if(c == "-" && s == "/")
        return false;
    if(c == "-" && s == "+")
        return true;
    if(c == "-" && s == "-")
        return true;
}
