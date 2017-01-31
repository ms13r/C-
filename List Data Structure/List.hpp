// The following code was done by Miroslav Sanader.
// Functions are also adapted from Dietel.
// Data Structures; Myers

template <typename T>
List<T>::const_iterator::const_iterator(){            // default zero parameter constructor
    current = nullptr;
}

template <typename T>
T & List<T>::const_iterator::retrieve() const{
    return (current->data);
}

template <typename T>
List<T>::const_iterator::const_iterator(Node *p) : current(p) {
}

template <typename T>
const T & List<T>::const_iterator::operator*() const{ // operator*() to return element
    return retrieve();
}

template <typename T>
// increment/decrement operators
typename List<T>::const_iterator & List<T>::const_iterator::operator++(){
    current = current->next;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int){
    const_iterator oldIter = *this;
    ++(*this);
    return oldIter;
}

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--(){
    current = current->prev;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int){
    const_iterator oldIter = *this;
    --(*this);
    return oldIter;
}

// comparison operators
template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const{
    if(current == rhs.current)
        return true;
    else
        return false;
}

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const{
    return !(*this == rhs);
}

/*Begin the iterator class that allows for data to be changed*/
template <typename T>
List<T>::iterator::iterator(){
}

template <typename T>
List<T>::iterator::iterator(Node *p) : const_iterator(p){
}

template <typename T>
T & List<T>::iterator::operator*(){
    return const_iterator::retrieve();
}

template <typename T>
const T & List<T>::iterator::operator*() const{
    return const_iterator::operator*();
}

// increment/decrement operators
template <typename T>
typename List<T>::iterator & List<T>::iterator::operator++(){
    this->current = this->current->next;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int){
    iterator oldItr = *this;
    ++(*this);
    return oldItr;
}

template <typename T>
typename List<T>::iterator & List<T>::iterator::operator--(){
    this->current = this->current->prev;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int){
    iterator oldItr = *this;
    --(*this);
    return oldItr;
}

/*_______________________________________________________________________*/

template <typename T>
List<T>::List(){                  // default zero parameter constructor
    init();
}

template <typename T>
List<T>::List(const List &rhs){   // copy constructor
    init();
    for(auto & incrementer: rhs)	// For each element in rhs, add it to the new list
	push_back(incrementer);
}

template <typename T>
List<T>::List(List && rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}{       // move constructor
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

// num elements with value of val
template <typename T>
List<T>::List(int num, const T& val){
    init();
    for(int i = 0; i < num; i++)
	push_back(val);
}

// constructs with elements [start, end)
template <typename T>
List<T>::List(const_iterator start, const_iterator end){
    init();
    for(const_iterator i = start; i != end; i++)
	push_back(*i);
}

// constructs with a copy of each of the elements in the initalizer_list
template <typename T>
List<T>::List(std::initializer_list<T> iList){
    init();
    for(auto & iter: iList)
	push_back(iter);
}

template <typename T>
List<T>::~List(){ // destructor
    clear();
    delete tail;
    delete head;
}

// copy assignment operator
template <typename T>
const List<T>& List<T>::operator=(const List &rhs){
    List<T> tempCopy = rhs;		// Make temporary copy
    std::swap(*this, tempCopy);		// Swap resources (no longer care about calling object's info)
    return *this;			// Return calling object, and allow for old resources to be deleted
}

// move assignment operator
template <typename T>
List<T> & List<T>::operator=(List && rhs){
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}

// sets list to the elements of the initializer_list
template <typename T>
List<T>& List<T>::operator= (std::initializer_list<T> iList){
    List<T> temp(iList);
    std::swap(*this, temp);
}

template <typename T>
int List<T>::size() const{       // number of elements
    return theSize;
}

template <typename T>
bool List<T>::empty() const{     // check if list is empty
    if(theSize == 0)
	return true;
    else
	return false;
}

template <typename T>
void List<T>::clear(){           // delete all elements
    while(!empty())
	pop_front();
}

template <typename T>
void List<T>::reverse(){         // reverse the order of the elements
    Node * itr = tail;		// Begin at the end of the List
    while(itr != head){		// While not the first element of the list
	std::swap(itr->next, itr->prev);	// Swap the pointers; previous is now next, and next is now previous
	itr = itr->next;			// Move to the previous node
    }
    std::swap(head, tail);

}

template <typename T>
T& List<T>::front(){             // reference to the first element
    return *begin();
}

template <typename T>
const T& List<T>::front() const{
    return *begin();
}

template <typename T>
T& List<T>::back(){              // reference to the last element
    return *--end();
}

template <typename T>
const T& List<T>::back() const{
    return *--end();		// Return the last element
}

template <typename T>
void List<T>::push_front(const T & val){ // insert to the beginning
    insert(begin(), val);
}

template <typename T>
void List<T>::push_front(T && val){      // move version of insert
    insert(begin(), std::move(val));
}

template <typename T>
void List<T>::push_back(const T & val){  // insert to the end
    insert(end(), val);
}

template <typename T>
void List<T>::push_back(T && val){       // move version of insert
    insert(end(), std::move(val));
}

template <typename T>
void List<T>::pop_front(){               // delete first element
    erase( begin() );
}

template <typename T>
void List<T>::pop_back(){                // delete last element
    erase( --end() );
}

template <typename T>
void List<T>::remove(const T &val){      // remove all elements with value = val
    iterator remover = begin();
    for(remover; remover != end(); remover++){
	if(*remover == val){		// If the value of what you are looking for is found, erase it using erase func
	    erase(remover);
	}
    }
}

template <typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred){       // remove all elements for which Predicate pred is true
    for(auto remover = begin(); remover != end(); remover++)
	if(pred(*remover) == true)		// If the predicate is true, erase the element (same as remove)
	    erase(remover);
}

// print out all elements. ofc is deliminitor
template <typename T>
void List<T>::print(std::ostream& os, char ofc) const{
    const_iterator iter = begin();
    for(iter; iter != end(); iter++){
	    os << *iter << ofc;
    }
}

template <typename T>
typename List<T>::iterator List<T>::begin(){               // iterator to first element
    return (head->next);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const{
    return (head->next);
}

template <typename T>
typename List<T>::iterator List<T>::end(){                 // end marker iterator
    return (tail);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const{
    return (tail);
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val){  // insert val ahead of itr
    Node * n = itr.current;
    theSize++;
    return (n->prev = n->prev->next = new Node(val, n->prev, n));
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val){      // move version of insert
    Node * n = itr.current;
    theSize++;
    return (n->prev = n->prev->next = new Node(std::move(val), n->prev, n));
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr){                 // erase one element
    Node *p = itr.current;
    iterator retVal{ p->next };
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;

    return retVal;
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end){ // erase [start, end)
    for(iterator itr = start; itr != end; )
	itr = erase(itr);

    return end;
}

template <typename T>
void List<T>::init(){
    theSize = 0;
    head = new Node;	// Construct a new node with nullptrs
    tail = new Node;
    head->next = tail;	// Makes head ptr point to the end
    tail->prev = head;	// Makes tail ptr point back to the beginning
}

/*___________________________________________________________*/
/*Operator overloading is done here*/

// overloading comparison operators
template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs){
    if(lhs.size() != rhs.size())		// If the size of the lists isn't equal, they can't be the same!
	return false;
    else{
	auto itr1 = lhs.begin();
	auto itr2 = rhs.begin();
	for(itr1; itr1 != lhs.end(); itr1++){
	    if(*itr1 != *itr2){			// If the two contents aren't the same
		return false;
	    }
	    itr2++;				// Make sure second iterator is incremented
	}
    }
    return true;
}

template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs){
    return !(lhs == rhs);
}

// overloading output operator
template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l){
    l.print(os);
    return os;
}
