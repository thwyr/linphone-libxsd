root := ../../..

include $(root)/build/cxx/rules.make
include $(root)/build/xsd/tree-rules.make

# Build.
#
driver: driver.o secure-dom-parser.o library.o

library.o: library.cxx library.hxx
secure-dom-parser.o: secure-dom-parser.cxx secure-dom-parser.hxx
driver.o: driver.cxx secure-dom-parser.hxx library.hxx

library.cxx library.hxx: library.xsd


# Test
#
.PHONY: test
test: driver library.xml
	./driver library.xml


# Clean.
#
.PHONY: clean
clean:
	rm -f library.o library.?xx secure-dom-parser.o driver.o driver
