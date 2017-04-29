#include <string>
#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

struct node {
	map<char, node*> to;
	node* link;
	int len;

	node() : link(0), len(0) {

	}
};

void add(node* root, node*& last, char c) {
	node* cur = new node();
	cur->len = last->len + 1;
	node* p = last;
	last = cur;

	while (p && !p->to.count(c)) {
		p->to[c] = cur;
		p = p->link;
	}

	if  (!p) {
		cur->link = root;
		return;
	}

	node* q = p->to[c];
	if  (q->len == p->len + 1) {
		cur->link = q;
		return;
	}

	node* clone = new node(*q);
	clone->len = p->len + 1;
	q->link = cur->link = clone;
	while (p && p->to.count(c) && p->to[c] == q) {
		p->to[c] = clone;
		p = p->link;
	}
}

node* build(const string& s) {
	node* root = new node();
	node* last = root;
	for (char c : s) {
		add(root, last, c);
	}
	return root;
}

void print(node* v, string s = "") {
	cout << v << " -> " << s << endl;
	for (auto it : v->to) {
		print(it.second, s + it.first);
	}
}

int main() {
	string s;
	cin >> s;
	auto root = build(s);
	print(root);
	return 0;
}
