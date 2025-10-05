#include "test_header.h"

INSTANTIATE_TEST_SUITE_P(
	VariousCreatorInputs,
	CreatorControlTest,
	::testing::Values(
		make_tuple(1, "Denis", 10.5),
		make_tuple(2, "Anna", 0.0),
		make_tuple(3, "Max", 99.9),
		make_tuple(4, "-", 5.0),
		make_tuple(5, "LongName", 12.3)
	)
);

TEST_P(CreatorControlTest, CreatorTest_Correct) {
	const string BinTestFileName = "testCreator.bin";
	const string InputTestFileName = "testCreatorInput.txt";
	int expected_num = get<0>(GetParam());
	const char* expected_name = get<1>(GetParam());
	double expected_hours = get<2>(GetParam());

	ofstream out(InputTestFileName);
	out << to_string(expected_num) << "\n" << expected_name << "\n" << to_string(expected_hours) << "\n";
	out.close();

	string BinTestFileAddress = "cmd.exe /C \"..\\Creator.exe " + BinTestFileName + " 1 < " + InputTestFileName + "\"";
	ASSERT_TRUE(startProcessCMD(BinTestFileAddress));

	ifstream in(BinTestFileName, ios::binary);
	ASSERT_TRUE(in.is_open());

	employee e;
	in.read(reinterpret_cast<char*>(&e), sizeof(employee));

	EXPECT_EQ(e.num, expected_num);
	EXPECT_STREQ(e.name, expected_name);
	EXPECT_EQ(e.hours, expected_hours);

	in.close();
	filesystem::remove(BinTestFileName);
	filesystem::remove(InputTestFileName);

}