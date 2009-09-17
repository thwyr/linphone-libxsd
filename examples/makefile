# file      : examples/makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2006-2009 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../build/bootstrap.make

default   := $(out_base)/
clean     := $(out_base)/.clean

.PHONY: $(default) $(clean)

$(default): $(out_base)/cxx/parser/ $(out_base)/cxx/tree/
$(clean): $(out_base)/cxx/parser/.clean $(out_base)/cxx/tree/.clean

$(call import,$(src_base)/cxx/parser/makefile)
$(call import,$(src_base)/cxx/tree/makefile)
