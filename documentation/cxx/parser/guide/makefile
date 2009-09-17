.PHONY: all
all: cxx-parser-guide.ps cxx-parser-guide.pdf

cxx-parser-guide.pdf: cxx-parser-guide.ps
	ps2pdf14 $<

cxx-parser-guide.ps: index.xhtml guide.html2ps
	html2ps -f guide.html2ps -o $@ $<

.PHONY: clean
clean:
	rm -f cxx-parser-guide.ps cxx-parser-guide.pdf
