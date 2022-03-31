// inlined in DoublyLinkedList.h

template<typename T>
typename DataStructures::DoublyLinkedList<T>::iterator&
DataStructures::DoublyLinkedList<T>::iterator::operator++()
{
  current = current->next;
  return *this;
}

template<typename T>
bool
DataStructures::DoublyLinkedList<T>::iterator::operator==(iterator other) const
{
  return current == other.current;
}

template<typename T>
bool
DataStructures::DoublyLinkedList<T>::iterator::operator!=(iterator other) const
{
  return current != other.current;
}

template<typename T>
T
DataStructures::DoublyLinkedList<T>::iterator::operator*() const
{
  return current->datum;
}

template<typename T>
typename DataStructures::DoublyLinkedList<T>::reverse_iterator&
DataStructures::DoublyLinkedList<T>::reverse_iterator::operator++()
{
  current = current->previous;
  return *this;
}

template<typename T>
bool
DataStructures::DoublyLinkedList<T>::reverse_iterator::operator==(
  reverse_iterator other) const
{
  return current == other.current;
}

template<typename T>
bool
DataStructures::DoublyLinkedList<T>::reverse_iterator::operator!=(
  reverse_iterator other) const
{
  return current != other.current;
}

template<typename T>
T
DataStructures::DoublyLinkedList<T>::reverse_iterator::operator*() const
{
  return current->datum;
}

template<typename T>
typename DataStructures::DoublyLinkedList<T>::iterator
DataStructures::DoublyLinkedList<T>::begin() const
{
  return iterator{ first };
}

template<typename T>
typename DataStructures::DoublyLinkedList<T>::iterator
DataStructures::DoublyLinkedList<T>::end() const
{
  return iterator{};
}

template<typename T>
typename DataStructures::DoublyLinkedList<T>::reverse_iterator
DataStructures::DoublyLinkedList<T>::rbegin() const
{
  return reverse_iterator{ last };
}

template<typename T>
typename DataStructures::DoublyLinkedList<T>::reverse_iterator
DataStructures::DoublyLinkedList<T>::rend() const
{
  return reverse_iterator{};
}

template<typename T>
DataStructures::DoublyLinkedList<T>::DoublyLinkedList(
  std::initializer_list<T> contents)
{
  number_of_elements = contents.size();

  Element* previous = nullptr;
  for (T datum : contents) {
    Element* new_element = new Element{ datum, previous, nullptr };

    if (previous != nullptr)
      previous->next = new_element;
    else
      first = new_element;

    previous = new_element;
  }
  last = previous;
}

template<typename T>
DataStructures::DoublyLinkedList<T>::DoublyLinkedList()
{
  first = nullptr;
  last = nullptr;
  number_of_elements = 0;
}

template<typename T>
DataStructures::DoublyLinkedList<T>::DoublyLinkedList(
  const DoublyLinkedList& other)
{
  number_of_elements = 0;
  *this = other;
}

template<typename T>
DataStructures::DoublyLinkedList<T>::DoublyLinkedList(
  DoublyLinkedList&& other) noexcept
{
  first = other.first;
  last = other.last;
  number_of_elements = other.number_of_elements;

  other.first = nullptr;
  other.last = nullptr;
  other.number_of_elements = 0;
}

template<typename T>
DataStructures::DoublyLinkedList<T>&
DataStructures::DoublyLinkedList<T>::operator=(const DoublyLinkedList& other)
{
  if (!empty())
    clear();
  first = nullptr;
  number_of_elements = other.size();
  Element* previous = first;
  for (T datum : other) {
    Element* next = new Element{ datum, previous, nullptr };
    if (first == nullptr)
      first = next;
    else
      previous->next = next;
    previous = next;
  }
  last = previous;
  return *this;
}

template<typename T>
DataStructures::DoublyLinkedList<T>&
DataStructures::DoublyLinkedList<T>::operator=(
  DoublyLinkedList&& other) noexcept
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
DataStructures::DoublyLinkedList<T>::~DoublyLinkedList()
{
  clear();
}

template<typename T>
size_t
DataStructures::DoublyLinkedList<T>::size() const
{
  return number_of_elements;
}

template<typename T>
bool
DataStructures::DoublyLinkedList<T>::empty() const
{
  return number_of_elements == 0;
}

template<typename T>
bool
DataStructures::DoublyLinkedList<T>::operator==(
  const DoublyLinkedList<T>& other) const
{
  if (other.size() != number_of_elements)
    return false;

  iterator this_it = begin();
  iterator other_it = other.begin();
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
DataStructures::DoublyLinkedList<T>::operator!=(
  const DoublyLinkedList<T>& other) const
{
  return !operator==(other);
}

template<typename T>
const T&
DataStructures::DoublyLinkedList<T>::front() const
{
  return first->datum;
}

template<typename T>
const T&
DataStructures::DoublyLinkedList<T>::back() const
{
  return last->datum;
}

template<typename T>
void
DataStructures::DoublyLinkedList<T>::push_front(const T& new_value)
{
  Element* new_first = new Element{ new_value, nullptr, first };
  if (first == nullptr)
    last = new_first;
  else
    first->previous = new_first;
  first = new_first;
  number_of_elements += 1;
}

template<typename T>
void
DataStructures::DoublyLinkedList<T>::push_back(const T& new_value)
{
  Element* new_last = new Element{ new_value, last, nullptr };
  if (last == nullptr)
    first = new_last;
  else
    last->next = new_last;
  last = new_last;
  number_of_elements += 1;
}

template<typename T>
T
DataStructures::DoublyLinkedList<T>::pop_front()
{
  T old_first_datum = first->datum;
  Element* new_first = first->next;
  if (number_of_elements > 1)
    new_first->previous = nullptr;
  else
    last = nullptr;
  first->next = nullptr;
  delete first;
  first = new_first;
  number_of_elements -= 1;
  return old_first_datum;
}

template<typename T>
T
DataStructures::DoublyLinkedList<T>::pop_back()
{
  T old_last_datum = last->datum;
  Element* new_last = last->previous;
  if (number_of_elements > 1)
    new_last->next = nullptr;
  else
    first = nullptr;
  last->previous = nullptr;
  delete last;
  last = new_last;
  number_of_elements -= 1;
  return old_last_datum;
}

template<typename T>
void
DataStructures::DoublyLinkedList<T>::clear()
{
  Element* current = first;
  while (current != nullptr) {
    Element* next = current->next;
    current->next = nullptr;
    current->previous = nullptr;
    delete current;
    current = next;
  }
  first = nullptr;
  last = nullptr;
  number_of_elements = 0;
}

template<typename T>
bool
DataStructures::DoublyLinkedList<T>::remove(const T& value)
{
  if (empty())
    return false;
  if (first->datum == value) {
    Element* old_first = first;
    first = first->next;
    first->previous = nullptr;
    delete old_first;
    number_of_elements -= 1;
    return true;
  }

  Element* current = first->next;
  while (current != nullptr) {
    if (current->datum == value) {
      current->previous->next = current->next;
      current->previous = nullptr;
      current->next = nullptr;
      delete current;
      number_of_elements -= 1;
      return true;
    }
    current = current->next;
  }
  return false;
}

template<typename T>
DataStructures::DoublyLinkedList<T>
DataStructures::DoublyLinkedList<T>::map(std::function<T(const T&)> closure)
{
  DoublyLinkedList<T> mapped_list = DoublyLinkedList<T>{};
  for (T datum : *this) {
    mapped_list.push_back(closure(datum));
  }
  return mapped_list;
}

template<typename T>
bool
operator==(typename DoublyLinkedList<T>::iterator a,
           typename DoublyLinkedList<T>::iterator b)
{
  return a.operator==(b);
}

template<typename T>
bool
operator!=(typename DoublyLinkedList<T>::iterator a,
           typename DoublyLinkedList<T>::iterator b)
{
  return a.operator!=(b);
}

template<typename T>
bool
operator==(typename DoublyLinkedList<T>::reverse_iterator a,
           typename DoublyLinkedList<T>::reverse_iterator b)
{
  return a.operator==(b);
}

template<typename T>
bool
operator!=(typename DoublyLinkedList<T>::reverse_iterator a,
           typename DoublyLinkedList<T>::reverse_iterator b)
{
  return a.operator!=(b);
}

template<typename T>
bool
operator==(DoublyLinkedList<T> a, DoublyLinkedList<T> b)
{
  return a.operator==(b);
}

template<typename T>
bool
operator!=(DoublyLinkedList<T> a, DoublyLinkedList<T> b)
{
  return a.operator!=(b);
}
