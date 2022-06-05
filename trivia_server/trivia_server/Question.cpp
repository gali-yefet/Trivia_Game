#include "Question.h"

Question::Question(std::string question, std::string ans1, std::string ans2, std::string ans3, std::string ans4, int rightAns)
	:question(question), ans1(ans1), ans2(ans2), ans3(ans3), ans4(ans4), rightAns(rightAns)
{}

std::string Question::getQuestion()
{
	return this->question;
}

std::string Question::getAns1()
{
	return this->ans1;
}

std::string Question::getAns2()
{
	return this->ans2;
}

std::string Question::getAns3()
{
	return ans3;
}

std::string Question::getAns4()
{
	return this->ans4;
}

int Question::getRightAns()
{
	return this->rightAns;
}

void Question::setQuestion(std::string question)
{
	this->question = question;
}

void Question::setAns1(std::string ans1)
{
	this->ans1 = ans1;
}

void Question::setAns2(std::string ans2)
{
	this->ans2 = ans2;
}

void Question::setAns3(std::string ans3)
{
	this->ans3 = ans3;
}

void Question::setAns4(std::string ans4)
{
	this->ans4 = ans4;
}

void Question::setRightAns(int rightAns)
{
	this->rightAns = rightAns;
}

std::map<unsigned int, std::string> Question::getAnswers()
{
	std::map<unsigned int, std::string> answers;

	answers.emplace(1, ans1);
	answers.emplace(2, ans2);
	answers.emplace(3, ans3);
	answers.emplace(4, ans4);

	return answers;
}
