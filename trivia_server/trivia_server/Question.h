#pragma once
#include <string>

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




private:
	std::string question;
	std::string ans1;
	std::string ans2;
	std::string ans3;
	std::string ans4;
	int rightAns;
};
