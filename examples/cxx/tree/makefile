# file      : examples/cxx/tree/makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2006-2009 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../build/bootstrap.make

examples := binary caching custom hello library messaging mixed multiroot \
performance polymorphism streaming wildcard

ifeq ($(xsd_with_dbxml),y)
examples += dbxml
endif

ifeq ($(xsd_with_xqilla),y)
examples += xpath
endif

default   := $(out_base)/
clean     := $(out_base)/.clean

.PHONY: $(default) $(clean)

$(default): $(addprefix $(out_base)/,$(addsuffix /,$(examples)))
$(clean): $(addprefix $(out_base)/,$(addsuffix /.clean,$(examples)))

$(foreach e,$(examples),$(call import,$(src_base)/$e/makefile))
