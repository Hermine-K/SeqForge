all: 	
	g++ -std=c++20 devops_Hermine.cpp verification_HK.cpp verification_HK.hpp verification_FASTA.hpp verification_FASTA.cpp -o devops
	./devops
	
