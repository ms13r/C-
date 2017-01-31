#include <iostream>
#include <string>

class BET{
     public:
	BET();
	BET(const std::string postfix);
	BET(const BET& x);
	~BET();
	bool buildFromPostfix(const std::string postfix);
	const BET & operator=(const BET& x);
	void printInfixExpression();
	void printPostfixExpression();
	size_t size();
	size_t leaf_nodes();
	bool empty();
	struct BinaryNode{
	    std::string data;
	    BinaryNode * left;
	    BinaryNode * right;

	    BinaryNode( const std::string theElement = {}, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr): data{ theElement }, left{ lt }, right{ rt } { }

	    BinaryNode( std::string && theElement, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr): data{ std::move( theElement ) }, left{ lt},right{rt}{}
	};

     private:
	BinaryNode * root;
	void printInfixExpression(BinaryNode *n);
	void makeEmpty(BinaryNode* &t);
	BinaryNode * clone(BinaryNode *t) const;
	void printPostfixExpression(BinaryNode *n);
	size_t size(BinaryNode *t);
	size_t leaf_nodes(BinaryNode *t);
};
