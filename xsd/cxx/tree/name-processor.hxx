// file      : xsd/cxx/tree/name-processor.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_TREE_NAME_PROCESSOR_HXX
#define CXX_TREE_NAME_PROCESSOR_HXX

#include <cxx/tree/elements.hxx>
#include <cxx/tree/options.hxx>

namespace CXX
{
  namespace Tree
  {
    using namespace Cult::Types;

    class NameProcessor
    {
    public:
      NameProcessor (); // Dummy ctor, helps with long symbols on HP-UX.

      Boolean
      process (options const&,
               XSDFrontend::SemanticGraph::Schema&,
               XSDFrontend::SemanticGraph::Path const& file,
               StringLiteralMap const&);
    };
  }
}

#endif // CXX_TREE_NAME_PROCESSOR_HXX
