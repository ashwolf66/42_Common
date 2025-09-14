#ifndef VEC2_HPP
# define VEC2_HPP

#include <iostream>
#include <vector>

class vec2 {
	private:
		std::vector <int> _vector;

	public:
		vec2();
		vec2(int num1, int num2);
		vec2(const vec2& other);
		vec2& operator=(const vec2& other);
		~vec2();

		vec2 operator+(int num) const;
		vec2 operator+(const vec2& other) const;
		vec2 operator-(int num) const;
		vec2 operator-(const vec2& other) const;
		vec2 operator*(int num) const;
		vec2 operator*(const vec2& other) const;

		vec2& operator++();
		vec2 operator++(int);
		vec2& operator--();
		vec2 operator--(int);

		vec2& operator+=(int num);
		vec2& operator+=(const vec2& other);
		vec2& operator-=(int num);
		vec2& operator-=(const vec2& other);
		vec2& operator*=(int num);
		vec2& operator*=(const vec2& other);

		bool operator==(const vec2& other)const;
		bool operator!=(const vec2& other)const;

		// Remove incorrect member declarations for operator* and operator<<
		// Declare them as friend functions below

		friend vec2 operator*(int num, const vec2& v);
		friend std::ostream& operator<<(std::ostream& out, const vec2& v);
};

#endif
