#pragma once

#include <cassert>

#include <utility>
#include <tuple>
#include <vector>

namespace breakout
{
	template<typename... Args>
	class IDelegate
	{
	public:
		virtual void Execute(Args&&... args) = 0;
	};

	template<typename TLambda, typename... Args>
	class LambdaDelegate : public IDelegate<Args...>
	{
	public:
		explicit LambdaDelegate(TLambda&& lambda)
			: m_lambda(std::forward<TLambda>(lambda))
		{};

		void Execute(Args&&... args) override
		{
			(m_lambda)(std::forward<Args>(args)...);
		}

	private:

		TLambda m_lambda;
	};

	template<typename Object, typename... Args>
	class ObjMethodDelegate : public IDelegate<Args...>
	{
		using DelegateFunction = void(Object::*)(Args...);

	public:
		explicit ObjMethodDelegate(Object* i_class, DelegateFunction i_method)
			: m_class(i_class),
			  m_method(i_method)
		{}


		void Execute(Args&&... args) override
		{
			(m_class->*m_method)(std::forward<Args>(args)...);
		}

	private:

		Object* m_class;
		DelegateFunction m_method;
	};

	template<typename... Args>
	class MulticastDelegate
	{
	public:

		using IDelegateT = IDelegate<Args...>;

		template<typename Object, typename... Args2>
		using DelegateFunction = void(Object::*)(Args...);

		template<typename LambdaType, typename... Args2>
		inline void BindLambda(LambdaType&& lambda, Args2&&... args)
		{
			m_containers.push_back(CreateLambda<LambdaType>(std::forward<LambdaType>(lambda)));
		}

		template<typename T, typename... Args2>
		inline void BindObject(T* i_class, DelegateFunction<T, Args2...> i_method)
		{
			m_containers.push_back(CreateObjMethod<T>(i_class, i_method));
		}

		MulticastDelegate() = default;

		~MulticastDelegate()
		{
			Unbind();
		}

		void Unbind()
		{
			for (auto& container : m_containers)
			{
				delete container;
			}
		}

		void Broadcast(Args... args) const
		{
			for (auto& container: m_containers)
			{
				container->Execute(std::forward<Args>(args)...);
			}
		}

	private:

		template<typename TLambda, typename... Args2>
		static IDelegateT* CreateLambda(TLambda&& lambda)
		{
			IDelegateT* new_lambda = new LambdaDelegate<TLambda, Args...>(std::forward<TLambda>(lambda));
			return new_lambda;
		}

		template<typename T, typename... Args2>
		static IDelegateT* CreateObjMethod(T* i_class, DelegateFunction<T, Args2...> i_method)
		{
			IDelegateT* new_method = new ObjMethodDelegate<T, Args...>(i_class, i_method);
			return new_method;
		}

		std::vector<IDelegateT*> m_containers = {};
	};
}