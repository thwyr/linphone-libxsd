root := ../../..

include $(root)/build/cxx/rules.make
include $(root)/build/xsd/tree-rules.make


override XSDFLAGS += --generate-serialization --suppress-parsing --root-element-all


# Build.
#
driver: driver.o records.o

records.o: records.cxx records.hxx 
driver.o: driver.cxx records.hxx

records.cxx records.hxx: records.xsd


# Test
#
.PHONY: test
test: driver
	./driver


# Clean.
#
.PHONY: clean
clean:
	rm -f records.o records.?xx driver.o driver out.xml
