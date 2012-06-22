// file      : xsd/cxx/tree/parser-source.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_TREE_PARSER_SOURCE_HXX
#define CXX_TREE_PARSER_SOURCE_HXX

#include <cxx/tree/elements.hxx>

namespace CXX
{
  namespace Tree
  {
    void
    generate_parser_source (Context&, size_t first, size_t last);
  }
}

#endif  // CXX_TREE_PARSER_SOURCE_HXX
