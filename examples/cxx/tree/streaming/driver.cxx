// file      : examples/cxx/tree/streaming/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <iostream>
#include <fstream>

#include "records.hxx"

using std::cerr;
using std::endl;
using std::ios_base;

int
main ()
{
  try
  {
    std::ofstream ofs;
    ofs.exceptions (ios_base::badbit | ios_base::failbit);
    ofs.open ("out.xml");

    // We will need to create XML declaration as well as open and close
    // the root tag ourselves.
    //
    ofs << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl
        << "<records>" << endl;

    // For performance reasons, we would like to initialize/terminate
    // Xerces-C++ ourselves once instead of letting the serialization
    // function do it for every record.
    //
    xercesc::XMLPlatformUtils::Initialize ();

    xml_schema::namespace_infomap map;

    for (unsigned long i (0); i < 1000; ++i)
    {
      // Create the next record.
      //
      record r ("data");
      
      record_ (ofs,
               r,
               map,
               "UTF-8",
               xml_schema::flags::dont_initialize |
               xml_schema::flags::no_xml_declaration);
    }

    xercesc::XMLPlatformUtils::Terminate ();

    ofs << "</records>" << endl;
  }
  catch (const xml_schema::exception& e)
  {
    cerr << e << endl;
    return 1;
  }
  catch (const std::ios_base::failure&)
  {
    cerr << "io failure" << endl;
    return 1;
  }
}
