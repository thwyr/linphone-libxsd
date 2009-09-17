# file      : examples/cxx/tree/custom/taxonomy/makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2005-2009 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../../../build/bootstrap.make

xsd := people.xsd
cxx := driver.cxx people-custom.cxx

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
--generate-forward \
--generate-polymorphic \
--custom-type "person=person_impl<person_base>/person_base" \
--custom-type "superman=superman_impl<superman_base>/superman_base" \
--custom-type "batman=batman_impl<batman_base>/batman_base" \
--fwd-prologue '\\\#include "people-custom-fwd.hxx"' \
--hxx-prologue '\\\#include "people-custom.hxx"'

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


# How to.
#
$(call include,$(bld_root)/cxx/o-e.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)
$(call include,$(scf_root)/xsd/tree/xsd-cxx.make)

# Dependencies.
#
$(call import,$(src_root)/xsd/makefile)
