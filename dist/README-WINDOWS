This package contains precompiled binaries of CodeSynthesis XSD, a
W3C XML Schema to C++ Data Binding compiler, built for Microsoft
Windows. For more information about XSD visit

http://www.codesynthesis.com/products/xsd/

This README file describes how to start using XSD in the Microsoft
Windows environment with Microsoft Visual C++ 7.1 (.NET 2003),
Microsoft Visual C++ 8 (Visual Studio 2005), and Microsoft Visual
C++ 9 (Visual Studio 2008).


Prerequisites
-------------

The XSD runtime library and the generated code depend on the Xerces-C++
XML parser which you can obtain from http://xerces.apache.org/xerces-c/.
You can also download precompiled Xerces-C++ libraries for Windows from
http://xerces.apache.org/xerces-c/download.cgi


Environment
-----------

Before you can start building examples or your applications that use XSD
you need to set include, library and executable search paths in the Visual
C++ IDE and the System Environment.

1. Setting up Xerces-C++

  First you need to set up Xerces-C++ include and library search paths.
  If you already have Xerces-C++ set up in your development environment,
  you can skip to the next step. Here we assume that your Xerces-C++ path
  is C:\projects\xerces-c-x.y.z. If you have Xerces-C++ in a different
  place you will need to adjust the paths below accordingly.


  a) In the Visual C++ IDE, select "Tools"/"Options"/"Projects"/"VC++
     Directories".

     Then, in the "Show directories for" field, select "Include files" and
     create a new entry with the value "C:\projects\xerces-c-x.y.z\include".

     After that, in the "Show directories for" field, select "Library files"
     and create a new entry with the value "C:\projects\xerces-c-x.y.z\lib".


  b) In the Control Panel, choose "System" and select the "Advanced" tab.
     Click on the "Environment Variables" button. In the "System Variables"
     list, select "Path" and add (via "Edit" button) the
     ";C:\projects\xerces-c-x.y.z\bin" path at the end.


2. Setting up XSD

  Now you need to set up XSD executable and include search paths. Here
  we assume that your XSD path is C:\projects\xsd-x.y.z. If you have XSD
  in a different place you will need to adjust the paths below accordingly.


  a) In the Visual C++ IDE, select "Tools"/"Options"/"Projects"/"VC++
     Directories".

     Then, in the "Show directories for" field, select "Include files" and
     create a new entry with the value "C:\projects\xsd-x.y.z\libxsd".

     After that, in the "Show directories for" field, select "Executable
     files" and create a new entry with the value "C:\projects\xsd-x.y.z\bin".
     Make sure it is the first line in the list of directories (use the
     "Up" button to move the new entry up, if necessary).


3. Restart the Visual C++ IDE. This is necessary for the new value of the
   "Path" environment variable to take effect.


Building Examples
-----------------

Now you are ready to build examples. Simply open the solution file
found in the examples/cxx/tree and examples/cxx/parser directories.

Some of the examples depend on additional third-party libraries or
show a specific feature of XSD and are not included in the solutions
above. They come with their individual solution files:

examples/cxx/tree/custom           - examples of type customization
examples/cxx/tree/custom/calendar  - depends on the Boost date_time library
examples/cxx/tree/binary/boost     - depends on the Boost serialization library
examples/cxx/tree/binary/cdr       - depends on the ACE library
examples/cxx/tree/binary/xdr       - requires a third-party XDR library
examples/cxx/tree/xpath            - depends on the XQilla library (XPath 2)
examples/cxx/tree/dbxml            - depends on the Berkeley DB XML library


Using in Your Projects
----------------------

For various ways to integrate the XSD compiler with the Microsoft Visual
Studio IDE as well as other Visual Studio-specific topics, refer to the
Using XSD with Microsoft Visual Studio Wiki page:

http://wiki.codesynthesis.com/Using_XSD_with_Microsoft_Visual_Studio


