/*
 * pgpry - PGP private key recovery
 * Copyright (C) 2010 Jonas Gehring
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include "key.h"
#include "pistream.h"
#include "tester.h"

#include "memblock.h"

using namespace std;

#define N 128

int main(int argc, char **argv)
{
	if(argc < 2) {
		fprintf(stderr, "Usage: %s <GPG Secret Key>\n", argv[0]);
		exit(-1);
	}

	ifstream inStream;
	inStream.open(argv[1]);
	Key key;
	try {
		PIStream in(inStream);
		in >> key;
	} catch(const std::string & str) {
		std::cerr << "Exception while parsing key: " << str << std::
		    endl;
		return EXIT_FAILURE;
	}
	catch(const char *cstr) {
		std::cerr << "Exception while parsing key: " << cstr << std::
		    endl;
		return EXIT_FAILURE;
	}

	if (!key.locked()) {
		std::
		    cerr << "Err, this secret key doesn't seem to be encrypted"
		    << std::endl;
		return EXIT_FAILURE;
	}
	Tester *t = new Tester(key, NULL);
	t->init();
	char passphrase[N];
	int l;
	while(fgets(passphrase, N, stdin) != NULL) {
		l = strlen(passphrase);
		passphrase[l-1] = 0;
 		Memblock *b = new Memblock(passphrase);
		if(t->check(*b)) {
			printf("Password Found : %s\n", passphrase);
			exit(0);
		}
	}
	exit(1);
}
