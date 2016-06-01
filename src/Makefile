CXX = g++
OBJ = main.o TypeTracing.o Base.o Date.o Person.o ProfessionAndRelated.o MaritalStatusAndRelated.o HobbyAndRelated.o
CXXFLAGS = -Wall -std=c++11
HDRS = TypeTracing.h Base.h Date.h Person.h ProfessionAndRelated.h MaritalStatusAndRelated.h HobbyAndRelated.h

QuestionnaireApp: $(OBJ)
	$(CXX) -o QuestionnaireApp $(OBJ)

%o: %.cpp $(HDRS)
	$(CXX) -c $(CXXFLAGS) $<
clean:
	rm *.o
