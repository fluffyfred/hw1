#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
// push back
void ULListStr::push_back(const std::string& val)
{
	if(empty()) {
		// list is empty
		Item* newitem = new Item();
		newitem->prev = NULL; 
		newitem->next = NULL; 
		newitem->last = 1;
		newitem->val[0] = val; 
		size_++;
		head_ = newitem; 
		tail_ = newitem;
	}
	else if(tail_->last == ARRSIZE) {
		// last item has no space
		Item* newitem = new Item(); 
		newitem->prev = tail_; 
		newitem->next = NULL; 
		newitem->last = 1; 
		newitem->val[0] = val; 
		size_++;
		tail_->next = newitem;
		tail_ = newitem;
	}
	else {
		// last item has space
		tail_->val[tail_->last] = val;
		tail_->last++;
		size_++;
	}
}

// pop back
void ULListStr::pop_back()
{
  if(empty()) {
    return;
  }
  else {
		tail_->last--; 
		size_--;
		if(tail_->first == tail_->last) {
			// if after pop back the array is "empty" then do this
			if(tail_->prev == NULL) {
				// if there is only one item
				delete tail_; 
				head_ = NULL; 
				tail_ = NULL;
				size_ = 0;
			}
			else {
				// if there are multiple items
				Item* temp = tail_->prev; 
				delete tail_; 
				temp->next = NULL;
				tail_ = temp;
			}
		}
	}
}

// push front
void ULListStr::push_front(const std::string& val)
{
  if(empty()) {
		Item* newitem = new Item();
		newitem->prev = NULL; 
		newitem->next = NULL; 
		newitem->last = ARRSIZE;
		newitem->first = newitem->last - 1;
		newitem->val[newitem->first] = val; 
		size_++;
		head_ = newitem; 
		tail_ = newitem;
  }
  else {
		if(head_->first  == 0) {
			// current head item has no room before the first item
			Item* newitem = new Item(); 
			newitem->prev = NULL; 
			newitem->next = head_;
			newitem->last = ARRSIZE;
		  newitem->first = newitem->last - 1;
			newitem->val[newitem->first] = val;
			head_->prev = newitem;
			head_ = newitem;
			size_++;
		}
		else {
			// current head item has room before the first item
			head_->val[head_->first - 1] = val;
			head_->first--;
			size_++;
		}
	}
}

// pop front
void ULListStr::pop_front()
{
	if(empty()) {
		return;
	}
	else {
		head_->first++;
		size_--;
		// now what if the head item array is "empty" after pop front
		// then we have to delete it
		if(head_->first == head_->last) {
			Item* temp = head_->next;
			delete head_;
			head_ = temp;
			head_->prev = NULL;
			if(empty()) {
				tail_ = NULL; 
				head_->next = NULL;
			}
		}
	}
}

// back
std::string const & ULListStr::back() const
{
	// assume the list is not empty 
	std::string const & output = tail_->val[tail_->last - 1];
	return output;
}

// front
std::string const & ULListStr::front() const
{
	// assume the list is not empty
	std::string const & output = head_->val[head_->first]; 
	return output;
}

// getValAtLoc
std::string* ULListStr::getValAtLoc(size_t loc) const
{
	Item* temp = head_; 
	while(temp != NULL) {
		if(loc <= temp->last - temp->first - 1) {
			return &(temp->val[temp->first + loc]);
		}
		else {
			loc = loc - (temp->last - temp->first); 
			temp = temp->next;
		}
	}
	return NULL;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
