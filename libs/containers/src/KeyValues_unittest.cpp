/* +------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)            |
   |                          https://www.mrpt.org/                         |
   |                                                                        |
   | Copyright (c) 2005-2020, Individual contributors, see AUTHORS file     |
   | See: https://www.mrpt.org/Authors - All rights reserved.               |
   | Released under BSD License. See: https://www.mrpt.org/License          |
   +------------------------------------------------------------------------+ */

#include <gtest/gtest.h>
#include <mrpt/config.h>
#include <mrpt/containers/KeyValues.h>

#include <algorithm>  // count()

TEST(KeyValues, emptyCtor)
{
	mrpt::containers::KeyValues<double> kv;
	EXPECT_TRUE(kv.empty());
}

TEST(KeyValues, SettersGetters)
{
	mrpt::containers::KeyValues<double> kv;
	kv["foo"] = 1.0;
	kv["bar"] = 2.0;

	EXPECT_EQ(kv["foo"], 1.0);
	EXPECT_EQ(kv["bar"], 2.0);
	EXPECT_EQ(kv.getWithDefaultVal("chi", .0), 0.0);
}
