# file      : tests/cxx/tree/wildcard/makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2006-2009 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../../build/bootstrap.make

xsd := test.xsd
cxx := driver.cxx

obj := $(addprefix $(out_base)/,$(cxx:.cxx=.o) $(xsd:.xsd=.o))
dep := $(obj:.o=.o.d)

driver := $(out_base)/driver
test   := $(out_base)/.test
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

$(out_base)/$(xsd:.xsd=.hxx) \
$(out_base)/$(xsd:.xsd=.ixx) \
$(out_base)/$(xsd:.xsd=.cxx): xsd := $(out_root)/xsd/xsd

$(out_base)/$(xsd:.xsd=.hxx) \
$(out_base)/$(xsd:.xsd=.ixx) \
$(out_base)/$(xsd:.xsd=.cxx): xsd_options := --generate-wildcard \
--generate-default-ctor --generate-from-base-ctor \
--generate-serialization --generate-comparison

$(out_base)/$(xsd:.xsd=.hxx) \
$(out_base)/$(xsd:.xsd=.ixx) \
$(out_base)/$(xsd:.xsd=.cxx): $(out_root)/xsd/xsd

$(call include-dep,$(dep))

# Convenience alias for default target.
#
.PHONY: $(out_base)/
$(out_base)/: $(driver)


# Test.
#
.PHONY: $(test)

$(test): driver := $(driver)
$(test): $(driver) $(src_base)/test.xml $(src_base)/output
	$(call message,test $$1,$$1 $(src_base)/test.xml | diff -u $(src_base)/output -,$(driver))

# Clean.
#
.PHONY: $(clean)

$(clean): $(driver).o.clean                                \
  $(addsuffix .cxx.clean,$(obj))                           \
  $(addsuffix .cxx.clean,$(dep))                           \
  $(addprefix $(out_base)/,$(xsd:.xsd=.cxx.xsd.clean))


# How to.
#
$(call include,$(bld_root)/cxx/o-e.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)
$(call include,$(scf_root)/xsd/tree/xsd-cxx.make)


# Dependencies.
#
$(call import,$(src_root)/xsd/makefile)
