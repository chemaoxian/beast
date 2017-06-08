//
// Copyright (c) 2013-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Test that header file is self-contained.
#include <beast/core/static_buffer.hpp>

#include "buffer_test.hpp"
#include <beast/unit_test/suite.hpp>
#include <boost/asio/buffer.hpp>
#include <string>

namespace beast {

class static_buffer_test : public beast::unit_test::suite
{
public:
    template<class ConstBufferSequence>
    static
    std::string
    to_string(ConstBufferSequence const& bs)
    {
        using boost::asio::buffer_cast;
        using boost::asio::buffer_size;
        std::string s;
        s.reserve(buffer_size(bs));
        for(auto const& b : bs)
            s.append(buffer_cast<char const*>(b),
                buffer_size(b));
        return s;
    }

    void
    testStaticBuffer()
    {
        using boost::asio::buffer;
        using boost::asio::buffer_cast;
        using boost::asio::buffer_size;
        char buf[12];
        std::string const s = "Hello, world";
        BEAST_EXPECT(s.size() == sizeof(buf));
        for(std::size_t i = 1; i < 4; ++i) {
        for(std::size_t j = 1; j < 4; ++j) {
        for(std::size_t x = 1; x < 4; ++x) {
        for(std::size_t y = 1; y < 4; ++y) {
        for(std::size_t t = 1; t < 4; ++ t) {
        for(std::size_t u = 1; u < 4; ++ u) {
        std::size_t z = sizeof(buf) - (x + y);
        std::size_t v = sizeof(buf) - (t + u);
        {
            std::memset(buf, 0, sizeof(buf));
            static_buffer_n<sizeof(buf)> ba;
            {
                auto d = ba.prepare(z);
                BEAST_EXPECT(buffer_size(d) == z);
            }
            {
                auto d = ba.prepare(0);
                BEAST_EXPECT(buffer_size(d) == 0);
            }
            {
                auto d = ba.prepare(y);
                BEAST_EXPECT(buffer_size(d) == y);
            }
            {
                auto d = ba.prepare(x);
                BEAST_EXPECT(buffer_size(d) == x);
                ba.commit(buffer_copy(d, buffer(s.data(), x)));
            }
            BEAST_EXPECT(ba.size() == x);
            BEAST_EXPECT(buffer_size(ba.data()) == ba.size());
            {
                auto d = ba.prepare(x);
                BEAST_EXPECT(buffer_size(d) == x);
            }
            {
                auto d = ba.prepare(0);
                BEAST_EXPECT(buffer_size(d) == 0);
            }
            {
                auto d = ba.prepare(z);
                BEAST_EXPECT(buffer_size(d) == z);
            }
            {
                auto d = ba.prepare(y);
                BEAST_EXPECT(buffer_size(d) == y);
                ba.commit(buffer_copy(d, buffer(s.data()+x, y)));
            }
            ba.commit(1);
            BEAST_EXPECT(ba.size() == x + y);
            BEAST_EXPECT(buffer_size(ba.data()) == ba.size());
            {
                auto d = ba.prepare(x);
                BEAST_EXPECT(buffer_size(d) == x);
            }
            {
                auto d = ba.prepare(y);
                BEAST_EXPECT(buffer_size(d) == y);
            }
            {
                auto d = ba.prepare(0);
                BEAST_EXPECT(buffer_size(d) == 0);
            }
            {
                auto d = ba.prepare(z);
                BEAST_EXPECT(buffer_size(d) == z);
                ba.commit(buffer_copy(d, buffer(s.data()+x+y, z)));
            }
            ba.commit(2);
            BEAST_EXPECT(ba.size() == x + y + z);
            BEAST_EXPECT(buffer_size(ba.data()) == ba.size());
            BEAST_EXPECT(to_string(ba.data()) == s);
            ba.consume(t);
            {
                auto d = ba.prepare(0);
                BEAST_EXPECT(buffer_size(d) == 0);
            }
            BEAST_EXPECT(to_string(ba.data()) == s.substr(t, std::string::npos));
            ba.consume(u);
            BEAST_EXPECT(to_string(ba.data()) == s.substr(t + u, std::string::npos));
            ba.consume(v);
            BEAST_EXPECT(to_string(ba.data()) == "");
            ba.consume(1);
            {
                auto d = ba.prepare(0);
                BEAST_EXPECT(buffer_size(d) == 0);
            }
            try
            {
                ba.prepare(ba.capacity() - ba.size() + 1);
                fail();
            }
            catch(...)
            {
                pass();
            }
        }
        }}}}}}
    }

    void
    testReadSizeHelper()
    {
    }

    void run() override
    {
        test::check_read_size_helper<static_buffer_n<32>>();

        testStaticBuffer();
    }
};

BEAST_DEFINE_TESTSUITE(static_buffer,core,beast);

} // beastp
