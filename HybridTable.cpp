#include "HybridTable.h"

using namespace std;

Node::Node(int index, int val) : index_(index), val_(val), next_(nullptr) {
	//New Node
}

Node::Node(int index, int val, Node* next) : index_(index), val_(val), next_(next) {
	//New Node with next
}

Node::~Node() {
	//IMPLEMENT ME
}

HybridTable::HybridTable() : array_(new int[INITIAL_ARRAY_SIZE]), arraySize(INITIAL_ARRAY_SIZE), listSize(0), list_(nullptr) {
	//INITIALISE CLASS
	for (int i = 0; i < INITIAL_ARRAY_SIZE; i++) { //Loop through array to make it all 0
		array_[i] = 0;
	}
}

HybridTable::HybridTable(const int *p, int n) : array_(new int[n]), arraySize(n), listSize(0), list_(nullptr) {
	//INITIALISE CLASS WITH PARAMETERS
	for (int i = 0; i < n; i++) { //Loop through the array to copy the values of the parameter
		array_[i] = p[i];
	}
}

HybridTable::~HybridTable() {
	//DESTRUCTOR
	//FREE UP MEMORY
	delete[] array_;
	Node* CurrentNode = list_;
	while (CurrentNode != nullptr) {
		Node* NextNode = CurrentNode->next_;
		delete CurrentNode;
		CurrentNode = NextNode;
	}
}

HybridTable::HybridTable(const HybridTable& other) : array_(new int[other.arraySize]), arraySize(other.arraySize), listSize(other.listSize), list_(nullptr) {
	//COPY CONSTRUCTOR
	//DEEP COPY ARRAY
	//array_ = new int[other.getArraySize()];
	for (int i = 0; i < other.getArraySize(); i++) {
		array_[i] = *(other.array_+i);
	}
	//DEEP COPY LIST
	if (listSize > 0 ) {
		list_ = new Node(other.list_->index_, other.list_->val_);
		Node* CurrentOtherNode = other.list_->next_;
		Node* CurrentNode = list_;
		for (int x = 0; x < listSize; x++) {
			if (CurrentOtherNode == nullptr) {
				break;
			} else {
				CurrentNode->next_ = new Node(CurrentOtherNode->index_, CurrentOtherNode->val_, CurrentOtherNode->next_);
				CurrentOtherNode = CurrentOtherNode->next_;
				CurrentNode = CurrentNode->next_;
			}
		}
	}
}

HybridTable& HybridTable::operator=(const HybridTable& other) {
	//COPY ASSIGNNMENT OPERATOR
	if (this != &other) {
		delete[] array_;
		Node* CurrentNode = list_;
		while (CurrentNode != nullptr) {
			Node* NextNode = CurrentNode->next_;
			delete CurrentNode;
			CurrentNode = NextNode;
		}

		array_ = new int[other.getArraySize()];
		list_ = nullptr;
		listSize = other.listSize;
		arraySize = other.arraySize;
		for (int i = 0; i < other.getArraySize(); i++) {
			array_[i] = *(other.array_+i);
		}
		//DEEP COPY LIST
		if (listSize > 0 ) {
			list_ = new Node(other.list_->index_, other.list_->val_);
			Node* CurrentOtherNode = other.list_->next_;
			Node* CurrentNode = list_;
			for (int x = 0; x < listSize; x++) {
				if (CurrentOtherNode == nullptr) {
					break;
				} else {
					CurrentNode->next_ = new Node(CurrentOtherNode->index_, CurrentOtherNode->val_, CurrentOtherNode->next_);
					CurrentOtherNode = CurrentOtherNode->next_;
					CurrentNode = CurrentNode->next_;
				}
			}
		}
	}
	return *this;
}

int HybridTable::get(int i) const {
	//GET VALUE
	if (i > (arraySize-1) || i < 0) {
		//OUTSIDE OF ARRAY
		if (list_ != nullptr && list_->index_ == i) { //if i is the head of the list
			return list_->val_;
		} else { //otherwise, loop through the list to find i
			if (list_ != nullptr) {
				Node* CurrentNode = list_->next_;
				for (int x = 0; x < listSize; x++) {
					if (CurrentNode == nullptr) {
						return 0;
					} else if (CurrentNode->index_ == i) {
						return CurrentNode->val_;
					} else {
						CurrentNode = CurrentNode->next_;
					}
				}
				return 0;
			} else {
				return 0;
			}
			
		}
	} else { //ELSE RETURN VALUE
		return *(array_+i);
	}
}

void HybridTable::set(int i, int val) {
	//SET VALUE
	if (i < arraySize && i >= 0) {
		//IN RANGE
		array_[i] = val; 
	} else { //OUT OF RANGE
		if (list_ == nullptr) { //If there is no starter node, assign it to the head of the list
			list_ = new Node(i, val);
			listSize++;
		} else {
			Node* CurrentNode = list_->next_;
			Node* PrevNode = list_;
			for (int x = 0; x < listSize; x++) { //Loop through the list
				if (CurrentNode == nullptr) {
					if (PrevNode->index_ > i) { //If the prev node is bigger than our i, then this i is the new head of the list
						list_ = new Node(i, val, PrevNode);	
						PrevNode->next_ = nullptr;
						listSize++;
						break;
					} else {
						PrevNode->next_ = new Node(i, val);	
						listSize++;
						break;
					}	
				}
				//OVERWRITING SAME INDEX
				if (CurrentNode->index_ == i ) {
					CurrentNode->val_ = val;
					break;
				}
				if (PrevNode->index_ == i ) {
					PrevNode->val_ = val;
					break;
				}
				//
				if (PrevNode->index_ > i) { //This is to check if the first node in list is bigger than our index
					list_ = new Node(i, val, PrevNode);	
					listSize++;
					break;
				}
				if (CurrentNode->index_ > i && PrevNode->index_ < i) { //If its index is inbetween prev and current node, then place node here
					PrevNode->next_ = new Node(i, val, CurrentNode);	
					listSize++;
					break;
				} else {
					PrevNode = CurrentNode;
					CurrentNode = CurrentNode->next_;
				}
			}
		}
	}
}

string HybridTable::toString() const {
	string OutputString; //Main String
	for (int i = 0; i < arraySize; i++) { //Loop through the array and generate strings
		string OneLine;
		OneLine = OneLine + to_string(i) + " : " + to_string(*(array_+i));
		if (i < (arraySize-1)) {
			OneLine = OneLine + "\n";
		}
		OutputString = OutputString + OneLine;
	}
	if (list_ != nullptr) { //If the list is not empty, loop through that too
		OutputString = OutputString + "\n" + "---" + "\n";
		OutputString = OutputString + to_string(list_->index_) + " : " + to_string(list_->val_);
		Node* CurrentNode = list_->next_;
		for (int x = 0; x < listSize; x++) {
			string OneLine;
			if (CurrentNode == nullptr) {
				break;
			} else {
				OneLine = OneLine + " --> " + to_string(CurrentNode->index_) + " : " + to_string(CurrentNode->val_);
				OutputString = OutputString + OneLine;
				CurrentNode = CurrentNode->next_;
			}
		}
	}
	return OutputString; // dummy

}

int HybridTable::getArraySize() const {
	return arraySize;
}

int HybridTable::getTotalSize() const {
	return arraySize + listSize; 
}