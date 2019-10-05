/******************************************************************************
	Name: dafl.h

	Des:
		File operations to create a direct access, fixed length record file
			structure

	Author: Matthew Day

	Date: 10/05/2019
******************************************************************************/

#pragma once

class dataFile {

public:

	/******************************************************************************
		Name: createFile

		Des:
			Create a binary input/output file and create a header for the file

		Params:
			fileName - type char*, the name of the file
			fileLength - type int, length of the file in bytes
	******************************************************************************/
	void createFile(char *fileName, int fileLength);

	/******************************************************************************
		Name: openFile

		Des:
			Open an existing binary input/output file and read the header for the
			file

		Params:
			fileName - type char*, the name of the file
	******************************************************************************/
	void openFile(char *fileName);

	/******************************************************************************
		Name: closeFile

		Des:
			Write the file header to the file then close the file
	******************************************************************************/
	void closeFile();

	/******************************************************************************
		Name: putRecord

		Des:
			Write a record to specified location in the file

		Params:
			relativeRecordNumber - type int, number indicating where the record
				should be placed in the file
			record - type const void *, pointer to the memory containing the
				record to be written to the file
	******************************************************************************/
	void putRecord(int relativeRecordNumber, const void *record);

	/******************************************************************************
		Name: getRecord

		Des:
			Read the selected record from the file

		Params:
			relativeRecordNumber - type int, number indicating where the record
				is located in the file
			record - type const void *, pointer to the memory where the record
				should be read into
	******************************************************************************/
	void getRecord(int relativeRecordNumber, const void *record);

	/******************************************************************************
		Name: recordCount

		Des:
			Return the count of records in the file

		Returns:
			type int, the count of records in the file
	******************************************************************************/
	int recordCount();

	/******************************************************************************
		Name: updateRecordCount

		Des:
			Increment or decrement the record count by the specified amount

		Params:
			n - type int, number to increment or decrement by
	******************************************************************************/
	void updateRecordCount(int n);

	/******************************************************************************
		Name: FileStatus

		Des:
			Return the status of the last file operation

		Returns:
			type int, the status of the last file operation
	******************************************************************************/
	int FileStatus();
};
