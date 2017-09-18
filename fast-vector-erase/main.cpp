

#include <vector>

#if 0
using Data = int;
#else

#include <string>

struct my_struct
{
  std::string str;

  my_struct(int i)
    : str("Yeeep a very long string to hold the integer: " + std::to_string(i))
  {
  }
};
using Data = my_struct;
#endif

/**
 * Firstly a method to build our test vector
 */
std::vector<Data>
make_vector(void)
{
  std::vector<Data> v;

  for (int i = 0; i < 1000; ++i) {
    v.push_back(i);
  }
  return v;
}

/*
 * This way requires to shift all the element to fill the gap made by deleting
 * the first entry.
 */
void
traditional_way(void)
{
  std::vector<Data> v = make_vector();

  // oups we need to delete the first row
  v.erase(v.begin());
}

/**
 * If you don't need to keep the same order, you can in fact just swap it with
 * the last element and pop the last one.
 */
void
fast_way(void)
{
  std::vector<Data> v = make_vector();

  // However swap is a method that has a cost so if it's plain data, prefer to
  // copy it

  const std::vector<Data>::size_type index = 0;
  // Make sure that the entry to be deleted (here begin()) is not the end
  if ((index + 1) < v.size()) {
    constexpr bool do_copy = std::is_trivially_copyable<Data>::value;
    if (do_copy) {
      v[0] = v.back();
    } else {
      std::swap(v.front(), v.back());
    }
  }

  // Then just pop back
  v.pop_back();
}

int
main(int argc, char* argv[])
{
  traditional_way();

  fast_way();
  return 0;
}
