#ifndef __DATA_STRUCTURES_LINKED_LIST
#define __DATA_STRUCTURES_LINKED_LIST

#include <cassert>
#include <functional>
#include <iterator>

namespace DataStructures {

template<typename T>
class LinkedList
{
public:
  static_assert(std::is_same<decltype(T{} == T{}), bool>(),
                "value type must have `operator==(T&)` defined");
  static_assert(std::is_same<decltype(T{} != T{}), bool>(),
                "value type must have `operator!=(T&)` defined");

private:
  struct Element
  {
    T datum;
    Element* next;
  };

  Element* first;
  Element* last;
  size_t number_of_elements;

public:
  /**
    A type for iterating forward through the list.
  */
  class iterator : std::iterator<std::forward_iterator_tag, T>
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
    bool operator==(iterator other) const;
    bool operator!=(iterator other) const;
    T operator*() const;
  };

  /**
    An iterator to the start of the list.
  */
  iterator begin() const;

  /**
    An iterator to the terminus of the list.
  */
  iterator end() const;

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
    Construct a copy of a list.
  */
  LinkedList(const LinkedList& other);

  /**
    Move the list to a new place.
  */
  LinkedList(LinkedList&& other) noexcept;

  /**
    Assign the list a copy of another list.
  */
  LinkedList& operator=(const LinkedList& other);

  /**
    Move data from another list to this list.
  */
  LinkedList& operator=(LinkedList&& other) noexcept;

  /**
    Destroy the list.
  */
  ~LinkedList();

  /**
    The number of elements in the list.
  */
  size_t size() const;

  /**
    Check if there are exactly 0 elements in the list.
  */
  bool empty() const;

  /**
    Check if this and that list have equal data.

    @param  other   A list whose equality you're interested in
  */
  bool operator==(const LinkedList<T>& other) const;

  /**
    Check if this and that list have inequal data.

    @param  other   A list whose inequality you're interested in
  */
  bool operator!=(const LinkedList<T>& other) const;

  /**
    The value of the first item in the list.

    Should the list be empty, this method will result in undefined
    behaviour, likely a crash.

    @return The datum beginning the list
    {
  */
  T& front();
  const T& cfront() const;
  /**}*/

  /**
    The value of the last item in the list.

    Should the list be empty, this method will result in undefined
    behaviour, likely a crash.

    @return The datum terminating the list
    {
  */
  T& back();
  const T& cback() const;
  /**}*/

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

    Should the list be empty, this method will result in undefined
    behaviour, likely a crash.

    @return The datum formerly at the start of the list
  */
  T pop_front();

  /**
    Remove the last item from the list and return it.

    Should the list be empty, this method will result in undefined
    behaviour, likely a crash.

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

template<typename T>
bool
operator==(const LinkedList<T>& a, const LinkedList<T>& b);

template<typename T>
bool
operator!=(const LinkedList<T>& a, const LinkedList<T>& b);

template<typename T>
bool
operator==(typename LinkedList<T>::iterator a,
           typename LinkedList<T>::iterator b);

template<typename T>
bool
operator!=(typename LinkedList<T>::iterator a,
           typename LinkedList<T>::iterator b);

#include "LinkedList.inl"

} // namespace DataStructures

#endif
