#include "LinkedList.h"

#include <gtest/gtest.h>

#include <string>
#include <type_traits>

using namespace DataStructures;

TEST(LinkedListTest, EmptyListIsEmpty)
{
  LinkedList<int> empty{};
  ASSERT_TRUE(empty.empty());
}

TEST(LinkedListTest, NonEmptyListIsNotEmpty)
{
  LinkedList<int> not_empty{ 1 };
  ASSERT_FALSE(not_empty.empty());
}

TEST(LinkedListTest, EmptyListIsSizeZero)
{
  LinkedList<int> empty{};
  ASSERT_EQ(empty.size(), 0);
}

TEST(LinkedListTest, SingleElementListIsSizeOne)
{
  LinkedList<int> not_empty{ 1 };
  ASSERT_EQ(not_empty.size(), 1);
}

TEST(LinkedListTest, MultiElementListIsSizeLarge)
{
  LinkedList<int> several_elements{ 1, 1, 2, 3, 5, 8 };
  ASSERT_EQ(several_elements.size(), 6);
}

TEST(LinkedListTest, ListIteratorBeginIsAtTheFrontOfTheList)
{
  LinkedList<std::string> mezzanine_computers{
    "T5600", "Premio", "Skull Canyon", "Hades Canyon", "HP Z2 G5 SFF"
  };
  LinkedList<std::string>::iterator cursor = mezzanine_computers.begin();
  ASSERT_EQ(*cursor, "T5600");
}

TEST(LinkedListTest, ListIteratorIteratesThroughEveryElement)
{
  LinkedList<std::string> mezzanine_computers{
    "T5600", "Premio", "Skull Canyon", "Hades Canyon", "HP Z2 G5 SFF"
  };
  LinkedList<std::string>::iterator cursor = mezzanine_computers.begin();
  ++cursor;
  ASSERT_EQ(*cursor, "Premio");
  ++cursor;
  ASSERT_EQ(*cursor, "Skull Canyon");
  ++cursor;
  ASSERT_EQ(*cursor, "Hades Canyon");
  ++cursor;
  ASSERT_EQ(*cursor, "HP Z2 G5 SFF");
}

TEST(LinkedListTest, ListIteratorEqualsEndAfterLastElement)
{
  LinkedList<std::string> mezzanine_computers{
    "T5600", "Premio", "Skull Canyon", "Hades Canyon", "HP Z2 G5 SFF"
  };
  LinkedList<std::string>::iterator cursor = mezzanine_computers.begin();
  while (cursor != mezzanine_computers.end()) {
    ASSERT_NE(mezzanine_computers.end(), cursor);
    ++cursor;
  }
  ASSERT_TRUE(mezzanine_computers.end() == cursor);
}

TEST(LinkedListTest, EmptyListEqualsEmptyList)
{
  LinkedList<int> empty_0{};
  LinkedList<int> empty_1{};
  ASSERT_EQ(empty_0, empty_1);
}

TEST(LinkedListTest, SameValuedListsAreEqual)
{
  LinkedList<int> non_empty_0{ 1 };
  LinkedList<int> non_empty_1{ 1 };
  ASSERT_EQ(non_empty_0, non_empty_1);
  LinkedList<int> fibonacci_0{ 1, 1, 2, 3, 5, 8 };
  LinkedList<int> fibonacci_1{ 1, 1, 2, 3, 5, 8 };
  ASSERT_EQ(fibonacci_0, fibonacci_1);
}

TEST(LinkedListTest, DifferentValueListsAreNotEqual)
{
  LinkedList<int> empty{};
  LinkedList<int> one{ 1 };
  LinkedList<int> fibonacci{ 1, 1, 2, 3, 5, 8 };
  LinkedList<int> fibonacci_zero{ 0, 1, 1, 2, 3, 5 };

  ASSERT_FALSE(empty == one);
  ASSERT_FALSE(one == fibonacci);
  ASSERT_FALSE(fibonacci == fibonacci_zero);
}

TEST(LinkedListTest, SameValuedListsAreNotInequal)
{
  LinkedList<int> non_empty_0{ 1 };
  LinkedList<int> non_empty_1{ 1 };
  ASSERT_FALSE(non_empty_0 != non_empty_1);
  LinkedList<int> fibonacci_0{ 1, 1, 2, 3, 5, 8 };
  LinkedList<int> fibonacci_1{ 1, 1, 2, 3, 5, 8 };
  ASSERT_FALSE(fibonacci_0 != fibonacci_1);
}

TEST(LinkedListTest, DifferentValueListsAreInequal)
{
  LinkedList<int> empty{};
  LinkedList<int> one{ 1 };
  LinkedList<int> fibonacci{ 1, 1, 2, 3, 5, 8 };
  LinkedList<int> fibonacci_zero{ 0, 1, 1, 2, 3, 5 };

  ASSERT_TRUE(empty != one);
  ASSERT_TRUE(one != fibonacci);
  ASSERT_TRUE(fibonacci != fibonacci_zero);
}

TEST(LinkedListTest, ClearingAnEmptyListDoesntApparentlyChangeAnything)
{
  LinkedList<std::string> empty{};
  LinkedList<std::string> also_empty{};
  also_empty.clear();
  ASSERT_EQ(also_empty, empty);
  ASSERT_TRUE(also_empty.empty());
}

TEST(LinkedListTest, ClearingANonEmptyListRemovesAllElements)
{
  LinkedList<int> two{ 2 };
  LinkedList<int> empty{};
  two.clear();
  ASSERT_EQ(two, empty);
  ASSERT_TRUE(two.empty());

  LinkedList<std::string> shovel_knight_bosses{
    "Black Knight",    "King Knight",      "Specter Knight",
    "Plague Knight",   "Mole Knight",      "Treasure Knight",
    "Reize",           "Phantom Striker",  "Baz",
    "Tinker Knight",   "Propellor Knight", "Polar Knight",
    "The Enchantress", "Remnant of Fate",
  };
  LinkedList<std::string> string_empty{};
  shovel_knight_bosses.clear();
  ASSERT_EQ(shovel_knight_bosses, string_empty);
  ASSERT_TRUE(shovel_knight_bosses.empty());
}

TEST(LinkedListTest, FrontGivesTheValueOfTheFirstElementOfTheList)
{
  LinkedList<double> iterated_cosines{
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
  ASSERT_FLOAT_EQ(iterated_cosines.front(), 1.0);
  ASSERT_FLOAT_EQ(iterated_cosines.cfront(), 1.0);
  ASSERT_TRUE(
    std::is_const<
      std::remove_reference<decltype(iterated_cosines.cfront())>::type>::value);

  LinkedList<std::string> non_orientable_manifolds{ "klein bottle" };
  ASSERT_EQ(non_orientable_manifolds.front(), "klein bottle");
  ASSERT_EQ(non_orientable_manifolds.cfront(), "klein bottle");
  ASSERT_TRUE(std::is_const<std::remove_reference<decltype(
                non_orientable_manifolds.cfront())>::type>::value);

  // empty.front() and empty.cfront are undefined
}

TEST(LinkedListTest, BackGivesTheValueOfTheFirstElementOfTheList)
{
  LinkedList<double> iterated_cosines{
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
  ASSERT_FLOAT_EQ(iterated_cosines.back(), 0.7314040424225098);
  ASSERT_FLOAT_EQ(iterated_cosines.cback(), 0.7314040424225098);
  ASSERT_TRUE(
    std::is_const<
      std::remove_reference<decltype(iterated_cosines.cback())>::type>::value);

  LinkedList<std::string> non_orientable_manifolds{ "klein bottle" };
  ASSERT_EQ(non_orientable_manifolds.back(), "klein bottle");
  ASSERT_EQ(non_orientable_manifolds.cback(), "klein bottle");
  ASSERT_TRUE(std::is_const<std::remove_reference<decltype(
                non_orientable_manifolds.cback())>::type>::value);

  // empty.back() and empty.cback are undefined
}

TEST(LinkedListTest, PushFrontAddsItemsToTheBeginningOfTheList)
{
  LinkedList<std::string> unc_thread_sizes{
    "2-56",
    "4-40",
    "6-32",
  };
  unc_thread_sizes.push_front("0-80");
  ASSERT_EQ(unc_thread_sizes.front(), "0-80");
  ASSERT_EQ(unc_thread_sizes.size(), 4);
  unc_thread_sizes.push_front("00-90");
  ASSERT_EQ(unc_thread_sizes.front(), "00-90");
  ASSERT_EQ(unc_thread_sizes.size(), 5);

  LinkedList<std::string> empty{};
  LinkedList<std::string> snacks_i_have{ "pretzels" };
  empty.push_front("pretzels");
  ASSERT_EQ(empty, snacks_i_have);
}

TEST(LinkedListTest, PushBackAddsItemsToTheEndOfTheList)
{
  LinkedList<unsigned char> fun_bytes{ 0xaa, 0x55 };
  fun_bytes.push_back(0x45);
  ASSERT_EQ(fun_bytes.back(), 0x45);
  ASSERT_EQ(fun_bytes.size(), 3);
  fun_bytes.push_back(0x2a);
  ASSERT_EQ(fun_bytes.back(), 0x2a);
  ASSERT_EQ(fun_bytes.size(), 4);

  LinkedList<std::string> empty{};
  LinkedList<std::string> snacks_i_have{ "pretzels" };
  empty.push_back("pretzels");
  ASSERT_EQ(empty, snacks_i_have);
}

TEST(LinkedListTest, PopFrontRemovesAndReturnsTheBeginningOfTheList)
{
  LinkedList<std::string> gothic_horror_novels{
    "Frankenstein", "Dracula", "A Picture of Dorian Grey", "Wuthering Heights"
  };
  ASSERT_EQ(gothic_horror_novels.pop_front(), "Frankenstein");
  ASSERT_EQ(gothic_horror_novels.front(), "Dracula");
  ASSERT_EQ(gothic_horror_novels.size(), 3);
  ASSERT_EQ(gothic_horror_novels.pop_front(), "Dracula");
  ASSERT_EQ(gothic_horror_novels.front(), "A Picture of Dorian Grey");
  ASSERT_EQ(gothic_horror_novels.size(), 2);
  ASSERT_EQ(gothic_horror_novels.pop_front(), "A Picture of Dorian Grey");
  ASSERT_EQ(gothic_horror_novels.front(), "Wuthering Heights");
  ASSERT_EQ(gothic_horror_novels.size(), 1);
  ASSERT_EQ(gothic_horror_novels.pop_front(), "Wuthering Heights");
  ASSERT_EQ(gothic_horror_novels.size(), 0);
  // empty.pop_front() is undefined
}

TEST(LinkedListTest, PushBackWorksAfterPopFront)
{
  // it stands to reason that .pop_front() could be implemented so
  // getting the back of the list doesn't work, and I don't want that
  LinkedList<int> hexagonal_numbers{ 1, 6, 15, 28, 45, 66 };
  LinkedList<int> hexagonal_numbers_after{ 6, 15, 28, 45, 66, 91 };
  hexagonal_numbers.pop_front();
  hexagonal_numbers.push_back(91);
  ASSERT_EQ(hexagonal_numbers, hexagonal_numbers_after);
}

TEST(LinkedListTest, PopBackRemovesAndReturnsTheBackOfTheList)
{
  LinkedList<std::string> mario_games{ "Paper Mario TTYD",
                                       "Super Mario Galaxy",
                                       "Super Mario Bros. 35" };
  ASSERT_EQ(mario_games.pop_back(), "Super Mario Bros. 35");
  ASSERT_EQ(mario_games.size(), 2);
  ASSERT_EQ(mario_games.back(), "Super Mario Galaxy");
  ASSERT_EQ(mario_games.pop_back(), "Super Mario Galaxy");
  ASSERT_EQ(mario_games.size(), 1);
  ASSERT_EQ(mario_games.back(), "Paper Mario TTYD");
  ASSERT_EQ(mario_games.pop_back(), "Paper Mario TTYD");
  ASSERT_EQ(mario_games.size(), 0);
  // empty.pop_back() is undefined
}

TEST(LinkedListTest, RemoveDeletesTheFirstEqualElement)
{
  LinkedList<int> naturals_mod_3{ 0, 1, 2, 0, 1, 2, 0 };
  ASSERT_TRUE(naturals_mod_3.remove(0));
  LinkedList<int> naturals_mod_3_sans_first_0{ 1, 2, 0, 1, 2, 0 };
  ASSERT_EQ(naturals_mod_3, naturals_mod_3_sans_first_0);
  ASSERT_TRUE(naturals_mod_3.remove(0));
  LinkedList<int> naturals_mod_3_sans_two_0s{ 1, 2, 1, 2, 0 };
  ASSERT_EQ(naturals_mod_3, naturals_mod_3_sans_two_0s);
  ASSERT_TRUE(naturals_mod_3.remove(0));
  LinkedList<int> naturals_mod_3_sans_all_0s{ 1, 2, 1, 2 };
  ASSERT_EQ(naturals_mod_3, naturals_mod_3_sans_all_0s);
  ASSERT_FALSE(naturals_mod_3.remove(0));
  ASSERT_EQ(naturals_mod_3, naturals_mod_3_sans_all_0s);

  LinkedList<int> empty{};
  LinkedList<int> empty_again{};
  ASSERT_FALSE(empty.remove(0));
  ASSERT_EQ(empty, empty_again);
}

TEST(LinkedListTest, MapAppliesAFunctionToEachElement)
{
  LinkedList<int> naturals{ 1, 2, 3, 4, 5 };
  LinkedList<int> squares{ 1, 4, 9, 16, 25 };
  naturals.map([](const int& x) -> int { return x * x; });
  ASSERT_EQ(naturals, squares);

  LinkedList<int> empty{};
  LinkedList<int> empty_again{};
  empty.map([](const int& x) -> int { return x * x; });
  ASSERT_EQ(empty, empty_again);
}

TEST(LinkedListTest, CopyConstructorCopiesTheData)
{
  LinkedList<int> pi{ 3, 1, 4, 1, 5, 9, 2 };
  LinkedList<int> pi_again{ 3, 1, 4, 1, 5, 9, 2 };
  LinkedList<int> pi_copy{ pi };
  ASSERT_EQ(pi_copy, pi);
  ASSERT_EQ(pi_copy, pi_again);
  pi_copy.push_back(6);
  ASSERT_NE(pi_copy, pi);
  ASSERT_EQ(pi, pi_again);
}

TEST(LinkedListTest, CopyAssignmentCopiesTheData)
{
  LinkedList<int> pi{ 3, 1, 4, 1, 5, 9, 2 };
  LinkedList<int> pi_again{ 3, 1, 4, 1, 5, 9, 2 };
  LinkedList<int> pi_copy;
  pi_copy = pi;
  ASSERT_EQ(pi_copy, pi);
  ASSERT_EQ(pi_copy, pi_again);
  pi_copy.push_back(6);
  ASSERT_NE(pi_copy, pi);
  ASSERT_EQ(pi, pi_again);

  LinkedList<int> pi_small{ 3, 1, 4 };
  LinkedList<int> pi_large{ 3, 1, 4, 1, 5, 9, 2, 6, 5 };
  pi_small = pi_large;
  ASSERT_EQ(pi_small, pi_large);
}

TEST(LinkedListTest, MoveConstructorMovesTheData)
{
  LinkedList<std::string> months{ "January", "February", "March",
                                  "April",   "May",      "June",
                                  "July",    "August",   "September",
                                  "October", "November", "December" };
  LinkedList<std::string> months_again{ "January", "February", "March",
                                        "April",   "May",      "June",
                                        "July",    "August",   "September",
                                        "October", "November", "December" };
  LinkedList<std::string> months_moved{ std::move(months) };
  ASSERT_EQ(months_moved, months_again);
  ASSERT_TRUE(months.empty());
}

TEST(LinkedListTest, MoveAssignmentMovesTheData)
{
  LinkedList<std::string> months{ "January", "February", "March",
                                  "April",   "May",      "June",
                                  "July",    "August",   "September",
                                  "October", "November", "December" };
  LinkedList<std::string> months_again{ "January", "February", "March",
                                        "April",   "May",      "June",
                                        "July",    "August",   "September",
                                        "October", "November", "December" };
  LinkedList<std::string> months_moved;
  months_moved = std::move(months);
  ASSERT_EQ(months_moved, months_again);
  ASSERT_TRUE(months.empty());
}

TEST(LinkedListTest, MoveWhenBothObjectsAlreadyHaveData)
{
  LinkedList<std::string> months_fi{ "Tammikuu", "Helmikuu",  "Maaliskuu",
                                     "Huhtikuu", "Toukokuu",  "Kesäkuu",
                                     "Heinäkuu", "Elokuu",    "Syyskuu",
                                     "Lokakuu",  "Marraskuu", "Joulukku" };
  LinkedList<std::string> months_fi_again{
    "Tammikuu", "Helmikuu", "Maaliskuu", "Huhtikuu", "Toukokuu",  "Kesäkuu",
    "Heinäkuu", "Elokuu",   "Syyskuu",   "Lokakuu",  "Marraskuu", "Joulukku"
  };
  LinkedList<std::string> months_en{ "January", "February", "March",
                                     "April",   "May",      "June",
                                     "July",    "August",   "September",
                                     "October", "November", "December" };
  months_en = std::move(months_fi);
  ASSERT_EQ(months_en, months_fi_again);
}

TEST(LinkedListTest, MoveEmptyLists)
{
  LinkedList<std::string> empty_0{};
  LinkedList<std::string> empty_1{};
  empty_0 = std::move(empty_1);
  ASSERT_TRUE(empty_0.empty());

  LinkedList<std::string> empty_2{};
  LinkedList<std::string> months_fi{ "Tammikuu", "Helmikuu",  "Maaliskuu",
                                     "Huhtikuu", "Toukokuu",  "Kesäkuu",
                                     "Heinäkuu", "Elokuu",    "Syyskuu",
                                     "Lokakuu",  "Marraskuu", "Joulukku" };
  LinkedList<std::string> months_fi_again{
    "Tammikuu", "Helmikuu", "Maaliskuu", "Huhtikuu", "Toukokuu",  "Kesäkuu",
    "Heinäkuu", "Elokuu",   "Syyskuu",   "Lokakuu",  "Marraskuu", "Joulukku"
  };
  empty_2 = std::move(months_fi);
  ASSERT_EQ(empty_2, months_fi_again);

  LinkedList<std::string> months_se{ "Januari", "Febuari",  "Mars",
                                     "April",   "Maj",      "Juni",
                                     "Juli",    "Augusti",  "September",
                                     "Oktober", "November", "December" };
  LinkedList<std::string> empty_3{};
  months_se = std::move(empty_3);
  ASSERT_TRUE(months_se.empty());
}

TEST(LinkedListTest, MoveAnObjectToItself)
{
  // moving an object to itself should be trivial
  LinkedList<std::string> empty{};
  empty = std::move(empty);
  ASSERT_TRUE(empty.empty());

  LinkedList<std::string> months_fi_0{ "Tammikuu", "Helmikuu",  "Maaliskuu",
                                       "Huhtikuu", "Toukokuu",  "Kesäkuu",
                                       "Heinäkuu", "Elokuu",    "Syyskuu",
                                       "Lokakuu",  "Marraskuu", "Joulukku" };
  LinkedList<std::string> months_fi_1{ "Tammikuu", "Helmikuu",  "Maaliskuu",
                                       "Huhtikuu", "Toukokuu",  "Kesäkuu",
                                       "Heinäkuu", "Elokuu",    "Syyskuu",
                                       "Lokakuu",  "Marraskuu", "Joulukku" };
  months_fi_0 = std::move(months_fi_0);
  ASSERT_EQ(months_fi_0, months_fi_1);
}
