CPP_LIBS = FollowInfo.cpp PostInfo.cpp UserInfo.cpp Utility.cpp
H_LIBS = FollowInfo.h PostInfo.h UserInfo.h Utility.h Priority.hpp WizardDB.hpp

proj: proj.cpp $(CPP_LIBS) $(H_LIBS)
	g++ -o proj proj.cpp $(CPP_LIBS) $(H_LIBS) -std=c++11
test: test.cpp $(CPP_LIBS) $(H_LIBS)
	g++ -o test test.cpp $(CPP_LIBS) $(H_LIBS) -std=c++11
clean:
	rm -f proj *~ *.tmp
