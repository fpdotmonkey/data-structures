#ifndef __DATA_STRUCTURES_DOUBLY_LINKED_LIST
#define __DATA_STRUCTURES_DOUBLY_LINKED_LIST

#include <functional>
#include <iterator>
#include <type_traits>

namespace DataStructures {

template<typename T>
class DoublyLinkedList
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
    Element* previous;
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
    explicit iterator(Element* start)
      : current(start)
    {}
    explicit iterator()
      : current(nullptr)
    {}
    iterator& operator++();
    bool operator==(iterator other) const;
    bool operator!=(iterator other) const;
    T operator*() const;
  };

  /**
    A type for iterating backward through the list.
  */
  class reverse_iterator : std::iterator<std::forward_iterator_tag, T>
  {
  public:
  private:
    Element* current;

  public:
    explicit reverse_iterator(Element* start)
      : current(start)
    {}
    explicit reverse_iterator()
      : current(nullptr)
    {}
    reverse_iterator& operator++();
    bool operator==(reverse_iterator other) const;
    bool operator!=(reverse_iterator other) const;
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
    An iterator to the back of the list that increments backwards.
  */
  reverse_iterator rbegin() const;

  /**
    An iterator to one before the start of the list that increments
    backwards.
  */
  reverse_iterator rend() const;

  /**
    Construct the list from the logical contents.

    @param  contents  Those elements which make up the list.
  */
  DoublyLinkedList(std::initializer_list<T> contents);

  /**
    Construct an empty list.
  */
  DoublyLinkedList();

  /**
    Construct a copy of a different list.

    @param  other     The list to copy
  */
  DoublyLinkedList(const DoublyLinkedList& other);

  /**
    Constuct a new list with the exact contents of an old list.

    @param  other     The list to move
  */
  DoublyLinkedList(DoublyLinkedList&& other) noexcept;

  /**
    Assign the list a copy of another list.

    @param  other     The list you'd like copied over
  */
  DoublyLinkedList& operator=(const DoublyLinkedList& other);

  /**
    Move the contents of another list to here.

    @param  other     The list whose data you'd like moved
  */
  DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept;

  /**
    Destroy the list.
  */
  ~DoublyLinkedList();

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
  bool operator==(const DoublyLinkedList<T>& other) const;

  /**
    Check if this and that list have inequal data.

    @param  other   A list whose inequality you're interested in
  */
  bool operator!=(const DoublyLinkedList<T>& other) const;

  /**
    The value of the first item in the list.

    Should the list be empty, this method will result in undefined
    behaviour, likely a crash.

    @return The datum beginning the list
  */
  const T& front() const;

  /**
    The value of the last item in the list.

    Should the list be empty, this method will result in undefined
    behaviour, likely a crash.

    @return The datum terminating the list
  */
  const T& back() const;

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
  DoublyLinkedList<T> map(std::function<T(const T&)> closure);
};

template<typename T>
bool
operator==(typename DoublyLinkedList<T>::iterator a,
           typename DoublyLinkedList<T>::iterator b);

template<typename T>
bool
operator!=(typename DoublyLinkedList<T>::iterator a,
           typename DoublyLinkedList<T>::iterator b);

template<typename T>
bool
operator==(typename DoublyLinkedList<T>::reverse_iterator a,
           typename DoublyLinkedList<T>::reverse_iterator b);

template<typename T>
bool
operator!=(typename DoublyLinkedList<T>::reverse_iterator a,
           typename DoublyLinkedList<T>::reverse_iterator b);

template<typename T>
bool
operator==(DoublyLinkedList<T> a, DoublyLinkedList<T> b);

template<typename T>
bool
operator!=(DoublyLinkedList<T> a, DoublyLinkedList<T> b);

#include "DoublyLinkedList.inl"

} // namespace DataStructures

#endif
