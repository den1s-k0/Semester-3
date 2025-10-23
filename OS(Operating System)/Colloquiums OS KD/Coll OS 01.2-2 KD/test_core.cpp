#include "test_core.h"

INSTANTIATE_TEST_SUITE_P(
    VariousFinInputs,
    NumberControlTest,
    ::testing::Values(
        make_tuple("abv", ReturnIsNumberCodes::No_it_isnt_Number),
        make_tuple("", ReturnIsNumberCodes::No_it_isnt_Number),
        make_tuple("12---21", ReturnIsNumberCodes::No_it_isnt_Number),
        make_tuple("-1001", ReturnIsNumberCodes::No_it_isnt_Number),
        make_tuple("1", ReturnIsNumberCodes::Yes_it_is_Number),
        make_tuple("1001001", ReturnIsNumberCodes::Yes_it_is_Number),
        make_tuple("11111111111111111111111111", ReturnIsNumberCodes::Yes_it_is_Number),
        make_tuple("1000000000000000000001", ReturnIsNumberCodes::Yes_it_is_Number),
        make_tuple("98765432123456789", ReturnIsNumberCodes::Yes_it_is_Number),
        make_tuple("987654321123456789", ReturnIsNumberCodes::Yes_it_is_Number),
        make_tuple("12001200210021", ReturnIsNumberCodes::Yes_it_is_Number),
        make_tuple("23", ReturnIsNumberCodes::Yes_it_is_Number),
        make_tuple("211111111111111111111111111", ReturnIsNumberCodes::Yes_it_is_Number),
        make_tuple("100000000020000000200001", ReturnIsNumberCodes::Yes_it_is_Number),
        make_tuple("9787652432123456789", ReturnIsNumberCodes::Yes_it_is_Number),
        make_tuple("981765432112322456789", ReturnIsNumberCodes::Yes_it_is_Number),
        make_tuple("1202120021002221", ReturnIsNumberCodes::Yes_it_is_Number)
    )
);

TEST_P(NumberControlTest, NumberVerif) {
    string expected_string = get<0>(GetParam());

    EXPECT_EQ(IsNumber(expected_string), get<1>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    VariousFinInputs,
    PalendControlTest,
    ::testing::Values(
        make_tuple("abv", ReturnIsPalendCodes::No_it_isnt_Palend),
        make_tuple("", ReturnIsPalendCodes::No_it_isnt_Palend),
        make_tuple("12---21", ReturnIsPalendCodes::Yes_it_is_Palend),
        make_tuple("-1001", ReturnIsPalendCodes::No_it_isnt_Palend),
        make_tuple("1", ReturnIsPalendCodes::Yes_it_is_Palend),
        make_tuple("1001001", ReturnIsPalendCodes::Yes_it_is_Palend),
        make_tuple("11111111111111111111111111", ReturnIsPalendCodes::Yes_it_is_Palend),
        make_tuple("1000000000000000000001", ReturnIsPalendCodes::Yes_it_is_Palend),
        make_tuple("98765432123456789", ReturnIsPalendCodes::Yes_it_is_Palend),
        make_tuple("987654321123456789", ReturnIsPalendCodes::Yes_it_is_Palend),
        make_tuple("12001200210021", ReturnIsPalendCodes::Yes_it_is_Palend),
        make_tuple("23", ReturnIsPalendCodes::No_it_isnt_Palend),
        make_tuple("211111111111111111111111111", ReturnIsPalendCodes::No_it_isnt_Palend),
        make_tuple("100000000020000000200001", ReturnIsPalendCodes::No_it_isnt_Palend),
        make_tuple("9787652432123456789", ReturnIsPalendCodes::No_it_isnt_Palend),
        make_tuple("981765432112322456789", ReturnIsPalendCodes::No_it_isnt_Palend),
        make_tuple("1202120021002221", ReturnIsPalendCodes::No_it_isnt_Palend)
    )
);

TEST_P(PalendControlTest, PalenVerif) {
    string expected_string = get<0>(GetParam());

    EXPECT_EQ(IsPalend(expected_string), get<1>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    VariousFinInputs,
    PalendNumberControlTest,
    ::testing::Values(
        make_tuple("abv", ReturnPalendNumberVerifCodes::Wrong_Number),
        make_tuple("", ReturnPalendNumberVerifCodes::Wrong_Number),
        make_tuple("12---21", ReturnPalendNumberVerifCodes::Wrong_Number),
        make_tuple("-1001", ReturnPalendNumberVerifCodes::Wrong_Number),
        make_tuple("1", ReturnPalendNumberVerifCodes::Yes_it_is_Palend),
        make_tuple("1001001", ReturnPalendNumberVerifCodes::Yes_it_is_Palend),
        make_tuple("11111111111111111111111111", ReturnPalendNumberVerifCodes::Yes_it_is_Palend),
        make_tuple("1000000000000000000001", ReturnPalendNumberVerifCodes::Yes_it_is_Palend),
        make_tuple("98765432123456789", ReturnPalendNumberVerifCodes::Yes_it_is_Palend),
        make_tuple("987654321123456789", ReturnPalendNumberVerifCodes::Yes_it_is_Palend),
        make_tuple("12001200210021", ReturnPalendNumberVerifCodes::Yes_it_is_Palend),
        make_tuple("23", ReturnPalendNumberVerifCodes::No_it_isnt_Palend),
        make_tuple("211111111111111111111111111", ReturnPalendNumberVerifCodes::No_it_isnt_Palend),
        make_tuple("100000000020000000200001", ReturnPalendNumberVerifCodes::No_it_isnt_Palend),
        make_tuple("9787652432123456789", ReturnPalendNumberVerifCodes::No_it_isnt_Palend),
        make_tuple("981765432112322456789", ReturnPalendNumberVerifCodes::No_it_isnt_Palend),
        make_tuple("1202120021002221", ReturnPalendNumberVerifCodes::No_it_isnt_Palend)
    )
);

TEST_P(PalendNumberControlTest, PalenNumberVerif) {
    string expected_string = get<0>(GetParam());

    EXPECT_EQ(TestPalendNumberVerif(expected_string), get<1>(GetParam()));
}