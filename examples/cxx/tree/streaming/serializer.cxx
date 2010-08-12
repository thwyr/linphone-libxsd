// file      : examples/cxx/tree/streaming/serializer.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <xercesc/util/XMLUni.hpp>

#include <xercesc/dom/DOM.hpp>

#include <xsd/cxx/xml/string.hxx>
#include <xsd/cxx/xml/dom/bits/error-handler-proxy.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

#include "serializer.hxx"

using namespace std;
using namespace xercesc;

namespace xml = xsd::cxx::xml;
namespace tree = xsd::cxx::tree;

class serializer_impl
{
public:
  typedef serializer::namespace_infomap namespace_infomap;

  serializer_impl ();

  void
  start (ostream& os, const string& encoding);

  DOMElement*
  create (const string& name, const namespace_infomap&);

  DOMElement*
  create (const string& ns, const string& qname, const namespace_infomap&);

  void
  serialize (DOMElement& e);

private:
  void
  add_namespaces (xercesc::DOMElement*, const namespace_infomap&);

private:
  // Serializer.
  //
#if _XERCES_VERSION >= 30000
  xml::dom::auto_ptr<DOMLSOutput> out_;
  xml::dom::auto_ptr<DOMLSSerializer> serializer_;
#else
  xml::dom::auto_ptr<DOMWriter> serializer_;
#endif

  auto_ptr<xml::dom::ostream_format_target> oft_;

  tree::error_handler<char> error_handler_;
  xml::dom::bits::error_handler_proxy<char> error_proxy_;

  // DOM document that we use to create the elements.
  //
  DOMImplementation& dom_impl_;
  xml::dom::auto_ptr<DOMDocument> doc_;
};

const XMLCh ls[] = {chLatin_L, chLatin_S, chNull};

serializer_impl::
serializer_impl ()
    : error_proxy_ (error_handler_),
      dom_impl_ (*DOMImplementationRegistry::getDOMImplementation (ls)),
      doc_ (dom_impl_.createDocument ())
{
#if _XERCES_VERSION >= 30000
  serializer_.reset (dom_impl_.createLSSerializer ());
  DOMConfiguration* conf (serializer_->getDomConfig ());

  conf->setParameter (XMLUni::fgDOMErrorHandler, &error_proxy_);
  conf->setParameter (XMLUni::fgDOMWRTDiscardDefaultContent, true);
  conf->setParameter (XMLUni::fgDOMWRTFormatPrettyPrint, true);
  conf->setParameter (XMLUni::fgDOMXMLDeclaration, false);
#else
  serializer_.reset (dom_impl_.createDOMWriter ());

  serializer_->setErrorHandler (&error_proxy_);
  serializer_->setFeature (XMLUni::fgDOMWRTDiscardDefaultContent, true);
  serializer_->setFeature (XMLUni::fgDOMWRTFormatPrettyPrint, true);
  serializer_->setFeature (XMLUni::fgDOMXMLDeclaration, false);
#endif
}

void serializer_impl::
start (ostream& os, const string& encoding)
{
  error_handler_.reset ();
  oft_.reset (new xml::dom::ostream_format_target (os));

#if _XERCES_VERSION >= 30000
  out_.reset (dom_impl_.createLSOutput ());
  out_->setEncoding (xml::string (encoding).c_str ());
  out_->setByteStream (oft_.get ());
#else
  serializer_->setEncoding (xml::string (encoding).c_str ());
#endif
}

DOMElement* serializer_impl::
create (const string& name, const namespace_infomap& map)
{
  DOMElement* r (doc_->createElement (xml::string (name).c_str ()));

  if (!map.empty ())
    add_namespaces (r, map);

  return r;
}

DOMElement* serializer_impl::
create (const string& ns, const string& qname, const namespace_infomap& map)
{
  DOMElement* r (
    doc_->createElementNS (
      xml::string (ns).c_str (), xml::string (qname).c_str ()));

  if (!map.empty ())
    add_namespaces (r, map);

  return r;
}

void serializer_impl::
add_namespaces (DOMElement* e, const namespace_infomap& map)
{
  for (namespace_infomap::const_iterator i (map.begin ()), end (map.end ());
       i != end; ++i)
  {
    if (i->first.empty ())
    {
      // Empty prefix.
      //
      if (!i->second.name.empty ())
        e->setAttributeNS (
          XMLUni::fgXMLNSURIName,
          xml::string ("xmlns").c_str (),
          xml::string (i->second.name).c_str ());
    }
    else
    {
      e->setAttributeNS (
        XMLUni::fgXMLNSURIName,
        xml::string ("xmlns:" + i->first).c_str (),
        xml::string (i->second.name).c_str ());
    }
  }
}

void serializer_impl::
serialize (DOMElement& e)
{
#if _XERCES_VERSION >= 30000
  serializer_->write (&e, out_.get ());
#else
  serializer_->writeNode (oft_.get (), e);
#endif

  error_handler_.throw_if_failed<tree::serialization<char> > ();
}

//
// serializer
//

serializer::
~serializer ()
{
}

serializer::
serializer ()
    : impl_ (new serializer_impl)
{
}

void serializer::
start (ostream& os, const string& encoding)
{
  impl_->start (os, encoding);
}

DOMElement* serializer::
create (const string& name, const namespace_infomap& map)
{
  return impl_->create (name, map);
}

DOMElement* serializer::
create (const string& ns, const string& qname, const namespace_infomap& map)
{
  return impl_->create (ns, qname, map);
}

void serializer::
serialize (DOMElement& e)
{
  impl_->serialize (e);
}
