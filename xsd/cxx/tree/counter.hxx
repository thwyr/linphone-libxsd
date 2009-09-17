// file      : xsd/cxx/tree/counter.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2009 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_TREE_COUNTER_HXX
#define CXX_TREE_COUNTER_HXX

#include <cxx/tree/elements.hxx>
#include <cxx/tree/cli.hxx>

namespace CXX
{
  namespace Tree
  {
    class Counter
    {
    public:
      Counter (); // Dummy ctor, helps with long symbols on HP-UX.

      Counts
      count (CLI::Options const& options,
             SemanticGraph::Schema&);
    };
  }
}

#endif // CXX_TREE_COUNTER_HXX
