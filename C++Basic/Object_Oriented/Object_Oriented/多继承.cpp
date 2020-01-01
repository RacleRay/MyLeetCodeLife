// C++允许一个类可以有多个父类（不建议使用，会增加程序设计复杂度）

#include <iostream>
using namespace std;

class Student {
public:
	int m_score;
	Student(int score = 0) :m_score(score) { }
	virtual void study() {
		cout << "Student::study() - score = " << m_score << endl;
	}
	void same(){}

	~Student() {
		cout << "~Student" << endl;
	}
};

class Worker {
public:
	int m_salary;
	Worker(int salary = 0) :m_salary(salary) { }
	virtual void work() {
		cout << "Worker::work() - salary = " << m_salary << endl;
	}
	void same() {}
	~Worker() {
		cout << "~Worker" << endl;
	}
};

// 多继承多个父类
// 如果子类继承的多个父类都有虚函数，那么子类对象就会产生对应的多张虚表
class Undergraduate : public Student, public Worker {
public:
	int m_grade;
	Undergraduate(
		int score = 0,
		int salary = 0,
		int grade = 0) :Student(score), Worker(salary), m_grade(grade) {

	}
	void play() {
		cout << "Undergraduate::play() - grade = " << m_grade << endl;
	}
	void same() {}
	~Undergraduate() {
		cout << "~Undergraduate" << endl;
	}
};

int main() {
	{
		Undergraduate ug;
		ug.m_score = 100;
		ug.m_salary = 2000;
		ug.m_grade = 4;
		ug.study();
		ug.work();
		ug.play();
		
		// 同名函数，外部调用
		ug.Student::same();
		ug.Worker::same();
		ug.Undergraduate::same();

		ug.same();  // Undergraduate::same()
	}

	cout << sizeof(Undergraduate) << endl;

	getchar();
	return 0;
}