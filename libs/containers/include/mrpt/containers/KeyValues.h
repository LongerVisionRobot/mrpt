/* +------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)            |
   |                          https://www.mrpt.org/                         |
   |                                                                        |
   | Copyright (c) 2005-2020, Individual contributors, see AUTHORS file     |
   | See: https://www.mrpt.org/Authors - All rights reserved.               |
   | Released under BSD License. See: https://www.mrpt.org/License          |
   +------------------------------------------------------------------------+ */
#pragma once

#include <mrpt/config.h>
#include <mrpt/core/common.h>  // Disable MSVC warning 4251 in this class

#include <algorithm>  // std::max
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

namespace mrpt::containers
{
/** An extension of std::map with print, const [] operator, and default values.
 *
 *  A default list of parameters can be passed to the constructor:
 *
 *  \code
 *    KeyValues<double> p({"par1",2.0},{"par2",-4.5});
 *  \endcode
 *
 * \ingroup mrpt_containers_grp
 * \sa the example in MRPT/samples/params-by-name
 */
template <typename T>
struct KeyValues
{
	using BASE = std::map<std::string, T>;
	BASE base;
	using iterator = typename BASE::iterator;
	using const_iterator = typename BASE::const_iterator;

	/** Default constructor (initializes empty) */
	KeyValues() = default;

	/** Constructor with a list of initial values (see the description and use
	 * example in mrpt::system::TParameters) */
	KeyValues(std::initializer_list<typename BASE::value_type> init)
		: base(init)
	{
	}
	inline bool has(const std::string& s) const
	{
		return base.end() != base.find(s);
	}
	/** A const version of the [] operator, for usage as read-only.
	 * \exception std::logic_error On parameter not present. Please, check
	 * existence with "has" before reading.
	 */
	inline T operator[](const std::string& s) const
	{
		using namespace std::string_literals;
		auto it = base.find(s);
		if (base.end() == it)
			throw std::logic_error(
				("Parameter '"s + s + "' is not present."s).c_str());
		return it->second;
	}
	/** A const version of the [] operator and with a default value in case the
	 * parameter is not set (for usage as read-only).
	 */
	template <typename RET>
	inline RET getWithDefaultVal(
		const std::string& s, const RET& defaultVal) const
	{
		auto it = base.find(s);
		if (base.end() == it)
			return defaultVal;
		else
			return static_cast<RET>(it->second);
	}
	/** The write (non-const) version of the [] operator. */
	inline T& operator[](const std::string& s) { return base[s]; }
	/** Dumps to console the output from getAsString() */
	inline void dumpToConsole() const
	{
		::fputs(getAsString().c_str(), stdout);
	}

	/** Returns a multi-line string representation of the parameters like : 'nam
	 * = val\nnam2   = val2...' */
	inline std::string getAsString() const
	{
		std::string s;
		getAsString(s);
		return s;
	}

	/** Returns a multi-line string representation of the parameters like : 'nam
	 * = val\nnam2   = val2...' */
	void getAsString(std::string& s) const
	{
		size_t maxStrLen = 10;
		for (const auto& e : *this)
			maxStrLen = std::max(maxStrLen, e.first.size());
		maxStrLen++;
		std::stringstream str;
		for (const auto& e : *this)
			str << e.first << std::string(maxStrLen - e.first.size(), ' ')
				<< " = " << e.second << std::endl;
		s = str.str();
	}

	inline void clear() { base.clear(); }
	inline bool empty() const { return base.empty(); }
	iterator find(const std::string& key) { return base.find(key); }
	const_iterator find(const std::string& key) const { return base.find(key); }
	iterator begin() noexcept { return base.begin(); }
	const_iterator begin() const noexcept { return base.begin(); }
	iterator end() noexcept { return base.end(); }
	const_iterator end() const noexcept { return base.end(); }
};

}  // namespace mrpt::containers
