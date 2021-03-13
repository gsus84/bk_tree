# Makefile for make-bktree

CPPCOMP = g++
#DEFINES	= -DNDEBUG

show-near-words : include/bktree.hpp src/search_bk.cpp Makefile
	# Download German word list
	wget www1.ids-mannheim.de/fileadmin/kl/derewo/derewo-v-ww-bll-320000g-2012-12-31-1.0.zip
	unzip derewo-v-ww-bll-320000g-2012-12-31-1.0.zip
	mv derewo-v-ww-bll-320000g-2012-12-31-1.0.txt data/derewo-v-ww-bll-320000g-2012-12-31-1.0.txt
	rm derewo-v-ww-bll-320000g-2012-12-31-1.0.zip
	rm derewo-v-ww-bll-320000g-2012-12-31-1.0.pdf
	rm derewo-general-remarks-2013.pdf

	$(CPPCOMP) -O3 -std=c++11 $(DEFINES) -o show-near-words src/search_bk.cpp
	cp show-near-words bin/show-near-words
	$(CPPCOMP) -O3 -std=c++11 $(DEFINES) -o test-bk-1 src/test_bk_1.cpp
	cp test-bk-1 bin/test-bk-1
	$(CPPCOMP) -O3 -std=c++11 $(DEFINES) -o convert-derewo src/convert_derewo.cpp
	cp convert-derewo bin/convert-derewo
	bin/convert-derewo data/derewo-v-ww-bll-320000g-2012-12-31-1.0.txt data/derewo-forms.list
	rm data/derewo-v-ww-bll-320000g-2012-12-31-1.0.txt


interactive :
	bin/show-near-words data/derewo-forms.list gen_files/derewo-bktree.xdot

tests : include/bktree.hpp src/test_bk_1.cpp
	bin/test-bk-1 data/test_data_pathes.list < data/test_data_pathes.list
	dot -Tpdf -O gen_files/Test_BK_tree.xdot

clean:
	rm -f bin/show-near-words
	rm -f show-near-words
	rm -f bin/test-bk-1
	rm -f test-bk-1
	rm -f convert-derewo 
	rm -f bin/convert-derewo
	rm -f data/derewo-forms.list
	rm -f gen_files/small_test_bk_tree.xdot
	rm -f gen_files/Test_BK_tree.xdot
	rm -f gen_files/Test_BK_tree.xdot.pdf
	rm -f gen_files/derewo-bktree.xdot

	rm -rf doc/html
	rm -f *.dot *.xdot *.pdf
