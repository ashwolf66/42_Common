#ifndef VECT2_HPP
# define VECT2_HPP

#include <iostream>
#include <vector>

class vect2 {
	private:
		std::vector <int> _vector;

	public:
		vect2();
		vect2(int num1, int num2);
		vect2(const vect2& other);
		vect2& operator=(const vect2& other);
		~vect2();

		vect2 operator+(int num) const;
		vect2 operator+(const vect2& other) const;
		vect2 operator-(int num) const;
		vect2 operator-(const vect2& other) const;
		vect2 operator*(int num) const;
		vect2 operator*(const vect2& other) const;

		vect2& operator++();
		vect2 operator++(int);
		vect2& operator--();
		vect2 operator--(int);

		vect2& operator+=(int num);
		vect2& operator+=(const vect2& other);
		vect2& operator-=(int num);
		vect2& operator-=(const vect2& other);
		vect2& operator*=(int num);
		vect2& operator*=(const vect2& other);

		bool operator==(const vect2& other)const;
		bool operator!=(const vect2& other)const;

		friend vect2 operator*(int num, const vect2& v);
		friend std::ostream& operator<<(std::ostream& out, const vect2& v);
};

#endif
