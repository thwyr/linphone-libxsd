# file      : build/import/libboost/serialization/rules.make
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2009 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

$(dcf_root)/import/libboost/%: root := $(libboost_root)

$(dcf_root)/import/libboost/serialization/serialization.l: \
  | $(dcf_root)/import/libboost/serialization/.

ifeq ($(libboost_type),archive)

$(dcf_root)/import/libboost/serialization/serialization.l: \
  $(libboost_root)/stage/lib/libboost_serialization-gcc$(libboost_toolset)-$(libboost_version).a
	@echo $< >$@

else

$(dcf_root)/import/libboost/serialization/serialization.l: \
  $(libboost_root)/stage/lib/libboost_serialization-gcc$(libboost_toolset)-$(libboost_version).so
	@echo $< >$@
	@echo rpath:$(root)/stage/lib >>$@

endif


$(dcf_root)/import/libboost/serialization/serialization.l.cpp-options: \
  | $(dcf_root)/import/libboost/serialization/.
	@echo include: -I$(root) >$@

ifndef %foreign%

disfigure::
	$(call message,rm $(dcf_root)/import/libboost/serialization/serialization.l,\
rm -f $(dcf_root)/import/libboost/serialization/serialization.l)
	$(call message,,rm -f $(dcf_root)/import/libboost/serialization/serialization.l.cpp-options)

endif
