// file      : xsd/cxx/parser/validator.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_PARSER_VALIDATOR_HXX
#define CXX_PARSER_VALIDATOR_HXX

#include <xsd.hxx>
#include <types.hxx>

#include <cxx/parser/elements.hxx>
#include <cxx/parser/options.hxx>

namespace CXX
{
  namespace Parser
  {
    class Validator
    {
    public:
      Validator (); // Dummy ctor, helps with long symbols on HP-UX.

      bool
      validate (options const&,
                SemanticGraph::Schema&,
                SemanticGraph::Path const& tu,
                bool gen_driver,
                const WarningSet& disabled_warnings);
    };
  }
}

#endif  // CXX_PARSER_VALIDATOR_HXX
