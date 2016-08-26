CXX=g++
IDIR=inc
ODIR=obj
SDIR=src
TESTDIR=unittest
TESTODIR=unittest/obj

LIBSRC:=facet.cpp gmshreader.cpp
TESTS:=testgmsh.cpp
LIBOBJ:=${LIBSRC:%.cpp=%.o}
LIBOBJ:=${addprefix ${ODIR}/, ${LIBOBJ}}
LIBSRC:=${addprefix ${SDIR}/, ${LIBSRC}}
LIBNAME=libmecapp.so
TESTSRC:=${addprefix unittest/, ${TESTS}}
TESTOBJ:=${TESTS:%.cpp=%.o}
TESTOBJ:=${addprefix ${TESTODIR}/, ${TESTOBJ}}
FLAGS=-std=c++11

.PHONY: clean

lib: ${LIBOBJ}	
	${CXX} -shared -o ${LIBNAME} $^

test: lib ${TESTOBJ} 
	${CXX} -o ${TESTDIR}/alltest.out ${TESTOBJ}  -L./ -lmecapp -lboost_program_options -lboost_unit_test_framework

${ODIR}/%.o: ${SDIR}/%.cpp
	${CXX} ${FLAGS} -fPIC -o $@ -c $< -I ${IDIR}

${TESTODIR}/%.o: ${TESTDIR}/%.cpp
	${CXX} ${FLAGS} -c -o -fPIC $@ $< -I ${IDIR}

clean:
	rm ${ODIR}/*.o
