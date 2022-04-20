#include <criterion/criterion.h>
#include "../src/philo.h"

Test(check_inputs, expected_msg_dont_contain_args)
{
	char *argv[] = {
		"aristoteles",
		"socrates",
		NULL
	};
	cr_assert_eq(check_inputs(argv), 1);
}

Test(check_inputs, expected_msg_dont_contain_args_1)
{
	char *argv[] = {
		"123",
		"2a3",
		NULL
	};
	cr_assert_eq(check_inputs(argv), 1);
}

Test(check_inputs, expected_msg_dont_contain_args_2)
{
	char *argv[] = {
		"123",
		"213",
		NULL
	};
	cr_assert_eq(check_inputs(argv), 0);
}

Test(check_inputs, expected_msg_dont_contain_args_3)
{
	char *argv[] = {
		"123",
		"2-13",
		NULL
	};
	cr_assert_eq(check_inputs(argv), 1);
}

Test(check_inputs, expected_msg_dont_contain_args_4)
{
	char *argv[] = {
		"123",
		"213",
		"21<3",
		NULL
	};
	cr_assert_eq(check_inputs(argv), 1);
}

Test(check_inputs, expected_msg_dont_contain_args_5)
{
	char *argv[] = {
		"+123",
		"+213",
		"+213",
		NULL
	};
	cr_assert_eq(check_inputs(argv), 0);
}

Test(check_inputs, expected_msg_dont_contain_args_6)
{
	char *argv[] = {
		"+123",
		"-213",
		"+213",
		NULL
	};
	cr_assert_eq(check_inputs(argv), 1);
}

Test(check_inputs, expected_msg_dont_contain_args_7)
{
	char *argv[] = {
		"+123",
		"21+3",
		"+213",
		NULL
	};
	cr_assert_eq(check_inputs(argv), 1);
}
