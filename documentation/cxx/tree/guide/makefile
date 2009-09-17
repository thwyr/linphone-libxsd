.PHONY: all
all: cxx-tree-guide.ps cxx-tree-guide.pdf

cxx-tree-guide.pdf: cxx-tree-guide.ps
	ps2pdf14 $<

cxx-tree-guide.ps: index.xhtml guide.html2ps
	html2ps -f guide.html2ps -o $@ $<

.PHONY: clean
clean:
	rm -f cxx-tree-guide.ps cxx-tree-guide.pdf
