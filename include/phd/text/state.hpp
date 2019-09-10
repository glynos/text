#pragma once

#ifndef PHD_TEXT_STATE_HPP
#define PHD_TEXT_STATE_HPP

namespace phd::text {

	template <typename _T>
	struct encoding_state {
		using type = typename _T::state;
	};

	template <typename _T>
	using encoding_state_t = typename encoding_state<_T>::type;

} // namespace phd

#endif // PHD_TEXT_STATE_HPP
