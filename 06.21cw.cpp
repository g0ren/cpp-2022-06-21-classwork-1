#include <iostream>
#include <ctime>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Command {
protected:
	vector<int> *vect;
public:
	void data(vector<int> *vect) {
		this->vect = vect;
	}
	Command(vector<int> *vect) {
		this->vect = vect;
	}
	Command() :
			Command(nullptr) {
	}
	virtual void execute()=0;
	virtual ~Command() {
	}
};

class VectorSortCommand: public Command {
public:
	VectorSortCommand(vector<int> *vect) :
			Command(vect) {
	}
	VectorSortCommand() :
			Command() {
	}
	void execute() override {
		sort(vect->begin(), vect->end());
	}
};

class VectorShowCommand: public Command {
public:
	VectorShowCommand(vector<int> *vect) :
			Command(vect) {
	}
	VectorShowCommand() :
			Command() {
	}
	void execute() override {
		for (auto i : *(this->vect))
			cout << i << " ";
		cout << endl;
	}
};

class Receiver {
	vector<int> *data;
	queue<Command*> commands;
public:
	Receiver(vector<int> *data, Command *command) :
			data(data) {
		this->commands.push(command);
	}
	void addCommand(Command *command) {
		this->commands.push(command);
	}
	void run() {
		while (!commands.empty()) {
			this->commands.front()->data(this->data);
			this->commands.front()->execute();
			this->commands.pop();
		}
	}
};

int main() {
	srand(time(NULL));
	vector<int> v(10);
	generate(v.begin(), v.end(), []() {
		return rand() % 100;
	});
	Receiver r(&v, new VectorShowCommand);
	r.addCommand(new VectorSortCommand);
	r.addCommand(new VectorShowCommand);
	r.run();

	return 0;
}
