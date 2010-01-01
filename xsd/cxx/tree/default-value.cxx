// file      : xsd/cxx/tree/default-value.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2010 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cxx/tree/default-value.hxx>

namespace CXX
{
  namespace Tree
  {
    namespace
    {
      Void
      normalize (String& s)
      {
        Size n (s.size ());

        for (Size i (0); i < n; ++i)
        {
          WideChar& c (s[i]);

          if (c == 0x0D || // carriage return
              c == 0x09 || // tab
              c == 0x0A)
            c = 0x20;
        }
      }

      Void
      collapse (String& s)
      {
        Size n (s.size ()), j (0);
        Boolean subs (false), trim (true);

        for (Size i (0); i < n; ++i)
        {
          WideChar c (s[i]);

          if (c == 0x20 || c == 0x09 || c == 0x0A)
            subs = true;
          else
          {
            if (subs)
            {
              subs = false;

              if (!trim)
                s[j++] = 0x20;
            }

            if (trim)
              trim = false;

            s[j++] = c;
          }
        }

        s.resize (j);
      }

      Void
      strip_zeros (String& s)
      {
        Size n (s.size ()), i (0);

        if (n > 0 && (s[i] == '-' || s[i] == '+'))
          i++;

        Size j (i);

        Boolean strip (true);

        for (; i < n; ++i)
        {
          WideChar c (s[i]);

          if (c == '0')
          {
            if (!strip)
              s[j++] = c;
          }
          else
          {
            s[j++] = c;

            if (strip)
              strip = false;
          }
        }

        if (strip && j < n)
          s[j++] = '0'; // There was nothing except zeros so add one back.

        s.resize (j);
      }

      Void
      make_float (String& s)
      {
        if (s.find ('.') == String::npos &&
            s.find ('e') == String::npos &&
            s.find ('E') == String::npos)
          s += L".0";
      }
    }

    //
    // IsLiteralValue
    //

    IsLiteralValue::
    IsLiteralValue (Boolean& r)
        : IsFundamentalType (r)
    {
      *this >> inherits_ >> *this;
    }

    Void IsLiteralValue::
    traverse (SemanticGraph::Complex& c)
    {
      inherits (c);
    }

    //
    // LiteralValue
    //

    LiteralValue::
    LiteralValue (Context& c)
        : Context (c)
    {
      *this >> inherits_ >> *this;
    }

    String LiteralValue::
    dispatch (SemanticGraph::Node& type, String const& value)
    {
      literal_.clear ();
      value_ = value;
      Traversal::NodeBase::dispatch (type);
      return literal_;
    }

    Void LiteralValue::
    traverse (SemanticGraph::Complex& c)
    {
      inherits (c);
    }

    // Boolean.
    //
    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::Boolean&)
    {
      collapse (value_);
      literal_ = (value_ == L"true" || value_ == L"1") ? L"true" : L"false";
    }

    // Integral types.
    //
    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::Byte&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_;
    }

    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::UnsignedByte&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_;
    }

    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::Short&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_;
    }

    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::UnsignedShort&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_;
    }

    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::Int&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_;
    }

    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::UnsignedInt&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_;
    }

    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::Long&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_;
      literal_ += L"LL";
    }

    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::UnsignedLong&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_;
      literal_ += L"ULL";
    }

    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::Integer&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_ + L"LL";
    }

    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::NonPositiveInteger&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_ + L"LL";
    }

    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::NonNegativeInteger&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_ + L"ULL";
    }

    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::PositiveInteger&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_ + L"ULL";
    }

    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::NegativeInteger&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_ + L"LL";
    }

    // Floats.
    //
    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::Float& t)
    {
      collapse (value_);

      if (value_ == L"NaN")
      {
        literal_ = L"::std::numeric_limits< " + fq_name (t) +
          L" >::quiet_NaN ()";
      }
      else if (value_ == L"INF")
      {
        literal_ = L"::std::numeric_limits< " + fq_name (t) +
          L" >::infinity ()";
      }
      else if (value_ == L"-INF")
      {
        literal_ = L"- ::std::numeric_limits< " + fq_name (t) +
          L" >::infinity ()";
      }
      else
      {
        strip_zeros (value_);
        make_float (value_);
        literal_ = value_ + L"F";
      }
    }

    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::Double& t)
    {
      collapse (value_);

      if (value_ == L"NaN")
      {
        literal_ = L"::std::numeric_limits< " + fq_name (t) +
          L" >::quiet_NaN ()";
      }
      else if (value_ == L"INF")
      {
        literal_ = L"::std::numeric_limits< " + fq_name (t) +
          L" >::infinity ()";
      }
      else if (value_ == L"-INF")
      {
        literal_ = L"- ::std::numeric_limits< " + fq_name (t) +
          L" >::infinity ()";
      }
      else
      {
        strip_zeros (value_);
        make_float (value_);
        literal_ = value_;
      }
    }

    Void LiteralValue::
    traverse (SemanticGraph::Fundamental::Decimal&)
    {
      collapse (value_);
      strip_zeros (value_);
      make_float (value_);
      literal_ = value_;
    }

    //
    // InitValue
    //

    IsSimpleInit::
    IsSimpleInit (Boolean& r)
        : r_ (r)
    {
      *this >> inherits_ >> *this;
    }

    Void IsSimpleInit::
    traverse (SemanticGraph::List&)
    {
      r_ = false;
    }

    Void IsSimpleInit::
    traverse (SemanticGraph::Complex& c)
    {
      inherits (c);
    }

    Void IsSimpleInit::
    traverse (SemanticGraph::Fundamental::NameTokens&)
    {
      r_ = false;
    }

    Void IsSimpleInit::
    traverse (SemanticGraph::Fundamental::IdRefs&)
    {
      r_ = false;
    }

    Void IsSimpleInit::
    traverse (SemanticGraph::Fundamental::Entities&)
    {
      r_ = false;
    }

    //
    // InitValue
    //

    InitValue::
    InitValue (Context& c)
        : Context (c), type_name_ (c), literal_value_ (c)
    {
    }

    Void InitValue::
    dispatch (SemanticGraph::Node& type, String const& value)
    {
      value_ = value;
      Traversal::NodeBase::dispatch (type);
    }

    Void InitValue::
    traverse (SemanticGraph::List& l)
    {
      collapse (value_);

      if (!value_)
        return;

      SemanticGraph::Type& t (l.argumented ().type ());

      String ov (value_);
      Size b (0);

      for (Size e (ov.find (' ')); ; e = ov.find (' ', b))
      {
        String v (ov, b, e != String::npos ? e - b : e);

        os << "{";
        type_name_.dispatch (t);
        os << " tmp (";

        String lit (literal_value_.dispatch (t, v));

        if (lit)
          os << lit;
        else
        {
          value_ = v;
          Traversal::NodeBase::dispatch (t);
        }

        os << ");"
           << "r.push_back (tmp);"
           << "}";

        if (e == String::npos)
          break;

        b = e + 1;
      }

      value_ = ov;
    }

    Void InitValue::
    traverse (SemanticGraph::Union&)
    {
      os << strlit (value_);
    }

    Void InitValue::
    traverse (SemanticGraph::Complex& c)
    {
      Traversal::NodeBase::dispatch (ultimate_base (c));
    }

    // anySimpleType.
    //
    Void InitValue::
    traverse (SemanticGraph::AnySimpleType&)
    {
    }

    // Strings.
    //
    Void InitValue::
    traverse (SemanticGraph::Fundamental::String&)
    {
      os << strlit (value_);
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::NormalizedString&)
    {
      normalize (value_);
      os << strlit (value_);
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::Token&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::NameToken&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::NameTokens&)
    {
      string_sequence_type (
        dynamic_cast<SemanticGraph::Type&> (
          xs_ns ().find ("NMTOKEN").first->named ()));
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::Name&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::NCName&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::Language&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    // Qualified name.
    //
    Void InitValue::
    traverse (SemanticGraph::Fundamental::QName&)
    {
    }

    // ID/IDREF.
    //
    Void InitValue::
    traverse (SemanticGraph::Fundamental::Id&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::IdRef&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::IdRefs&)
    {
      string_sequence_type (
        dynamic_cast<SemanticGraph::Type&> (
          xs_ns ().find ("IDREF").first->named ()));
    }

    // URI.
    //
    Void InitValue::
    traverse (SemanticGraph::Fundamental::AnyURI&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    // Binary.
    //
    Void InitValue::
    traverse (SemanticGraph::Fundamental::Base64Binary&)
    {
      collapse (value_);

      if (value_)
        os << "#error base64Binary default values are not yet supported"
           << endl;
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::HexBinary&)
    {
      collapse (value_);

      if (value_)
        os << "#error hexBinary default values are not yet supported"
           << endl;
    }


    // Date/time.
    //
    Void InitValue::
    traverse (SemanticGraph::Fundamental::Date& t)
    {
      // date := [-]CCYY[N]*-MM-DD[Z|(+|-)HH:MM]
      //
      collapse (value_);

      Size b (0);
      Size e (value_.find ('-', value_[0] == '-' ? 5 : 4));
      String year (value_, 0, e);

      b = e + 1;
      String month (value_, b, 2);

      b += 3;
      String day (value_, b, 2);

      strip_zeros (year);
      strip_zeros (month);
      strip_zeros (day);

      os << fq_name (t) << " (" << year << ", " << month << ", " << day;
      time_zone (b + 2);
      os << ")";
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::DateTime& t)
    {
      // date_time := [-]CCYY[N]*-MM-DDTHH:MM:SS[.S+][Z|(+|-)HH:MM]
      //
      collapse (value_);

      Size b (0);
      Size e (value_.find ('-', value_[0] == '-' ? 5 : 4));
      String year (value_, 0, e);
      b = e + 1;

      String month (value_, b, 2);
      b += 3;

      String day (value_, b, 2);
      b += 3;

      String hours (value_, b, 2);
      b += 3;

      String minutes (value_, b, 2);
      b += 3;

      e = b + 2;
      for (; e < value_.size (); ++e)
      {
        WideChar c (value_[e]);

        if (c == 'Z' || c == '+' || c == '-')
          break;
      }

      String seconds (value_, b, e - b);

      strip_zeros (year);
      strip_zeros (month);
      strip_zeros (day);
      strip_zeros (hours);
      strip_zeros (minutes);
      strip_zeros (seconds);
      make_float (seconds);

      os << fq_name (t) << " ("
         << year << ", " << month << ", " << day << ", "
         << hours << ", " << minutes << ", " << seconds;
      time_zone (e);
      os << ")";
    }

    namespace
    {
      Size
      find_delim (String const& s, Size pos)
      {
        for (; pos < s.size (); ++pos)
        {
          WideChar c (s[pos]);

          if (c == 'Y' || c == 'D' || c == 'M' || c == 'H' ||
              c == 'M' || c == 'S' || c == 'T')
            break;
        }

        return pos;
      }
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::Duration& t)
    {
      // duration := [-]P[nY][nM][nD][TnHnMn[.n+]S]
      //
      collapse (value_);

      Size b (1), e, n (value_.size ());

      os << fq_name (t) << " (";

      if (value_[0] == '-')
      {
        os << "true, ";
        b++;
      }
      else
        os << "false, ";

      e = find_delim (value_, b);

      if (e < n && value_[e] == 'Y')
      {
        String v (value_, b, e - b);
        strip_zeros (v);
        os << v << ", ";

        b = e + 1;
        e = find_delim (value_, b);
      }
      else
        os << "0, ";

      if (e < n && value_[e] == 'M')
      {
        String v (value_, b, e - b);
        strip_zeros (v);
        os << v << ", ";

        b = e + 1;
        e = find_delim (value_, b);
      }
      else
        os << "0, ";

      if (e < n && value_[e] == 'D')
      {
        String v (value_, b, e - b);
        strip_zeros (v);
        os << v << ", ";

        b = e + 1;
        e = find_delim (value_, b);
      }
      else
        os << "0, ";

      if (e < n && value_[e] == 'T')
      {
        b = e + 1;
        e = find_delim (value_, b);
      }

      if (e < n && value_[e] == 'H')
      {
        String v (value_, b, e - b);
        strip_zeros (v);
        os << v << ", ";

        b = e + 1;
        e = find_delim (value_, b);
      }
      else
        os << "0, ";

      if (e < n && value_[e] == 'M')
      {
        String v (value_, b, e - b);
        strip_zeros (v);
        os << v << ", ";

        b = e + 1;
        e = find_delim (value_, b);
      }
      else
        os << "0, ";

      if (e < n && value_[e] == 'S')
      {
        String v (value_, b, e - b);
        strip_zeros (v);
        make_float (v);
        os << v;

        b = e + 1;
        e = find_delim (value_, b);
      }
      else
        os << "0.0";

      os << ")";
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::Day& t)
    {
      // gday := ---DD[Z|(+|-)HH:MM]
      //
      collapse (value_);

      String day (value_, 3, 2);
      strip_zeros (day);

      os << fq_name (t) << " (" << day;
      time_zone (5);
      os << ")";
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::Month& t)
    {
      // gmonth := --MM[Z|(+|-)HH:MM]
      //
      collapse (value_);

      String month (value_, 2, 2);
      strip_zeros (month);

      os << fq_name (t) << " (" << month;
      time_zone (4);
      os << ")";
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::MonthDay& t)
    {
      // gmonth_day := --MM-DD[Z|(+|-)HH:MM]
      //
      collapse (value_);

      String month (value_, 2, 2);
      String day (value_, 5, 2);

      strip_zeros (month);
      strip_zeros (day);

      os << fq_name (t) << " (" << month << ", " << day;
      time_zone (7);
      os << ")";
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::Year& t)
    {
      // gyear := [-]CCYY[N]*[Z|(+|-)HH:MM]
      //
      collapse (value_);

      Size pos (value_[0] == '-' ? 5 : 4);
      for (; pos < value_.size (); ++pos)
      {
        WideChar c (value_[pos]);

        if (c == 'Z' || c == '+' || c == '-')
          break;
      }

      String year (value_, 0, pos);
      strip_zeros (year);

      os << fq_name (t) << " (" << year;
      time_zone (pos);
      os << ")";
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::YearMonth& t)
    {
      // gyear_month := [-]CCYY[N]*-MM[Z|(+|-)HH:MM]
      //
      collapse (value_);

      Size pos (value_.find ('-', value_[0] == '-' ? 5 : 4));

      String year (value_, 0, pos);
      String month (value_, pos + 1, 2);

      strip_zeros (year);
      strip_zeros (month);

      os << fq_name (t) << " (" << year << ", " << month;
      time_zone (pos + 3);
      os << ")";
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::Time& t)
    {
      // time := HH:MM:SS[.S+][Z|(+|-)HH:MM]
      //
      collapse (value_);

      String hours (value_, 0, 2);
      String minutes (value_, 3, 2);

      Size e (8);
      for (; e < value_.size (); ++e)
      {
        WideChar c (value_[e]);

        if (c == 'Z' || c == '+' || c == '-')
          break;
      }

      String seconds (value_, 6, e - 6);

      strip_zeros (hours);
      strip_zeros (minutes);
      strip_zeros (seconds);
      make_float (seconds);

      os << fq_name (t) << " (" << hours << ", " << minutes << ", " << seconds;
      time_zone (e);
      os << ")";
    }

    Void InitValue::
    time_zone (Size pos)
    {
      // time_zone := Z|(+|-)HH:MM
      //
      if (pos < value_.size ())
      {
        String h, m;

        if (value_[pos] == 'Z')
        {
          h = "0";
          m = "0";
        }
        else
        {
          if (value_[pos] == '-')
          {
            h = "-";
            m = "-";
          }

          h.append (value_, pos + 1, 2);
          m.append (value_, pos + 4, 2);

          strip_zeros (h);
          strip_zeros (m);
        }

        os << ", " << h << ", " << m;
      }
    }

    // Entity.
    //
    Void InitValue::
    traverse (SemanticGraph::Fundamental::Entity&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    Void InitValue::
    traverse (SemanticGraph::Fundamental::Entities&)
    {
      string_sequence_type (
        dynamic_cast<SemanticGraph::Type&> (
          xs_ns ().find ("ENTITY").first->named ()));
    }

    Void InitValue::
    string_sequence_type (SemanticGraph::Type& t)
    {
      collapse (value_);

      if (!value_)
        return;

      Size b (0);

      for (Size e (value_.find (' ')); ; e = value_.find (' ', b))
      {
        String v (value_, b, e != String::npos ? e - b : e);

        os << "{";
        type_name_.dispatch (t);
        os << " tmp (" << strlit (v) << ");"
           << "r.push_back (tmp);"
           << "}";

        if (e == String::npos)
          break;

        b = e + 1;
      }
    }
  }
}
