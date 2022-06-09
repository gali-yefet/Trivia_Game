#pragma once
#include <string>
#include <iostream>
#include <map>
#include "define.h"

class Question
{
public:
	Question() = default;
	Question(std::string question, std::string ans1, std::string ans2, std::string ans3, std::string ans4, int rightAns);
	
	std::string getQuestion();
	std::string getAns1();
	std::string getAns2();
	std::string getAns3();
	std::string getAns4();
	int getRightAns();

	void setQuestion(std::string question);
	void setAns1(std::string ans1);
	void setAns2(std::string ans2);
	void setAns3(std::string ans3);
	void setAns4(std::string ans4);
	void setRightAns(int rightAns);
	std::map<unsigned int, std::string> getAnswers();

private:
	std::string _question;
	std::string _ans1;
	std::string _ans2;
	std::string _ans3;
	std::string _ans4;
	int _rightAns;
};
