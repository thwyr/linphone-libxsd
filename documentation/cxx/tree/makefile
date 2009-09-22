# file      : documentation/cxx/tree/makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2006-2009 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../build/bootstrap.make

docs := guide manual

default  := $(out_base)/
dist     := $(out_base)/.dist
dist-win := $(out_base)/.dist-win
cleandoc := $(out_base)/.cleandoc

# Build.
#
$(default): $(addprefix $(out_base)/,$(addsuffix /,$(docs)))

# Dist.
#
dist-common := $(out_base)/.dist-common

$(dist-common): path := $(subst $(src_root)/,,$(src_base))
$(dist-common):
	$(call install-dir,$(src_base)/dbxml,$(dist_prefix)/$(path)/dbxml)
	$(call install-dir,$(src_base)/reference,$(dist_prefix)/$(path)/reference)

$(dist): $(dist-common) $(addprefix $(out_base)/,$(addsuffix /.dist,$(docs)))
$(dist-win): $(dist-common) $(addprefix $(out_base)/,$(addsuffix /.dist-win,$(docs)))

# Clean.
#
$(cleandoc): $(addprefix $(out_base)/,$(addsuffix /.cleandoc,$(docs)))

$(foreach m,$(docs),$(call import,$(src_base)/$m/makefile))
