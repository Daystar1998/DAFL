#include "dafl.h"

void dataFile::createFile(char *fileName, int fileLength) {

	finOut.clear();
	finOut.open(fileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::app | std::ios::ate);

	if (finOut.is_open()) {

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

		if (finOut.bad()) {

			fs = fsCreateFail;
		} else {

			fs = fsSuccess;
		}
	} else {

		fs = fsCreateFail;
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

			fs = fsOpenFail;
		} else {

			fs = fsSuccess;
		}
	} else {

		fs = fsOpenFail;
	}
}

void dataFile::closeFile() {

	finOut.clear();
	
	// Write header to file
	finOut.write((char *)& recSize, sizeof(recSize));
	finOut.write((char *)& recCount, sizeof(recCount));
	
	finOut.close();

	if (finOut.bad()) {

		fs = fsCloseFail;
	} else {

		fs = fsSuccess;
	}
}

void dataFile::putRecord(int relativeRecordNumber, const void *record) {

	finOut.clear();

	// Record number x record size + header size
	int recordOffset = relativeRecordNumber * recSize + sizeof(recSize) + sizeof(recCount);

	finOut.seekp(recordOffset);

	if(relativeRecordNumber > recCount) {

		updateRecordCount(1);
		finOut.write((char *) record, sizeof(record));
	} else {

		// Edit record
	}

	if (finOut.bad()) {

		fs = fsPutFail;
	} else {

		fs = fsSuccess;
	}
}
