// inlined in LinkedList.h

#include <cstdlib>
#include <stdexcept>

template<typename T>
DataStructures::LinkedList<T>::iterator::iterator(Element* start)
{
  current = start;
}

template<typename T>
typename DataStructures::LinkedList<T>::iterator&
DataStructures::LinkedList<T>::iterator::operator++()
{
  current = current->next;
  return *this;
}

template<typename T>
bool
DataStructures::LinkedList<T>::iterator::operator==(iterator other)
{
  return current == other.current;
}

template<typename T>
bool
DataStructures::LinkedList<T>::iterator::operator!=(iterator other)
{
  return current != other.current;
}

template<typename T>
T
DataStructures::LinkedList<T>::iterator::operator*() const
{
  return current->datum;
}

template<typename T>
typename DataStructures::LinkedList<T>::iterator
DataStructures::LinkedList<T>::begin()
{
  DataStructures::LinkedList<T>::iterator begin{ first };
  return begin;
}

template<typename T>
typename DataStructures::LinkedList<T>::iterator
DataStructures::LinkedList<T>::end()
{
  return DataStructures::LinkedList<T>::iterator{};
}

template<typename T>
static void
assert_type_has_operator_equal_and_nequal()
{
  T a;
  static_assert(std::is_same<decltype(a == a), bool>(),
                "value type must have `operator==(T&)` defined");
  static_assert(std::is_same<decltype(a != a), bool>(),
                "value type must have `operator!=(T&)` defined");
}

template<typename T>
DataStructures::LinkedList<T>::LinkedList(std::initializer_list<T> contents)
{
  assert_type_has_operator_equal_and_nequal<T>();
  number_of_elements = contents.size();

  Element* next = nullptr;
  for (auto it = std::crbegin(contents); it != std::crend(contents); ++it) {
    Element* current = new Element{ *it, next };
    next = current;
  }
  first = next;
}

template<typename T>
DataStructures::LinkedList<T>::LinkedList()
{
  assert_type_has_operator_equal_and_nequal<T>();
  number_of_elements = 0;
  first = nullptr;
}

template<typename T>
DataStructures::LinkedList<T>::~LinkedList()
{
  clear();
}

template<typename T>
size_t
DataStructures::LinkedList<T>::size()
{
  return number_of_elements;
}

template<typename T>
bool
DataStructures::LinkedList<T>::empty()
{
  return number_of_elements == 0;
}

template<typename T>
bool
DataStructures::LinkedList<T>::operator==(LinkedList<T>& other)
{
  if (other.size() != number_of_elements)
    return false;

  auto this_it = begin();
  auto other_it = other.begin();
  while (this_it != end()) {
    if (*this_it != *other_it)
      return false;
    ++this_it;
    ++other_it;
  }
  return true;
}

template<typename T>
bool
DataStructures::LinkedList<T>::operator!=(LinkedList<T>& other)
{
  return !operator==(other);
}

template<typename T>
T&
DataStructures::LinkedList<T>::front()
{
  return first->datum;
}

template<typename T>
T&
DataStructures::LinkedList<T>::back()
{
  for (Element* current_element = first; current_element != nullptr;
       current_element = current_element->next) {
    if (current_element->next == nullptr) {
      return current_element->datum;
    }
  }
  // This shouldn't be reached
  return first->datum;
}

template<typename T>
void
DataStructures::LinkedList<T>::push_front(const T& new_value)
{
  number_of_elements += 1;
  Element* new_first = new Element{ new_value, first };
  first = new_first;
}

template<typename T>
void
DataStructures::LinkedList<T>::push_back(const T& new_value)
{
  number_of_elements += 1;
  Element* new_last = new Element{ new_value, nullptr };
  Element* old_last = first;
  while (old_last->next != nullptr)
    old_last = old_last->next;
  old_last->next = new_last;
}

template<typename T>
T
DataStructures::LinkedList<T>::pop_front()
{
  Element* old_first = first;
  first = first->next;
  number_of_elements -= 1;
  T old_first_datum = old_first->datum;
  delete old_first;
  old_first = nullptr;
  return old_first_datum;
}

template<typename T>
T
DataStructures::LinkedList<T>::pop_back()
{
  T old_last_datum;
  if (first->next == nullptr) {
    old_last_datum = first->datum;
    delete first;
    first = nullptr;
    number_of_elements -= 1;
    return old_last_datum;
  }

  Element* previous_element = first;
  Element* current_element = first->next;
  while (current_element->next != nullptr) {
    previous_element = current_element;
    current_element = current_element->next;
  }
  old_last_datum = current_element->datum;
  delete current_element;
  previous_element->next = nullptr;
  number_of_elements -= 1;
  return old_last_datum;
}

template<typename T>
void
DataStructures::LinkedList<T>::clear()
{
  Element* current = first;
  while (current != nullptr) {
    Element* next = current->next;
    current->next = nullptr;
    delete current;
    current = next;
  }
  first = nullptr;
  number_of_elements = 0;
}

template<typename T>
bool
DataStructures::LinkedList<T>::remove(const T& value)
{
  if (first->datum == value) {
    Element* old_first = first;
    first = first->next;
    delete old_first;
    number_of_elements -= 1;
    return true;
  }
  Element* previous_element = first;
  Element* current_element = first->next;
  while (current_element != nullptr) {
    if (current_element->datum == value) {
      previous_element->next = current_element->next;
      delete current_element;
      number_of_elements -= 1;
      return true;
    }
    previous_element = current_element;
    current_element = current_element->next;
  }
  return false;
}

template<typename T>
void
DataStructures::LinkedList<T>::map(std::function<T(const T&)> closure)
{
  Element* current_element = first;
  while (current_element != nullptr) {
    current_element->datum = closure(current_element->datum);
    current_element = current_element->next;
  }
}
