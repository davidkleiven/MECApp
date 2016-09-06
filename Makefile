CXX=g++
IDIR=inc
ODIR=obj
SDIR=src
TESTDIR=unittest
TESTODIR=unittest/obj

include makefilepaths.sh # Contains VTK_HEADER

LIBSRC:=facet.cpp gmshreader.cpp point.cpp facets.cpp
#TESTS:=testgmsh.cpp vec3test.cpp
TESTS:=alltest.cpp
LIBOBJ:=${LIBSRC:%.cpp=%.o}
LIBOBJ:=${addprefix ${ODIR}/, ${LIBOBJ}}
LIBSRC:=${addprefix ${SDIR}/, ${LIBSRC}}
LIBNAME=libmecapp.so
TESTSRC:=${addprefix unittest/, ${TESTS}}
TESTOBJ:=${TESTS:%.cpp=%.o}
TESTOBJ:=${addprefix ${TESTODIR}/, ${TESTOBJ}}
FLAGS=-std=c++11

.PHONY: clean check cleantest ${TESTODIR}/alltest.o

lib: ${LIBOBJ}	
	${CXX} -shared -o ${LIBNAME} $^

test: lib ${TESTOBJ} 
	${CXX} -o ${TESTDIR}/alltest.out ${TESTOBJ}  -L./ -lmecapp -lboost_program_options -lboost_unit_test_framework

check: test
	cd ${TESTDIR}; \
	./alltest.out; \
	cd ../

${ODIR}/%.o: ${SDIR}/%.cpp
	${CXX} ${FLAGS} -fPIC -o $@ -c $< -I ${IDIR} -I ${VTK_HEADER}

${TESTODIR}/alltest.o: ${TESTDIR}/alltest.cpp
	${CXX} ${FLAGS} -fPIC -c -o $@ $< -I ${IDIR} -I ${TESTDIR}

${TESTODIR}/%.o: ${TESTDIR}/%.cpp
	${CXX} ${FLAGS} -fPIC -c -o $@ $< -I ${IDIR}

clean:
	rm ${ODIR}/*.o
cleantest:
	rm ${TESTODIR}/*.o
