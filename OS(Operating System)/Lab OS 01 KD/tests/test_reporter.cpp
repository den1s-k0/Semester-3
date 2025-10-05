#include "test_header.h"

INSTANTIATE_TEST_SUITE_P(
	VariousReporterInputs,
	ReporterControlTest,
	::testing::Values(
		make_tuple(1, "Denis", 10.5, 1),
		make_tuple(2, "Anna", 0.0, 10),
		make_tuple(3, "Max", 99.9, 13),
		make_tuple(4, "-", 5.0, 0),
		make_tuple(5, "LongName", 12.3, 0)
	)
);

TEST_P(ReporterControlTest, ReporterTest_Correct) {
	const string BinTestFileName = "testReporterB.bin";
	const string TxtTestFileName = "testReporterT.txt";
	int expected_num = get<0>(GetParam());
	const char* expected_name = get<1>(GetParam());
	double expected_hours = get<2>(GetParam());
	int expected_hourly_rate = get<3>(GetParam());

	WriteBinFile(BinTestFileName, employee(expected_num, expected_name, expected_hours));

	string TxtTestFileAddress = "..\\Reporter.exe " + BinTestFileName + " "	+ TxtTestFileName + " "	+ to_string(expected_hourly_rate);
	ASSERT_TRUE(startProcessCMD(TxtTestFileAddress));

	ifstream in(TxtTestFileName);
	ASSERT_TRUE(in.is_open());

	string output;
	int salary;
	int i = 1;

	getline(in, output);
	EXPECT_TRUE(output.find("ID") != string::npos);
	EXPECT_TRUE(output.find("Name") != string::npos);
	EXPECT_TRUE(output.find("Hours") != string::npos);
	EXPECT_TRUE(output.find("Salary") != string::npos);
	getline(in, output);

	while (getline(in, output)) {
		salary = expected_hourly_rate * expected_hours;
		EXPECT_TRUE(output.find(to_string(i) + ".") != string::npos);
		EXPECT_TRUE(output.find(to_string(expected_num)) != string::npos);
		if (strlen(expected_name) > 0) {
			EXPECT_TRUE(output.find(string(expected_name)) != string::npos);
		}
		ostringstream hours_oss;
		hours_oss << fixed << setprecision(2) << expected_hours;
		EXPECT_TRUE(output.find(hours_oss.str()) != string::npos);
		ostringstream salary_oss;
		salary_oss << fixed << setprecision(2) << salary;
		EXPECT_TRUE(output.find(salary_oss.str()) != string::npos);
		i++;
	}

	in.close();
	filesystem::remove(BinTestFileName);
	filesystem::remove(TxtTestFileName);

}