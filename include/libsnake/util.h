#pragma once

#include <algorithm>

namespace utl {
	/**
	 * @brief Checks if \p val is contained within the container \p cont.
	 * 
	 * @tparam _Container The container-type.
	 * @tparam T The value-type.
	 * @param cont The container in which to search for \p val.
	 * @param val The value to search for in the \p cont if it is contained.
	 * @return true iff \p val is contained in \p cont.
	 */
	template <class _Container, class T>
	constexpr inline bool contains(const _Container& cont, const T& val) {
		return std::find(std::begin(cont), std::end(cont), val) != std::end(cont);
	}
}