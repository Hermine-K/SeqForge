all: devops

.PHONY: clean

devops:
	g++ -std=c++20 devops_Hermine.cpp verification_HK.cpp verification_HK.hpp verification_FASTA.hpp verification_FASTA.cpp verification_FASTQ.hpp verification_FASTQ.cpp Analyse_HK.hpp Analyse_HK.cpp Analyse_FASTA.cpp Analyse_FASTA.hpp Analyse_FASTQ.cpp Analyse_FASTQ.hpp userPrompt.cpp userPrompt.hpp -o devops

clean: 
	rm -f ./devops	
	
