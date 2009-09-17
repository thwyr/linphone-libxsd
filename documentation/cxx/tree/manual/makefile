.PHONY: all
all: cxx-tree-manual.ps cxx-tree-manual.pdf

cxx-tree-manual.pdf: cxx-tree-manual.ps
	ps2pdf14 $<

cxx-tree-manual.ps: index.xhtml manual.html2ps
	html2ps -f manual.html2ps -o $@ $<

.PHONY: clean
clean:
	rm -f cxx-tree-manual.ps cxx-tree-manual.pdf
