#include <iostream>
#include <exception>
#include <stack>
#include <queue>
using namespace std;

template <typename T> class Queue
{
public:
	void push(const T &x);
	T pop();
private:
	stack<T> s1;
	stack<T> s2;
};

template <typename T> void Queue<T>::push(const T &x)
{
	s1.push(x);
}

template <typename T> T Queue<T>::pop()
{
	if (s2.empty()) {
		while(!s1.empty()) {
			s2.push(s1.top());
			s1.pop();
		}
	}
	
	if (s2.empty())
		throw exception();
		
	T head = s2.top();
	s2.pop();
	return head;
}

template <typename T> class Stack
{
public:
	void push(const T &x);
	T pop();
private:
	queue<T> q1;
	queue<T> q2;
};

template <typename T> void Stack<T>::push(const T &x)
{
	q1.push(x); // elements all in q1
}

template <typename T> T Stack<T>::pop()
{
	if (q1.empty())
		throw exception();

	while (q1.size() > 1) {
		q2.push(q1.front());
		q1.pop();
	}

	T head = q1.front();
	q1.pop();
	q1.swap(q2); // keep q2 the empty one
	return head;
}

template <typename T> class StackWithMin
{
public:
	void push(const T &x);
	void pop();
	const T& min();
private:
	stack<T> data_;
	stack<T> min_;
};

template <typename T> void StackWithMin<T>::push(const T &x)
{
	data_.push(x);

	if (min_.empty() || x < min_.top())
		min_.push(x);
	else
		min_.push(min_.top());
}

template <typename T> void StackWithMin<T>::pop()
{
	data_.pop();
	min_.pop();
}

template <typename T> const T &StackWithMin<T>::min()
{
	return min_.top();
}

bool IsPopOrder(const int *push, const int* pop, int length)
{
	bool isPossible = false;

	if (push != NULL && pop != NULL && length > 0) {
		const int *nextPush = push;
		const int *nextPop = pop;

		stack<int> s;

		while (nextPop - pop < length) {
			while (s.empty() || s.top() != *nextPop) {
				if (nextPush - push == length)
					break;

				s.push(*nextPush);
				++nextPush;
			}

			if (s.top() != *nextPop)
				break;

			s.pop();
			++nextPop;
		}


		if (s.empty() && nextPop - pop == length)
			isPossible = true;
	}

	return isPossible;
}

int main()
{
	int push[] = {1, 2, 3, 4, 5};
	int pop[] = {4, 5, 3, 2, 1};
	cout << IsPopOrder(push, pop, 5) << endl;
}