// Copyright (C) 2015 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

// { dg-options "-std=gnu++14" }

#include <set>
#include <testsuite_hooks.h>

struct Cmp
{
  typedef void is_transparent;

  bool operator()(int i, long l) const { return i < l; }
  bool operator()(long l, int i) const { return l < i; }
  bool operator()(int i, int j) const { ++count; return i < j; }

  static int count;
};

int Cmp::count = 0;

using test_type = std::set<int, Cmp>;

test_type x{ 1, 3, 5 };
const test_type& cx = x;

void
test01()
{
  Cmp::count = 0;

  auto it = x.find(1L);
  VERIFY( it != x.end() && *it == 1 );
  it = x.find(2L);
  VERIFY( it == x.end() );

  auto cit = cx.find(3L);
  VERIFY( cit != cx.end() && *cit == 3 );
  cit = cx.find(2L);
  VERIFY( cit == cx.end() );

  VERIFY( Cmp::count == 0);
}

void
test02()
{
  Cmp::count = 0;

  auto n = x.count(1L);
  VERIFY( n == 1 );
  n = x.count(2L);
  VERIFY( n == 0 );

  auto cn = cx.count(3L);
  VERIFY( cn == 1 );
  cn = cx.count(2L);
  VERIFY( cn == 0 );

  VERIFY( Cmp::count == 0);
}

void
test03()
{
  Cmp::count = 0;

  auto it = x.lower_bound(1L);
  VERIFY( it != x.end() && *it == 1 );
  it = x.lower_bound(2L);
  VERIFY( it != x.end() && *it == 3 );

  auto cit = cx.lower_bound(1L);
  VERIFY( cit != cx.end() && *cit == 1 );
  cit = cx.lower_bound(2L);
  VERIFY( cit != cx.end() && *cit == 3 );

  VERIFY( Cmp::count == 0);
}

void
test04()
{
  Cmp::count = 0;

  auto it = x.upper_bound(1L);
  VERIFY( it != x.end() && *it == 3 );
  it = x.upper_bound(5L);
  VERIFY( it == x.end() );

  auto cit = cx.upper_bound(1L);
  VERIFY( cit != cx.end() && *cit == 3 );
  cit = cx.upper_bound(5L);
  VERIFY( cit == cx.end() );

  VERIFY( Cmp::count == 0);
}

void
test05()
{
  Cmp::count = 0;

  auto it = x.equal_range(1L);
  VERIFY( it.first != it.second && *it.first == 1 );
  it = x.equal_range(2L);
  VERIFY( it.first == it.second && it.first != x.end() );

  auto cit = cx.equal_range(1L);
  VERIFY( cit.first != cit.second && *cit.first == 1 );
  cit = cx.equal_range(2L);
  VERIFY( cit.first == cit.second && cit.first != cx.end() );

  VERIFY( Cmp::count == 0);
}


int
main()
{
  test01();
  test02();
  test03();
  test04();
  test05();
}