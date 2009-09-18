# file      : documentation/makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2005-2009 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../build/bootstrap.make

default  := $(out_base)/
install  := $(out_base)/.install
cleandoc := $(out_base)/.cleandoc

$(default): $(out_base)/cxx/

# Install.
#
$(install):
	$(call install-dir,$(src_base)/cxx,$(install_doc_dir)/xsd/cxx)
	$(call install-data,$(src_base)/default.css,$(install_doc_dir)/xsd/default.css)
	$(call install-data,$(src_base)/future.xhtml,$(install_doc_dir)/xsd/future.xhtml)
	$(call install-data,$(src_base)/schema-authoring-guide.xhtml,$(install_doc_dir)/xsd/schema-authoring-guide.xhtml)
	$(call install-data,$(src_base)/xsd.xhtml,$(install_doc_dir)/xsd/xsd.xhtml)
	$(call install-data,$(src_base)/xsd.1,$(install_man_dir)/man1/xsd.1)

# Clean.
#
$(cleandoc): $(src_base)/cxx/.cleandoc

$(call include,$(bld_root)/install.make)

$(call import,$(src_base)/cxx/makefile)
