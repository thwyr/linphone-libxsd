// file      : xsd/cxx/tree/counter.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_TREE_COUNTER_HXX
#define CXX_TREE_COUNTER_HXX

#include <cxx/tree/elements.hxx>
#include <cxx/tree/options.hxx>

namespace CXX
{
  namespace Tree
  {
    class Counter
    {
    public:
      Counts
      count (options const&,
             SemanticGraph::Schema&,
             SemanticGraph::Path const&);
    };
  }
}

#endif // CXX_TREE_COUNTER_HXX
