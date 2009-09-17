# file      : examples/cxx/tree/custom/double/makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2005-2009 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../../../build/bootstrap.make

xsd := order.xsd
cxx := driver.cxx double-custom.cxx

obj := $(addprefix $(out_base)/,$(cxx:.cxx=.o) $(xsd:.xsd=.o))
dep := $(obj:.o=.o.d)

driver := $(out_base)/driver
clean  := $(out_base)/.clean


# Import.
#
$(call import,\
  $(scf_root)/import/libxerces-c/stub.make,\
  l: xerces_c.l,cpp-options: xerces_c.l.cpp-options)


# Build.
#
$(driver): $(obj) $(xerces_c.l)

$(obj) $(dep): cpp_options := -I$(src_root)/libxsd
$(obj) $(dep): $(xerces_c.l.cpp-options)

$(out_base)/xml-schema.hxx: $(out_root)/xsd/xsd
	$(call message,xsd $(src_base)/xml-schema.xsd,\
$(out_root)/xsd/xsd cxx-tree --output-dir $(out_base) --generate-xml-schema \
--generate-serialization --custom-type double=double \
--hxx-epilogue '\#include "double-custom.hxx"' xml-schema.xsd)

genf := $(xsd:.xsd=.hxx) $(xsd:.xsd=.ixx) $(xsd:.xsd=.cxx)
gen  := $(addprefix $(out_base)/,$(genf))

$(gen): xsd := $(out_root)/xsd/xsd

$(gen): xsd_options := \
--generate-serialization --extern-xml-schema xml-schema.xsd

$(gen): $(out_root)/xsd/xsd

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

# Generated .gitignore.
#
ifeq ($(out_base),$(src_base))
$(gen): | $(out_base)/.gitignore
$(driver): | $(out_base)/.gitignore

$(out_base)/.gitignore: files := driver xml-schema.hxx $(genf)
$(clean): $(out_base)/.gitignore.clean

$(call include,$(bld_root)/git/gitignore.make)
endif

# How to.
#
$(call include,$(bld_root)/cxx/o-e.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)
$(call include,$(scf_root)/xsd/tree/xsd-cxx.make)

# Dependencies.
#
$(call import,$(src_root)/xsd/makefile)
