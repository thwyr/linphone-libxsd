// file      : xsd/cxx/tree/validator.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_TREE_VALIDATOR_HXX
#define CXX_TREE_VALIDATOR_HXX

#include <cxx/tree/elements.hxx>
#include <cxx/tree/options.hxx>

#include <xsd.hxx>

namespace CXX
{
  namespace Tree
  {
    class Validator
    {
    public:
      Validator (); // Dummy ctor, helps with long symbols on HP-UX.

      Boolean
      validate (options const&,
                SemanticGraph::Schema&,
                SemanticGraph::Path const& tu,
                const WarningSet& disabled_warnings,
                Counts const& counts);
    };
  }
}

#endif  // CXX_TREE_VALIDATOR_HXX
