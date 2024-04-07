#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestCreateDataFile)
		{
			const string inputFileName = "input_test.bin";

			ofstream outputFile(inputFileName, ios::binary);
			Assert::IsTrue(outputFile.is_open(), L"Cannot create input file.");

			vector<int> testData = { 1, 2, 3, 4, 5 };
			for (const int& num : testData) {
				outputFile.write(reinterpret_cast<const char*>(&num), sizeof(num));
			}

			outputFile.close();

			ifstream inputFile(inputFileName, ios::binary);
			Assert::IsTrue(inputFile.is_open(), L"Input file was not created.");

			int num;
			for (size_t i = 0; i < testData.size(); ++i) {
				inputFile.read(reinterpret_cast<char*>(&num), sizeof(num));
				Assert::AreEqual(testData[i], num);
			}

			inputFile.close();
		}
	};
}