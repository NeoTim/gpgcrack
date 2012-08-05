target:
	g++ -Wall -O2 my.cpp tester.cpp pistream.cpp key.cpp string2key.cpp packetheader.cpp utils.cpp cryptutils.cpp -lcrypto -o gpgcrack
