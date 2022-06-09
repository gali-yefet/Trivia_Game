#include "Question.h"

Question::Question(std::string question, std::string ans1, std::string ans2, std::string ans3, std::string ans4, int rightAns):
	_question(question), _ans1(ans1), _ans2(ans2), _ans3(ans3), _ans4(ans4), _rightAns(rightAns)
{}

std::string Question::getQuestion()
{
	return this->_question;
}

std::string Question::getAns1()
{
	return this->_ans1;
}

std::string Question::getAns2()
{
	return this->_ans2;
}

std::string Question::getAns3()
{
	return _ans3;
}

std::string Question::getAns4()
{
	return this->_ans4;
}

int Question::getRightAns()
{
	return this->_rightAns;
}

void Question::setQuestion(std::string question)
{
	this->_question = question;
}

void Question::setAns1(std::string ans1)
{
	this->_ans1 = ans1;
}

void Question::setAns2(std::string ans2)
{
	this->_ans2 = ans2;
}

void Question::setAns3(std::string ans3)
{
	this->_ans3 = ans3;
}

void Question::setAns4(std::string ans4)
{
	this->_ans4 = ans4;
}

void Question::setRightAns(int rightAns)
{
	this->_rightAns = rightAns;
}

std::map<unsigned int, std::string> Question::getAnswers()
{
	std::map<unsigned int, std::string> answers;

	answers.emplace(1, _ans1);
	answers.emplace(2, _ans2);
	answers.emplace(3, _ans3);
	answers.emplace(4, _ans4);

	return answers;
}
