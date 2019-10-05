#include "dafl.h"

void dataFile::createFile(char *fileName, int fileLength) {

	finOut.clear();
	finOut.open(fileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::app | std::ios::ate);

	if (!finOut.is_open()) {

		fs = fsCreateFail;
	} else {

		// Check if the file is empty
		if (finOut.tellg() == 0) {

			recSize = 0;
			recCount = 0;

			// Write header to file
			finOut.write((char *)& recSize, sizeof(recSize));
			finOut.write((char *)& recCount, sizeof(recCount));
		} else {

			finOut.seekp(std::ios::beg);

			// Read header
			finOut.read((char *)& recSize, sizeof(recSize));
			finOut.read((char *)& recCount, sizeof(recCount));
		}

		if (!finOut.bad()) {

			fs = fsCreateFail;
		} else {

			fs = fsSuccess;
		}
	}
}

void dataFile::openFile(char *fileName) {

	finOut.clear();
	finOut.open(fileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::app | std::ios::ate);

	if (finOut.is_open()) {

		finOut.seekp(std::ios::beg);

		// Read header
		finOut.read((char *)& recSize, sizeof(recSize));
		finOut.read((char *)& recCount, sizeof(recCount));

		if (finOut.bad()) {

			fs = fsSuccess;
		} else {

			fs = fsCreateFail;
		}
	} else {

		fs = fsCreateFail;
	}
}

