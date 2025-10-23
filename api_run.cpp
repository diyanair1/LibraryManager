

int main() {
    try {
        // Boost.Asio setup
        boost::asio::io_context ioc{1};
        boost::asio::ip::tcp::acceptor acceptor{ioc, {boost::asio::ip::tcp::v4(), 8080}};

        for (;;) {
            boost::asio::ip::tcp::socket socket{ioc};
            acceptor.accept(socket);

            std::thread{[sock = std::move(socket)]() mutable {
                beast::flat_buffer buffer;
                http::request<http::string_body> req;
                http::read(sock, buffer, req);

                auto response = handle_requests(std::move(req));
                http::write(sock, std::move(response));
            }}.detach();
        }
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
