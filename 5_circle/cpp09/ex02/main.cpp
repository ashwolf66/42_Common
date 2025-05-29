#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	try {
		if (argc < 2)
			throw std::runtime_error("Error");

		PmergeMe pm;
		pm.process(argc, argv);  // ✅ 멤버 함수 호출
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
