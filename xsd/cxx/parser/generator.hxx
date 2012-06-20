// file      : xsd/cxx/parser/generator.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_PARSER_GENERATOR_HXX
#define CXX_PARSER_GENERATOR_HXX

#include <cult/types.hxx>

#include <cult/containers/vector.hxx>

#include <xsd-frontend/semantic-graph/elements.hxx> // Path
#include <xsd-frontend/semantic-graph/schema.hxx>

#include <xsd.hxx>

#include <cxx/literal-map.hxx>
#include <cxx/parser/options.hxx>

namespace CXX
{
  namespace Parser
  {
    using namespace Cult::Types;

    class Generator
    {
    public:
      static Void
      usage ();

      struct Failed {};

      static UnsignedLong
      generate (options const&,
                XSDFrontend::SemanticGraph::Schema&,
                XSDFrontend::SemanticGraph::Path const& file,
                Boolean file_per_type,
                StringLiteralMap const&,
                Boolean gen_driver,
                const WarningSet& disabled_warnings,
                FileList& file_list,
                AutoUnlinks& unlinks);

    private:
      Generator ();
    };
  }
}

#endif // CXX_PARSER_GENERATOR_HXX
