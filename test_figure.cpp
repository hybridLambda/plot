/*
 * hybrid-Lambda is used to simulate gene trees given species network under
 * coalescent process.
 *
 * Copyright (C) 2010 -- 2014 Sha (Joe) Zhu
 *
 * This file is part of hybrid-Lambda.
 *
 * hybrid-Lambda is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "figure.hpp"
#pragma GCC diagnostic ignored "-Wwrite-strings"

class TestFigure : public CppUnit::TestCase {

    CPPUNIT_TEST_SUITE( TestFigure );

    CPPUNIT_TEST( good_CMD );
    CPPUNIT_TEST( bad_CMD );

    CPPUNIT_TEST_SUITE_END();

  private:

    void good_CMD() {
        char* argv1[] = { "./plot", "-graph", "trees/7_tax_sp_nt1_para", "-dotF", "blah", "-branch", "-label" };
        CPPUNIT_ASSERT_NO_THROW ( Figure( 6, argv1 ) );
        CPPUNIT_ASSERT_NO_THROW ( Figure( 5, argv1 ) );

        char* argv2[] = { "./plot", "-graph", "trees/7_tax_sp_nt1_para", "-dotF", "blah", "-label", "-branch" };
        CPPUNIT_ASSERT_NO_THROW ( Figure( 6, argv1 ) );
        CPPUNIT_ASSERT_NO_THROW ( Figure( 5, argv1 ) );

    }

    void bad_CMD(){
        char* argv1[] = { "./plot", "-graph", "trees/7_tax_sp_nt1_para", "-dotF", "blah", "-branch", "-label" };
        CPPUNIT_ASSERT_THROW ( Figure( 7, argv1 ) , TooManyOption ); // too many options
        CPPUNIT_ASSERT_THROW ( Figure( 4, argv1 ) , NotEnoughArg ); // missing file name for -dotF

        char* argv2[] = { "./plot", "-graph", "(A:1,B:2);", "as" };
        CPPUNIT_ASSERT_THROW ( PlotApp( 4, argv2 ) , UnknowArg ); // missing file name for -dotF
        CPPUNIT_ASSERT_THROW ( Figure( 4, argv2 ) , MethodUndefined ); // missing file name for -dotF

    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestFigure );
