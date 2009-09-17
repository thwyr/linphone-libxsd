# file      : examples/cxx/tree/custom/calendar/makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2005-2009 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../../../build/bootstrap.make

xsd := calendar.xsd
cxx := driver.cxx xml-schema-custom.cxx

obj := $(addprefix $(out_base)/,$(cxx:.cxx=.o) $(xsd:.xsd=.o))
dep := $(obj:.o=.o.d)

driver := $(out_base)/driver
clean  := $(out_base)/.clean


# Import.
#
$(call import,\
  $(scf_root)/import/libxerces-c/stub.make,\
  l: xerces_c.l,cpp-options: xerces_c.l.cpp-options)

$(call import,\
  $(scf_root)/import/libboost/date-time/stub.make,\
  l: boost_date_time.l,cpp-options: boost_date_time.l.cpp-options)

# Build.
#
$(driver): $(obj) $(xerces_c.l) $(boost_date_time.l)

$(obj) $(dep): cpp_options := -I$(src_root)/libxsd
$(obj) $(dep): $(xerces_c.l.cpp-options) $(boost_date_time.l.cpp-options)

# Header file for XML Schema namespace.
#
$(out_base)/xml-schema.hxx: $(out_root)/xsd/xsd
	$(call message,xsd $(src_base)/xml-schema.xsd,\
$(out_root)/xsd/xsd cxx-tree --output-dir $(out_base) --generate-xml-schema \
--custom-type date \
--hxx-epilogue '\#include "xml-schema-custom.hxx"' xml-schema.xsd)

#
#
$(out_base)/$(xsd:.xsd=.hxx) \
$(out_base)/$(xsd:.xsd=.ixx) \
$(out_base)/$(xsd:.xsd=.cxx): xsd := $(out_root)/xsd/xsd

# We have to double-escape '#' because the message function
# (which is used in command scripts) expands things twice.
#
$(out_base)/$(xsd:.xsd=.hxx) \
$(out_base)/$(xsd:.xsd=.ixx) \
$(out_base)/$(xsd:.xsd=.cxx): xsd_options := \
--generate-inline \
--extern-xml-schema xml-schema.xsd

$(out_base)/$(xsd:.xsd=.hxx) \
$(out_base)/$(xsd:.xsd=.ixx) \
$(out_base)/$(xsd:.xsd=.cxx): $(out_root)/xsd/xsd

$(call include-dep,$(dep))

# Convenience alias for default target.
#
.PHONY: $(out_base)/
$(out_base)/: $(driver)


# Clean.
#
.PHONY: $(clean)

$(clean): $(driver).o.clean                            \
  $(addsuffix .cxx.clean,$(obj))                       \
  $(addsuffix .cxx.clean,$(dep))                       \
  $(addprefix $(out_base)/,$(xsd:.xsd=.cxx.xsd.clean))
	$(call message,rm $$1,rm -f $$1,$(out_base)/xml-schema.hxx)


# How to.
#
$(call include,$(bld_root)/cxx/o-e.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)
$(call include,$(scf_root)/xsd/tree/xsd-cxx.make)

# Dependencies.
#
$(call import,$(src_root)/xsd/makefile)
