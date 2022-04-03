// inlined in LinkedList.h

template<typename T>
DataStructures::LinkedList<T>::iterator::iterator(Element* start)
{
  current = start;
}

template<typename T>
typename LinkedList<T>::iterator&
DataStructures::LinkedList<T>::iterator::operator++()
{
  current = current->next;
  return *this;
}

template<typename T>
bool
DataStructures::LinkedList<T>::iterator::operator==(const iterator other) const
{
  return current == other.current;
}

template<typename T>
bool
DataStructures::LinkedList<T>::iterator::operator!=(const iterator other) const
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
typename LinkedList<T>::iterator
DataStructures::LinkedList<T>::begin() const
{
  LinkedList<T>::iterator begin{ first };
  return begin;
}

template<typename T>
typename LinkedList<T>::iterator
DataStructures::LinkedList<T>::end() const
{
  return LinkedList<T>::iterator{};
}

template<typename T>
DataStructures::LinkedList<T>::LinkedList(std::initializer_list<T> contents)
{
  number_of_elements = contents.size();
  last = nullptr;

  Element* next = nullptr;
  for (auto it = std::crbegin(contents); it != std::crend(contents); ++it) {
    Element* current = new Element{ *it, next };
    if (last == nullptr)
      last = current;
    next = current;
  }
  first = next;
}

template<typename T>
DataStructures::LinkedList<T>::LinkedList()
{
  number_of_elements = 0;
  first = nullptr;
  last = nullptr;
}

template<typename T>
DataStructures::LinkedList<T>::LinkedList(const LinkedList& other)
{
  number_of_elements = 0;
  *this = other;
}

template<typename T>
LinkedList<T>&
DataStructures::LinkedList<T>::operator=(const LinkedList& other)
{
  if (!empty())
    clear();
  first = nullptr;
  number_of_elements = other.size();
  Element* previous;
  for (auto it = other.begin(); it != other.end(); ++it) {
    Element* next = new Element{ *it, nullptr };
    if (first == nullptr) {
      first = next;
    } else {
      previous->next = next;
    }
    previous = next;
  }
  last = previous;
  return *this;
}

template<typename T>
DataStructures::LinkedList<T>::LinkedList(LinkedList&& other) noexcept
{
  first = other.first;
  last = other.last;
  number_of_elements = other.number_of_elements;

  other.first = nullptr;
  other.last = nullptr;
  other.number_of_elements = 0;
}

template<typename T>
LinkedList<T>&
DataStructures::LinkedList<T>::operator=(LinkedList&& other) noexcept
{
  if (this == &other)
    return *this;

  Element* new_first = other.first;
  Element* new_last = other.last;
  size_t new_number_of_elements = other.number_of_elements;

  other.first = first;
  other.last = last;
  other.number_of_elements = number_of_elements;

  first = new_first;
  last = new_last;
  number_of_elements = new_number_of_elements;

  return *this;
}

template<typename T>
DataStructures::LinkedList<T>::~LinkedList()
{
  clear();
}

template<typename T>
size_t
DataStructures::LinkedList<T>::size() const
{
  return number_of_elements;
}

template<typename T>
bool
DataStructures::LinkedList<T>::empty() const
{
  return number_of_elements == 0;
}

template<typename T>
bool
DataStructures::LinkedList<T>::operator==(const LinkedList<T>& other) const
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
DataStructures::LinkedList<T>::operator!=(const LinkedList<T>& other) const
{
  return !operator==(other);
}

template<typename T>
T&
DataStructures::LinkedList<T>::front()
{
  assert(!empty());
  return first->datum;
}

template<typename T>
const T&
DataStructures::LinkedList<T>::cfront() const
{
  assert(!empty());
  return first->datum;
}

template<typename T>
T&
DataStructures::LinkedList<T>::back()
{
  assert(!empty());
  return last->datum;
}

template<typename T>
const T&
DataStructures::LinkedList<T>::cback() const
{
  assert(!empty());
  return last->datum;
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
  Element* new_last = new Element{ new_value, nullptr };
  if (!empty())
    last->next = new_last;
  else
    first = new_last;
  last = new_last;
  number_of_elements += 1;
}

template<typename T>
T
DataStructures::LinkedList<T>::pop_front()
{
  assert(!empty());
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
  assert(!empty());
  T old_last_datum;
  if (first->next == nullptr) {
    old_last_datum = first->datum;
    delete first;
    first = nullptr;
    number_of_elements -= 1;
    return old_last_datum;
  }

  Element* new_last = first;
  while (new_last->next != last) {
    new_last = new_last->next;
  }
  old_last_datum = last->datum;
  delete last;
  new_last->next = nullptr;
  last = new_last;
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
  last = nullptr;
  number_of_elements = 0;
}

template<typename T>
bool
DataStructures::LinkedList<T>::remove(const T& value)
{
  if (empty())
    return false;
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

template<typename T>
bool
operator==(const LinkedList<T>& a, const LinkedList<T>& b)
{
  return a.operator==(b);
}

template<typename T>
bool
operator!=(const LinkedList<T>& a, const LinkedList<T>& b)
{
  return a.operator!=(b);
}

template<typename T>
bool
operator==(typename LinkedList<T>::iterator a,
           typename LinkedList<T>::iterator b)
{
  return a.operator==(b);
}

template<typename T>
bool
operator!=(typename LinkedList<T>::iterator a,
           typename LinkedList<T>::iterator b)
{
  return a.operator!=(b);
}
