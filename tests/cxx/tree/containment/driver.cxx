// file      : tests/cxx/tree/test-template/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2009 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test tree node containment.
//

#include <memory> // std::auto_ptr

#include "test.hxx"

using namespace std;
using namespace test;

int
main ()
{
  // Change of a container in a sub-tree without ID.
  //
  {
    auto_ptr<inner> i (new inner ());
    i->ref ("foo");

    outer o;
    o.i (i);
    o.ref ("foo");

    assert (o.i ()->ref ()->get () == 0);
    assert (o.ref ()->get () == 0);
  }

  // Change of container in a sub-tree with ID inside.
  //
  {
    auto_ptr<inner> i (new inner ());
    inner* p (i.get ());
    i->id ("foo");
    i->ref ("foo");
    assert (i->ref ()->get () == p);

    outer o;
    o.i (i);
    o.ref ("foo");

    assert (o.i ()->ref ()->get () == p);
    assert (o.ref ()->get () == p);
  }

  // Change of a container in ID.
  //
  {
    auto_ptr<xml_schema::id> id (new xml_schema::id ("foo"));

    inner i;
    i.id (id);
    i.ref ("foo");
    assert (i.ref ()->get () == &i);
  }

  // Change of a container in a type derived from ID with ID inside.
  //
  {
    auto_ptr<id_ex> id (new id_ex ("foo"));
    id_ex* p (id.get ());
    id->id ("bar");

    inner i;
    i.id_ex (id);

    i.ref ("foo");
    assert (i.ref ()->get () == &i);

    i.ref ("bar");
    assert (i.ref ()->get () == p);
  }
}
