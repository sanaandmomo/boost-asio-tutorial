#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main(void) {
	try {
		// 기본적으로 Boost Asio 프로그램은 하나의 IO Service 객체를 가진다.
		boost::asio::io_service io_service;

		// 도메인 이름에서 TCP 종단점으로 요청하기 위한 Resolver 사용 (도메인 -> ip:port)
		tcp::resolver resolver(io_service);

		// 서버로는 로컬 서버, 서비스는 Daytime 프로토콜을 적어준다. (내 컴퓨터의 13번 포트)
		tcp::resolver::query query("localhost", "daytime");

		// DNS를 거쳐 IP 주소 및 포트 번호 얻기
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		// 소켓 객체를 초기화하여 서버에 연결
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		while (1) {
			// 버퍼 및 오류 처리 변수 선언
			boost::array<char, 128> buf;
			boost::system::error_code error;

			// 버퍼를 이용해 서버로부터 데이터 받기
			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof) break;

			if (error) throw boost::system::system_error(error);

			// 버퍼에 담긴 데이터를 화면에 출력
			cout.write(buf.data(), len);
		}
	}
	catch (exception &e) {
		cerr << e.what() << endl;
	}

	system("pause");
	return 0;
}