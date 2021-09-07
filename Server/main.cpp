#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

// ���� ��ǻ���� ��¥ �� �ð� ���� ��ȯ
string makeDayTimeString() {
	time_t now = time(0);
	return ctime(&now);
}

int main(void) {
	try {
		// �⺻������ Boost Asio ���α׷��� �ϳ��� IO Service ��ü�� ������.
		boost::asio::io_service io_service;

		// TCP ���������� 13�� ��Ʈ�� ������ �޴� ���� ������ ����
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));

		// ��� Ŭ�� ���� ������ �ݺ� ����
		while (1) {
			// ���� ��ü�� ������ ������ ��ٸ�
			tcp::socket socket(io_service);
			acceptor.accept(socket);

			// ������ �Ϸ�Ǹ� �ش� Ŭ�󿡰� ���� �޼��� ����
			string message = makeDayTimeString();

			// �ش� Ŭ�󿡰� �޼����� ��� ����
			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}

	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}
}