.SUFFIXES:
.SUFFIXES: .htpp .html

SRCS=index.htpp running.htpp controller.htpp Controller.java.htpp framework.htpp sample.htpp \
	Ball.java.htpp Setup.java.htpp
DOCS=${SRCS:.htpp=.html}

.htpp.html:
	htmlpp $< > $@

build: ${DOCS}

clean:
	- rm ${DOCS}
	
all: clean build
