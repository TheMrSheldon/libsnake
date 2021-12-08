#pragma once

#include <algorithm>

namespace utl {
	template <class _Container, class T>
	_NODISCARD inline bool contains(const _Container& cont, const T& val) {
		return std::find(std::begin(cont), std::end(cont), val) != std::end(cont);
	}
}