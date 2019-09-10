#pragma once

#ifndef PHD_TEXT_CODE_POINT_HPP
#define PHD_TEXT_CODE_POINT_HPP

#include <phd/text/unicode_code_point.hpp>

namespace phd::text {

	template <typename _T>
	struct encoding_code_point {
		using type = typename _T::code_point;
	};

	template <typename _T>
	using encoding_code_point_t = typename encoding_code_point<_T>::type;

} // namespace phd::text

#endif // PHD_TEXT_CODE_POINT_HPP
