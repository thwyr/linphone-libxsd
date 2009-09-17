# file      : examples/cxx/tree/binary/makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2006-2009 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../../build/bootstrap.make

examples :=

ifeq ($(xsd_with_boost_serialization),y)
examples += boost
endif

ifeq ($(xsd_with_ace),y)
examples += cdr
endif

ifeq ($(xsd_with_xdr),y)
examples += xdr
endif

default   := $(out_base)/
clean     := $(out_base)/.clean

.PHONY: $(default) $(clean)

$(default): $(addprefix $(out_base)/,$(addsuffix /,$(examples)))
$(clean): $(addprefix $(out_base)/,$(addsuffix /.clean,$(examples)))

$(foreach e,$(examples),$(call import,$(src_base)/$e/makefile))
