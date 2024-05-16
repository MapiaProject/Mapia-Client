#pragma once
#include <functional>
#include <iostream>
#include <utility>

template <int>
struct variadic_placeholder {};

namespace std {
	template <int N>
	struct is_placeholder<variadic_placeholder<N>>
		: integral_constant<int, N + 1>
	{
	};
}


template <typename Ret, typename Class, typename... Args, size_t... Is, typename... Args2>
auto bind(std::index_sequence<Is...>, Ret (Class::*fptr)(Args...), Args2&&... args) {
	return std::bind(fptr, std::forward<Args2>(args)..., variadic_placeholder<Is>{}...);
}

template <typename Ret, typename Class, typename... Args, typename... Args2>
auto bind(Ret (Class::*fptr)(Args...), Args2&&... args) {
	return bind(std::make_index_sequence<sizeof...(Args) - sizeof...(Args2) + 1>{}, fptr, std::forward<Args2>(args)...);
}
