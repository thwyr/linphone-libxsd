// file      : xsd/cxx/tree/elements.ixx
// copyright : Copyright (c) 2005-2014 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsd
{
  namespace cxx
  {
    namespace tree
    {
      // content_order_type
      //

      inline bool
      operator== (const content_order& x, const content_order& y)
      {
        return x.id == y.id && x.index == y.index;
      }

      inline bool
      operator!= (const content_order& x, const content_order& y)
      {
        return !(x == y);
      }

      inline bool
      operator< (const content_order& x, const content_order& y)
      {
        return x.id < y.id || (x.id == y.id && x.index < y.index);
      }

      // type
      //

      inline _type::
      _type ()
          : container_ (0)
      {
      }

      template <typename C>
      inline _type::
      _type (const C*)
          : container_ (0)
      {
      }

      // simple_type
      //

      template <typename B>
      inline simple_type<B>::
      simple_type ()
      {
      }

      template <typename B>
      template <typename C>
      inline simple_type<B>::
      simple_type (const C*)
      {
      }
    }
  }
}
