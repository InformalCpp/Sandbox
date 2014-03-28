#include <iostream>
#include <type_traits>
#include <utility>

namespace adl
{
	using std::swap;

	template<typename T>
	void swapper(T& lhs, T& rhs) //noexcept(noexcept(swap(lhs, rhs)))
	{
		swap(lhs, rhs);
	}
}

class SwapOperator
{
	template<typename T>
	struct SwapWith
	{
		explicit SwapWith(T& t) noexcept : lhs(t) {}

		void operator%(T& rhs) const //noexcept(noexcept(adl::swapper(rhs, rhs)))
		{
			adl::swapper(lhs, rhs);
		}

		T& lhs;
	};

	template<typename T>
	friend SwapWith<T> operator%(T& t, SwapOperator) noexcept
	{ return SwapWith<T>(t); }
};

SwapOperator Swap;

int main(int, const char*const[])
{
	int l = 2;
	int r = 3;

	l %Swap% r;
	std::cout << "l=" << l << " r=" << r << std::endl;

	return 0;
}