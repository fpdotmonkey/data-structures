#ifndef __DATA_STRUCTURES_LINKED_LIST
#define __DATA_STRUCTURES_LINKED_LIST

#include <climits>
#include <functional>
#include <iterator>

namespace DataStructures {

template<typename T>
class LinkedList
{
public:
private:
  struct Element
  {
    T datum;
    Element* next;
  };

  Element* first;
  size_t number_of_elements;

public:
  /**
    A type for iterating forward through the list.
  */
  class iterator : std::iterator<std::input_iterator_tag, T>
  {
  public:
  private:
    Element* current;

  public:
    explicit iterator(Element* start);
    explicit iterator()
      : current(nullptr)
    {}
    iterator& operator++();
    bool operator==(iterator other);
    bool operator!=(iterator other);
    T operator*() const;
  };

  /**
    An iterator to the start of the list.
  */
  iterator begin();

  /**
    An iterator to the terminus of the list.
  */
  iterator end();

  /**
    Construct the list from the logical contents.

    @param  contents  Those elements which make up the list.
  */
  LinkedList(std::initializer_list<T> contents);

  /**
    Construct an empty list.
  */
  LinkedList();

  /**
    There will be no copies nor moves of this class.
    {
  */
  LinkedList(const LinkedList& /*unused*/) = delete;
  LinkedList& operator=(const LinkedList& /*unused*/) = delete;
  LinkedList(LinkedList&& /*unused*/) = delete;
  LinkedList& operator=(LinkedList&& /*unused*/) = delete;
  /**}*/

  /**
    Destroy the list.
  */
  ~LinkedList();

  /**
    The number of elements in the list.
  */
  size_t size();

  /**
    Check if there are exactly 0 elements in the list.
  */
  bool empty();

  /**
    Check if this and that list have equal data.

    @param  other   A list whose equality you're interested in
  */
  bool operator==(LinkedList<T>& other);

  /**
    Check if this and that list have inequal data.

    @param  other   A list whose inequality you're interested in
  */
  bool operator!=(LinkedList<T>& other);

  /**
    The value of the first item in the list.

    @return The datum beginning the list
  */
  T& front();

  /**
    The value of the last item in the list.

    @return The datum terminating the list
  */
  T& back();

  /**
    Add the given value to the beginning of the list.

    @param  new_value   The datum to be added to the list
  */
  void push_front(const T& new_value);

  /**
    Add the given value to the end of the list.

    @param  new_value   The datum to be added to the list
  */
  void push_back(const T& new_value);

  /**
    Remove the first item from the list and return it.

    @return The datum formerly at the start of the list
  */
  T pop_front();

  /**
    Remove the last item from the list and return it.

    @return The datum that was previously the list's last
  */
  T pop_back();

  /**
    Remove all elements from the list.
  */
  void clear();

  /**
    Delete the first element equal to the given value.

    @param  value   That value whose equal will be tossed out.

    @return True if value had an equal to be removed, otherwise false
  */
  bool remove(const T& value);

  /**
    Apply the given function element-wise to the list.

    @param closure  A function representing the desired mutation
  */
  void map(std::function<T(const T&)> closure);
};

#include "LinkedList.inl"

} // namespace DataStructures

#endif
