# file      : examples/cxx/parser/makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2006-2009 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../build/bootstrap.make

examples := generated hello library mixin mixed multiroot performance \
polymorphism polyroot wildcard

default   := $(out_base)/
clean     := $(out_base)/.clean

.PHONY: $(default) $(clean)

$(default): $(addprefix $(out_base)/,$(addsuffix /,$(examples)))
$(clean): $(addprefix $(out_base)/,$(addsuffix /.clean,$(examples)))

$(foreach e,$(examples),$(call import,$(src_base)/$e/makefile))
