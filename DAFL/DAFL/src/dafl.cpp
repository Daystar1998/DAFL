#include "dafl.h"

void dataFile::createFile(char *fileName, int recordSize) {

	finOut.clear();
	// Create file
	finOut.open(fileName, std::ios::out);
	finOut.close();

	finOut.clear();
	finOut.open(fileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);

	if (finOut.is_open()) {

		// Check if the file is empty
		if (finOut.tellg() == 0) {

			recSize = recordSize;
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
	finOut.open(fileName, std::ios::in);

	// Check if the file exists before reopening it as an input/output file
	if (finOut) {

		finOut.close();

		finOut.clear();
		finOut.open(fileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
	} else {

		finOut.close();
	}

	if (finOut.is_open()) {

		finOut.seekg(std::ios::beg);
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

	finOut.seekp(std::ios::beg);

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

	if (relativeRecordNumber >= 0 && relativeRecordNumber <= recCount) {

		finOut.clear();

		// Record number x record size + header size
		int recordOffset = relativeRecordNumber * recSize + sizeof(recSize) + sizeof(recCount);

		finOut.seekp(recordOffset);
		finOut.write((char *)record, recSize);

		if (finOut.bad()) {

			fs = fsPutFail;
		} else {

			fs = fsSuccess;
		}
	} else {

		fs = fsPutFail;
	}
}

void dataFile::getRecord(int relativeRecordNumber, const void *record) {

	if (relativeRecordNumber >= 0 && relativeRecordNumber < recCount) {

		finOut.clear();

		// Record number x record size + header size
		int recordOffset = relativeRecordNumber * recSize + sizeof(recSize) + sizeof(recCount);

		finOut.seekg(recordOffset);
		finOut.read((char *)record, recSize);

		if (finOut.bad()) {

			fs = fsGetFail;
		} else {

			fs = fsSuccess;
		}
	} else {

		fs = fsGetFail;
	}
}

int dataFile::recordCount() {

	return recCount;
}

void dataFile::updateRecordCount(int n) {

	recCount += n;
}

int dataFile::fileStatus() {

	return fs;
}
