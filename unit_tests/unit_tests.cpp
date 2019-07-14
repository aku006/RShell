#include <iostream>
#include "../header/and.hpp"
#include "../header/base.hpp"
#include "../header/connector.hpp"
#include "../header/or.hpp"
#include "../header/semicolon.hpp"
#include "../header/parser.hpp"

#include "../header/command.hpp"
#include "fakeTrueCommand.hpp"
#include "fakeFalseCommand.hpp"
#include "mockCommand.hpp"
#include "gtest/gtest.h"

#include "../header/input_redirection.hpp"
#include "../header/single_out_redirection.hpp"
#include "../header/double_out_redirection.hpp"
#include "../header/pipe.hpp"

/*Test AND connectors using preset booleans that return true or false*/
TEST(AndTest, BothTrue) {
	int in = 0;
	int out = 1;
        FakeTrueCommand* cmd1 = new FakeTrueCommand();
        FakeTrueCommand* cmd2 = new FakeTrueCommand();
        And* test_this = new And(cmd1, cmd2);
        EXPECT_EQ(true, test_this->execute(in, out));
}

TEST(AndTest, BothFalse) {
	int in = 0;
	int out = 1;
        FakeFalseCommand* cmd1 = new FakeFalseCommand();
        FakeFalseCommand* cmd2 = new FakeFalseCommand();
        And* test_this = new And(cmd1, cmd2);
        EXPECT_EQ(false, test_this->execute(in, out));
}

TEST(AndTest, FirstTrueSecondFalse) {
	int in = 0;
	int out = 1;
        FakeTrueCommand* cmd1 = new FakeTrueCommand();
        FakeFalseCommand* cmd2 = new FakeFalseCommand();
        And* test_this = new And(cmd1, cmd2);
        EXPECT_EQ(false, test_this->execute(in, out));
}

TEST(AndTest, FirstFalseSecondTrue) {
	int in = 0;
	int out = 1;
        FakeFalseCommand* cmd1 = new FakeFalseCommand();
        FakeTrueCommand* cmd2 = new FakeTrueCommand();
        And* test_this = new And(cmd1, cmd2);
        EXPECT_EQ(false, test_this->execute(in, out));
}

/*Test OR connectors using preset booleans*/
TEST(OrTest, BothTrue) {
	int in = 0;
	int out = 1;
	FakeTrueCommand* cmd1 = new FakeTrueCommand();
	FakeTrueCommand* cmd2 = new FakeTrueCommand();
	Or* test_this = new Or(cmd1, cmd2);
	EXPECT_EQ(true, test_this->execute(in, out));
}

TEST(OrTest, FirstTrueSecondFalse) {
	int in = 0;
	int out = 1;
	FakeTrueCommand* cmd1 = new FakeTrueCommand();
	FakeFalseCommand* cmd2 = new FakeFalseCommand();
	Or* test_this = new Or(cmd1, cmd2);
	EXPECT_EQ(true, test_this->execute(in, out));
}

TEST(OrTest, FirstFalseSecondTrue) {
	int in = 0;
	int out = 1;
	FakeFalseCommand* cmd1 = new FakeFalseCommand();
	FakeTrueCommand* cmd2 = new FakeTrueCommand();
	Or* test_this = new Or(cmd1, cmd2);
	EXPECT_EQ(true, test_this->execute(in, out));
}

TEST(OrTest, BothFalse) {
	int in = 0;
	int out = 1;
	FakeFalseCommand* cmd1 = new FakeFalseCommand();
	FakeFalseCommand* cmd2 = new FakeFalseCommand();
	Or* test_this = new Or(cmd1, cmd2);
	EXPECT_EQ(false, test_this->execute(in, out));
}

/*Test Semicolon connectors using preset booleans*/
TEST(SemicolonTest, BothTrue) {
	int in = 0;
	int out = 1;
	FakeTrueCommand* cmd1 = new FakeTrueCommand();
	FakeTrueCommand* cmd2 = new FakeTrueCommand();
	Semicolon* test_this = new Semicolon(cmd1, cmd2);
	EXPECT_EQ(true, test_this->execute(in, out));
}

TEST(SemicolonTest, FirstTrueSecondFalse) {
	int in = 0;
	int out = 1;
	FakeTrueCommand* cmd1 = new FakeTrueCommand();
	FakeFalseCommand* cmd2 = new FakeFalseCommand();
	Semicolon* test_this = new Semicolon(cmd1, cmd2);
	EXPECT_EQ(false, test_this->execute(in, out));
}

TEST(SemicolonTest, FirstFalseSecondTrue) {
	int in = 0;
	int out = 1;
	FakeFalseCommand* cmd1 = new FakeFalseCommand();
	FakeTrueCommand* cmd2 = new FakeTrueCommand();
	Semicolon* test_this = new Semicolon(cmd1, cmd2);
	EXPECT_EQ(true, test_this->execute(in, out));
}

TEST(SemicolonTest, BothFalse) {
	int in = 0;
	int out = 1;
	FakeFalseCommand* cmd1 = new FakeFalseCommand();
	FakeFalseCommand* cmd2 = new FakeFalseCommand();
	Semicolon* test_this = new Semicolon(cmd1, cmd2);
	EXPECT_EQ(false, test_this->execute(in, out));
}


TEST(mockCommand, create_MockCmd) {
	mockCommand* nein = new mockCommand("nein nein nein");
	EXPECT_EQ("nein nein nein", nein->getArgs());
}

TEST(parserTest, testIfAllocates) {
	Parser *nein = new Parser("ls -a");	
}

TEST(parserTest, testIfAllocates2) {
	Parser *nein = new Parser("ls -a || echo hello");	
}
//test command files
/*Test to see if "echo hello" returns properly*/
TEST(CommandTest, EchoSingleWord) {
	int in = 0;
	int out = 1;
	Command* cmd = new Command("echo hello ");
	EXPECT_EQ(true, cmd->execute(in, out));
}
//Test to see if "ls -a" returns properly*/
TEST(CommandTest, ls) {
	int in = 0;
	int out = 1;
	Command* cmd = new Command("ls -a ");
	EXPECT_EQ(true, cmd->execute(in, out));
}

/*Test mkdir test*/
TEST(CommandTest, mkdir) {
	int in = 0;
	int out = 1;
	Command* cmd = new Command("mkdir dummy_folder ");
	EXPECT_EQ(true, cmd->execute(in, out));
}

/*Test an invalid command*/
TEST(CommandTest, InvalidCode) {
	int in = 0;
	int out = 1;
	Command* cmd = new Command("hello hello ");
	EXPECT_EQ(false, cmd->execute(in, out));
}

//Test a longer echo
TEST(CommandTest, EchoLongerString) {
	int in = 0;
	int out = 1;
	Command* cmd = new Command("echo You were expecting Hello World, but it was me, Dio! ");
	EXPECT_EQ(true, cmd->execute(in, out));
}

//Test -e without brackets
TEST(TestFunctionTest, DashETest) {
	int in = 0;
	int out = 1;
	Command* cmd = new Command("test -e CMakeLists.txt");
	EXPECT_EQ(true, cmd->execute(in, out));
}

//Test -f without brackets
TEST(TestFunctionTest, DashFTest) {
	int in = 0;
	int out = 1;
	Command* cmd = new Command("test -f CMakeLists.txt");
	EXPECT_EQ(true, cmd->execute(in, out));
}

//Test -d without brackets
TEST(TestFunctionTest, DashDTest) {
	int in = 0;
	int out = 1;
	Command* cmd = new Command("test -d unit_tests/");
	EXPECT_EQ(true, cmd->execute(in, out));
}

//Test for one command in parenthesis
TEST(ParenthesesTest, SingleCommand) {
	int in = 0;
	int out = 1;
	Command* cmd = new Command("(echo a)");
	EXPECT_EQ(true, cmd->execute(in, out));
}

//Read redirection test with existing file
TEST(IORedirectionTest, ReadTrue) {
	int in = 0;
	int out = 1;
	Command* cmd1 = new Command("cat");
	Command* cmd2 = new Command("input_red.txt");
	InputRedirection* testThis = new InputRedirection(cmd1, cmd2);
	EXPECT_EQ(true, testThis->execute(in, out));
}

//Read redirection test with nonexistent file
TEST(IORedirectionTest, ReadFalse) {
	int in = 0;
	int out = 1;
	Command* cmd1 = new Command("cat");
	Command* cmd2 = new Command("nonexist.txt");
	InputRedirection* testThis = new InputRedirection(cmd1, cmd2);
	EXPECT_EQ(false, testThis->execute(in, out));
}

//Write redirection test
TEST(IORedirectionTest, Write) {
	int in = 0;
	int out = 1;
	Command* cmd1 = new Command("echo hello");
	Command* cmd2 = new Command("out_red.txt");
	SingleOutRedirection* testThis = new SingleOutRedirection(cmd1, cmd2);
	EXPECT_EQ(true, testThis->execute(in, out));
}

//Append redirection test
TEST(IORedirectionTest, Append) {
	int in = 0;
	int out = 1;
	Command* cmd1 = new Command("echo If you see this, that means that append is working. Probably.");
	Command* cmd2 = new Command("append_test.txt");
	DoubleOutRedirection* testThis = new DoubleOutRedirection(cmd1, cmd2);
	EXPECT_EQ(true, testThis->execute(in, out));
}

TEST(IORedirectionTest, Pipe) {
	int in = 0;
	int out = 1;
	Command* cmd1 = new Command("ls -la");
	Command* cmd2 = new Command("grep -e -r");
	Pipe* test = new Pipe(cmd1, cmd2);
	EXPECT_EQ(true, test->execute(in, out));
}

int main(int argc, char **argv) {
        ::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

