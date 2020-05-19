#ifndef FFTWMALLOCATOR_HPP
#define FFTWMALLOCATOR_HPP
#include <fftw3.h>
#include <new>
#include <limits>

template <class T>
struct FftwMallocator
{
  typedef T value_type;

  FftwMallocator () = default;
  template <class U> constexpr FftwMallocator (const FftwMallocator <U>&) noexcept {}

  [[nodiscard]] T* allocate(std::size_t n) {
	if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
	  throw std::bad_alloc();

	if (auto p = static_cast<T*>(fftwf_malloc(n*sizeof(T))))
	  return p;

	throw std::bad_alloc();
  }
  void deallocate(T* p, std::size_t) noexcept { fftwf_free(p); }
};

template <class T, class U>
bool operator==(const FftwMallocator <T>&, const FftwMallocator <U>&) { return true; }
template <class T, class U>
bool operator!=(const FftwMallocator <T>&, const FftwMallocator <U>&) { return false; }

#endif // FFTWMALLOCATOR_HPP
