CXX=g++
IDIR=inc
ODIR=obj
SDIR=src

LIBSRC:=facet.cpp gmshreader.cpp
LIBOBJ:=${LIBSRC:%.cpp=%.o}
LIBOBJ:=${addprefix ${ODIR}/, ${LIBOBJ}}
LIBSRC:=${addprefix ${SDIR}/, ${LIBSRC}}
LIBNAME=mecapp.so
FLAGS=-std=c++11

.PHONY: clean

lib: ${LIBOBJ}	
	${CXX} -shared -fPIC -o ${LIBNAME} $^

${ODIR}/%.o: ${SDIR}/%.cpp
	${CXX} ${FLAGS} -fPIC -o $@ -c $< -I ${IDIR}

clean:
	rm ${ODIR}/*.o
