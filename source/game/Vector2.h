#pragma once

#include <array>
#include <algorithm>
#include <cassert>

namespace breakout
{
	template<typename T>
	class Vector2
	{
	public:

		Vector2() = default;
		Vector2(const std::array<T, 2>&);
		Vector2(std::initializer_list<T>&);
		~Vector2() = default;

		void operator=(const std::array<T, 2>&);
		void operator+=(const std::array<T, 2>&);

		void operator=(const Vector2<T>&);
		void operator+=(const Vector2<T>&);

		void operator=(std::initializer_list<T>&);

		Vector2<T> operator+(Vector2<T>&);
		Vector2<T> operator-(Vector2<T>&);
		Vector2<T> operator*(T);

		std::array<T, 2>& operator->();

		const std::array<T, 2>& data() const;

		T length()
		{
			return static_cast<T>(0);
		}

		T sqrLength()
		{
			return static_cast<T>(0);
		}

		Vector2<T> normalized()
		{
			return Vector2<T>();
		}

		T& operator[](std::size_t i);

		T& x();
		T& y();

		static T Dot(const Vector2<T>&, const Vector2<T>&);
		static T Dot(const std::array<T, 2>&, const std::array<T, 2>&);

		static Vector2<T> Clamp(const Vector2<T>&, const Vector2<T>&);
		static Vector2<T> Clamp(const std::array<T, 2>&, const std::array<T, 2>&);

	private:

		std::array<T, 2> m_data = {0, 0};
	};

	template<typename T>
	Vector2<T>::Vector2(const std::array<T, 2>& arr)
	{
		m_data = arr;
	}

	template<typename T>
	Vector2<T>::Vector2(std::initializer_list<T>& list)
	{
		m_data.fill(list);
	}

	template<typename T>
	void Vector2<T>::operator=(const std::array<T, 2>& arr)
	{
		m_data = arr;
	}

	template<typename T>
	void Vector2<T>::operator+=(const std::array<T, 2>& arr)
	{
		m_data = {this->x() + arr[0], this->y() + arr[1]};
	}

	template<typename T>
	void Vector2<T>::operator=(const Vector2<T>& vector)
	{
		m_data = vector.data();
	}

	template<typename T>
	void Vector2<T>::operator+=(const Vector2<T>& v)
	{
		const std::array<float, 2> arr = v.data();
		m_data = { this->x() + arr[0], this->y() + arr[1] };
	}

	template<typename T>
	void Vector2<T>::operator=(std::initializer_list<T>& list)
	{
		m_data.fill(list);
	}


	template<typename T>
	Vector2<T> Vector2<T>::operator+(Vector2<T>& v)
	{
		return Vector2<T>({this->x() + v.x(), this->y()+ v.y()});
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator-(Vector2<T>& v)
	{
		return Vector2<T>({ this->x() - v.x(), this->y() - v.y() });
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator*(T val)
	{
		return Vector2<T>({this->x() * val, this->y() * val});
	}

	template<typename T>
	std::array<T, 2>& Vector2<T>::operator->()
	{
		return m_data;
	}

	template<typename T>
	const std::array<T, 2>& Vector2<T>::data() const
	{
		return m_data;
	}


	template<>
	float Vector2<float>::length()
	{
		return sqrtf(m_data[0] * m_data[0] + m_data[1] * m_data[1]);
	}

	template<>
	float Vector2<float>::sqrLength()
	{
		return m_data[0] * m_data[0] + m_data[1] * m_data[1];
	}

	template<>
	Vector2<float> Vector2<float>::normalized()
	{
		float invLen = 1.f / length();
		return Vector2<float>({m_data[0] * invLen, m_data[1] * invLen });
	}

	template<typename T>
	T& Vector2<T>::operator[](std::size_t i)
	{
		return m_data.at(i);
	}

	template<typename T>
	T& Vector2<T>::x()
	{
		return m_data.at(0);
	}

	template<typename T>
	T& Vector2<T>::y()
	{
		return m_data.at(1);
	}

	template<typename T>
	T Vector2<T>::Dot(const Vector2<T>& v1, const Vector2<T>& v2)
	{
		return v1.x() * v2.x() + v1.y() * v2.y();
	}

	template<typename T>
	T Vector2<T>::Dot(const std::array<T, 2>& arr1, const std::array<T, 2>& arr2)
	{
		return arr1[0] * arr2[0] + arr1[1] * arr2[1];
	}

	template<typename T>
	Vector2<T> Vector2<T>::Clamp(const Vector2<T>& v1, const Vector2<T>& v2)
	{
		const auto& arr1 = v1.data();
		const auto& arr2 = v2.data();

		T rx = std::clamp(arr1[0], -arr2[0], arr2[0]);
		T ry = std::clamp(arr1[1], -arr2[1], arr2[1]);

		return Vector2<T>({rx, ry});
	}

	template<typename T>
	Vector2<T> Vector2<T>::Clamp(const std::array<T, 2>& arr1, const std::array<T, 2>& arr2)
	{
		T rx = std::clamp(arr1[0], -arr2[0], arr2[0]);
		T ry = std::clamp(arr1[1], -arr2[1], arr2[1]);

		return Vector2<T>({ rx, ry });
	}
}