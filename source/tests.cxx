#include "LinkedList.h"

#include <cassert>
#include <cmath>
#include <string>

void
test_linked_list()
{
  // LinkedList::LinkedList()
  DataStructures::LinkedList<int> empty{};
  DataStructures::LinkedList<int> not_empty{ 1 };
  DataStructures::LinkedList<int> several_elements{ 1, 1, 2, 3, 5, 8 };

  // LinkedList::empty()
  assert(empty.empty());
  assert(!not_empty.empty());

  // LinkedList::size()
  assert(empty.size() == 0);
  assert(not_empty.size() == 1);
  assert(several_elements.size() == 6);

  // LinkedList::begin
  DataStructures::LinkedList<std::string> mezzanine_computers{
    "T5600", "Premio", "Skull Canyon", "Hades Canyon", "HP Z2 G5 SFF"
  };
  DataStructures::LinkedList<std::string>::iterator cursor =
    mezzanine_computers.begin();
  assert(*cursor == "T5600");
  ++cursor;
  assert(*cursor == "Premio");
  ++cursor;
  assert(*cursor == "Skull Canyon");
  ++cursor;
  assert(*cursor == "Hades Canyon");
  ++cursor;
  assert(*cursor == "HP Z2 G5 SFF");

  // LinkedList::end
  ++cursor;
  assert(mezzanine_computers.end() == cursor);
  assert(!(cursor != mezzanine_computers.end()));
  assert(mezzanine_computers.begin() != mezzanine_computers.end());

  // LinkedList::operator==(LinkedList)
  DataStructures::LinkedList<int> also_empty{};
  assert(empty == also_empty);
  DataStructures::LinkedList<int> one{ 1 };
  assert(not_empty == one);
  DataStructures::LinkedList<int> fibonacci{ 1, 1, 2, 3, 5, 8 };
  assert(several_elements == fibonacci);
  assert(!(one == empty));
  assert(!(fibonacci == one));
  DataStructures::LinkedList<int> other_fibonacci{ 0, 1, 1, 2, 3, 5 };
  assert(!(other_fibonacci == fibonacci));

  // LinkedList::operator!=(LinkedList)
  assert(one != empty);
  assert(fibonacci != one);
  assert(!(empty != empty));
  assert(!(fibonacci != several_elements));

  // LinkedList::clear()
  also_empty.clear();
  assert(also_empty == empty);
  assert(also_empty.size() == 0);
  DataStructures::LinkedList<int> two{ 2 };
  two.clear();
  assert(two == empty);
  assert(two.size() == 0);
  fibonacci.clear();
  assert(fibonacci == empty);
  assert(fibonacci.size() == 0);
  DataStructures::LinkedList<std::string> shovel_knight_bosses{
    "Black Knight",    "King Knight",      "Specter Knight",
    "Plague Knight",   "Mole Knight",      "Treasure Knight",
    "Reize",           "Phantom Striker",  "Baz",
    "Tinker Knight",   "Propellor Knight", "Polar Knight",
    "The Enchantress", "Remnant of Fate",
  };
  DataStructures::LinkedList<std::string> string_empty{};
  shovel_knight_bosses.clear();
  assert(shovel_knight_bosses == string_empty);
  assert(shovel_knight_bosses.size() == 0);

  // LinkedList::front()
  DataStructures::LinkedList<double> iterated_cosines{
    1.0,
    0.5403023058681398,
    0.8575532158463934,
    0.6542897904977791,
    0.7934803587425656,
    0.7013687736227565,
    0.7639596829006542,
    0.7221024250267077,
    0.7504177617637605,
    0.7314040424225098,
  };
  assert(iterated_cosines.front() == 1.0);
  DataStructures::LinkedList<std::string> non_orientable_manifolds{
    "klein bottle"
  };
  assert(non_orientable_manifolds.front() == "klein bottle");
  // empty.front() is undefined

  // LinkedList::back()
  assert(std::abs(iterated_cosines.back() - 0.7314040424225098) < 0.000001);
  assert(non_orientable_manifolds.back() == "klein bottle");
  // empty.back() is undefined

  // LinkedList::push_front(const T&)
  DataStructures::LinkedList<std::string> unc_thread_sizes{
    "2-56",
    "4-40",
    "6-32",
  };
  unc_thread_sizes.push_front("0-80");
  assert(unc_thread_sizes.front() == "0-80");
  assert(unc_thread_sizes.size() == 4);
  unc_thread_sizes.push_front("00-90");
  assert(unc_thread_sizes.front() == "00-90");
  assert(unc_thread_sizes.size() == 5);

  // LinkedList::push_back(const T&)
  DataStructures::LinkedList<unsigned char> fun_bytes{ 0xaa, 0x55 };
  fun_bytes.push_back(0x45);
  assert(fun_bytes.back() == 0x45);
  assert(fun_bytes.size() == 3);
  fun_bytes.push_back(0x2a);
  assert(fun_bytes.back() == 0x2a);
  assert(fun_bytes.size() == 4);

  // LinkedList::pop_front()
  DataStructures::LinkedList<std::string> gothic_horror_novels{
    "Frankenstein", "Dracula", "A Picture of Dorian Grey", "Wuthering Heights"
  };
  assert(gothic_horror_novels.pop_front() == "Frankenstein");
  assert(gothic_horror_novels.front() == "Dracula");
  assert(gothic_horror_novels.size() == 3);
  assert(gothic_horror_novels.pop_front() == "Dracula");
  assert(gothic_horror_novels.front() == "A Picture of Dorian Grey");
  assert(gothic_horror_novels.size() == 2);
  assert(gothic_horror_novels.pop_front() == "A Picture of Dorian Grey");
  assert(gothic_horror_novels.front() == "Wuthering Heights");
  assert(gothic_horror_novels.size() == 1);
  assert(gothic_horror_novels.pop_front() == "Wuthering Heights");
  assert(gothic_horror_novels.size() == 0);
  // empty.pop_front() is undefined

  // LinkedList::pop_front() then LinkedList::push_back()
  DataStructures::LinkedList<int> hexagonal_numbers{ 1, 6, 15, 28, 45, 66 };
  DataStructures::LinkedList<int> hexagonal_numbers_after{
    6, 15, 28, 45, 66, 91
  };
  hexagonal_numbers.pop_front();
  hexagonal_numbers.push_back(91);
  assert(hexagonal_numbers == hexagonal_numbers_after);

  // LinkedList::pop_back()
  DataStructures::LinkedList<std::string> mario_games{ "Paper Mario TTYD",
                                                       "Super Mario Galaxy",
                                                       "Super Mario Bros. 35" };
  assert(mario_games.pop_back() == "Super Mario Bros. 35");
  assert(mario_games.size() == 2);
  assert(mario_games.back() == "Super Mario Galaxy");
  assert(mario_games.pop_back() == "Super Mario Galaxy");
  assert(mario_games.size() == 1);
  assert(mario_games.back() == "Paper Mario TTYD");
  assert(mario_games.pop_back() == "Paper Mario TTYD");
  assert(mario_games.size() == 0);
  // empty.pop_back() is undefined

  // LinkedList::remove(const T&)
  DataStructures::LinkedList<int> naturals_mod_3{ 0, 1, 2, 0, 1, 2, 0 };
  assert(naturals_mod_3.remove(0));
  DataStructures::LinkedList<int> naturals_mod_3_sans_first_0{
    1, 2, 0, 1, 2, 0
  };
  assert(naturals_mod_3 == naturals_mod_3_sans_first_0);
  assert(naturals_mod_3.remove(0));
  DataStructures::LinkedList<int> naturals_mod_3_sans_two_0s{ 1, 2, 1, 2, 0 };
  assert(naturals_mod_3 == naturals_mod_3_sans_two_0s);
  assert(naturals_mod_3.remove(0));
  DataStructures::LinkedList<int> naturals_mod_3_sans_all_0s{ 1, 2, 1, 2 };
  assert(naturals_mod_3 == naturals_mod_3_sans_all_0s);
  assert(!naturals_mod_3.remove(0));
  assert(naturals_mod_3 == naturals_mod_3_sans_all_0s);

  // LinkedList::map(std::function<const T&>&&)
  DataStructures::LinkedList<int> naturals{ 1, 2, 3, 4, 5 };
  DataStructures::LinkedList<int> squares{ 1, 4, 9, 16, 25 };
  naturals.map([](const int& x) -> int { return x * x; });
  assert(naturals == squares);
}

int
main(int /*argc*/, char** /*argv*/)
{
  test_linked_list();
  return 0;
}
