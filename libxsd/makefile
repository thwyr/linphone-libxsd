# file      : libxsd/makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2005-2009 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../build/bootstrap.make

install   := $(out_base)/.install

.PHONY: $(install)

$(install):
	$(call install-dir,$(src_base)/xsd,$(install_inc_dir)/xsd)
	$(call install-data,$(src_base)/FLOSSE,$(install_doc_dir)/libxsd/FLOSSE)
	$(call install-data,$(src_base)/GPLv2,$(install_doc_dir)/libxsd/GPLv2)
	$(call install-data,$(src_base)/LICENSE,$(install_doc_dir)/libxsd/LICENSE)
	$(call install-data,$(src_base)/README,$(install_doc_dir)/libxsd/README)


$(call include,$(bld_root)/install.make)
