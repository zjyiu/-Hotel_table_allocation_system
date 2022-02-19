#include"Customer.h"

using namespace std;

int main() {
	vector<vector<Table>> Tables;
	vector<Customer> Customers;
	create(Tables);
	create(Customers);
	handle(Customers, Tables);
	out(Customers);
	return 0;
}