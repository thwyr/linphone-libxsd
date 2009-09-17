// file      : xsd/cxx/tree/parser-header.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2009 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_TREE_PARSER_HEADER_HXX
#define CXX_TREE_PARSER_HEADER_HXX

#include <xsd-frontend/semantic-graph/schema.hxx>

#include <cxx/tree/elements.hxx>


namespace CXX
{
  namespace Tree
  {
    Void
    generate_parser_header (Context&);
  }
}

#endif  // CXX_TREE_PARSER_HEADER_HXX
