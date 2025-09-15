#include "bigint.hpp"

int	main(void)
{
    {
        const Bigint	a(42);
        Bigint			b(21), c, d(1337), e(d);
        
        //All are in base10
        std::cout << a << std::endl; // 42
        std::cout << b << std::endl; // 21
        std::cout << c << std::endl; // 0
        std::cout << d << std::endl; // 1337
        std::cout << e << std::endl; // 1337
        std::cout << "a + b = " << a + b << std::endl; // a + b = 63
        std::cout << "(c += a) = " << (c += a) << std::endl; // c = 42, donc (c += a) = 42
        
        std::cout << "\n\n" << std::endl;
        std::cout << "b = " << b << std::endl; // 21
        std::cout << "++b = " << ++b << std::endl; // 22
        std::cout << "b++ = " << b++ << std::endl; // 22
        std::cout << "b = " << b << std::endl; // 23
        int	i = 0;//checking**
        std::cout << "i = " << i << std::endl; // 0
        std::cout << "++i = " << ++i << std::endl; // 1
        std::cout << "i++ = " << i++ << std::endl; // 1
        std::cout << "i = " << i << std::endl; // 2

        std::cout << "\n\n" << std::endl;
        std::cout << "\"((b << 10) + 42)\" = " << ((b << 10) + 42) << std::endl; // 230000000042
        std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl; // 13370000
        std::cout << "(d >>= 2) = " << (d >>= 2) << std::endl; // 133700
        std::cout << "a = " << a << std::endl; // 42
        std::cout << "d = " << d << std::endl; // 133700
        std::cout << "(d < a) = " << (d < a) << std::endl; // 0
        std::cout << "(d > a) = " << (d > a) << std::endl; // 1
        std::cout << "(d == a) = " << (d == a) << std::endl; // 0
        std::cout << "(d != a) = " << (d != a) << std::endl; // 1
        std::cout << "(d == a) = " << (d == d) << std::endl; // 1
        std::cout << "(d <= a) = " << (d <= a) << std::endl; // 0
        std::cout << "(d >= a) = " << (d >= a) << std::endl; // 1

        Bigint x(1234);
        std::cout << std::endl;
        std::cout << "\"(x << 2)\"--> " << (x << 2) << "\n";   // 123400
        std::cout << "\"(x >>= 2)\"--> " << (x >>= 2) << "\n";   // 12
    }
    return (0);
}