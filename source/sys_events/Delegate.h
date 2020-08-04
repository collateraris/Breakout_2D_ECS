#pragma once

#include <cassert>

#include <iostream>

namespace breakout
{

	struct NIL {};

	class IArguments
	{
	public:

		virtual ~IArguments() {};
	};

	template<class T1 = NIL, class T2 = NIL,
			class T3 = NIL, class T4 = NIL>
	class Arguments : public IArguments
	{
	public:

		Arguments(const T1& i_arg1, const T2& i_arg2)
			: m_arg1(i_arg1), m_arg2(i_arg2) {};

		Arguments(const T1& i_arg1, const T2& i_arg2,
			const T1& i_arg3, const T2& i_arg4)
			: m_arg1(i_arg1), 
			m_arg2(i_arg2),
			m_arg3(i_arg3), 
			m_arg4(i_arg4)
		{};

		T1 m_arg1;
		T2 m_arg2;
		T3 m_arg3;
		T4 m_arg4;
	};

	class IContainer 
	{
	public:

		virtual void Call(IArguments*) = 0;
	};

	template<class T, class M>
	class Container : public IContainer {};

	template<class T, class A1, class A2>
		class Container<T, void (T::*)(A1, A2)>
		: public IContainer
	{

		typedef void (T::* M)(A1, A2);
		typedef Arguments<A1, A2> A;

		T* m_class;
		M m_method;

	public:

		Container(T* i_class, M i_method)
			: m_class(i_class),
			m_method(i_method)
		{};

		void Call(IArguments* i_args)
		{
			A* a = dynamic_cast<A*>(i_args);
			assert(a);
			if (a)
			{
				(m_class->*m_method)(a->m_arg1, a->m_arg2);
			}
		}
	};

	template<class T, class A1, class A2,
		class A3, class A4>
	class Container<T, void (T::*)(A1, A2, A3, A4)>
		: public IContainer
	{
	
		typedef void (T::* M)(A1, A2, A3, A4);
		typedef Arguments<A1, A2, A3, A4> A;

		T* m_class;
		M m_method;

	public:

		Container(T* i_class, M i_method)
			: m_class(i_class),
			m_method(i_method)
		{};

		void Call(IArguments* i_args)
		{
			A* a = dynamic_cast<A*>(i_args);
			assert(a);
			if (a)
			{
				(m_class->*m_method)(a->m_arg1,
					a->m_arg2,
					a->m_arg3,
					a->m_arg4);
			}
		}
	};

	class Delegate
	{
	public:

		Delegate()
			: m_container(nullptr)
		{};

		~Delegate()
		{
			if (m_container) delete m_container;
		};

		template<class T, class M>
		void Bind(T* i_class, M i_method)
		{
			if (m_container) delete m_container;
			m_container = new Container<T, M>(i_class, i_method);
		}

		template<class T1, class T2>
		void Execute(const T1& i_arg1, const T2& i_arg2)
		{
			m_container->Call(&Arguments<T1, T2>(i_arg1, i_arg2));
		}

		template<class T1, class T2, class T3, class T4 >
		void Execute(const T1& i_arg1, const T2& i_arg2,
			const T3& i_arg3, const T4& i_arg4)
		{
			m_container->Call(&Arguments<T1, T2, T3, T4>(i_arg1, i_arg2, i_arg3, i_arg4));
		}

	private:
		
		IContainer* m_container = nullptr;
	};

	class TestDelegate
	{
	public:

		void KeyButton(int key, int scancode, int action, int mode)
		{
			std::cout << "k " << key << " s " << scancode
				<< " a " << action << " m " << mode << std::endl;
		}

		void Mouse(double xpos, double ypos)
		{
			std::cout << "x " << xpos << " y " << ypos << std::endl;
		}
	};

}