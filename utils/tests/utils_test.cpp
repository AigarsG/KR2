#include <string.h>
#include <unistd.h>
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "utils.h"
}

TEST_GROUP(helper_functions)
{
	const char *haystack[5];
	size_t haystacksz;

	void setup()
	{
		haystack[0] = "apples";
		haystack[1] = "Oranges";
		haystack[2] = "Apples";
		haystack[3] = "bananas";
		haystack[4] = "blueberries";
		haystacksz = sizeof haystack / sizeof *haystack;
	}

	void teardown()
	{
	}
};

TEST(helper_functions, in_str_array_positive)
{
	CHECK(0 < in_str_array("bananas", haystack, haystacksz));
	CHECK(0 < in_str_array("blueberries", haystack, haystacksz));
}

TEST(helper_functions, in_str_array_negative)
{
	CHECK_EQUAL(-1, in_str_array(NULL, haystack, haystacksz));
	CHECK_EQUAL(-1, in_str_array("", haystack, haystacksz));
	CHECK_EQUAL(-1, in_str_array("oranges", haystack, haystacksz));
}


TEST_GROUP(CircularBuffer)
{
	CircularBuffer *cbuf;

	void setup()
	{
		cbuf = circular_buffer_create(5);
	}

	void teardown()
	{
		circular_buffer_destroy(cbuf);
	}
};


TEST(CircularBuffer, 01_test_circular_buffer_create)
{
	CHECK(cbuf != NULL);
}

TEST(CircularBuffer, 02_test_circular_buffer_push_pop)
{
	STRCMP_EQUAL(NULL, circular_buffer_pop(cbuf));

	circular_buffer_push(cbuf, "first value");
	circular_buffer_push(cbuf, "second value");
	circular_buffer_push(cbuf, "third value");
	circular_buffer_push(cbuf, "fourth value");
	circular_buffer_push(cbuf, "fifth value");

	STRCMP_EQUAL("first value", circular_buffer_pop(cbuf));
	STRCMP_EQUAL("second value", circular_buffer_pop(cbuf));
	STRCMP_EQUAL("third value", circular_buffer_pop(cbuf));
	STRCMP_EQUAL("fourth value", circular_buffer_pop(cbuf));
	STRCMP_EQUAL("fifth value", circular_buffer_pop(cbuf));
	STRCMP_EQUAL(NULL, circular_buffer_pop(cbuf));
}

TEST(CircularBuffer, 03_test_circular_buffer_push_pop_overwrite)
{
	circular_buffer_push(cbuf, "first value");
	circular_buffer_push(cbuf, "second value");
	circular_buffer_push(cbuf, "third value");
	circular_buffer_push(cbuf, "fourth value");
	circular_buffer_push(cbuf, "fifth value");
	circular_buffer_push(cbuf, "sixth value");
	circular_buffer_push(cbuf, "seventh value");
	circular_buffer_push(cbuf, "eight value");
	circular_buffer_push(cbuf, "nineth value");
	circular_buffer_push(cbuf, "tenth value");
	circular_buffer_push(cbuf, "eleventh value");

	STRCMP_EQUAL("seventh value", circular_buffer_pop(cbuf));
	STRCMP_EQUAL("eight value", circular_buffer_pop(cbuf));
	STRCMP_EQUAL("nineth value", circular_buffer_pop(cbuf));
	STRCMP_EQUAL("tenth value", circular_buffer_pop(cbuf));
	STRCMP_EQUAL("eleventh value", circular_buffer_pop(cbuf));
	STRCMP_EQUAL(NULL, circular_buffer_pop(cbuf));
}

TEST(CircularBuffer, 04_test_circular_buffer_clear)
{
	circular_buffer_push(cbuf, "first value");
	circular_buffer_push(cbuf, "second value");
	circular_buffer_push(cbuf, "third value");

	circular_buffer_clear(cbuf);

	STRCMP_EQUAL(NULL, circular_buffer_pop(cbuf));
}

TEST(CircularBuffer, 05_test_circular_buffer_push_immutable)
{
	char s[] = "first value";
	circular_buffer_push(cbuf, s);
	s[0] = 'M';

	STRCMP_EQUAL("first value", circular_buffer_pop(cbuf));
}

TEST(CircularBuffer, 06_test_circular_buffer_count)
{
	LONGS_EQUAL(0, circular_buffer_count(cbuf));

	circular_buffer_push(cbuf, "first value");
	circular_buffer_push(cbuf, "second value");
	circular_buffer_push(cbuf, "e");
	LONGS_EQUAL(3, circular_buffer_count(cbuf));

	circular_buffer_pop(cbuf);
	circular_buffer_pop(cbuf);
	circular_buffer_pop(cbuf);
	LONGS_EQUAL(0, circular_buffer_count(cbuf));

	circular_buffer_push(cbuf, "third value");
	circular_buffer_push(cbuf, "fourth value");
	circular_buffer_push(cbuf, "fifth value");
	circular_buffer_push(cbuf, "sixth value");
	LONGS_EQUAL(4, circular_buffer_count(cbuf));

	circular_buffer_push(cbuf, "seventh value");
	circular_buffer_push(cbuf, "eight value");
	LONGS_EQUAL(5, circular_buffer_count(cbuf));

	circular_buffer_clear(cbuf);
	LONGS_EQUAL(0, circular_buffer_count(cbuf));
}

TEST(CircularBuffer, 07_test_circular_buffer)
{
	circular_buffer_destroy(cbuf);
	cbuf = circular_buffer_create(3);
	circular_buffer_push(cbuf, "yada");
	circular_buffer_push(cbuf, "blaha blaha");
	circular_buffer_push(cbuf, "hey");
	circular_buffer_push(cbuf, "c");
	circular_buffer_push(cbuf, "kah");

	LONGS_EQUAL(3, circular_buffer_count(cbuf));
	STRCMP_EQUAL("hey", circular_buffer_pop(cbuf));
	STRCMP_EQUAL("c", circular_buffer_pop(cbuf));
	STRCMP_EQUAL("kah", circular_buffer_pop(cbuf));
	STRCMP_EQUAL(NULL, circular_buffer_pop(cbuf));
}

TEST(CircularBuffer, 08_test_circular_buffer_empty)
{
	circular_buffer_destroy(cbuf);
	cbuf = circular_buffer_create(0);
	CHECK(cbuf == NULL)
}

TEST(CircularBuffer, 09_test_circular_buffer_partially_full)
{
	circular_buffer_destroy(cbuf);
	cbuf = circular_buffer_create(10);
	circular_buffer_push(cbuf, "yada");
	circular_buffer_push(cbuf, "blaha blaha");

	LONGS_EQUAL(2, circular_buffer_count(cbuf));
	STRCMP_EQUAL("yada", circular_buffer_pop(cbuf));
	STRCMP_EQUAL("blaha blaha", circular_buffer_pop(cbuf));
	STRCMP_EQUAL(NULL, circular_buffer_pop(cbuf));
}


TEST_GROUP(mlfgets)
{
	const char *path, *s;
	FILE *fp;

	void setup()
	{
		s = "this\nis\nmultiline\ntext";
		path = "fixture_multiline.txt";
		fp = fopen(path, "w");
		fwrite(s, sizeof *s, strlen(s) + 1, fp);
		fclose(fp);

		fp = fopen(path, "r");
	}

	void teardown() {
		fclose(fp);
		remove(path);
	}
};

TEST(mlfgets, 01_test_mlfgets)
{
	char buf[23];

	mlfgets(buf, sizeof buf / sizeof *buf, fp);

	STRCMP_EQUAL("this\nis\nmultiline\ntext", buf);

}

TEST(mlfgets, 02_test_mlfgets)
{
	char buf[10];

	mlfgets(buf, sizeof buf / sizeof *buf, fp);

	STRCMP_EQUAL("", buf);
}

TEST_GROUP(bit_operations)
{
	unsigned long addr[4];

	void setup()
	{
		memset(addr, 0, sizeof addr);
	}
};

TEST(bit_operations, 01_set_bit)
{
	set_bit(0, addr);
	set_bit(63, addr);
	set_bit(63, addr);
	set_bit(78, addr);
	LONGS_EQUAL(0x8000000000000001, addr[0]);
	LONGS_EQUAL(0x4000, addr[1]);
	LONGS_EQUAL(0, addr[2]);
	LONGS_EQUAL(0, addr[3]);
}

TEST(bit_operations, 01_get_bit)
{
	set_bit(0, addr);
	set_bit(63, addr);
	set_bit(78, addr);
	LONGS_EQUAL(1, get_bit(0, addr));
	LONGS_EQUAL(0, get_bit(1, addr));
	LONGS_EQUAL(0, get_bit(62, addr));
	LONGS_EQUAL(1, get_bit(63, addr));
	LONGS_EQUAL(0, get_bit(64, addr));
	LONGS_EQUAL(0, get_bit(77, addr));
	LONGS_EQUAL(1, get_bit(78, addr));
	LONGS_EQUAL(0, get_bit(79, addr));
}

TEST(bit_operations, 01_ULONG_BITMAP_SIZE)
{
	LONGS_EQUAL(0, ULONG_BITMAP_SIZE(0));
	LONGS_EQUAL(1, ULONG_BITMAP_SIZE(1));
	LONGS_EQUAL(1, ULONG_BITMAP_SIZE(63));
	LONGS_EQUAL(2, ULONG_BITMAP_SIZE(64));
	LONGS_EQUAL(2, ULONG_BITMAP_SIZE(127));
	LONGS_EQUAL(3, ULONG_BITMAP_SIZE(128));
}

TEST_GROUP(Treenode)
{
	Treenode *root;
	const char *tmpfile;

	void setup()
	{
		root = Treenode_init();
		tmpfile = NULL;
	}

	void teardown()
	{
		Treenode_destroy(root);
		remove(tmpfile);
	}
};

TEST(Treenode, Treenode_init)
{
	CHECK(NULL != root);
}

TEST(Treenode, Treenode_destroy)
{
	Treenode_destroy(root);
	root = NULL;
}

TEST(Treenode, Treenode_count)
{
	CHECK_EQUAL(0, Treenode_count(root, NULL));
}

TEST(Treenode, Treenode_add)
{
	int count_before, count_after;
	count_before = Treenode_count(root, NULL);
	CHECK(NULL != Treenode_add(root, "Bananas"));
	CHECK(NULL != Treenode_add(root, "Oranges"));
	CHECK(NULL != Treenode_add(root, "Apples"));
	CHECK(NULL != Treenode_add(root, "Apples"));
	CHECK(NULL != Treenode_add(root, "apples"));
	STRCMP_EQUAL("Bananas", Treenode_get_value(root));
	count_after = Treenode_count(root, NULL);
	CHECK_EQUAL(0, count_before);
	CHECK_EQUAL(5, count_after);
	CHECK_EQUAL(2, Treenode_count(root, "Apples"));
	CHECK_EQUAL(1, Treenode_count(root, "apples"));
	CHECK_EQUAL(1, Treenode_count(root, "Oranges"));
	CHECK_EQUAL(1, Treenode_count(root, "Bananas"));
	CHECK_EQUAL(0, Treenode_count(root, "whatever"));
}

TEST(Treenode, Treenode_find)
{
	Treenode *ret, *expected;
	Treenode_add(root, "Bananas");
	Treenode_add(root, "Apples");
	Treenode_add(root, "Oranges");
	ret = Treenode_find(root, "Oranges");
	STRCMP_EQUAL("Oranges", Treenode_get_value(ret));
}

TEST(Treenode, Treenode_print)
{
	FILE *fp;
	char buffer[44];
	memset(buffer, 0, sizeof buffer);
	tmpfile = "/tmp/treenode_print_testsfile";
	fp = fopen(tmpfile, "w+");
	CHECK(NULL != fp);
	Treenode_add(root, "Bananas");
	Treenode_add(root, "Oranges");
	Treenode_add(root, "Apples");
	Treenode_add(root, "Apples");
	Treenode_add(root, "apples");
	Treenode_print(root, fp);
	fseek(fp, 0, SEEK_SET);
	CHECK(0 < fread(buffer, sizeof *buffer, sizeof buffer, fp));
	STRCMP_EQUAL("Apples: 2\nBananas: 1\nOranges: 1\napples: 1\n", buffer);
	fclose(fp);
}

int main(int argc, char** argv)
{
	MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
