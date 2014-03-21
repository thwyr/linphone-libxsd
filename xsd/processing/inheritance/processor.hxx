// file      : processing/inheritance/processor.hxx
// copyright : Copyright (c) 2006-2014 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef PROCESSING_INHERITANCE_PROCESSOR_HXX
#define PROCESSING_INHERITANCE_PROCESSOR_HXX

#include <xsd-frontend/semantic-graph/elements.hxx> // Path
#include <xsd-frontend/semantic-graph/schema.hxx>

#include <types.hxx>

namespace Processing
{
  namespace Inheritance
  {
    class Processor
    {
    public:
      struct Failed {};

      void
      process (XSDFrontend::SemanticGraph::Schema&,
               XSDFrontend::SemanticGraph::Path const& file);
    };
  }
}

#endif // PROCESSING_INHERITANCE_PROCESSOR_HXX
