# file      : examples/cxx/parser/polymorphism/makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2005-2009 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../../build/bootstrap.make

xsd := supermen.xsd
cxx := driver.cxx supermen-pimpl.cxx

obj := $(addprefix $(out_base)/,$(cxx:.cxx=.o) $(xsd:.xsd=-pskel.o))
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

skel := $(out_base)/$(xsd:.xsd=-pskel.hxx) \
        $(out_base)/$(xsd:.xsd=-pskel.ixx) \
        $(out_base)/$(xsd:.xsd=-pskel.cxx)

$(skel): xsd := $(out_root)/xsd/xsd
$(skel): xsd_options := --generate-polymorphic
$(skel): $(out_root)/xsd/xsd

$(call include-dep,$(dep))

# Convenience alias for default target.
#
.PHONY: $(out_base)/
$(out_base)/: $(driver)


# Clean.
#
.PHONY: $(clean)

$(clean): $(driver).o.clean                                 \
  $(addsuffix .cxx.clean,$(obj))                            \
  $(addsuffix .cxx.clean,$(dep))                            \
  $(addprefix $(out_base)/,$(xsd:.xsd=-pskel.cxx.xsd.clean))


# How to.
#
$(call include,$(bld_root)/cxx/o-e.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)
$(call include,$(scf_root)/xsd/parser/xsd-cxx.make)


# Dependencies.
#
$(call import,$(src_root)/xsd/makefile)
